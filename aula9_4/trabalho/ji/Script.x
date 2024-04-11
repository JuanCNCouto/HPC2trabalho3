#!/bin/bash

rm tempoij.txt
make clean
make 
	
(./progji) > tempoji.txt &
