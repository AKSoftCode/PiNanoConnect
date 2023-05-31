#!/bin/sh -x

cd $HOME/Controller

sudo kill $(ps aux | grep '[L]aunchController*' | awk '{print $2}')
sudo kill $(ps aux | grep '[C]ontroller.HMI.Server*' | awk '{print $2}')
sudo kill $(ps aux | grep '[C]ontroller.Server*' | awk '{print $2}')

./LaunchControllerServer.sh  > OutServer.txt &

sleep 5

./LaunchControllerClient.sh > OutClient.txt &

sleep 2

sensible-browser https://localhost:5003
