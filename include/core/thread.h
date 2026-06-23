#pragma once
#include "../arch/x86_64/context.h"
#include <stddef.h>
#include <stdint.h>   /* missing — needed for uint64_t */

#define STACK_SIZE (4096 * 8)   /* 32kb */
typedef enum{
    READY,
    RUNNING,
    BLOCKED,
    DEAD
}State;

typedef
struct thread_t{
    context_t ctx;
    State state;
    void* stack;
    size_t stack_size;
    uint64_t tid;
    // we can give it some stack i assume
    void       (*fn)(void*);   /* stored for reference/debugging */
    void*        arg;
}thread_t;

void      t_init(context_t* ctx, void* stack, size_t stack_size, void (*fn)(void*), void* arg);
thread_t* t_create(void (*fn)(void*), void* arg);
void      t_destroy(thread_t* t);