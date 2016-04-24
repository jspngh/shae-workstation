#!/bin/bash

function connect {
	nmcli dev wifi connect SoloLink_Shae password projectshae
}
current_ssid=$(iwconfig wlan0 | grep 'ESSID:' | awk '{print $4}' | sed 's/ESSID://g' | sed 's/"//g')

# TODO: Check of this is really the solo ssid
solo_ssid="SoloLink_Shae"

if [ "$solo_ssid" != "$current_ssid" ]
then
	echo "Connecting"
	i=5
	while [ $i -gt 0 ]
	do
		output="$(nmcli dev wifi connect SoloLink_Shae password projectshae 2>&1)"

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

if [ $i -eq 0 ]
then
	>&2 echo "Not connected"
fi

