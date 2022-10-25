// File Date.cpp 
// contiene la definizione delle funzioni della 
// classe Date che non sono pure virtual

#include "date.h"
#include <iostream>
//#include <cassert>
//#include <stdexcept>
#include <iomanip>
#include <math.h>

//using namespace std;

namespace lab2
{

  // TESTING DRIVER ===========================================
 // void Date::runTestDriver(){}
  
  // static functions cannot be const
 // int Date::set_default_date() {return default_date;}
  //============================================================  

  double Date::get_JDnumber() const
  {
    return JDnumber;   
  }
 
  //=================================================
  // Overload input operator for class Date;
  std::istream &operator>> (std::istream &input, Date &v)
  {
  // it is needed to run test driver
    return input; 
  }


  //========================= operator+=()
  void Date::operator+= (int a) //tar int som parameter 
  {
    JDnumber += (double)a;   
  }

  //========================= operator-=()
  void Date::operator-= (int a) //tar int som parameter
  {
    JDnumber -= (double)a;
  }

  //======================== operator==()
  bool operator== (const Date& d1, const Date& d2) 
  {
    return (floor(d1.mod_julian_day() == d2.mod_julian_day()));
  }

  //========================= operator!=()
  // Determine if 2 dates are not equal and
  // return true, otherwise return false (uses operator==)
  bool operator!= (const Date& d1, const Date& d2)
  { 
    //floor(x) Returns the largest integral value that is not greater than x.
    return (floor(d1.mod_julian_day() != d2.mod_julian_day()));
  }

  //======================== operator<()
  bool operator< (const Date& d1, const Date& d2) 
{
    return (floor(d1.mod_julian_day() < d2.mod_julian_day())); 
}

  //======================== operator<=()
  bool operator<= (const Date& d1, const Date& d2)
  {
    return (floor(d1.mod_julian_day() <= d2.mod_julian_day()));
  }
  //======================== operator>()
  bool operator> (const Date& d1, const Date& d2)
  {
    return (floor(d1.mod_julian_day() > d2.mod_julian_day()));
  }

  //======================== operator>=()
  bool operator>= (const Date& d1, const Date& d2)
  {
    return (floor(d1.mod_julian_day() >= d2.mod_julian_day()));
  }

  //======================== operator-()
  //returnerar heltalsdifferensen mellan två datum
  int operator- (const Date& d1, const Date& d2) 
  {                                            
    return (floor(d1.mod_julian_day() - d2.mod_julian_day()));  
  }

  //========================= operator<<()
  // Overload output operator for class Date, extern function
  std::ostream& operator<< (std::ostream& os, const Date& d)
  {
     return os << std::setfill('0') << std::setw(4) << d.year() << "-" 
               << std::setw(2) << d.month() << "-" 
               << std::setw(2) << d.day(); 
  }

}
/*
int main()
{
  Vector::runTestDriver();
}
*/



