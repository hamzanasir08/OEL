#!/bin/bash
cd /home/abdussamad/Desktop/VSCode/
#Compile the C file
gcc  weekly_report.c -o weekly_report
./weekly_report
#send email 
./send_weekly_email.sh


