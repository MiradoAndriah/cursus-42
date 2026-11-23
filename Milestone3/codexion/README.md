*This project has been created as part of the 42 curriculum by herinaan.*

# Codexion

## Description

Codexion is a concurrent programming project written in C using POSIX threads (`pthread`). It simulates multiple coders sharing a limited number of dongles to perform compilation, debugging, and refactoring tasks.

The goal is to manage shared resources safely, implement scheduling algorithms, and handle concurrency issues such as race conditions, deadlocks, starvation, and coder burnout.

Two scheduling algorithms are supported: FIFO (First In, First Out) and EDF (Earliest Deadline First).

## Features

- Concurrent execution using POSIX threads.
- FIFO and EDF scheduling.
- Shared dongle management and cooldown handling.
- Coder burnout detection.
- Synchronized logging.
- Input validation and resource cleanup.

## Technical Choices

- **Language:** C
- **Threading:** POSIX threads
- **Synchronization:** Mutexes and condition variables
- **Scheduling:** Custom priority heap
- **Build system:** Makefile
- **Memory testing:** Valgrind

## Instructions

### Requirements

- C compiler (`cc` or `gcc`)
- GNU Make
- POSIX threads
- Valgrind (optional, for memory checks)

### Compilation

```bash
make
```

### Execution

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown fifo|edf
```

All time values are expressed in milliseconds.

### Example

```bash
./codexion 4 1500 200 200 200 3 100 fifo
./codexion 4 1500 200 200 200 3 100 edf
```

### Arguments

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coders |
| `time_to_burnout` | Maximum time before burnout |
| `time_to_compile` | Compilation duration |
| `time_to_debug` | Debugging duration |
| `time_to_refactor` | Refactoring duration |
| `number_of_compiles_required` | Required compilations per coder |
| `dongle_cooldown` | Dongle cooldown duration |
| `fifo\|edf` | Scheduling algorithm |

### Makefile Commands

```bash
make       # Compile
make clean # Remove object files
make fclean # Remove objects and executable
make re    # Recompile everything
```

## Blocking cases handled

- **Deadlock prevention:** Dongle acquisition and release must follow the implemented scheduling and synchronization rules. The solution must avoid circular waiting where applicable.
- **Coffman's conditions:** Deadlock prevention depends on how resource allocation and waiting are managed; verify the implementation's guarantees.
- **Starvation prevention:** FIFO or EDF request ordering helps organize access, but does not automatically guarantee that every coder will progress.
- **Cooldown handling:** A dongle cannot be reused before its cooldown period has elapsed.
- **Burnout detection:** The monitor checks whether a coder exceeds the permitted time without completing the required activity.
- **Log serialization:** Shared log output is synchronized to prevent interleaved messages.
- **Termination and cleanup:** Waiting threads must be notified as needed, and acquired resources and threads must be cleaned up safely.

## Thread synchronization mechanisms

- **`pthread_mutex_t`:** `print_mutex` serializes log output, `state_mutex` protects the stop flag and coder counters, and `queue_mutex` protects dongle ownership and the waiting queues.
- **`pthread_cond_t`:** `queue_cond` lets coders wait for their dongles and be woken when a dongle is released or the simulation stops.
- **Scheduling:** Each dongle keeps a priority heap (`waiters`) of pending requests, ordered by arrival ticket (FIFO) or by burnout deadline (EDF).
- **Monitor communication:** Shared coder state must be protected by synchronization so the monitor can check burnout and completion without data races.
- **Race-condition prevention:** Shared variables are accessed under the appropriate synchronization primitive. Condition waits must recheck their predicates after waking, and shutdown must safely wake any threads that could otherwise remain blocked.

These mechanisms coordinate coder threads, dongle access, logging, and the monitor. The exact guarantees depend on the implementation.

## Testing

Test both scheduling algorithms with different coder counts, durations, and cooldown values.

Check memory management with Valgrind:

```bash
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
    ├── main.c                  # Entry point
    ├── args_parser.c           # Argument parsing and validation
    ├── clock.c                 # Time helpers (get_time_ms, sleep_ms)
    ├── setup.c                 # Initialization of the simulation (coders, dongles, mutexes)
    ├── teardown.c              # Cleanup and resource release
    ├── logger.c                # Synchronized logging
    ├── runner.c                # Thread creation, start and join
    ├── coder.c                 # Coder thread routine
    ├── dongle_access.c         # Acquiring / releasing dongles (+ cooldown)
    ├── scheduler.c             # FIFO / EDF request queue logic
    ├── pacing.c                # Start-time staggering between coders
    ├── shutdown.c              # Stop flag and waking of waiting threads
    ├── monitor.c               # Burnout / completion monitor thread
    ├── priority_heap.c         # Priority heap (init, push, remove, destroy)
    └── priority_heap_utils.c   # Heap helpers (compare, swap, sift up/down)
```

## Main data structures

- `t_params`: parsed command-line parameters (`coder_count`, `compile_goal`, `edf_mode`, ...).
- `t_sim`: global simulation state (coders, dongles, mutexes, `stop_flag`, monitor thread).
- `t_coder`: one coder thread, with its `left_dongle`, `right_dongle` and `compile_count`.
- `t_dongle`: a dongle with `in_use`, `available_at` (cooldown) and a `waiters` priority heap.
- `t_heap` / `t_node`: priority heap ordered by `priority` (ticket for FIFO, deadline for EDF).

## Resources

- POSIX threads: *https://man7.org/linux/man-pages/man7/pthreads.7.html*
- Mutexes: *https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html*
- Condition variables: *https://man7.org/linux/man-pages/man3/pthread_cond_wait.3p.html*
- Valgrind: *https://valgrind.org/docs/*
- Lifo algorithm : *https://www.youtube.com/watch?v=cjWnEtnKVGM*

### AI Usage

AI tools were used to clarify POSIX thread concepts, investigate synchronization bugs, review scheduling logic, and interpret Valgrind reports. The resulting suggestions were reviewed and tested against the project implementation.

## Learning Objectives

- Understand concurrent programming in C.
- Synchronize access to shared resources.
- Implement and compare scheduling algorithms.
- Detect race conditions and manage thread lifecycles.
- Improve debugging and memory management skills.
