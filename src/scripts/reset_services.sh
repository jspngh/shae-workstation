#!/bin/bash

rsa_key = $1
ssh -i rsa_key root@10.1.1.10 'sv restart /etc/solo-services/shae-server'
ssh -i rsa_key root@10.1.1.10 'sv restart /etc/solo-services/shae-control'
