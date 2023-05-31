#!/bin/sh

export ASPNETCORE_URLS="https://+:5002;https://+:5003"
export Kestrel__Certificates__Default__Path=$HOME/Controller/Resources/Cert/https-web.pfx
export Kestrel__Certificates__Default__Password=https-web


cd Client/Controller.HMI

while true; do sudo ASPNETCORE_URLS="https://+:5002;https://+:5003" Kestrel__Certificates__Default__Path=$HOME/Controller/Resources/Cert/https-web.pfx Kestrel__Certificates__Default__Password=https-web  $HOME/.dotnet/dotnet Controller.HMI.Server.dll > client.out  && break; done






