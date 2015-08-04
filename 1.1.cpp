#include <iostream>
using namespace std;

class Classf{
	public:
		Classf(){cout << "Classf created" << endl;}
		double operator() (double x){
			return x*2;
		}
};

int main()
{
	Classf cf;
	cout << cf(2) << endl;
	cout << Classf() << endl;
	return 0;
}
