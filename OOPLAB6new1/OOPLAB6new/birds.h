
#include<string>
class Birds
{
<<<<<<< HEAD
protected:
=======
private:
>>>>>>> 5fe91a5ce80b8746fffc16f0ac78c1c4d6fcc3a3
	std::string name;
	int color;
	int hp;
public:
	Birds();
	Birds(std::string name, int color, int hp);
<<<<<<< HEAD

	~Birds();
	virtual int Calculatestrenght();
	virtual void Showinfo();
	virtual void Setinfo();
=======
	~Birds();
	virtual int Calculatestrenght();
	//void printbird ( Birds *x); // print bird stats
	//void initializebird ( Birds &x); //initialize with the defaults values. in order to avoid memoryproblems. note: point to the address of the actual 
	// void setbird( Birds&x);
>>>>>>> 5fe91a5ce80b8746fffc16f0ac78c1c4d6fcc3a3
};
class Crow : public Birds
{

public:
<<<<<<< HEAD
	Crow();
	Crow(std::string name, int color, int hp, std::string Crow_Species, int Crow_Rank);
	//Crow(std::string Crow_Species, int Crow_Rank);
	~Crow();
	int Calculatestrenght();
	void Showinfo();
	void Setinfo();
protected:
	std::string Crow_Species;
	int Crow_Rank;
};
class Seagull : public Birds
{
public:
	Seagull();
	Seagull(std::string name, int color, int hp,int Seagull_rank);
	int Calculatestrenght();
protected:
	int Seagull_rank;
=======

	Crow(std::string name, int color, int hp, std::string Crow_Species, int Crow_Rank);
	~Crow();
	int Calculatestrenght();
private:
	std::string Crow_Species;
	int Crow_Rank;
>>>>>>> 5fe91a5ce80b8746fffc16f0ac78c1c4d6fcc3a3
};