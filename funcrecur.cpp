#include <iostream>

using namespace std;

int it=0;

void reverse()
{
	char ch;
	cin.get(ch);
	if(ch != '\n') {
		reverse();
		cout.put(ch);
	}
}

void receive();

void store()
{
	cout << "store()" << it << endl;
	receive();
	cout << "post store()" << it << endl;
}

void decode()
{
	cout << "decode()" << it << endl;
	store();
	cout << "post decode()" << it << endl;
}

void receive()
{
	if (it < 10){
		cout << "receive()" << ++it << endl;
		decode();
		cout << "post receive()" << --it << endl;
	}
}

int main()
{
	/*reverse();*/
	receive();
	return 0;
}
