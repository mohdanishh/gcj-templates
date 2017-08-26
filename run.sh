#!/usr/bin/bash

source ~/.bashrc

g++ -std=c++11 single.cpp -o single
g++ -std=c++11 multi_thread_aplusb.cpp -pthread -o multi

for i in {1..1}
do
   python test.py > in
   echo "Running single threaded"
   time ./single < in > o_single.txt
   echo "Running multi threaded"
   time ./multi < in > o_parallel.txt
   diff o_single.txt o_parallel.txt
done
