#!/bin/bash

ssh -i $1 root@10.1.1.10 'sv stop /etc/solo-services/shae-server'
ssh -i $1 root@10.1.1.10 'sv stop /etc/solo-services/shae-control'
ssh -i $1 root@10.1.1.10 'sv start /etc/solo-services/shae-server'
ssh -i $1 root@10.1.1.10 'sv start /etc/solo-services/shae-control'
