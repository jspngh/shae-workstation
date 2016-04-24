#!/bin/bash

if [ $# -ne 2 ]
then
	>&2 echo "Error: This command needs two arguments: ssid and password"
else
	solo wifi --name=$1 --password=$2
fi
