#ifndef SHARED_H
#define SHARED_H

#include <sys/types.h>

struct SharedData {
    int multiple; // multiple of 3
    int counter; //shared counter
};

#endif