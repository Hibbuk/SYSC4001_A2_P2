#include <iostream>
#include <unistd.h>  // usleep()
using namespace std;

int main() {
    int counter = 0;
    int cycle = 0;

    cout << "[Process 2] Started." << endl;

    // Run until counter < -500
    while (counter > -500) {
        if (counter % 3 == 0)
            cout << "[Process 2] Cycle " << cycle
                 << " - " << counter << " is a multiple of 3" << endl;
        else
            cout << "[Process 2] Cycle " << cycle << endl;

        counter--;
        cycle++;
        usleep(300000); // 0.3s delay
    }

    cout << "[Process 2] Counter below -500, exiting..." << endl;
    return 0;
}
