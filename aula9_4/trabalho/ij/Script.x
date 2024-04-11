#!/bin/bash

rm tempoij.txt
make clean
make 
	
(./progij) >> tempoij.txt &
