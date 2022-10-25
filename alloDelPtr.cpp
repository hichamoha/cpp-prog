//Allocating and deleting a pointer
#include <iostream>
using namespace std;

int main()
{
	int localVar = 5;
	int *pLocal = &localVar;
	int *pHeap = new int;
	*pHeap = 7;

	cout << "localVar: " << localVar << endl;
	cout << "*pLocal: " << *pLocal << endl;
	cout << "*pHeap: " << *pHeap << endl << endl;

	delete pHeap;
	pHeap = new int;
	*pHeap = 9;

	cout << "*pHeap: " << *pHeap << endl;
	delete pHeap;

	return 0;
}
