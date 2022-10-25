// File julian.cpp 
// contiene la definizione delle funzioni della classe Julian

/*
 Historisk bakgrund Den Julianska kalendern infördes av Julius Caesar år 46 f.Kr.
 Detta år infogade Julius Caesar hela 90 dagar till den romerska kalendern för att
 återföra månaderna till deras rätta ställe på året med hänsyn till årstiderna.
 I den Julianska kalendern infinner sig skottår vart fjärde år. 
*/

#include "julian.h"
//#include <iostream>
//#include <cassert>
//#include <stdexcept>
//#include <iomanip>

//using namespace std;

namespace lab2
{
   // TESTING DRIVER ===========================================
   void Julian::runTestDriver()
   {
     Julian j;  // dagens datum
     std::cout << " Today it is  " << j << " julian";
   }
  
   // static functions cannot be const
   // int Date::set_default_date() {return default_date;}
   //============================================================  

    /* 
    // Default constructor ger dagens datum. 
    // För att få dagens datum ska du inte använda systemanrop direkt utan gå via
    // en speciell funktion, se filen kattistime.h på kurskatalogen.
    // The time() function returns the value  of  time  in  seconds
    // since 00:00:00 UTC, January 1, 1970.
    // JD number for 1 january 1970 = 2440587
    // current time in seconds converted to day: k_time(0)/60*60*24

    Derived-class constructors: Although a derived object contains members that 
    it inherits from its base, it cannot directly initialize those members. 
    A derived class must use a base-class constuctor to initialize its base-class
    part.

    A derived class initializes its direct base class only.
    */
    Julian::Julian() : Roman()
    {
      is_date(year(), month(), day());
    }

    // Other constructor 
    //Julian(double JDN) : Date(JDN) {} ??????
    //a class may initialize only its direct base class

    // Other constructor: check for valid date and initialize
    Julian::Julian(int yy, int mm, int dd) : Roman(0) 
    {
       is_date(yy,mm,dd);
       Date::JDnumber = julian_to_jd(yy, mm, dd);
    }  

    // kopieringskonstruktor ???????
    Julian::Julian(const Date & date) : Roman(0)
    {
       Date::JDnumber = date.get_JDnumber();
       is_date(year(), month(), day());
    }
   
    Julian::Julian(const Date* date) : Roman(0) //????
    {
       Date::JDnumber = date->get_JDnumber();
       is_date(year(), month(), day());
    }
  
    // Assignment operator
    //const Date& operator=(const Date &);
     
// ====== Particular funktionalitet i klassen Date ===================
// Åtkomst (9)...For examing the Date (Non modifying operations)
    int Julian::year() const
    {
       return jd_to_julian(Date::JDnumber).year;
    } 
 
    int Julian::month() const //första månaden ska representeras av talet 1
    {
       return jd_to_julian(Date::JDnumber).month;
    }

    //den första i varje månad ska representeras av talet 1 
    int Julian::day() const
    {
       return jd_to_julian(Date::JDnumber).day;
    } 
   
    //============================================= days_this_month()
    //returnerar antal dagar den aktuella månaden  
    int Julian::days_this_month() const
    {
       int m = month();
       int i=0;
       for (; i<31; i++)
       {
         data ymd = jd_to_julian(Date::JDnumber+i);
         if (ymd.month != m)
           break;
       }
       return jd_to_julian(Date::JDnumber+i-1).day; 
    }  
    

// Mutator (7)...For changing the Date (Modifying operations)
    Julian Julian::operator++ (int) //returnerar kopia av sig själv
    {
       Julian source(*this);
       ++(*this);
       return source;       
    }

    Julian Julian::operator-- (int) //returnerar kopia av sig själv
    {
       Julian source(*this);
       --(*this);
       return source;     
    }

    Date& Julian::operator++ () //returnerar referens till sig själv
    {
       ++Date::JDnumber;
       return *this;
    }

    Date& Julian::operator-- () //returnerar referens till sig själv
    {
       --Date::JDnumber;
       return *this;
    }

    // ****** Help functions: 
    data Julian::jd_to_date(double JD) const
    {
       return jd_to_julian(JD);     
    }

    double Julian::date_to_jd(int y,int m ,int d) const
    {
       return julian_to_jd(y, m, d);
    }

    bool Julian::leap_year(int y) const
    //Korrekt hantering av skottår. I den julianska är det vart fjärde år.
    {
       return y%4 == 0;
    }
  
    //============================================ julian_to_jd()
    double Julian::julian_to_jd(int y,int m ,int d) const
    {
       if (m<=2)
         { 
           y--; 
           m+=12; 
         }
		
         double E = floor(365.25*(y+4716));
	 double F = floor(30.6001*(m+1));
	 double JD = d + E + F - 1524.5;
	 return JD;
    } 
    
    //=========================================== jd_to_julian()
    data Julian::jd_to_julian(double JD) const
    {
       data ymd;
       double Z = floor(JD+0.5);
       double A=Z; // for jd to julian
       double B = A + 1524;
       double C = floor((B-122.1)/365.25);

       double D = floor(365.25*C);
       double E = floor((B-D)/30.6001);
       double F = floor(30.6001*E);
       double G = Z - floor(Z);

       ymd.day = B-D-F+G;
       // (must get number less than or equal to 12)
       ymd.month = ( E-1<=12) ? E-1: E-13;
               
       ymd.year = (ymd.month<=2) ? C-4715 : C-4716;
		
       return ymd;
    }
    
    /*
    int main()
    {
      Julian::runTestDriver();
      //runTestDriver();

      return 0;
    }
    */
}

/*
 UNDEFINED REFERENCE:
 Undefined reference is typically a linker error, not a compiler error.

 Typical causes of these are:
 - missing functionality in the project, did you compile ALL the source files
 - typo's in symbol names, myFunc != MyFunc
 - missing libraries, where you're trying to make use of 3rd party code.

 All the project files should be compiled separately then linked together 
 not compiled together.

 Another common cause of undefined symbols is when you have multiple source files
 of your own that you want to compile separately, but each file refers to 
 variables or functions defined in the other files. In this case, you need to 
 compile each file into an object file, not a complete executable, and then link
 the various object files together: 
 Code:
	g++ -c file1.cpp -lm -lSDL -o file1.o
	g++ -c file2.cpp -lm -lSDL -o file2.o
	g++ file1.o file2.o
*/

