#!/bin/bash

# Get current ssid
output="$(nmcli con status)"
solo_ssid="SoloLink_Shae"
i=5

# Check if already connected to solo network
if [[ $output =~ "$solo_ssid" ]]
then
	echo "Already connected"
else
	echo "Connecting"
	while [ $i -gt 0 ]
	do
		# Connect to solo network
		output="$(nmcli dev wifi connect SoloLink_Shae password projectshae 2>&1)"

		# Check for errors and retry if so (max 5 times)
		if [[ $output =~ "Error:" ]]
		then
		        echo "${output}"

			if [[ $output =~ "No network with SSID 'SoloLink_Shae' found." ]]
			then
				echo "Sleep 5 seconds"
#				sleep 5
			fi

			echo "Retry..."
			i=$((i-1))
		else
		        echo "Connected"
			break
		fi
	done
fi

# If connection failed, print error
if [ $i -eq 0 ]
then
	echo "Not connected: $output"
fi

