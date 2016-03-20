#!/bin/bash

while true
do		
  ./raspeberry "raspberry_temp" /opt/vc/bin/vcgencmd measure_temp
    sleep 10m
done
