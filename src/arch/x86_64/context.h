#include <stdint.h>

typedef
struct context_t{
    /*
        rax 
        rip -> instruction pointer where the task resumes.
        rbx -> calle-saved register; optinally used as base pointer
        rcx -> used to pass 4th arg to func, loop counter
        rdx -> used to pass 3rd arg to func, 2nd return register for 128bit returns (rdx:rax)
        rsp -> stack pointer
        rbp -> calle-saved register; optionally used as frame ptr
        rsi -> used to pass 2nd arg to func; source index
        rdi -> used to pass 1st arg to func; destination index
        r8 -> used to pass 5th arg to func
        r9 -> used to pass 6th arg to func
        r10 -> tmp reg; used to passing func;s static chain ptr
        r11 -> tmp register
        r12-r15 -> calle-saved register
        xmm0-xmm1 -> used to pass & return floating point arg
        xmm2-xmm7 -> used to pass floating point arg
        xmm8-xmm15 -> tmp register
        mmx0-mmx7 -> tmp register
        st0,st1 -> tmp register; used to return long double arg
        st2-st7 -> tmp register;
        fs -> reserved for system(as thread specific data reg)
        mxcsr -> sse2 control and status word
        x87 sw -> status word
        x87 cw -> control word
    */
    uint64_t rip; // where to resume
    uint64_t rsp; // stack top
    uint64_t rbp; // frame base
    uint64_t rflags; // condition codes

   /* calle saved ints*/
    uint64_t rbx;

    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
}context_t;

void ctx_switch(context_t* old_ctx, context_t* new_ctx);
