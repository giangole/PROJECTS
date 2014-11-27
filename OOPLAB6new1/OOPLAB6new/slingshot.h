#include<string>
class Slingshot
{
private:
	int force;
	double angle; //in radiants 180 degree = 1 r
	double Xaxis;
	double Yaxis;
public:
	Slingshot();
	Slingshot(int force,double angle,double Xaxis,double Yaxis);
	~Slingshot();
};