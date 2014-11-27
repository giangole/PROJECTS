#include <iostream>
#include<string>
#include <stdlib.h>

float division(int x, int y);
int main(int argc, char* argv[])
{
	int input1, input2 ;
	float result = 0;
	std::cin >> input1;
	std::cin >> input2;
	
	try {
		result = division(input1, input2);
		
	}

	catch (int result)
	{
		std::cerr << "error: divison by 0 happened" << result;
	}

	std::cout << result;
	std::cin.get();
	std::cin.get();
	return 0;
}
float division(int x, int y)
{
	if (y == 0)
	{
		throw 9999;
	}
	return x / y;
	throw "not possible to divide by 0";
}