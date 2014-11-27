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
<<<<<<< HEAD
	std::cout <<"\n";

=======
	std::cout << "\n";
	std::cout << "\n";
>>>>>>> 5fe91a5ce80b8746fffc16f0ac78c1c4d6fcc3a3
}
Birds::~Birds()
{
	std::cout << "Bird Deleted\n";
}
<<<<<<< HEAD

Crow::Crow(std::string xname, int xcolor, int xhp, std::string xSpecies, int xRank) : Birds(xname, xcolor, xhp), Crow_Species(xSpecies), Crow_Rank(xRank) //inherit the constructor form parent class) by using xVARIABLE, u can access them even if private??
{
	std::cout << "This is a crow\n";
=======
Crow::Crow(std::string xname, int xcolor, int xhp, std::string xSpecies, int xRank) : Birds(xname, xcolor, xhp), Crow_Species(xSpecies), Crow_Rank(xRank) //inherit the constructor form parent class) by using xVARIABLE, u can access them even if private??
{
	std::cout << "This is a crow\n";
	std::cout << xname << "\n";
	std::cout << xcolor << "\n";
	std::cout << xhp << "\n";
>>>>>>> 5fe91a5ce80b8746fffc16f0ac78c1c4d6fcc3a3
	std::cout << xSpecies<< "\n";
	std::cout <<  xRank<< "\n";
	std::cout << "\n";
	std::cout << "\n";
}
<<<<<<< HEAD
void Birds::Showinfo()
{
	
	std::cout << "INFO of the selcted crow \n";
	std::cout << name <<"\n";
	std::cout << color <<"\n";
	std::cout << hp << "\n";

}
void Birds::Setinfo()
{
	std::cout << "Select which value you want to change: 1)name 2) color or 3) hp?\n";
	int input;
	std::cin >> input;
	switch (input)
	{

	case (1) : std::cin >> name;  std::cout << "\n";
	case (2) : std::cin >> color; std::cout  << "\n";
	case (3) : std::cin >> hp; std::cout  << "\n";
	default:
		std::cout << "nope\n";
	}
	std::cout << "INFO of new bird\n";
	std::cout << hp << "<-- newhps\n";

}
=======
>>>>>>> 5fe91a5ce80b8746fffc16f0ac78c1c4d6fcc3a3
int Crow::Calculatestrenght()
{
	//Crow temp();
	return Crow_Rank * 10;
}
<<<<<<< HEAD

Crow::~Crow()
{
	std::cout << "BB crow :(\n";
	std::cout << "\n";
}
void Crow::Showinfo()
{	
	std::cout << "INFO of the selcted crow \n";
	std::cout << name << "\n";
	std::cout << color << "\n";
	std::cout << hp << "\n";
	std::cout << Crow_Species << "\n";
	std::cout << Crow_Rank << "\n";
	std::cout << "\n";
}
void Crow::Setinfo()
{
	std::cout << "Select which value you want to change: 1)name 2) color or 3) hp 4 species 5 rank?\n";
	int input;
	std::cin >> input;
	switch (input)
	{

	case (1) : std::cin >> name;  std::cout << "\n";
	case (2) : std::cin >> color; std::cout << "\n";
	case (3) : std::cin >> hp; std::cout << "\n";
	case (4) : std::cin >> Crow_Species; std::cout << "\n";
	case (5) : std::cin >> Crow_Rank; std::cout << "\n";
	default:
		std::cout << "nope\n";
	}
	std::cout << "INFO of new crow\n";
	std::cout << hp << "<-- newhps\n";
	std::cout << hp << "\n";


}

Seagull::Seagull(std::string xname, int xcolor, int xhp, int xSeagull_rank) : Birds(xname, xcolor, xhp), Seagull_rank(xSeagull_rank)
{
}
int Seagull::Calculatestrenght()
{
	return Seagull_rank * 5;
}
=======
Crow::~Crow()
{
	std::cout << "BB crow :(\n";
}
>>>>>>> 5fe91a5ce80b8746fffc16f0ac78c1c4d6fcc3a3
