class Birds
{


		private:
std::string name;
int color;
int hp;
		public:
Birds(std::string name,int color,int hp);
~Birds();
virtual void Calculatestrenght ();
//void printbird ( Birds *x); // print bird stats
//void initializebird ( Birds &x); //initialize with the defaults values. in order to avoid memoryproblems. note: point to the address of the actual 
// void setbird( Birds&x);
};
class Crow::public Birds
{
private:
std::string CrowSpecies; 
int Crow_Rank;
Crow();
~Crow();
void Calculatestenght(Crow crow);

};