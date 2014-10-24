class birds
{


		private:
char name[20];
int color;
int hp;
		public:
			birds();
			~birds();

void printbird ( bird *x); // print bird stats
void initializebird ( bird &x); //initialize with the defaults values. in order to avoid memoryproblems. note: point to the address of the actual 
void setbird( bird &x);
};