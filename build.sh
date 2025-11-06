#!/bin/bash
# Stop immediately if any command fails
set -e


#   SYSC4001_A2_P2 Build File


# Part 1
# echo " Building Part 1..."
# g++ -o Part1/part1 Part1/part1.cpp

# Part 2 
#echo " Building Part 2..."
#g++ -o Part2/process1 Part2/process1.cpp
#g++ -o Part2/process2 Part2/process2.cpp

# Part 3
#echo " Building Part 3..."
#g++ -o Part3/process1_3 Part3/process1_3.cpp
#g++ -o Part3/process2_3 Part3/process2_3.cpp

# Part 4
#echo " Building Part 4..."
#g++ -o Part4/process1_4 Part4/process1_4.cpp
#g++ -o Part4/process2_4 Part4/process2_4.cpp

#Part 5
#!/bin/bash
echo "Building Part 5..."
g++ Part5/process1_5.cpp -o Part5/process1_5
g++ Part5/process2_5.cpp -o Part5/process2_5

echo ""
echo "Build Complete!"
