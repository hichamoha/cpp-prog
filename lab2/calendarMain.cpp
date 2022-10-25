#include <iostream>
#include "date.h"
#include "gregorian.h"
#include "julian.h"
#include "calendar.h"

using namespace lab2;

int main()
{ 
  std::cout << std::endl << " Kuriosa of Excel. \n";
  Gregorian gExcel(1900,1,1);
  
  gExcel += 60;    // add 60 days -> 1900-03-02 Right!
  std::cout << gExcel << std::endl;
  //gExcel.add_month(2); 
  //std::cout << gExcel << std::endl;
  
  std::cout << std::endl << " Datecruncher. \n";
  Gregorian g(2012,9,30);
  Julian j(2012,2,29);
  

  for ( int i=0; i<10; i++ )
  {
    int c = 0;
    if ( g == j ) 
      c=1; 
    
    std::cout << g << " "<< g.month_name() << " " 
              << g.week_day_name() << " " << g.days_this_month() << " " 
              << g.mod_julian_day() << " ---- " 
              
              << j.mod_julian_day() << " " 
              << j << " "<< j.month_name() << " " << j.week_day_name() << " " 
              << j.days_this_month() << "  " << c << "\n";
  //++g;
  //g++;
  //j+=1;
  g.add_month(1);
  j.add_year(4);

  //	Gregorian g4(2100,2,29);
        
  //g.add_year(2);
  }

  /*	Gregorian g4(1974,02,20);
	Julian j4(g4);
	std::cout << j4 << "\n";
  */
  g=j;
  std::cout << g << " "<< g.month_name() << " " << g.week_day_name() 
            << " " << g.days_this_month() << " " << g.mod_julian_day() 
            << " ---- " << j.mod_julian_day() << " " 
            << j << " "<< j.month_name() << " " << j.week_day_name() 
            << " " << j.days_this_month() << "\n";

  Calendar<Gregorian> c(1974,02,10);
  c.add_event("testing", 20,02,1974);
  Calendar<Julian> j1(c);
  Calendar<Gregorian> c2(c);

  std::cout << j1;

  /*
        Calendar<Gregorian> c;
        c.set_date(2012,10,28);
        c.add_event("Julafton",29,10,2012);
        c.add_event("Tyskkorven",01,11,2012);
        c.add_event("Julafton",30,12,2012);
        c.add_event("Tyskkorven",31,12,2012);
        c.add_event("Julafton",29,10,2012);
        c.add_event("Tyskkorven",01,11,2012);
        c.add_event("el Julafton",30,12,2012);
        c.add_event("elTyskkorven",31,12,2012);
        c.add_event("il Julafton",29,10,2012);
        c.add_event("ul Tyskkorven",01,11,2012);
        c.add_event("dasd Julafton",30,12,2012);
        c.add_event("das Tyskkorven",31,12,2012);
        c.add_event("des Julafton",29,10,2012);
        c.add_event("il Tyskkorven",01,11,2012);
        c.add_event("ul Julafton",30,12,2012);
        c.add_event("ol Tyskkorven",31,12,2012);
        c.add_event("jajajaja");
        c.remove_event("jajajaja");
        c.remove_event("Tyskkorven",31,12,2012);
        c.remove_event("ol Tyskkorven",31,12,2012);
       
       
        std::cout << c;
  */        
  Gregorian g2(1858,11,17);
  Julian j2(1858,11,5);
  std::cout << g2 << "\n";
  std::cout << j2 << "\n"; 
  
  if (g2==j2) std::cout << "The same\n"; else std::cout << "not equal" << std::endl;
     j2++;

  if (g2==j2) std::cout << "The same"; else std::cout << "not equal" << std::endl;

  return 0;
}

