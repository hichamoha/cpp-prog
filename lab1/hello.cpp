
// hello.cpp - uppgift 1.1 (iteration, pekare, make)

/**
Denna uppgift går ut på att skriva ett program som skriver ut olika varianter på 
texten Hello world!. Programmet ska kunna ta en text och/eller ett tal som argument. Exempelkörning:
	datan> hello
	Hello world!
	datan> hello C++
	Hello C++!
	datan> hello 3 C++ lurigt !
	Hello C++ C++ C++!
	datan> hello 2
	Hello world world!
	datan>
Tips: Använd argv och argc. Använd atoi för att översätta en char * till ett
tal (om strängen inte representerar ett tal får man noll).

* argv is an array of pointers to C-style character strings.
* argc passes the number of strings in that array.
* When arguments are passed to main, the first element in argv points either to 
  the name of the  program or to the empty string.
*/

#include<iostream>
#include<string>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])  // argv[] = *argv, array rules
{                                   
    if (--argc==0)
         cout << "  Hello world! " << endl;
       
    else if (argc==1 && atoi(argv[1])!=0)
    {
         int n = atoi(argv[1]);
	 string s2 = "world ";

	 for (int r=1; r<n; r++)
         {    
             s2 = s2 + "world ";
         } 
         cout << " Hello "+ s2 + "!!!!" << endl;
    }

    else if (argc>1 && atoi(argv[1]) != 0)
    {
        int n2 = atoi(argv[1]);
        string s3 = argv[2];
 
        for (int j=1; j<n2; j++)
        {
	  s3 = s3 + " " + argv[2];  
        }
        cout << " Hello "+ s3 + "!!!" << endl; 
    }

    else if (argc==1)
    {
      string s4 = argv[1];
         cout << " Hello " + s4 + "!!" << endl;
    } 
  
    return 0;
   
 }
    	
