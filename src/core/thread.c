#include <core/thread.h>
#include <arch/x86_64/context.h>

uint8_t t_stack[STACK_SIZE]; //<<< this has to be changed to a memory manager

int t_init(context_t* ctx, void (*func)(void*), void* arg){
    uint64_t* stack_top = (uint64_t*)((uint8_t*)t_stack + STACK_SIZE);
    stack_top = (uint64_t*)((uintptr_t)stack_top & ~0x0F);
    stack_top--;
    *stack_top = 0;

    ctx->rip = (uint64_t)func;
    ctx->rsp = (uint64_t)stack_top;
    ctx->rbp = 0;
    ctx->rflags = 0x202;

    ctx->rdi = (uint64_t)arg;
}

thread_t* t_create(void (*fn)(void*), void* arg){
    // create a new ctx here
    context_t *ctx;
    t_init(ctx, fn, arg);
    // we will create the thread here
    thread_t rt = {
        .ctx = ctx,
        .state = READY,
        .stack = 0, // please cchange this 
        .stack_size = STACK_SIZE,
        // well i am thinking we can use hashmap so yea 
        // will see what to do
        .tid = 0, // we need a thread id
    };
    //we need a queue to push this thread too
    // thread_q.push(&rt);
    //we will return the thread*
    return &rt;
}
size_t t_join(thread_t* t);