#!/bin/bash

rm temponw.txt
make clean
make 

(./prog) >> temponw.txt &
