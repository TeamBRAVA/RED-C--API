   
#include "../Red_librairies/Red.h"

#include <iostream>
#include <stdio.h>
//1 arg is data type 2 arg is value 
int main(int argc, char *argv[])
{
	Red* red =new Red();	
	string data_type=argv[1];
	string value =argv[2];	
	cout<<"type: "<<data_type<<endl ;
	cout<<"data: "<<value<<endl ;
	return 0;
}
