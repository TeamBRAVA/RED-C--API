
#include "Red_librairies/Red.h"


int main(void)
{

	Red* red = new Red; 
	string res;
	//red=Red_init();	
	red->set_red_option(red,Red_Option::SET_DEVICE_ID,1);
	red->set_red_option(red,Red_Option::SET_HOST,"http://localhost:3000");
	//red->set_red_option(red,Red_Option::SET_HOST,"http://localhost:3000");
	red->set_red_option(red,Red_Option::SET_DATA_TYPE,"temp");
	red->set_red_option(red,Red_Option::SET_BUFFER,"HEARSTONE");
	cout<<red->set_red_option(red,Red_Option::GET_BUFFER);
	cout<<red->set_red_option(red,Red_Option::SET_RED_HOST);
	red->display();
	red->post(red,"goggogogogogo");
	//cout<< red->get(red);

}