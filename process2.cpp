//part 2

#include <iostream>;
#include <unistd.h>;

int (main){
    int counter = 0;
    int cycle = 0;

    while(true){
        if (counter % 3 == 0){
            cout << "Process 2 Cycle" << cycle << " - " << counter << "is a multiple of 3" << endl;

        } else {
            cout << "Process 2 Cycle" << cycle << endl;
        }
        counter--;
        cycle++;
        usleep(300000);
    }
    return 0;
}