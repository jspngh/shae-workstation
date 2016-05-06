#!/bin/bash

if [ $# -ne 2 ]
then
        echo "Error: This command needs two arguments: ssid and password" >> $2
else
	# Check internet connection
        output="$(timeout 10 ping 8.8.8.8 2>&1)"

        # Print echo
        if [[ $output =~ "ttl=" ]]
        then
                echo "Gateway was already set" >> $2
		exit
        fi

	# Set gateway with a timeout of x seconds
        timeout 60 solo wifi --name=$0 --password=$1 2>&1

	# Reconnect to the solo network. It could be that the signal is lost
	./connect_to_solo_network.sh

	# Check internet connection
        output="$(timeout 10 ping www.google.com 2>&1)"

	# Print echo
	if [[ $output =~ "ttl=" ]]
	then
                echo "Gateway correctly added" >> $2
	else
                echo "Error: The gateway is not correctly added" >> $2
	fi
fi
