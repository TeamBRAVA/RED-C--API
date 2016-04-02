#!/bin/bash
echo "Installing the last version of RED API code"
git clone https://github.com/TeamBRAVA/RED-C-API.git
echo "Cloning down"
echo "Downloading latest compiler"
sudo apt-get install g++
echo "Downloading latest curl"
sudo apt-get install libcurl4-openssl-dev
echo "Done"


