*This project has been created as part of the 42 curriculum by <login>.*

# Codexion

## Description

Codexion is a concurrency simulation. N coders sit in a circle with N USB
dongles between them. Each coder loops on compile, debug, refactor, and needs
two dongles to compile. A coder who does not start compiling within
`time_to_burnout` ms of the start of their last compile (or of the
simulation) burns out and the simulation stops. It also stops when every
coder has compiled `number_of_compiles_required` times.

The goal is to share the dongles without deadlock or starvation, with a
cooldown on released dongles and a FIFO or EDF arbitration policy.

## Instructions

```
make
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
    time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Times are in milliseconds, `scheduler` is `fifo` or `edf`.

```
./codexion 5 800 200 200 200 7 50 edf
./codexion 1 800 200 200 200 3 0 fifo
```

Rules: `make`, `make clean`, `make fclean`, `make re`. Flags used:
`-Wall -Wextra -Werror -pthread`.

## Blocking cases handled

- **Deadlock prevention (Coffman).** The circular wait condition is broken:
  every coder takes the dongle with the lowest index first, then the other.
  Hold-and-wait and mutual exclusion are kept (they are inherent to the
  problem), so removing the cycle is enough.
- **Starvation prevention.** Each dongle has a priority queue (binary heap).
  FIFO orders requests by arrival number, EDF by deadline
  (`last_compile_start + time_to_burnout`). Equal keys are broken by coder id
  so the order is always deterministic.
- **Cooldown.** A released dongle stores `available_at = now + cooldown`. A
  coder can take it only when it is free, first in the queue, and
  `now >= available_at`. While waiting for the cooldown, the coder sleeps on
  `pthread_cond_timedwait` until `available_at`.
- **Precise burnout detection.** A separate monitor thread checks every
  ~0.5 ms, so the burnout message appears within a few ms of the real burnout.
  Coders sleep with `smart_sleep` (short slices that check the stop flag), so
  nobody is blind during a long compile/debug/refactor.
- **Log serialization.** All output goes through one `print_mutex`. The stop
  flag is set while holding it, so no line can appear after `burned out`.
- **Single coder.** With one coder there is one dongle. The coder takes it,
  can never compile, and burns out.

## Thread synchronization mechanisms

- `pthread_mutex_t` per dongle: protects `is_taken`, `available_at`, the
  sequence counter and the heap.
- `pthread_cond_t` per dongle: coders wait on it for their turn; `release`
  broadcasts it; the monitor broadcasts it at the end to wake everybody.
- `state_mutex`: protects `stop`, `last_compile_start` and `compile_count`.
  Coders write them, the monitor reads them.
- `print_mutex`: serializes the logs.
- `config` is read-only after parsing, so it needs no lock.

Lock order is always dongle -> state and print -> state. The state mutex is
never held while taking another one, so no lock cycle is possible.

Race example: the monitor sets `stop` under `state_mutex`; coders read it with
`is_stopped`, which locks the same mutex. Lost wake-up example: the monitor
takes each dongle mutex before `pthread_cond_broadcast`, so a coder cannot
check `stop`, then miss the broadcast before it starts waiting.

## Resources

- POSIX threads manual pages (`pthread_mutex_*`, `pthread_cond_*`).
- The classic Dining Philosophers problem (Dijkstra) and Coffman conditions.
- Earliest Deadline First scheduling.

**AI usage:** <to complete with your own words: which tasks AI helped with
and which parts you wrote and tested yourself>.
