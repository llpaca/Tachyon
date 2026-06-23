#pragma once

#include "core/thread.h"
#include "core/sched.h"
#include "arch/x86_64/context.h"

#define tachyon_init() \
    do { \
        _tachyon_init(); \
        ctx_save(&g_sched.main_ctx); \
    } while(0)

void _tachyon_init();

thread_t* tachyon_thread(void (*func)(void*), void* arg);
void      tachyon_spool(int n, void (*func)(void*), void* arg);
void      tachyon_yield();
void      tachyon_join(thread_t* t);
void      tachyon_thread_exit();