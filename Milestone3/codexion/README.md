*This project has been created as part of the 42 curriculum by herinaan.*

# Codexion

## Description

Codexion is a concurrent programming project written in C with POSIX threads (`pthread`). Several coders sit around a table and share a limited number of USB dongles. To compile their quantum code, a coder needs **two dongles at the same time** (the one on their left and the one on their right). Between two compiles they debug, then refactor, and they must start compiling again before they burn out.

The goal is to share the dongles safely and fairly: no data race, no deadlock, no starvation, a precise burnout detection and clean, non-interleaved logs.

Two arbitration policies are supported by the dongles:

- `fifo`: the request that arrived first is served first.
- `edf` (Earliest Deadline First): the coder with the earliest deadline (`last_compile_start + time_to_burnout`) is served first.

### How the simulation works

- One thread per coder, plus one monitor thread.
- There are as many dongles as coders (a single coder has a single dongle and can never compile, so he burns out).
- Each coder loops over: **compile** (holding two dongles) → **debug** → **refactor**.
- A released dongle is unavailable until `dongle_cooldown` ms have elapsed.
- A coder burns out if he does not **start** a compile within `time_to_burnout` ms after the start of his last compile (or after the start of the simulation for the first one).

### End of the simulation

The simulation stops in one of two ways:

1. **A coder burns out.** The monitor prints `X burned out` (within 10 ms of the real burnout) and stops everything.
2. **Every coder has compiled at least `number_of_compiles_required` times.** A compile is counted when it is finished. As soon as a coder finishes his last required compile, he releases his dongles and leaves: he does not debug or refactor anymore. When the last coder has done so, the monitor stops the simulation.

In the second case the last line of the log is therefore always the `is compiling` line of the last coder to finish, and every coder has exactly `number_of_compiles_required` `is compiling` lines.

Example (`./codexion 3 30000 20 20 20 2 800 fifo`):

```text
0 1 has taken a dongle
0 1 has taken a dongle
0 1 is compiling
20 1 is debugging
40 1 is refactoring
820 2 has taken a dongle
820 2 has taken a dongle
820 2 is compiling
...
4100 3 has taken a dongle
4100 3 has taken a dongle
4100 3 is compiling
```

## Instructions

### Requirements

- C compiler (`cc`)
- GNU Make
- POSIX threads

### Compilation

```bash
make
```

The project is compiled with `-Wall -Wextra -Werror -pthread` and produces the `codexion` binary.

### Execution

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

All time values are in milliseconds and all arguments are mandatory.

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coders (and of dongles), at least 1 |
| `time_to_burnout` | Max time between the starts of two compiles of a coder |
| `time_to_compile` | Duration of a compile (two dongles held), at least 1 |
| `time_to_debug` | Duration of the debugging phase |
| `time_to_refactor` | Duration of the refactoring phase |
| `number_of_compiles_required` | Compiles each coder must reach to end the simulation, at least 1 |
| `dongle_cooldown` | Time a released dongle stays unavailable |
| `scheduler` | `fifo` or `edf` |

Invalid inputs (negative numbers, letters, empty strings, values above `INT_MAX`, unknown scheduler, wrong number of arguments) are rejected with an error message and exit code 1.

### Examples

```bash
./codexion 4 1500 200 200 200 3 100 fifo
./codexion 5 2000 200 200 200 7 0 edf
./codexion 1 800 200 200 200 10 0 fifo   # a lone coder burns out
```

### Makefile rules

```bash
make        # build
make clean  # remove object files
make fclean # remove objects and binary
make re     # rebuild everything
```

## Blocking cases handled

- **Deadlock prevention and Coffman's conditions.** A coder never holds one dongle while waiting for the other. Both dongles are taken in a single critical section (under `queue_mutex`), and only when both are free and the coder is at the head of the waiting queue of both. This breaks the *hold and wait* condition, so a circular wait cannot appear. Dongles are also released together.
- **Starvation prevention.** Each dongle has a priority heap of waiting requests. With `fifo` the priority is an arrival ticket, so nobody can be overtaken forever. With `edf` the coder closest to his burnout deadline is served first, and ties are broken by the coder id so the order is fully deterministic. Starts are also staggered (`pacing.c`) so that coders do not all fight for the same dongles at time 0 when the parameters allow it.
- **Cooldown handling.** When a coder releases his dongles, each one gets `available_at = now + dongle_cooldown`. A waiting coder sleeps with `pthread_cond_timedwait` until the cooldown of both dongles has passed.
- **Precise burnout detection.** A separate monitor thread checks every millisecond whether a coder with unfinished work has gone `time_to_burnout` ms without starting a compile. The delay between the real burnout and its log is therefore about 1 ms, far under the 10 ms limit. A coder who has already reached his goal can no longer burn out.
- **Single coder.** With one coder there is one dongle: he takes it, can never take a second one and burns out.
- **Log serialization.** Every message is printed under `print_mutex`. The stop flag is checked inside the same critical section, so no line is printed after the final `burned out` line and two messages never interleave.
- **Clean termination.** When the simulation stops, `request_stop` sets the stop flag and broadcasts on the condition variable so that coders blocked while waiting for dongles wake up. Sleeps are cut short, all threads are joined and all memory and mutexes are released.

