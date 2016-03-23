#!/bin/bash
declare -i number
number=0
while true
do	
	number=$((number+1))
  ./raspeberry "number" $number
    sleep 10m
done
