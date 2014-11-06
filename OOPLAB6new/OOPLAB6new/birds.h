
#include<string>
class Birds
{
private:
	std::string name;
	int color;
	int hp;
public:
	Birds();
	Birds(std::string name, int color, int hp);
	~Birds();
	virtual int Calculatestrenght();
	//void printbird ( Birds *x); // print bird stats
	//void initializebird ( Birds &x); //initialize with the defaults values. in order to avoid memoryproblems. note: point to the address of the actual 
	// void setbird( Birds&x);
};
class Crow : public Birds
{

public:

	Crow(std::string name, int color, int hp, std::string Crow_Species, int Crow_Rank);
	~Crow();
	int Calculatestrenght();
private:
	std::string Crow_Species;
	int Crow_Rank;
};