
// Pointers

//Setup a variable
int myVar = 5;

//Setup a pointer to myVar
int *pVar = &myVar;

//Give address of pointer
cout << &pVar << endl;

//Give address of myVar through pointer
cout << pVar << endl;

//Give address of myVar (same address, different method of last address)
cout << &myVar << endl;

//Read value in memory of myVar through our pointer
cout << *pVar;
