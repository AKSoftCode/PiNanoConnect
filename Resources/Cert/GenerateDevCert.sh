#!/bin/sh
#https://robrich.org/presentation/2020/08/05/developing-https-containers.aspx
#https://youtu.be/oAf3_8k17E8

sudo apt install -y libnss3-tools

sudo wget https://github.com/FiloSottile/mkcert/releases/download/v1.3.0/mkcert-v1.3.0-linux-arm -O /usr/local/bin/mkcert
sudo chmod +x /usr/local/bin/mkcert

echo "Installing Cert"
mkcert -install 
mkcert -key-file https-web.key -cert-file https-web.pem localhost 127.0.0.1
openssl pkcs12 -export -out https-web.pfx -inkey https-web.key -in https-web.pem -certfile rootCA.pem -passout pass:https-web
mkcert -install
