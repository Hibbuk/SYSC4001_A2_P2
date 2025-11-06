//Part 1
// Assignment 2 Shael Kotecha & Declan Koster
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if(pid<0){
        cerr << "Fork Failed" << endl;
        return 1;
    }

    if(pid == 0){
        //child process
        int counter = 0;
        while (true)
        {
            cout << "Child Counter" << counter++ << endl;
            usleep(500000);// sleep for 0.3

        }
        
    }else {
        //parentprocesss

        int counter = 0;
        while(true){
            cout << "Parent Counter" << counter++ << endl;
            usleep(500000);
        }
    }
    return 0;
}