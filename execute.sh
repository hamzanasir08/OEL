#!/bin/bash
cd /home/abdussamad/Desktop/VSCode/
#Compiling all the C files
gcc -c send_email.c -o send_email.o
gcc -c convert_from_json.c -o convert_from_json.o
gcc -c calculate_averages.c -o calculate_averages.o
gcc -c heading.c -o heading.o
gcc -c main.c -o main.o
gcc main.o send_email.o convert_from_json.o calculate_averages.o heading.o -o executable -lcurl -ljansson
#Run the compiled program
./executable
#clean up the compiled object files
rm send_email.o convert_from_json.o calculate_averages.o heading.o