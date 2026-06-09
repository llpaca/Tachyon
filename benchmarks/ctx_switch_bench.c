// ///@file:main.c
// /*
// lets say this is where we use context switch
// */
// #include <stdint.h>
// #include <stddef.h>
// #include <stdio.h>
// #include "context.h"

// context_t main_ctx;
// context_t task_ctx;

// void task_function() {
//     while (1) {
//         // printf("inside task\n");

//         ctx_switch(&task_ctx, &main_ctx);
//     }
// }
// uint8_t task_stack[4096];

// void init_task(context_t* ctx, void (*func)(), void* stack, size_t stack_size) {
//     uint64_t* stack_top =
//         (uint64_t*)((uint8_t*)stack + stack_size);

//     stack_top = (uint64_t*)((uintptr_t)stack_top & ~0xF);
//     stack_top--;
//     *stack_top = 0;
    
//     ctx->rip = (uint64_t)func;
//     ctx->rsp = (uint64_t)stack_top;
//     ctx->rbp = 0;
//     ctx->rflags = 0x202;
// }

// int main() {
//     init_task(&task_ctx, task_function,
//               task_stack, sizeof(task_stack));
//     int i = 0;
//      while (1) {
//         // printf("switching to task\n");

//         ctx_switch(&main_ctx, &task_ctx);

//         printf("%d\n", i);
//         i++;
//     }

//     return 0;
// }
// //gcc -g -fno-omit-frame-pointer main.c context_s.o -o main
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "context.h"

context_t main_ctx;
context_t task_ctx;

void task_function() {
    while (1) {
        ctx_switch(&task_ctx, &main_ctx);
    }
}

uint8_t task_stack[4096];

void init_task(context_t* ctx, void (*func)(), void* stack, size_t stack_size) {
    uint64_t* stack_top = (uint64_t*)((uint8_t*)stack + stack_size);
    stack_top = (uint64_t*)((uintptr_t)stack_top & ~0xF);
    stack_top--;
    *stack_top = 0;

    ctx->rip = (uint64_t)func;
    ctx->rsp = (uint64_t)stack_top;
    ctx->rbp = 0;
    ctx->rflags = 0x202;
}

// static volatile int stop = 0;
static int stop = 0;

void alarm_handler(int sig) {
    stop = 1;  // set flag on SIGALRM, main loop checks it
}

int main() {
    init_task(&task_ctx, task_function, task_stack, sizeof(task_stack));

    signal(SIGALRM, alarm_handler);
    alarm(1);  // fire SIGALRM after 1 second

    long long count = 0;

    while (!stop) {
        ctx_switch(&main_ctx, &task_ctx);
        count++;
    }

    // task_function is still alive in its infinite loop, no need to touch it

    printf("Round trips (main<->task) : %lld\n", count);
    printf("Total context switches    : %lld\n", count * 2);
    printf("Avg per switch            : %.2f ns\n", 1e9 / (double)(count * 2));

    return 0;
}
//taskset -c 0 ./main