#include "birds.h"
#include<string>
#include <iostream>
//constructor
Birds::Birds(std::string xname,int xcolor,int xhp) : name(xname), color(xcolor), hp(xhp)
{
std::cout<<"Bird Initialized.n/";
}

Birds::~Birds()
{
std::cout<<"Bird Deleted.n/";
}

Crow::Crow(std::string xname,int xcolor,int xhp, std::string xSpecies, int xRank) :  Birds(xname,xcolor,xhp), Crow_Species(xSpecies), Crow_Rank(xRank) //inherit the constructor form parent class) by using xVARIABLE, u can access them even if private??
{
std::cout<<"This is a crow.n/";
}
	
int Crow::Calculatestenght (Crow x_crow)
{
	Crow temp();
	return x_crow.Crow_Rank * 10;
}

Crow::~Crow()
{
std::cout<<"BB crow :(.n/";
}
