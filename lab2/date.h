//%%%%%%%%%%%%%%%%%%%% 2.1 Abstrakt basklass Date (General-purpose)
/*
Denna uppgift är den första av flera där du ska skapa datum- och kalenderklasser.
Du ska hädanefter samla allt som har med din kalender att göra i namnrymden
(namespace) lab2.
Med en abstrakt basklass definierar man upp ett gränssnitt som nedärvda
klasser måste uppfylla. Skriv en generell basklass Date som har följande funktioner.
Om inget annat sägs är returtypen int.

*/

#ifndef DATE_H
#define DATE_H

//#include <stdexcept>
//#include <cstring>
//#include <iomanip>
//#include <iterator>
#include <iostream>
//#include <cstddef>    //size_t type is defined in the cstddef header
//#include <initializer_list> 
//#include <cassert>
//#include <algorithm>  // to call find() and sort(begin, end)

//using namespace std;
/*
Namespaces can be used to structure a program into "logical units".
By enabling this program structure, C++ makes it easier for you to divide up a 
program into groups that each perform their own separate functions, in the same 
way that classes or structs simplify object oriented design. But namespaces, 
unlike classes, do not require instantiation; you do not need an object to use a
specific namespace. You only need to prefix the function you wish to call with
namespace_name:: -- similar to how you would call a static member function of a 
class.
Another convenience of namespaces is that they allow you to use the same function 
name, when it makes sense to do so, to perform multiple different actions

you can introduce only specific members of a namespace using a using-declaration 
with the syntax: using namespace_name::thing;
One trick with namespaces is to use an unnamed namespace to avoid naming conflicts.

Linker Errors: -- Including object files
               -- Having the correct paths to your libraries. 
*/
namespace lab2 
{
  struct data
  {
    int day;
    int month;
    int year;
  };

// CLASSE BASE ASTRATTA: Una classe che contiene almeno una funzione virtuale 
// pura, e per la quale quindi non e' possibile definire oggetti, viene detta 
// classe base astratta.
// Definiamo una classe base astratta per realizzare il tipo astratto Date
// INDIPENDENTEMENTE dal metodo di representazione, e 2 classi derivate che 
// realizzano il tipo astratto secondo 2 diversi metodi di rapresentazione.
  class Date
  { 
     friend std::istream & operator>> (std::istream & is, Date &);

     //Låt utskriften vara år-månad-dag (med bindestreck).
     friend std::ostream & operator<< (std::ostream & os, const Date &);

  public:
    // Default constructor
    Date() : JDnumber(0) {};    

    // Other constructor 
    Date(double JD) : JDnumber(JD) {}; //JD=Julian Day 1Jan4713 BC
                                             
    // kopieringskonstruktor.
    //Date(const Date &);
    
    // Destructor: Base classes ordinarily should define a virtual destructor.     
    virtual ~Date() {};                 

    // Assignment operator
    //const Date& operator=(const Date &);
 
    //move-konstruktor och move-operator så att std::move fungerar.
    //Date(Date &&) noexcept;
  
    //Date& operator=(Date &&) noexcept;

// ====== Particular funktionalitet i klassen Date ===================
// Åtkomst (9)...For examing the Date (Non modifying operations)
    virtual int year() const = 0;  
    virtual int month() const = 0; //första månaden ska representeras av talet 1
    virtual int day() const = 0;   //den första i varje månad ska 
                                       //representeras av talet 1 
    virtual int week_day() const = 0; //måndag = 1
    
    virtual int days_per_week() const = 0; //returnerar ett fix antal dagar
    virtual int days_this_month() const = 0; //returnerar antal dagar 
                                             //den aktuella månaden   
    virtual int months_per_year() const = 0; 
    
    virtual std::string week_day_name() const = 0;
    virtual std::string month_name() const = 0;

// Mutator (7)...For changing the Date (Modifying operations)
    virtual Date& operator++ () = 0; //returnerar referens till sig själv
    virtual Date& operator-- () = 0; //returnerar referens till sig själv
    void operator+= (int) ; //tar int som parameter 
    void operator-= (int) ; //tar int som parameter
    virtual bool add_year(int n = 1) = 0;  //lägger till n år/månad,
    virtual bool add_month(int n = 1) = 0; //där n är positiv eller negativ
    
    /*
     mod_julian_day() returnerar antal dagar sedan det modifierade 
     julianska dygnet vilket i vår nuvarande kalender är den 17 november 1858.
    */
    virtual int mod_julian_day() const = 0; // modified julian day MJD

    double get_JDnumber() const;
    
    //static void runTestDriver(); 
    //static Date default_date;  
    
