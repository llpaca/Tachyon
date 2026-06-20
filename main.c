#include "include/tachyon.h"

void worker(void* arg){

}

int main(){

    tachyon_init();
    int n = 10;
    //lets say we want n-gthreads for a worker
    tachyon_spool(n, worker, (void*)"this is a test");

    //for single thread
    tachyon_thread(worker, (void*)"single thread");

    return 0;
}