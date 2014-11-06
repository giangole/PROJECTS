
#include <iostream>
#include<string>
#include <stdlib.h>
#include "birds.h"
#include "slingshot.h"
//MAIN CPP



int main(int argc, char* argv[])
{
	std::string Parrot_name("Felice");
	Birds parrot(Parrot_name, 5, 1000);
	std::string Boss_name("Hyori");
	std::string Boss_species("biggest");
	Crow Boss(Boss_name, 4, 2000, Boss_species, 100);
	std::cin.get();
	return 0;
}