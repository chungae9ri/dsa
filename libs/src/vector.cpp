#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

template<typename T>
void printVector(const char *s, const vector<T>& v) {
	cout << s << " = (";
	if (v.size() == 0) {
		cout << ")" << endl;
		return;
	}
	typename vector<T>::const_iterator i = v.begin();
	for(; i != v.end()-1 ; i++)
		cout << *i << ' ' ;
	cout << *i << ")" << endl;
}

bool f1(int n) {
	return n<4;
}

int main() 
{
	int a[] = {1,2,3,4,5};
	vector<int> v1;
	printVector("v1", v1);
	for (int j=1 ; j<=5 ; j++) 
		v1.push_back(j);
	printVector("v1", v1);
	vector<int> v2(3,7);
	vector<int>::iterator i1 = v1.begin()+1;
	/*printVector("i1", i1);*/
	vector<int> v3(i1, i1+3);
	vector<int> v4(v1);
	vector<int> v5(5);
	return 0;
}
