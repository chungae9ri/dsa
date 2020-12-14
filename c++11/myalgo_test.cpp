#include "myalgo.h"
#include <vector>
#include <iostream>


int main()
{
	// 1. permute test
	std::vector<char> carray;

	carray.push_back('a');
	carray.push_back('b');
	carray.push_back('c');
	carray.push_back('d');
	carray.push_back('e');

	myalgo::permute<char> mypermute;
	mypermute(carray, 0, carray.size() - 1);

	// 2. set test
	myalgo::set<char> myset;
	myset(carray);
	return 0;
}
