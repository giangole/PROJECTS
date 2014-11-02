class Slingshot
{
		private:
int strenght;
int position;
double Xaxis;
double Yaxis;
		public:
			Slingshot();
			~Slingshot();
void printshot ( Slingshot x); // print shot stats notes: uses a pointer to the actual 
void initializeshot ( Slingshot x); // initialize with the defaults values. in order to avoid memoryproblems. note: point to the address of the actual 

};