#include <iostream>
#include <vector>
#include "DynamicArray.h"
using namespace std;

void testDynamicArray()
{
	DynamicArray<int> da = DynamicArray<int>();
	da.push(1);
	da.push(2);
	da.push(3);
	da.push(4);
	da.push(5);
	
	da.pop();

	da.insert(6, 2);
	da.remove(3);
	da.insert(7, da.size());
	da.push(8);
	da.push(9);
	da.remove(da.size() - 1);

	for (int i : da)
	{
		cout << i << endl;
	}

	cout << "size: " << da.size() << endl;
	cout << "cap: " << da.capacity() << endl << endl;

	DynamicArray<int> da2 = DynamicArray<int>();
	da2 = da;

	for (int i : da2)
	{
		cout << i << endl;
	}

	cout << endl << da2[2] << endl << "-------" << endl;

	da.clear();

	da.push(1);

	da[0];

	for (int i : da)
	{
		cout << i << endl;
	}
}

int main()
{
	vector<int> test;

	test.reserve(5);

	cout << test.size() << endl;
	cout << test.capacity() << endl;

	test.insert(test.end(), 2);

	for (int i : test)
	{
		cout << i << endl;
	}


	DynamicArray<int> da(5);
}