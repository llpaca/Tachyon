#include "core/sched.h"
#include <string.h>

sched_t g_sched;

void sched_init() {
    memset(&g_sched, 0, sizeof(sched_t));
    g_sched.current  = NULL;   /* main is running, not a thread */
    g_sched.next_tid = 1;      /* tid 0 reserved for main       */
}

void sched_push(thread_t* t) {
    if (g_sched.count >= MAX_THREADS) return;  /* TODO: error handling */
    g_sched.queue[g_sched.tail] = t;
    g_sched.tail  = (g_sched.tail + 1) % MAX_THREADS;
    g_sched.count++;
}

thread_t* sched_pop() {
    if (g_sched.count == 0) return NULL;
    thread_t* t   = g_sched.queue[g_sched.head];
    g_sched.head  = (g_sched.head + 1) % MAX_THREADS;
    g_sched.count--;
    return t;
}