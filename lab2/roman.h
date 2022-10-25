/*
****************** 2.2 (arv från abstrakt basklass)
Den julianska respektive gregorianska kalendern ska ärva INDIREKT från klassen Date
genom den "middle" abstrakta klassen Roman.

*/


#ifndef ROMAN_H
#define ROMAN_H

#include "date.h"
#include "kattistime.h"
//#include <iomanip>
#include <string>
#include <iostream>

//using namespace std;

namespace lab2 
{
/*  
The Julian Period is a chronological interval of 7980 years beginning 4713 BC. 
It has been used by historians since its introduction in 1583 to convert between
different calendars. 2012 is year 6725 of the current Julian Period. The next Julian Period begins in the year 3268 AD.

What is the Julian Day of 00:00:00 UTC,1 january 1970? 
Because the time() function returns the value in seconds since 00:00:00 UTC,
January 1, 1970.
This can be calculated in this way:

 From 4713 BC to AD 1970 there are 6683-1 = 6682 years. In the Julian calendar, 
 years have 365.25 days, so 6682 years correspond to 6682×365.25= 2440600 days.
 Subtract from this the 13 days that the Gregorian calendar is ahead of the 
 Julian calendar, and we get 2440587.
*/
  class Roman : public Date
  { 
  public:
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
    */
    Roman() : Date(2440587.5 + (k_time(0)/86400)) {}; // JD number from 01jan1970   

    // Other constructor 
    Roman(double JDN) : Date(JDN) {} //JDn=Julian Day Number from 1Jan4713 BC

    // Other constructor
    //Roman(int yy, int mm, int dd) // testa validation
    //  {if (!is_date(yy,mm,dd)) throw Invalid();}  
    
                                             
    // Destructor: Base classes ordinarily should define a virtual destructor.     
    virtual ~Roman() {};                 

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
    virtual int week_day() const; //måndag = 1
    
    virtual int days_per_week() const; //returnerar ett fix antal dagar
    virtual int days_this_month() const = 0; //returnerar antal dagar 
                                             //den aktuella månaden   
    virtual int months_per_year() const; 
    
    virtual std::string week_day_name() const;
    virtual std::string month_name() const;

// Mutator (7)...For changing the Date (Modifying operations)
    //virtual Date& operator++ () = 0; //returnerar referens till sig själv
    //virtual Date& operator-- () = 0; //returnerar referens till sig själv
    //void operator+= (int ) ; //tar int som parameter 
    //void operator-= (int ) ; //tar int som parameter
    virtual bool add_year(int n = 1);  //lägger till n år/månad,
    virtual bool add_month(int n = 1); //där n är positiv eller negativ
    
    /*
     mod_julian_day() returnerar antal dagar sedan det modifierade 
     julianska dygnet vilket i vår nuvarande kalender är den 17 november 1858.
    */
    virtual int mod_julian_day() const; // modified julian day MJD

    //double get_days_from_zero() const;
    
    //static void runTestDriver(); 
    //static Date default_date;  
    
  protected:
    // ****** Help functions: 
    virtual data jd_to_date(double JD) const = 0;
    virtual double date_to_jd(int y,int m ,int d) const = 0;
    
    virtual bool leap_year(int y) const = 0;
    
    void is_date(int y,int m,int d) const;  //a constructor !?
    int days_per_month(int y,int m) const;
    int days_one_month(int y,int m) const;

    static const std::string Day[];
    static const std::string Month[];

  };

}
#endif


/*
****************** 2.2 (arv från abstrakt basklass)
Gör följande: skriv två klasser Julian och Gregorian för den julianska respektive
gregorianska kalendern. Dessa ska ärva (direkt eller indirekt) från klassen Date.

Funktionalitet hos klasserna:
• Implementation av basklassens virtuella funktioner vid behov
• Konstruktor som tar år, månad, dag som int.
• Man ska kunna kopiera och tilldela dateobjekt. Skillnaden mellan datumen
ska vara noll efter tilldelning/kopiering.
• postfix-operatorer ++ och -- som returnerar kopia av sig själv.
• Konstruktion utan argument (defaultkonstruktorn) ger dagens datum. För
att få dagens datum ska du inte använda systemanrop direkt utan gå via
en speciell funktion, se filen kattistime.h på kurskatalogen.
• Korrekt hantering av skottår. I den julianska är det vart fjärde år. I den
Gregorianska kalendern infaller skottdagen vart fjärde år men utgår de
sekelårtal som inte är jämnt delbara med 400.
• Utskriftsoperatorn ska definieras och skriva ut datumet på formen YYYYMM-
DD där ental fylls ut med nollor (2000-01-01).
• add_month ska ge samma datum i nästa månad men om det inte går så
ska det plussas på 30 dagar istället. Exempel 1/9 -> 1/10 och 31/5 ->
30/6. Den 31/1 kan bli 1:a eller 2:a mars beroende på om det är skottår.
• För skottdagen ska add_year ge sista februari: 29/2 2004 -> 28/2 2005.
Anropar man add_year den 29/2 först med 1 och därefter med -1 så ska
man hamna på 28/2. Läggerman till fyra år till skottdagen ska man hamna
på skottdagen igen om det nu är skottår då: 29/2 2004 -> 29/2 2008. Hade
man istället lagt till ett år i taget hade man hamnat på den 28:e
• Anropar man add_month med argumentet 5 så ska det vara ekivivalent
med om man gör add_month 5 gånger. Motsvarande gäller inte alltid för
add_year se ovan.
• Försöker man komma åt eller skapa ogiltiga dagar så ska out_of_range
slängas.
• Använd engelska namn med små bokstäver på dagar och månader. Var
noga med stavningen.
• Deklaration och implementation av klasserna ska skrivas i i separata headerrespektive
implementationsfiler (.h .cpp).

Alla implementationsdetaljer exempelvis om du har en hjälpfunktion leap_year())
ska döljas med protected eller private.
För att underlätta räkningar kan du låta datumen representeras av ett avstånd
till ett fixt datum. Du behöver inte implementera en sluten formel för
datumberäkning utan det är tillåtet att använda en hårdkodad (förberäknad)
tabell som t.ex. innehåller avstånd till årets början. Det räcker om din kalender
klarar datum från och med år 1858 fram till och med år 2558.
 
*/
