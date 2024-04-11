#!/bin/bash

rm tempoij.txt
make clean
make 
for i in $(seq 10000 10000 100000);
do
	time ./progij $i $i; 2> tempoij.txt &
done
