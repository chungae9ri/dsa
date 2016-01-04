#include <iostream>
#include <math.h>

using namespace std;

int main () 
{
	bool ret = true;
	unsigned int max;
	int i, count = 0;

	cout << "input max number " << endl;
	cin >> max;
	bool *flags = new bool[max + 1];

	for(i = 0 ; i < max ; i++) {
		if(i == 0 || i == 1) flags[i] = false;
		else flags[i] = true;
	}

	unsigned int prime = 3;
	unsigned int limit = sqrt(max);
	/*while(prime <= sqrt(max)) {*/
	while(prime <= max) {
		for(i=2 ; i <= limit ; i++) {
			if(prime%i == 0 && i != prime) {
				/* not prime number*/
				ret = false;
				break;
			}
		}
		/* all pass, then prime number */
		if(ret) cout << "prime : " << prime << endl;
		ret = true;
		/* all even number is not prime number */
		prime += 2;
	}

	return 0;
}
