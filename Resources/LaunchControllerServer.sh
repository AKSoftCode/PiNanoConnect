#!/bin/sh


cd Resources/Proxy/envoy

sudo service docker restart

sudo modprobe spidev
sudo docker-compose down
sudo docker-compose up -d

cd ../../../Server/Controller.Server
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`

while true; do ./Controller.Server > server.out && break; done







