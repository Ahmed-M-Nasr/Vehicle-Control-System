#include <stdio.h>
#include <stdlib.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1 /*if the define =1 engine temperature data is used, if define =0 engine temperature data is not used */
/* functions declarations */
void en(void);
void traffic();
void r_temp();
void print();
void eng();
/* an enum used for on/off states*/
enum state{
	on=0, off=1
};
/* struct of six variables that will be displayed*/
struct readings{
	enum state engine;
	enum state AC;
	enum state controller;
	int speed;
	int room ;
	int engine_temp;
}red; /* A global variable of struct state to be used in all functions*/
/*Main Function*/
int main(void) {
	char c;
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	while(1){
	printf("choose Vehicle state \n a. Turn on the vehicle engine \n b. Turn off the vehicle engine \n c. Quit the system \n");
	scanf(" %c",&c);
	if(c=='a'){
		en();
		red.engine=on;
	}
	else if(c=='b'){
		printf("engine off\n");}
	else if(c=='c'){
		printf("Quit");
	break;}
	else printf("invalid\n");
	}
		return 0;}
/*function when the engine is on*/
void en(void){
	red.speed=100;
	red.engine_temp=90;
	red.room=35;
	red.AC=off;
#if(WITH_ENGINE_TEMP_CONTROLLER)
	red.controller=off;
#endif
	char r;
	while(1){
	printf(" a. Turn off the engine \n b. Set the traffic light color. \n c. Set the room temperature \n");
#if(WITH_ENGINE_TEMP_CONTROLLER)
	printf(" d. Set the engine temperature \n");
#endif
	scanf( " %c" , &r);
	switch(r){
	case 'a':
		printf("engine off\n");
		return;
		break;
	case 'b':
		traffic();
		break;
	case 'c':
		r_temp();
		break;
#if(WITH_ENGINE_TEMP_CONTROLLER)
	case 'd':
		eng();
		break;
#endif
	}
	print();
	}
	return;
}
void traffic(){ /*function to choose the traffic light*/
	char z;
	printf("enter the color\n");
	scanf(" %c",&z);
	switch(z){
		case 'g':
			red.speed=100;
			break;
		case 'o':
			red.speed=30;
			red.AC=on;
			red.room=(red.room*(1.25))+1;
		#if(WITH_ENGINE_TEMP_CONTROLLER)
			red.controller=on;
			red.engine_temp=(red.engine_temp*(1.25))+1;
		#endif
			break;
		case'r':
			red.speed=0;
			break;
}}
void r_temp(){ /*function to set the room temperature*/
	int t;
	printf("enter required room temp\n");
	scanf("%d",&t);
	if(t<10 || t>30){
		red.AC=on;
		red.room=20;
	} else red.AC=off;
}
void eng(){ /*function to set the engine temperature*/
	int t;
	printf("enter required engine temp\n");
	scanf("%d",&t);
	if(t<100 || t>150){
		red.controller=on;
		red.engine_temp=125;
	}else {red.controller=off;
	red.engine_temp=90;
	return;
	}
}
void print(){ /*function to print all the states and data */
	if(red.engine==0){
		printf("Engine is ON \n");
	}else printf("Engine is off \n");
	if(red.AC==0){
	printf("AC is ON \n");
	}else printf("AC is off \n");
	printf("Room temp: %d \nVehicle speed: %d \n",red.room,red.speed);
#if(WITH_ENGINE_TEMP_CONTROLLER)
	printf("Engine temp: %d \n",red.engine_temp);
	if(red.controller==0){
	printf("Temp controller is ON \n");
		}
	else printf("Temp controller is off \n");
#endif
}
