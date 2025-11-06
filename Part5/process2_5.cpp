#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shared.h"

using namespace std;

void sem_wait(int semid) {
    struct sembuf op = {0, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal(int semid) {
    struct sembuf op = {0, 1, 0};
    semop(semid, &op, 1);
}

int main() {
    key_t key = ftok("Part5/shared.h", 65);
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int shmid = shmget(key, sizeof(SharedData), 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    int semid = semget(key, 1, 0666);
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    SharedData* data = (SharedData*) shmat(shmid, nullptr, 0);
    if (data == (void*) -1) {
        perror("shmat");
        return 1;
    }

    cout << "[Process 2] Connected to shared memory.\n";

    while (true) {
        sem_wait(semid);

        if (data->counter > 500) {
            sem_signal(semid);
            break;
        }

        if (data->counter > 100) {
            cout << "[Process 2] " << data->multiple << " x "
                 << data->counter << " = " << data->multiple * data->counter << endl;
        }

        sem_signal(semid);
        usleep(250000);
    }

    shmdt((void*)data);
    cout << "[Process 2] Done.\n";
    return 0;
}
