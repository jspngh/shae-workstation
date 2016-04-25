#!/bin/bash

# Get current ssid
current_ssid=$(iwconfig wlan0 | grep 'ESSID:' | awk '{print $4}' | sed 's/ESSID://g' | sed 's/"//g')

solo_ssid="SoloLink_Shae"
i=5

# If not yet connected to solo network
if [ "$solo_ssid" != "$current_ssid" ]
then
	echo "Connecting"
	while [ $i -gt 0 ]
	do
		# Connect to solo network
		output="$(nmcli dev wifi connect SoloLink_Shae password projectshae 2>&1)"

		# Check for errors and retry if so (max 5 times)
		if [[ $output =~ "Error:" ]]
		then
		        echo "${output}"
			echo "Retry..."
			i=$((i-1))
		else
		        echo "Connected"
			break
		fi
	done
else
	echo "Already connected"
fi

# If connection failed, print error
if [ $i -eq 0 ]
then
	>&2 echo "Not connected"
fi