## Thread synchronization mechanisms

- **`pthread_mutex_t print_mutex`** serializes the output. It also guarantees that nothing is printed once the simulation is stopped.
- **`pthread_mutex_t state_mutex`** protects the shared state read by several threads: `stop_flag`, and for each coder `last_compile_start` and `compile_count`. Coders write these values under this mutex and the monitor reads them under the same mutex, so the monitor never sees a half-updated state.
- **`pthread_mutex_t queue_mutex` and `pthread_cond_t queue_cond`** protect the dongles (`in_use`, `available_at`) and their waiting heaps. A coder waits on `queue_cond` until his turn comes. Every release of dongles and every stop does a `pthread_cond_broadcast`, and the wait loop re-checks its condition each time it wakes up (`wait_turn`), so spurious wakeups are harmless.
- **Lock order.** Mutexes are always taken in the same order (`print_mutex` or `queue_mutex` first, then `state_mutex`, never the opposite), which prevents lock-ordering deadlocks.

How race conditions are prevented:

- Two coders can never get the same dongle: the check `ready_time` and the assignment `in_use = 1` happen in the same critical section of `queue_mutex`.
- A coder and the monitor never touch `compile_count` or `last_compile_start` at the same time: both go through `state_mutex`.
- The monitor communicates with the coders only through `stop_flag`. Once it is set, every coder sees it at his next check (`is_stopped`) or when he is woken up by the broadcast, and returns.

## Testing

Tests used during development:

```bash
./codexion 1 800 200 200 200 10 0 fifo     # must burn out around 800 ms
./codexion 5 2000 200 200 200 10 0 fifo    # must finish, nobody burns out
./codexion 5 2000 200 200 200 7 0 edf      # must finish, nobody burns out
./codexion 5 500 200 200 200 10 0 fifo     # infeasible, must burn out around 500 ms
./codexion 5 3000 200 200 200 10 400 fifo  # cooldown check
./codexion 5 3000 200 200 200 10 800 edf   # heavy contention
```

Data races and memory errors can be checked with:

```bash
cc -g -fsanitize=thread -pthread -Iinclude src/*.c -o codexion_tsan
cc -g -fsanitize=address,undefined -pthread -Iinclude src/*.c -o codexion_asan
valgrind --tool=helgrind ./codexion 4 1500 200 200 200 3 100 fifo
valgrind --leak-check=full ./codexion 4 1500 200 200 200 3 100 fifo
```

## Project Structure

```text
codexion/
├── Makefile
├── README.md
├── include/
│   └── codexion.h
└── src/
    ├── main.c            # Entry point
    ├── parsing.c         # parse_args: argument parsing and scheduler selection
    ├── valid_parsing.c   # Number validation and value checks, error printing
    ├── clock.c           # Time helpers (get_time_ms, sleep_ms)
    ├── setup.c           # Initialization (coders, dongles, mutexes)
    ├── cleanup.c         # Cleanup and resource release
    ├── logger.c          # Synchronized logging (log_event, log_burnout)
    ├── runner.c          # Thread creation, start and join
    ├── coder.c           # Coder thread routine
    ├── dongle.c          # Acquiring / releasing both dongles, cooldown wait
    ├── scheduler.c       # FIFO / EDF request queue logic
    ├── pacing.c          # Start-time staggering between coders
    ├── shutdown.c        # Stop flag and waking of waiting threads
    ├── monitor.c         # Burnout / completion monitor thread
    ├── heap.c            # Priority heap (init, push, remove, destroy)
    └── heap_utils.c      # Heap helpers (compare, swap, sift up/down)
```

### Main data structures

- `t_params`: parsed command-line parameters (`coder_count`, `compile_goal`, `edf_mode`, ...).
- `t_sim`: shared simulation state (coders, dongles, mutexes, `stop_flag`, monitor thread).
- `t_coder`: one coder thread, with its `left_dongle`, `right_dongle`, `compile_count` and `last_compile_start`.
- `t_dongle`: a dongle with `in_use`, `available_at` (cooldown) and a `waiters` priority heap.
- `t_heap` / `t_node`: priority heap ordered by `priority` (ticket for FIFO, deadline for EDF), ties broken by coder id.

## Resources

- POSIX threads: *https://man7.org/linux/man-pages/man7/pthreads.7.html*
- Mutexes: *https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html*
- Condition variables: *https://man7.org/linux/man-pages/man3/pthread_cond_wait.3p.html*
- Valgrind: *https://valgrind.org/docs/*
- Lifo algorithm : *https://www.youtube.com/watch?v=cjWnEtnKVGM*

### AI Usage

AI tools were used to clarify POSIX thread concepts, investigate synchronization bugs, review scheduling logic, rename files and variables, help write this README, and interpret sanitizer and Valgrind reports. All suggestions were reviewed, tested and understood before being kept in the project.
