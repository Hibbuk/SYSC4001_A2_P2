#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include "shared.h"

using namespace std;

void sem_wait(int semid) {
    struct sembuf op = {0, -1, 0}; // P operation (wait)
    semop(semid, &op, 1);
}

void sem_signal(int semid) {
    struct sembuf op = {0, 1, 0}; // V operation (signal)
    semop(semid, &op, 1);
}

int main() {
    key_t key = ftok("Part5/shared.h", 65);
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create shared memory
    int shmid = shmget(key, sizeof(SharedData), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // Attach shared memory
    SharedData* data = (SharedData*) shmat(shmid, nullptr, 0);
    if (data == (void*) -1) {
        perror("shmat");
        return 1;
    }

    // Create semaphore
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    // Initialize semaphore to 1 (unlocked)
    semctl(semid, 0, SETVAL, 1);

    data->multiple = 3;
    data->counter = 0;

    cout << "[Process 1] Created shared memory and semaphore.\n";

    pid_t pid = fork();

    if (pid == 0) {
        execl("./Part5/process2_5", "process2_5", NULL);
        perror("execl");
        exit(1);
    } else {
        while (true) {
            sem_wait(semid); // lock

            if (data->counter > 500) {
                sem_signal(semid); // unlock before exit
                break;
            }

            data->counter++;
            cout << "[Process 1] counter = " << data->counter << endl;

            sem_signal(semid); // unlock

            usleep(100000);
        }

        wait(NULL);

        // Cleanup
        shmdt((void*)data);
        shmctl(shmid, IPC_RMID, nullptr);
        semctl(semid, 0, IPC_RMID);
        cout << "[Process 1] Done. Shared memory and semaphore removed.\n";
    }

    return 0;
}
