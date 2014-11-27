
#include <iostream>
#include<string>
#include <stdlib.h>
#include "birds.h"
#include "slingshot.h"
//MAIN CPP



int main(int argc, char* argv[])
{
	std::string Parrot_name("Felice");
<<<<<<< HEAD
	std::string Seagull_name("forex");
=======
>>>>>>> 5fe91a5ce80b8746fffc16f0ac78c1c4d6fcc3a3
	Birds parrot(Parrot_name, 5, 1000);
	std::string Boss_name("Hyori");
	std::string Boss_species("biggest");
	Crow Boss(Boss_name, 4, 2000, Boss_species, 100);
<<<<<<< HEAD
	Seagull Jim(Seagull_name, 2, 2000, 90);
	parrot.Showinfo();
	Boss.Showinfo();
	Boss.Calculatestrenght();

	parrot.Setinfo();
	Boss.Setinfo();


	std::cin.get();
	return 0;
}


//in this case the output is:
// 3 bird= 2 birds and 1 crow, the same bird is created twice (hyori) cause it inherited the constructor from its parent class (bird)
=======
	std::cin.get();
	return 0;
}
>>>>>>> 5fe91a5ce80b8746fffc16f0ac78c1c4d6fcc3a3
