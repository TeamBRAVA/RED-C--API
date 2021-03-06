//To send : g++ -o launch Simple_create_send_get.cpp -lcurl -std=c++11 -Wall && ./launch

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////	 _____    _____   _____  ///////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////	|  _  \  | ____| |  _  \ ///////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////	| |_| |  | |__   | | | | ///////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////	|  _  /  |  __|  | | | | ///////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////	| | \ \  | |___  | |_| | ///////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////	|_|  \_\ |_____| |_____/ ///////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////	                         ///////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Red_librairies/Red.h"

#include <iostream>
#include <stdio.h>


int main(void)
{
	Red* red =new Red();
	string sent_value="Elephant";	
	string data_type = "Animal";
	string return_value;

	//red_config will return a red object with the Red server adress by default
	//Or you can set up your own server adress by using red->set_red_option(red,Red_Option::SET_HOST,"http://example.com");
	//Or you can set up after the default Red server adress if you don't want to pass by red_config using : red->set_red_option(red,Red_Option::SET_RED_HOST);
	red=red_config(); 

	//Creating the new device
	device_id=red->set_red_option(red,Red_Option::ADD_NEW_DEVICE);

	//Name your own data type label such as apple or peach
	red->set_red_option(red,Red_Option::SET_DATA_TYPE,data_type);

	red->set_red_option(red,Red_Option::SET_CERTIFICATE,"RED-certifs/device1.pem");
	red->set_red_option(red,Red_Option::SET_PASSPHRASE,"0F9BCA6E5B");

	//You may want to display all the info about the red object before sending
	red->display();

	//Send it safely using post (return a std::string response indication)
    String return_post_value= red->set_red_option(red,Red_Option::SEND_DATAS,sent_value);
	

}
