#!/bin/bash
variable=$(/opt/vc/bin/vcgencmd measure_temp)
while true
do
  echo $variable
  ./raspberry "Raspberry_temp" $variable
    sleep 30m
done

