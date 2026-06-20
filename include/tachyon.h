#pragma once

#include "core/thread.h"

void tachyon_init();
int tachyon_spool(int n, void (*func)(void* arg), void* arg);
int tachyon_thread(void (*func)(void* arg), void* arg);