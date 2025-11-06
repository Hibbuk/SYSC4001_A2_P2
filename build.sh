#!/bin/bash
# Stop immediately if any command fails
set -e

# ============================
#   SYSC4001_A2_P2 Build File
# ============================

# -------- Part 1 --------
# echo " Building Part 1..."
# g++ -o Part1/part1 Part1/part1.cpp

# -------- Part 2 --------
#echo " Building Part 2..."
#g++ -o Part2/process1 Part2/process1.cpp
#g++ -o Part2/process2 Part2/process2.cpp

# -------- Part 3 --------
echo " Building Part 3..."
g++ -o Part3/process1_3 Part3/process1_3.cpp
g++ -o Part3/process2_3 Part3/process2_3.cpp

echo ""
echo "Build Complete!"
