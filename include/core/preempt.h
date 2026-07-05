#pragma once
/**
 * we wanna signal the scheduler to switch the thread every few milliseconds(69ms)
 */
#include <signal.h>
#include <time.h>

#define __USE_POSIX199309

void scheduler_interrupt(int blah){

}

void preempt_init(){
    struct sigaction sigact;
    sigemptyset(&sigact.sa_mask);
    sigact.__sigaction_handler.sa_sigaction = scheduler_interrupt;
    // sigact.sig
}