#include <iostream> //for cout cerr endl
#include <unistd.h> //for fork() execl() usleep()
#include <sys/types.h> //for pid_t size_t
#include <sys/wait.h> // for wait
#include <sys/ipc.h> // for ftok() and key mangement
#include <sys/shm.h> // for shmget shmat etc
#include <cstdlib>
#include "shared.h"

using namespace std;

int main() {
    
    key_t key = ftok("shared.h", 65); //file name and the PID
    if (key = -1)
    {
        perror(" error ftok");
        return 1;
    }

    //shard memory
    int shmid = shmget(key, sizeof(SharedData), IPC_CREAT | 0666);
    if(shmid == -1){
        perror("shmid");
        return 1;
    }

    //attach the shared mem
    SharedData* data = (SharedData*) shmat(shmid, nullptr, 0);
    if( data == (void*) -1){
        perror("shmat");
        return 1;
    }

    //init shared data
    data->multiple = 3;
    data->counter = 0;

    cout << "Process 1 cretaed Shared mem. multiple = " << data->multiple << endl;

    //fork and start process 2
    pid_t pid = fork(); // create a child process

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }
    else if (pid == 0) {
        //Child Process 
        execl("./Part4/process2_4", "process2_4", NULL);
        perror("exec failed");
        exit(1);
    } 
    else {
        //Parent Process and increment counter
        while(data->counter <= 200){
            data->counter++;
            cout << "Process 1 counter" << data->counter << endl;
            usleep(100000) //.1 delay
        }
        //wait for child to finsh
        wait(NULL);
        //remove the memory
        shmdt((void*) data);
        shmctl(shmid, IPC_RMID, nullptr); 

        count << "Process 1 done and the shared memory is removed" << endl;
    }
    return 0;
}