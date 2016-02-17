//To send : g++ -o launch Simple_post.cpp -lcurl -std=c++11 -Wall && ./launch
          
#include "../Red_librairies/Red.h"

#include <iostream>
#include <stdio.h>

int main(void)
{
	Red* red =new Red();
	string value="Girafe";
	string data_type="Animal";
	//red_config will return a red object with the Red server adress by default
	//Or you can set up your own server adress by using red->set_red_option(red,Red_Option::SET_HOST,"http://example.com");
	//Or you can set up after the default Red server adress if you don't want to pass by red_config using : red->set_red_option(red,Red_Option::SET_RED_HOST);
	red=red_config(); 

	//Setting up the device Id
	//red->set_red_option(red,Red_Option::SET_DEVICE_ID,device_id);
	//Set your certificate that proves your a owner and give us your device ID
	red->set_red_option(red,Red_Option::SET_CERTIFICATE,"RED-certifs/device1.pem");
	red->set_red_option(red,Red_Option::SET_PASSPHRASE,"0F9BCA6E5B");

	//Name your own data type labemonl such as apple or peach
	red->set_red_option(red,Red_Option::SET_DATA_TYPE,data_type);

	//You may want to display all the info about the red object before sending
	red->display();
	//Send it safely using post (return a std::string response indication)
    cout<< red->set_red_option(red,Red_Option::SEND_DATAS,value);
		
    return 0;
}
