#!/bin/sh

echo "Controller Initial Setup....."

root_dir=$HOME/Controller

cd $root_dir
cd Resources/Build/
./BuildInstall.sh

cd $root_dir
cd Resources/Cert
./GenerateDevCert.sh

cd $root_dir
cp -f HMI.desktop $HOME/Desktop


