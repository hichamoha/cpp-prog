/*
****************** 2.2 (arv från abstrakt basklass)
Den julianska respektive gregorianska kalendern ska ärva INDIREKT från klassen Date
genom den "middle" abstrakta klassen Roman.

*/

#include "roman.h"
#include "kattistime.h"

#include <stdexcept>
//#include <iomanip>
#include <math.h>
#include <iostream>

//using namespace std;

namespace lab2 
{
   // TESTING DRIVER ===========================================
   // void Date::runTestDriver(){}
  
   // static functions cannot be const
   // int Date::set_default_date() {return default_date;}
   //============================================================  


    const std::string Roman::Day[] = {"monday", "tuesday", "wednesday", 
                       "thursday", "friday", "saturday", "sunday"};

    const std::string Roman::Month[] = {"january", "february", "march", "april",
                                   "may", "june", "july", "august", 
                              "september", "october","november","december"};

    //========================================= days_per_week()
    int Roman::days_per_week() const //returnerar ett fix antal dagar 
    {  return 7; }

    //========================================= month_per_year()
    int Roman::months_per_year() const
    {  return 12; } 

    //========================================= week_day()
    int Roman::week_day() const    //måndag = 1
    {
      int d = (int)floor(Date::JDnumber + 0.5) % days_per_week() + 1;
      return d;
    }
   
    //======================================== week_day_name()
    std::string Roman::week_day_name() const
    {
      int dayName = (int)floor(Date::JDnumber + 0.5) % 7;  
      return Day[dayName];
    }

    //======================================== month_name()
    std::string Roman::month_name() const
    {
      return Month[month() - 1];
    }

    // ========================================= add_year
    /*
     För skottdagen ska add_year ge sista februari: 29/2 2004 -> 28/2 2005.
     Anropar man add_year den 29/2 först med 1 och därefter med -1 så ska
     man hamna på 28/2. Läggerman till fyra år till skottdagen ska man hamna
     på skottdagen igen om det nu är skottår då: 29/2 2004 -> 29/2 2008. Hade
     man istället lagt till ett år i taget hade man hamnat på den 28:e 
    */
 
    //lägger till n år/månad, där n är positiv eller negativ
    bool Roman::add_year(int n)
    {
       int y = year();
       int m = month();
       int d = day();

       if (d==29 && m==2 && !leap_year(y+n))  
         Date::JDnumber = date_to_jd(y+n, m, 28);
       
       else
         Date::JDnumber = date_to_jd(y+n, m, d);

       return true;  
    }
    
    // ========================================== add_month() 
    /*
     add_month ska ge samma datum i nästa månad men om det inte går så
     ska det plussas på 30 dagar istället. Exempel 1/9 -> 1/10 och 31/5 ->
     30/6. Den 31/1 kan bli 1:a eller 2:a mars beroende på om det är skottår.
     
     Anropar man add_month med argumentet 5 så ska det vara ekivivalent
     med om man gör add_month 5 gånger. Motsvarande gäller inte alltid för
     add_year se ovan.
    */
    bool Roman::add_month(int n)
    {
       int count = 0;  // counter for month() argument n
       if (n<0) 
         count = -1;
       else count = 1;

       while (n!=0)
       {
          // *** Forward in time
          if (n>0) 
          {
            int oldDay = day();
            
            int leftDays = days_per_month(year(), month()) - day(); 
            //shift ahead to the first day of the next month 
            Date::JDnumber += leftDays + 1;

            if (oldDay <= days_this_month())
              // ska ge samma datum i nästa månad 1/9 -> 1/10
              Date::JDnumber += oldDay - 1;

            // om det inte går så ska det plussas på 30 dagar istället 
            else 
              Date::JDnumber += 30 - (leftDays + 1);  // 31/5 -> 30/6
          }

          // *** Backward in time
          else
          {
             int oldDay = day();
            
            //shift back to the last day of the previous month 
            Date::JDnumber -= oldDay;

            if ( oldDay <= days_per_month(year(), month()) )
              // ska ge samma datum i förra månad 1/10 -> 1/9
              Date::JDnumber -= (days_this_month() - oldDay);

            // om det inte går så ska det minskas på 30 dagar istället
            else 
              Date::JDnumber -= (30 - oldDay);  // 31/5 -> 30/4
          }
          
      // ???? Den 31/1 kan bli 1:a eller 2:a mars beroende på om det är skottår.
          n -= count;
       }

       return true;
       
      
    }

    //========================================== mod_julian_day()     
    /*
     mod_julian_day() returnerar antal dagar sedan det modifierade 
     julianska dygnet vilket i vår nuvarande kalender är den 17 november 1858.
     
     A Modified Julian Day (MJD): is created by subtracting 2400000.5 from a 
    Julian day number, and thus represents the number of days elapsed since
    midnight (00:00) Universal Time on November 17, 1858. MJD is 2,400,000.5 less 
    than the JD. MJD 0 thus started on 17 Nov 1858 (Gregorian) at 
    00:00:00 TT.
    */
    int Roman::mod_julian_day() const // modified julian day MJD
    {
      int MJD = floor(Date::JDnumber - 2400000.5); //days_from_zero=JDnumber
      return MJD; 
    }

    //========================================= is_date()
    void Roman::is_date(int y, int m, int d) const
    {
       // we assume that year is valid
       if (m<1 || m>12) 
         throw std::out_of_range(" Month OUT OF RANGE !");
       
       if (d<1 || d>days_per_month(y, m))
         throw std::out_of_range(" Day OUT OF RANGE !!"); 
    }
    
    //=========================================== days_per_month()
    int Roman::days_per_month(int year,int month) const
    {
       switch (month)
       {
         case 1: case 3: case 5:  case 7: case 8: case 10: case 12: 
             return 31; 
             break;
         case 2: 
             return (leap_year(year))? 29 : 28;  // conditional operator "?:"
             //if (leap_year(year)==true) return 29;
             //else return 28;    
             break;
         default:
             return 30; 
             break;
       }

       return 0; 
    }
   
    //=========================================== days_one_month() ???????
    int Roman::days_one_month(int y,int m) const
    {
       int jd = date_to_jd(y,m,1);
       
       int i=0;
       for (; i<31; i++)
       {
         data ymd = jd_to_date(jd+i);
         if (ymd.month != m)
           break;
       }
       return jd_to_date(jd+i-1).day; 
    }

}

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
