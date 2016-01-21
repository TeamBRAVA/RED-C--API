//Launch :  g++ -o launch *.cpp -lcurl 
#include "Red.h"
//#include "Red.h"
void Sending(Red* red);
void Getting (Red* red);
int main(void)
{
	Red testred= Red();
	Red* red =&testred ;	

	int commande='0';
	string host;		

	red->set_red_option(red,Red_Option::SET_DEVICE_ID,10);
	
	red->set_red_option(red,Red_Option::SET_DATA_TYPE,"temperature");
	
	printf("\n////////////////WELCOME TO RED API/////////////////////");
	printf("\n**********Automatic or manual connection?**********\n");
	printf("\n////////////1:Automatic to RED/////////////// \n////////////2:Manual connection////////////\n");
	scanf("%d",&commande);
	if(commande==1)
	{
		host="http://localhost:3000";
	}else if(commande==2)
	{
		printf("\nPlease enter your config\n");
		scanf("%s",&host[0]);
	}
	red->set_red_option(red,Red_Option::SET_HOST,host);

	red->display();
	while(commande!=0)
	{
		printf("\nWhat would you like to do ?");
		printf("\n1:SEND \n2:GET\n\n");
		
		scanf("%d",&commande);	
			switch (commande)
			{
				case 1: 
				Sending(red);
				break;
				case 2:
				Getting(red);
				break;
				case 0:
				printf("Goodbye =)");
				break;
				default:
				printf("You didn't select the right number\n");
				
			}
	}
	
  return 0;
}
void Sending(Red* red)
{
	int commande;
	printf("\nWhat would you like to do ?");
	printf("\n1:SEND DATAS \n2:LIST PERMISSION \n3:WATCH DATA\n4:GET UPDATE\n");
	scanf("%d",&commande);

	switch (commande)
	{
		case 1: 
		red->post(red,"lalilala");
		break;
		case 2:
		red->list_permission();
		break;
		case 3:
		red->watch();
		break;
		case 4:
		red->update();
		break;
		default:
		Sending(red);
	}
}

void Getting (Red* red)
{
	int commande;
	printf("\nWhat would you like to do ?");
	printf("\n1:GET DATA \n2:GET DATA FROM ANOTHER OBJECT\n");
	scanf("%d",&commande);

	switch (commande)
	{
		case 1: 
		cout<< red->get(red);
		break;
		case 2:
		cout<< red->get_from(red);
		break;
		default:
		Getting(red);
	}
	
}


