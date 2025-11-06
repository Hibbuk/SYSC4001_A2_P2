//apart of part 2

#include <iostream>;
#include <unistd.h>;
#include <sys/types.h>;
#include <cstdlib>;

int main(){
    pid_t pid = fork();

    if(pid < 0){
        cerr << " Fork Failed" << endl;
        return 1;
    }
    else if (pid == 0){
        exec1("./process2", "process2", NULL);

        perror("exec failed");
        exit(1);
    }
    else {
        int counter = 0;
        int cycle = 0;

        while(true){
            if(counter % 3 == 0){
                cout << "Process 1 Cycle" << cycle << " - " << counter << " is a multiple of 3" << endl;

            } else {
                cout << " Process Cycle " << cycle << endl;
            }

            counter++;
            cycle++;
            usleep(300000)

        }
    }
    return 0;
}