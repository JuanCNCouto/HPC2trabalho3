#!/bin/bash

rm saida.txt
make clean
make 

for i in $(seq 2 4);
do 
	echo "$i " >> saida.txt
	mpirun -np $i ./prog10 30000 30000 >> saida.txt
done 
