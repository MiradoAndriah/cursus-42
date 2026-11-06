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
./codexion nb_coders time_to_burnout time_to_compile time_to_debug time_to_refactor required_compilations dongle_cooldown fifo|edf
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
| `nb_coders` | Number of coders |
| `time_to_burnout` | Maximum time before burnout |
| `time_to_compile` | Compilation duration |
| `time_to_debug` | Debugging duration |
| `time_to_refactor` | Refactoring duration |
| `required_compilations` | Required compilations per coder |
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

- **`pthread_mutex_t`:** Protects shared state, such as dongle ownership, scheduler data, and log output, where used by the implementation.
- **`pthread_cond_t`:** Allows threads to wait for resource availability and be notified when shared state changes.
- **Custom scheduling events:** The scheduler and its priority heap organize pending requests according to FIFO or EDF, if implemented in this way.
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
Codexion/
├── Makefile
├── README.md
└── coders/
    ├── cleanup.c
    ├── coder.c
    ├── dongle.c
    ├── heap.c
    ├── log.c
    ├── main.c
    ├── monitor.c
    ├── parsing.c
    ├── scheduler.c
    ├── utils.c
    └── codexion.h
```

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
