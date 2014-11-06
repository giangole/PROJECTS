/*/*
#include <iostream>
#include <stdlib.h>
//EXAMPLE
struct birds
{
char name[20];
int color;
int hp;
};
struct slingshot
{
int strenght;
int position;
double Xaxis;
double Yaxis;
};
void printbirds (struct birds *x); // print bird stats
void printslingshot (struct slingshot *x); // print slingshot stats notes: uses a pointer to the actual struct
void initializebird (struct birds &x); //initialize with the defaults values. in order to avoid memoryproblems. note: point to the address of the actual struct
void initializeslingshot (struct slingshot &x); // initialize with the defaults values. in order to avoid memoryproblems. note: point to the address of the actual struct
void setbirds(struct birds &x);
int main(int argc, char* argv[])
{
/*char bird[]= "flappy";
std::cout<< bird<<"\n";
char*ptr;   // SOLVED, WAS JUST A RENDUNDANT CIN IN THE FUNCTION -.-
ptr = &bird[0];
std::cout<< ptr;
				
				birds firstbird;
				slingshot *birdpoint;
				birdpoint = new slingshot;
				initializebird(firstbird);
				initializeslingshot(*birdpoint); 
				setbirds(firstbird);

				printbirds(&firstbird);
				printslingshot(birdpoint);
				char *toname;
				toname = &firstbird.name[0];
				std::cout<< "this is the pointer:\n";
				std::cout<< toname<<"\n";
				
std::cin.get();
std::cin.get();
return 0;
}

void printbirds (struct birds *x)
{
std::cout<< (*x).name[0]<<"\n";
std::cout<< (*x).name<<"\n";
std::cout<< (*x).color<<"\n";
std::cout<< (*x).hp<<"\n";
std::cout<<"\n";
std::cout<<"\n";
}

void printslingshot (struct slingshot *x)
{
std::cout<< (*x).strenght<<"\n";
std::cout<< (*x).position<<"\n";
std::cout<<(*x).Xaxis<<"\n";
std::cout<<(*x).Yaxis<<"\n";
std::cout<<"\n";
std::cout<<"\n";
}

void initializebird (struct birds &x)
{
x.color = 1;
x.hp = 1000;
for (int i=0;i<20;i++)
{
x.name[i] = 'T';
}
}

void initializeslingshot (struct slingshot &x)
{
x.position = 0;
x.strenght = 0;
x.Xaxis = 1;
x.Yaxis = 1;
}
void setbirds(struct birds &x)
{
std::cout<<"Set bird stats:\n"<<"name:\n";
std::cin.getline(x.name,20);
//std::cin.get();

std::cout<<"color: (1 to 9)\n";
std::cin>> x.color;
//std::cin.get();
std::cout<<"hp:\n";
std::cin>> x.hp;
//std::cin.get();
}


/////////////////////////////WITH TYPEDEF \\\\\\\\\\\\\\\\\\\\\\\\




#include <iostream>
#include <stdlib.h>
//MAIN CPP
 struct birds
{
char name[20];
int color;
int hp;
};
 struct slingshot
{
int strenght;
int position;
double Xaxis;
double Yaxis;
};

typedef struct birds bird;
typedef struct slingshot shot;
void printbird ( bird *x); // print bird stats
void printshot ( shot *x); // print shot stats notes: uses a pointer to the actual 
void initializebird ( bird &x); //initialize with the defaults values. in order to avoid memoryproblems. note: point to the address of the actual 
void initializeshot ( shot &x); // initialize with the defaults values. in order to avoid memoryproblems. note: point to the address of the actual 
void setbird( bird &x);
int main(int argc, char* argv[])
{
/*char bird[]= "flappy";
std::cout<< bird<<"\n";
char*ptr;   // SOLVED, WAS JUST A RENDUNDANT CIN IN THE FUNCTION -.-
ptr = &bird[0];
std::cout<< ptr;*/
				/*
				bird firstbird;
				shot *birdpoint;
				birdpoint = new shot;
				initializebird(firstbird);
				initializeshot(*birdpoint); 
				setbird(firstbird);

				printbird(&firstbird);
				printshot(birdpoint);
				char *toname;
				toname = &firstbird.name[0];
				std::cout<< "this is the pointer:\n";
				std::cout<< toname<<"\n";
				
std::cin.get();
std::cin.get();
return 0;
}

void printbird ( bird *x)
{
std::cout<< (*x).name[0]<<"\n";
std::cout<< (*x).name<<"\n";
std::cout<< (*x).color<<"\n";
std::cout<< (*x).hp<<"\n";
std::cout<<"\n";
std::cout<<"\n";
}

void printshot ( shot *x)
{
std::cout<< (*x).strenght<<"\n";
std::cout<< (*x).position<<"\n";
std::cout<<(*x).Xaxis<<"\n";
std::cout<<(*x).Yaxis<<"\n";
std::cout<<"\n";
std::cout<<"\n";
}

void initializebird ( bird &x)
{
x.color = 1;
x.hp = 1000;
for (int i=0;i<20;i++)
{
x.name[i] = 'T';
}
}

void initializeshot ( shot &x)
{
x.position = 0;
x.strenght = 0;
x.Xaxis = 1;
x.Yaxis = 1;
}
void setbird( bird &x)
{
std::cout<<"Set bird stats:\n"<<"name:\n";
std::cin.getline(x.name,20);
//std::cin.get();

std::cout<<"color: (1 to 9)\n";
std::cin>> x.color;
//std::cin.get();
std::cout<<"hp:\n";
std::cin>> x.hp;
//std::cin.get();
}













*/