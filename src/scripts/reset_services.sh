#!/bin/bash
ssh -i shae_rsa root@10.1.1.10 'sv restart /etc/solo-services/shae-server'
ssh -i shae_rsa root@10.1.1.10 'sv restart /etc/solo-services/shae-control'
