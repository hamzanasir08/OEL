#!/bin/bash

recipient="$1"
sender="$2"


subject="Warning: Weather Alert: High Temperature Advisory"
message="Dear Citizens,

Be aware of soaring temperatures ahead.Stay hydrated, seek shades and avoid strenous activity during peak heat .
Look out for each other.Follow local advisories for a safe summer.
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

