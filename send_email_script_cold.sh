#!/bin/bash

recipient="$1"
sender="$2"


subject="Warning: Weather Alert:Low Temperature Advisory"
message="Dear Citizens,

Temperatures are dropping .Stay warm,layer up and limit outdoor exposure.
Check on neighbours.Follow local advisories.
Safety First!

Regards,
City Weather service
"


echo -e "$message" | mutt -s "$subject"  -- "$recipient"

# Checking the exit status of the mail command
if [ $? -eq 0 ]; then
    echo "Email sent successfully."
else
    echo "Failed to send email."
fi


