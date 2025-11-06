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
    key_t key = ftok("Part4/shared.h", 65);
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
    
    while(data->counter <= 500){
        cout << "Process 2" << data->multiple << "x" << data->counter << "=" << (data->counter * data->multiple) << endl;
        usleep(250000);
    }
    
    shmdt((void*)data);
    cout << "[Process 2] Done, exiting..." << endl;
    return 0;
 }