# Tachyon — Development Roadmap

## Phase 1 — Foundation (current)
**Goal:** bare-metal context switch working and benchmarked.

- [x] context_t struct (x86-64 callee-saved regs)
- [x] ctx_switch in raw assembly
- [x] init_task to bootstrap a stack
- [x] Round-trip benchmark (SIGALRM, count switches/sec)
- [x] Restructure into src/ include/ layout
- [ ] Rename and document public API in tachyon.h

## Phase 2 — 1:1 User Thread Scheduler
**Goal:** real threads with a scheduler loop, not just two hardcoded contexts.

- [ ] Thread Control Block (TCB): id, stack, context, state
- [ ] States: READY / RUNNING / BLOCKED / DONE
- [ ] thread_create(func, arg, stack_size)
- [ ] thread_yield() — cooperative switch
- [ ] thread_exit() — mark DONE, pick next
- [ ] Run queue (circular linked list or array for now)
- [ ] Scheduler: pick_next(), schedule()

## Phase 3 — Preemption
**Goal:** threads can't hog CPU.

- [ ] SIGALRM-based timer tick
- [ ] Signal handler calls schedule()
- [ ] Scheduler lock (block SIGALRM in critical sections)
- [ ] Per-thread time slice

## Phase 4 — Sync Primitives
**Goal:** threads can wait on each other correctly.

- [ ] thread_join(tid) — block until target is DONE
- [ ] thread_sleep(ms) — sleep queue, sorted by wakeup time
- [ ] mutex_t — lock/unlock with wait queue (no spinning)
- [ ] condvar_t — wait/signal/broadcast

## Phase 5 — M:N Scheduling
**Goal:** map M user threads onto N kernel threads (pthreads).

- [ ] Per-kernel-thread run queue
- [ ] Work stealing between queues
- [ ] Synchronize queues (spinlocks or lock-free)
- [ ] Benchmark: compare 1:1 vs M:N throughput

## Notes
- Target: x86-64 Linux only (for now)
- No libc ucontext — raw asm only
- Each phase should have a working example in examples/