#include "slingshot.h"
#include<string>
#include <iostream>

Slingshot::Slingshot(int xforce, double xangle, double xXaxis, double xYaxis) : force(xforce), angle(xangle), Xaxis(xXaxis), Yaxis(xYaxis)
//Slingshot::Slingshot(int force, double angle, double Xaxis, double Yaxis) : force, angle, Xaxis, Yaxis{}
{
	std::cout << "Shot ready Initialized\n";
	std::cout << xforce<< "\n";
	std::cout << xangle << "\n";
	std::cout << xXaxis << "\n";
	std::cout << xYaxis << "\n";
	std::cout << "\n";
	std::cout << "\n";
}

Slingshot::~Slingshot()
{
	std::cout << "Shot Destroyed\n";

}
