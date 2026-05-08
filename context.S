/*context.S
byte = 1 byte
word = 2 byte
double word = 4 byte
quad word = 8 byte
mov a, b
copies a to b
*/

.globl ctx_switch
.type ctx_switch, @function
ctx_switch:
    /* rdi -> old context */
    /* rsi -> new context */
    /* the `call` instruction that invoked this function pushed
    the return address (rip) onto the stack. we read it from (%rsp)*/
    movq (%rsp), %rax
    movq %rax, 0(%rdi) /* rip */

    leaq 8(%rsp), %rax
    movq %rax, 8(%rdi) /* rsp: save pre-call rsp (rsp+8), not rsp which points AT the return addr */

    /*movq %rsp, 8(%rdi) rsp */
    movq %rbp, 16(%rdi)/* rbp */
    /* flags also i will like to save */
    /* 24(%rdi) */
    pushfq
    popq 24(%rdi)
    movq %rbx, 32(%rdi)
    movq %r12, 40(%rdi)
    movq %r13, 48(%rdi)
    movq %r14, 56(%rdi)
    movq %r15, 64(%rdi)

    /* load the context to the regis */
    movq 32(%rsi), %rbx
    movq 40(%rsi), %r12
    movq 48(%rsi), %r13
    movq 56(%rsi), %r14
    movq 64(%rsi), %r15

    movq 16(%rsi), %rbp

    /* restore flags */
    pushq 24(%rsi)
    popfq

    movq 8(%rsi), %rsp

    pushq 0(%rsi)
    ret