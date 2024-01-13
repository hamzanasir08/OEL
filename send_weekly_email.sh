#!/bin/bash

recipient="aadi64499@gmail.com"
sender="aadi64499@gmail.com"
attachment="report.txt"


subject="Weekly Weather Report "
message="Dear Citizens,

Attached is the weekly report of previous week.

Regards,
City Weather service
"


echo -e "$message" | mutt -s "$subject" -a "$attachment"  -- "$recipient"

# Checking the exit status of the mail command
if [ $? -eq 0 ]; then
    echo "Email sent successfully."
else
    echo "Failed to send email."
fi


