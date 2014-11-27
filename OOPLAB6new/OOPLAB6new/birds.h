
#include<string>
class Birds
{
protected:
	std::string name;
	int color;
	int hp;
public:
	Birds();
	Birds(std::string name, int color, int hp);

	~Birds();
	virtual int Calculatestrenght();
	virtual void Showinfo();
	virtual void Setinfo();
};
class Crow : public Birds
{

public:
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
};