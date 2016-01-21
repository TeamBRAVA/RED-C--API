
#include "Red.h"

int main(void)
{

	Red* red = new Red; 
	
	//red=Red_init();	
	red->set_red_option(red,Red_Option::SET_DEVICE_ID,1);
	red->set_red_option(red,Red_Option::SET_HOST,"http://localhost:3000");
	red->set_red_option(red,Red_Option::SET_DATA_TYPE,"temp");
	red->set_red_option(red,Red_Option::SET_BUFFER,"HEARSTONE");
	red->display();
	red->post(red,"goggogogogogo");
	//cout<< red->get(red);

}