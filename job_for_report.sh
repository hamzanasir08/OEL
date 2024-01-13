#!/bin/bash


#(crontab -l ; echo "0 */3 * * * /home/abdussamad/Desktop/VSCode/run_weekly_report.sh") | crontab -
#Setting a job that executes run_weekly_report.sh every sunday.
(crontab -l ; echo "0 0 * * 0 /home/abdussamad/Desktop/VSCode/run_weekly_report.sh") | crontab -