#include <iostream>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <sys/shm.h>
 #include "shared.h"
 
 using namespace std;
 
 int main() {
    cout << "[Process 2] Started and connecting to shared memory..." << endl;
    
    // Use same key as process 1
    key_t key = ftok("shared.h", 65);
    if (key == -1) {
        perror("ftok");
        return 1;
    }
    
    // Access shared memory created by Process 1
    int shmid = shmget(key, sizeof(SharedData), 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }
    
    // Attach to shared memory
    SharedData* data = (SharedData*) shmat(shmid, nullptr, 0);
    if (data == (void*) -1) {
        perror("shmat");
        return 1;
    }
    
    cout << "[Process 2] Waiting for counter > 100..." << endl;
    while (data->counter <= 100) {
        usleep(100000);
    }
    
    cout << "[Process 2] Counter > 100 reached. Multiple = " << data->multiple << endl;
    
    for (int i = 1; i <= 10; ++i) {
    cout << "[Process 2] " << data->multiple << " x " << i << " = " << (data->multiple * i) << endl;
    sleep(1);
    }
    
    shmdt((void*)data);
    cout << "[Process 2] Done, exiting..." << endl;
    return 0;
 }