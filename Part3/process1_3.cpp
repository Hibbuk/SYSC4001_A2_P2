#include <iostream>
#include <unistd.h>     // fork(), execl(), usleep()
#include <sys/wait.h>   // wait()
#include <sys/types.h>
#include <cstdlib>      // exit()

using namespace std;

int main() {
    pid_t pid = fork(); // create a child process

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }
    else if (pid == 0) {
        //Child Process 
        execl("./Part3/process2_3", "process2_3", NULL);
        perror("exec failed");
        exit(1);
    } 
    else {
        //Parent Process
        int counter = 0;
        int cycle = 0;

        cout << "[Process 1] Started and waiting for Process 2..." << endl;

        // Wait until process2 finishes
        wait(NULL);

        cout << "[Process 1] Detected Process 2 ended. Exiting now..." << endl;
    }

    return 0;
}