  protected:
    //Astronomers have used the Julian period to assign a 
    //unique number to every day since 1 January 4713 BC.
    //This is the so-called Julian Day (JD) or Julian Day Number (JDN).
    double JDnumber;  // days since 1jan4713 BC
  };

// Jämförelser (7):
    bool operator== (const Date& , const Date& );
    bool operator!= (const Date& , const Date& );
    bool operator< (const Date& , const Date& );
    bool operator<= (const Date& , const Date& );
    bool operator> (const Date& , const Date& );
    bool operator>= (const Date& , const Date& );
    int operator- (const Date& , const Date& ); //returnerar heltalsdifferensen
                                                //mellan två datum
}
#endif

/*
*********** What is the Julian Day?

Astronomers have used the Julian period to assign a unique number to every day 
since 1 January 4713 BC. This is the so-called Julian Day (JD) or Julian Day 
Number (JDN). JD 0 designates the 24 hours from noon TT on 1 January 4713 BC to
noon TT on 2 January 4713 BC. (TT=Terrestrial Time, which is roughly equivalent
to UTC. The current difference between the two is about one minute.[1])

This means that at noon TT on 1 January AD 2000, JD 2,451,545 started.

This can be calculated thus:

From 4713 BC to AD 2000 there are 6712 years. In the Julian calendar, years have 
365.25 days, so 6712 years correspond to 6712×365.25=2,451,558 days. Subtract 
from this the 13 days that the Gregorian calendar is ahead of the Julian calendar,
and you get 2,451,545.

Often fractions of Julian Days are used, so that 1 January AD 2000 at 15:00 TT 
is referred to as JD 2,451,545.125.

Note that some people use the term “Julian day number” to refer to any numbering
of days. NASA, for example, uses the term to denote the number of days since 1 
January of the current year, counting 1 January as day 1.

************* What is the modified Julian Day?

Sometimes a modified Julian Day (MJD) is used which is 2,400,000.5 less than the
Julian Day. This brings the numbers into a more manageable numeric range and 
makes the day numbers change at midnight TT rather than noon.

MJD 0 thus started on 17 Nov 1858 (Gregorian) at 00:00:00 TT.

================================================================================



       2.1 (abstrakta basklasser, strikt virtuella funktioner)


• Avgör vilka konstruktorer som ska vara med. Behövs tilldelningsoperator?

• Åtkomst: year(), month() (första månaden ska representeras av talet 1),
day() (den första i varje månad ska representeras av talet 1), week_day()
(måndag = 1), days_per_week() (returnerar ett fix antal dagar),
days_this_month() (returnerar antal dagar den aktuella månaden) och
months_per_year(). Skapa funktioner week_day_name() och month_name()
med returtyp std::string.

• Mutatorer:
– prefix-operatorer ++ och -- som returnerar referens till sig själv.
– +=, -= tar int som parameter. Välj lämplig returtyp.
– add_year(int n = 1) och add_month(int n = 1) (lägger till n år/månad,
där n är positiv eller negativ). Välj lämplig returtyp och motivera vid
redovisning.

• Obs! Basklassen ska kunna hantera alla sorters kalendersystem (persiska,
kinesiska m.m.). Basklassen ska därför inte innehålla något som är
specifikt för den kalender vi använder, såsom 12 månader per år,
veckodagarnas/månadernas namn eller dyl.

• Jämförelser (returnerar bool): ==, !=, <, <=, >, >=, - (returnerar heltalsdifferensen
mellan två datum)
• För att kunna jämföra olika datum som t.ex. ett persiskt datum med
ett svenskt datum, så ska du definiera en metod mod_julian_day som
returnerar antal dagar sedan det modifierade julianska dygnet vilket i vår
nuvarande kalender är den 17 november 1858. Mer information om just
detta dygn kan fås via google, eller wikipedia, sök på “modified julian day
number”.

• Man ska kunna skriva ut implementationer av datumklassen med utskriftsoperatorn.
Deklarera ostream & operator<<(ostream & os, const
Date &); . Låt utskriften vara år-månad-dag (med bindestreck).

• Operatorerna ska vara virtuella där så behövs. Låt de funktioner som inte
kan definieras i basklassen vara strikt virtuella (pure virtual).

• Vilka funktioner är const? Vilka argument/returtyper är const? Vid redovisningen
ska du övertyga handledaren att du kan använda const och
virtual.

Kuriosa: Excel använder 1:a januari 1900 som referensdag. Om man öppnar Excel
på PC, formaterar en cell till datum och matar in 60 så får man 29/2 1900. Den
skottdagen har dock aldrig funnits. Jag hyser stor tillsikt att ni klarar er bättre än
excelprogrammerarna.
*/
