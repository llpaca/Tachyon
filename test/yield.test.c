#include <stdio.h>
#include <tachyon.h>

void worker(void* arg) {
    printf("hi from the thread\n");
    tachyon_yield();
    /* tachyon_thread_exit() called automatically by thread_entry when worker returns */
}

int main() {
    tachyon_init();

    printf("we are in the main thread\n");

    thread_t* t1 = tachyon_thread(worker, (void*)0);

    /* yield so main gives up CPU and worker actually runs */
    tachyon_yield();

    printf("we are back in main\n");

    return 0;
}