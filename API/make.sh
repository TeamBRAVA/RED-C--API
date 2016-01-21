#!/bin/bash
if [ $1 == 1 ]; then
	g++ -o launch main.cpp -lcurl -std=c++11 -Wall 
	./launch
elif [ $1 == 2 ]; then
	g++ -o launch RandomApp.cpp -lcurl -std=c++11 -Wall 
	./launch
else 
	echo "No parameter or wrong parameter"
fi

#echo "Gcc completed"


#echo "DONE"
