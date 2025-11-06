#!/bin/bash

# Stop if any fail

set -e

g++ -o part1 part1.cpp

echo " building process1 and 2"

g++ -o process1 process1.cpp

g++ -o process2 process2.cpp

echo "Build Complete"
echo ""
