/*
****************** 2.2 (arv från abstrakt basklass)
Den julianska respektive gregorianska kalendern ska ärva INDIREKT från klassen Date
genom den "middle" abstrakta klassen Roman.

*/
#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "roman.h"

//#include <iomanip>
//#include <iterator>
#include <math.h>

//using namespace std;

namespace lab2 
{
/*  
The Julian Period is a chronological interval of 7980 years beginning 4713 BC. It has been used by historians since its introduction in 1583 to convert between different calendars. 2012 is year 6725 of the current Julian Period. The next Julian Period begins in the year 3268 AD.

What is the Julian Day of 00:00:00 UTC,1 january 1970? 
Because the time() function returns the value in seconds since 00:00:00 UTC,
January 1, 1970.
This can be calculated in this way:

 From 4713 BC to AD 1970 there are 6683-1 = 6682 years. In the Julian calendar, 
 years have 365.25 days, so 6682 years correspond to 6682×365.25= 2440600 days.
 Subtract from this the 13 days that the Gregorian calendar is ahead of the 
 Julian calendar, and we get 2440587.
*/

  // Nota Bene: a derived class may include the "virtual" keyword on the functions
  // it overrides, but it is not required to do so.
  class Gregorian : public Roman
  { 
  public:
    // Default constructor ger dagens datum. 
    // För att få dagens datum ska du inte använda systemanrop direkt utan gå via
    // en speciell funktion, se filen kattistime.h på kurskatalogen.
    // The time() function returns the value  of  time  in  seconds
    // since 00:00:00 UTC, January 1, 1970.
    // JD number for 1 january 1970 = 2440587
    // current time in seconds converted to day: k_time(0)/60*60*24
    Gregorian();

    // Other constructor 
    //Julian(double JDN) : Date(JDN) {} //JDn=Julian Day Number from 1Jan4713 BC

    // Other constructor
    Gregorian(int yy, int mm, int dd); //  check for valid date and initialize
    
    // kopieringskonstruktor ????????
    Gregorian(const Date & date);
   
    Gregorian(const Date* date); //????

    // Assignment operator
    //const Date& operator=(const Date &);
     
// ====== Particular funktionalitet i klassen Date ===================
// Åtkomst (9)...For examing the Date (Non modifying operations)
    int year() const;  
    int month() const; //första månaden ska representeras av talet 1
    int day() const;   //den första i varje månad ska 
                                       //representeras av talet 1 
    //virtual int week_day() const; //måndag = 1
    
    //virtual int days_per_week() const; //returnerar ett fix antal dagar
    int days_this_month() const; //returnerar antal dagar 
                                             //den aktuella månaden   
    //virtual int months_per_year() const; 
    
    //virtual std::string week_day_name() const;
    //virtual std::string month_mame() const;

// Mutator (7)...For changing the Date (Modifying operations)
    Gregorian operator++ (int); //returnerar kopia av sig själv
    Gregorian operator-- (int); //returnerar kopia av sig själv
    Date& operator++ (); //returnerar referens till sig själv
    Date& operator-- (); //returnerar referens till sig själv
    //void operator+= (int ) ; //tar int som parameter 
    //void operator-= (int ) ; //tar int som parameter
    //virtual bool add_year(int n = 1);  //lägger till n år/månad,
    //virtual bool add_month(int n = 1); //där n är positiv eller negativ
   
    static void runTestDriver(); 
    //static Date default_date;  
    
  private:
    // ****** Help functions: 
    data jd_to_date(double JD) const;
    double date_to_jd(int y,int m ,int d) const;
    bool leap_year(int y) const;

    double gregorian_to_jd(int y,int m ,int d) const;
    data jd_to_gregorian(double JD) const;

    // new functions respect to Julian class
    //bool leap_year();  // ????????
    //int days_this_month(int y, int m) const; // ???????
    //int days_of_year(int y);  
  };

}
#endif


