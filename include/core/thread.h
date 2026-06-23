#include "../arch/x86_64/context.h"
#include "stddef.h"

#define STACK_SIZE 4096 //4kb

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
}thread_t;

int t_init();
thread_t* t_create(void (*fn)(void*), void* arg);
size_t t_join(thread_t* t);