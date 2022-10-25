// File gregorian.cpp 
// contiene la definizione delle funzioni della classe Julian

/*
 Historisk bakgrund Den Julianska kalendern infördes av Julius Caesar år 46 f.Kr.
 Detta år infogade Julius Caesar hela 90 dagar till den romerska kalendern för att
 återföra månaderna till deras rätta ställe på året med hänsyn till årstiderna.
 I den Julianska kalendern infinner sig skottår vart fjärde år. 
*/

#include "gregorian.h"
//#include <iostream>
//#include <cassert>
//#include <stdexcept>
//#include <iomanip>

//using namespace std;

namespace lab2
{
    // TESTING DRIVER ===========================================
    // void Date::runTestDriver(){}
  
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
    Gregorian::Gregorian() : Roman()
    {
      is_date(year(), month(), day());
    }

    // Other constructor 
    //Julian(double JDN) : Date(JDN) {} ?????
    //a class may initialize only its direct base class

    // Other constructor: check for valid date and initialize
    Gregorian::Gregorian(int yy, int mm, int dd) : Roman(0) 
    {
       is_date(yy,mm,dd);
       Date::JDnumber = gregorian_to_jd(yy, mm, dd);
    }  

    // kopieringskonstruktor ?????
    Gregorian::Gregorian(const Date & date) : Roman(0) // cosi si azzera JDnumber
    {
       Date::JDnumber = date.get_JDnumber();
       is_date(year(), month(), day());
    }
   
    Gregorian::Gregorian(const Date* date) : Roman(0) //????
    {
       Date::JDnumber = date->get_JDnumber();
       is_date(year(), month(), day());
    }
  
    // Assignment operator
    //const Date& operator=(const Date &);
     
// ====== Particular funktionalitet i klassen Date ===================
// Åtkomst (9)...For examing the Date (Non modifying operations)
    int Gregorian::year() const
    {
       return jd_to_gregorian(Date::JDnumber).year;
    } 
 
    int Gregorian::month() const //första månaden ska representeras av talet 1
    {
       return jd_to_gregorian(Date::JDnumber).month;
    }

    //den första i varje månad ska representeras av talet 1 
    int Gregorian::day() const
    {
       return jd_to_gregorian(Date::JDnumber).day;
    } 
   
    //============================================= days_this_month()
    /*
     int days_in_month(int style, int year, int month)
     {
       static int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

       return month==2 && is_leap(style,year) ? 29 : days[month-1];
     } 
    */


    //returnerar antal dagar den aktuella månaden  
    int Gregorian::days_this_month() const
    {
       int m = month();
       int i=0;
       for (; i<31; i++)
       {
         data ymd = jd_to_gregorian(Date::JDnumber+i);
         if (ymd.month != m)
           break;
       }
       return jd_to_gregorian(Date::JDnumber+i-1).day; 
    }  
    

// Mutator (7)...For changing the Date (Modifying operations)
    Gregorian Gregorian::operator++ (int) //returnerar kopia av sig själv
    {
       Gregorian source(*this);
       ++(*this);
       return source;       
    }

    Gregorian Gregorian::operator-- (int) //returnerar kopia av sig själv
    {
       Gregorian source(*this);
       --(*this);
       return source;     
    }

    Date& Gregorian::operator++ () //returnerar referens till sig själv
    {
       ++Date::JDnumber;
       return *this;
    }

    Date& Gregorian::operator-- () //returnerar referens till sig själv
    {
       --Date::JDnumber;
       return *this;
    }

    // ****** Help functions: 
    data Gregorian::jd_to_date(double JD) const
    {
       return jd_to_gregorian(JD);     
    }

    double Gregorian::date_to_jd(int y,int m ,int d) const
    {
       return gregorian_to_jd(y, m, d);
    }
    
    //============================================= leap_year()
    /*
     Korrekt hantering av skottår. I den julianska är det vart fjärde år. I den
     Gregorianska kalendern infaller skottdagen vart fjärde år men utgår de
     sekelårtal som inte är jämnt delbara med 400. 
    */
    // Any year divisible by 4 except centenary years not divisible by 400
    bool Gregorian::leap_year(int y) const
    {  /*
       if (y % 4 == 0) return false;
       if (y%100==0 && y%400==0) return false;

       return true;
       */
       if (y % 400 == 0) return true; 
       if (y % 100 == 0) return false; 
       if (y % 4 == 0) return true; 

       return false;  
    }
  
    //============================================ gregorian_to_jd()
    double Gregorian::gregorian_to_jd(int y,int m ,int d) const
    {
       double JD = ( 1461 * ( y + 4800 + ( m - 14 ) / 12 ) ) / 4 +
                   ( 367 * ( m - 2 - 12 * ( ( m - 14 ) / 12 ) ) ) / 12 -
                   ( 3 * ( ( y + 4900 + ( m - 14 ) / 12 ) / 100 ) ) / 4 +
                    d - 32075  ;  
       return JD;
    } 
    
    //=========================================== jd_to_gregorian()
    data Gregorian::jd_to_gregorian(double JD) const
    {
       data ymd;
       JD = floor(JD+0.5);
       int l = JD + 68569;
       int n = ( 4 * l ) / 146097;
       l = l - ( 146097 * n + 3 ) / 4;
       int i = ( 4000 * ( l + 1 ) ) / 1461001;
       l = l - ( 1461 * i ) / 4 + 31;
       int j = ( 80 * l ) / 2447;
       ymd.day = l - ( 2447 * j ) / 80;
       l = j / 11;
       ymd.month = j + 2 - ( 12 * l );
       ymd.year = 100 * ( n - 49 ) + i + l;
       
       return ymd;
    }
    
/*
int main()
{
  Vector::runTestDriver();
}
*/

}

