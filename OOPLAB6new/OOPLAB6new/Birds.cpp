#include "birds.h"
#include<string>
#include <iostream>
//constructor
int Birds::Calculatestrenght()
{
	std::cout << "a non-specific bird has only 10 strenght :(\n";
	return 10;
}
Birds::Birds(std::string xname, int xcolor, int xhp) : name(xname), color(xcolor), hp(xhp)
{
	std::cout << "Bird Initialized \n";
	std::cout << xname <<"\n";
	std::cout << xcolor<<"\n";
	std::cout << xhp <<"\n";
	std::cout << "\n";
	std::cout << "\n";
}
Birds::~Birds()
{
	std::cout << "Bird Deleted\n";
}
Crow::Crow(std::string xname, int xcolor, int xhp, std::string xSpecies, int xRank) : Birds(xname, xcolor, xhp), Crow_Species(xSpecies), Crow_Rank(xRank) //inherit the constructor form parent class) by using xVARIABLE, u can access them even if private??
{
	std::cout << "This is a crow\n";
	std::cout << xname << "\n";
	std::cout << xcolor << "\n";
	std::cout << xhp << "\n";
	std::cout << xSpecies<< "\n";
	std::cout <<  xRank<< "\n";
	std::cout << "\n";
	std::cout << "\n";
}
int Crow::Calculatestrenght()
{
	//Crow temp();
	return Crow_Rank * 10;
}
Crow::~Crow()
{
	std::cout << "BB crow :(\n";
}
