#include "calendar.h"
#include "gregorian.h"
#include "julian.h"
#include "kattistime.h"

#include <iostream>
#include <time.h>

//terminal color codes only for linux
#define RESET  "\033[0;0m"
#define RED    "\033[0;31m"
#define YELLOW "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BOLD   "\033[1m\033[0;0m"

int main() {
	using namespace lab2;
	
	time_t time_now;
	time(&time_now);
	set_k_time(time_now);

        Calendar<Gregorian> cal;  // XXX

/* =================== calendar2.3 =============================================

	std::cout << "----------------------------------------" << std::endl;
	
	//Calendar<Gregorian> cal;

	cal.set_date(2000, 12, 2);
	cal.add_event("Basketträning", 4, 12, 2000);
	cal.add_event("Basketträning", 11, 12, 2000);
	cal.add_event("Nyårsfrukost", 1, 1, 2001);
	cal.add_event("Första advent", 1); // år = 2000, månad = 12
	cal.add_event("Vårdagjämning", 20, 3); // år = 2000
	cal.add_event("Julafton", 24, 12);
	cal.add_event("Kalle Anka hälsar god jul", 24); // också på julafton
	cal.add_event("Julafton", 24); // En likadan händelse samma datum ska 
                                       // ignoreras och inte sättas in i kalendern
	cal.add_event("Min första cykel", 20, 12, 2000);
	cal.remove_event("Basketträning", 4);
	std::cout << cal; // OBS! Vårdagjämning och första advent är före nuvarande datum och skrivs inte ut
	
	std::cout << "----------------------------------------" << std::endl;
	cal.remove_event("Vårdagjämning", 20, 3, 2000);
	cal.remove_event("Kalle Anka hälsar god jul", 24, 12, 2000);

	cal.set_date(2000, 11, 2);
	if (! cal.remove_event("Julafton", 24)) {
		std::cout << " cal.remove_event(\"Julafton\", 24) tar inte" << std::endl; 
		std::cout << " bort något eftersom aktuell månad är november" << std::endl;
	}
	
	std::cout << "----------------------------------------" << std::endl;
	std::cout << cal;
	std::cout << std::endl << "---------Test copy constructor----------" << std::endl;
	Calendar<Gregorian> gregorian_cal;
	gregorian_cal.add_event("Hacking the db");
	gregorian_cal.add_event("Basketträning");
	gregorian_cal.add_event("Gymnastik");
	Calendar<Gregorian> greg_cal(gregorian_cal);

	std::cout << "Calendar<Gregorian> gregorian_cal;" << std::endl;
	std::cout << "jul_cal.add_event(\"Hacking the db\");" << std::endl;
	std::cout << "jul_cal.add_event(\"Basketträning\");;" << std::endl;
	std::cout << "jul_cal.add_event(\"Gymnastik\");" << std::endl;
	std::cout << "Calendar<Gregorian> greg_cal(gegorian_cal);" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << greg_cal;
*/

//############ Extra2.1 ########################################################
	
	std::cout << std::endl << "\n\t*** Extrauppgift 2.1 *** \n" << std::endl;

	// Test move_event() ===================================================

        /* metoden move_event() kan flytta händelser i kalendern genom att först
           plocka ut och sedan lägga till händelsen på det nya datumet. Om händel-
           sen inte finns i from alternativt redan finns i to returneras false. */

	std::cout << CYAN << "\n ####### Test move_event() ######## \n" << std::endl;

	Calendar<Gregorian> move_events;

	move_events.add_event("Test one", 24, 12, 2013);
	move_events.add_event("Test one", 25, 12, 2013);

	std::cout << "move_events.add_event(\"Test one\", 24, 12, 2013);" 
                  << std::endl;
	std::cout << "move_events.add_event(\"Test one\", 25, 12, 2013);" 
                  << std::endl;
	std::cout << "----------------------------------------\n" << std::endl;

	std::cout << move_events;

	if(!move_events.move_event(Gregorian(2013,12,24), Gregorian(2013,12,25), "Test one")) {

	    std::cout << "move_events.move_event(Gregorian(2013,12,24), Gregorian(2013,12,25), \"Test one\")"
                      << std::endl;
	    std::cout << "\t Failed since event exists on date to move to" << std::endl;
	}

	std::cout << "----------------------------------------\n" << std::endl;

	if(!move_events.move_event(Gregorian(2013,12,24), Gregorian(2013,12,25), "Test two")) {

	    std::cout << "move_events.move_event(Gregorian(2013,12,24), Gregorian(2013,12,25), \"Test two\")";
	    std::cout << std::endl << "\t Failed since event does not exists " << std::endl;
	}
	std::cout << "----------------------------------------\n" << std::endl;

	if(move_events.move_event(Gregorian(2013,12,24), Gregorian(2013,12,31), "Test one")) {
	    std::cout << "move_event(Gregorian(2013,12,24), Gregorian(2013,12,31), \"Test one\")" 
                      << std::endl;
	}
	std::cout << "----------------------------------------\n" << std::endl;

	std::cout << move_events;

	cal.set_format(Calendar<Gregorian>::list);

        // Test related events ===================================================

         /*
         En händelse ska kunna relateras till en annan händelse genom att man anger det
         antal dagar som skiljer dem åt. Flyttas händelsen kommer den relativa
         händelsen att flyttas också. Tas den bort så tas den relativa händelsen
         också bort. */

        std::cout << RESET << "\n ###### Test related events ##### \n" << std::endl;

	Calendar<Gregorian> related;
	Gregorian tday;

	if(related.add_event("Today")) 
            std::cout << "related.add_event(\"Today\")" << std::endl;

	if(related.add_related_event(tday, 10, "Today", "Ten days from today")) {
	    std::cout << "related.add_related_event(Gregorian(), 10, \"Today\", \"Ten days from today\")" 
                      << std::endl;
	}

	Gregorian ten_days; ten_days += 10;

	if(related.add_related_event(ten_days, -2, "Ten days from today", "Ten minus two days from today")) {
	    std::cout << "related.add_related_event(Gregorian() += 10, -2, \"Ten days from today\"";
	    std::cout << ", \"Ten minus two days from today\")" << std::endl;
	}

	std::cout << "----------------------------------------\n" << std::endl;
	std::cout << related;
	std::cout << "----------------------------------------\n" << std::endl;

	Gregorian tmr; ++tmr;
	if(related.move_event(tday, tmr, "Today")) {
		std::cout << "related.move_event(Gregorian(), ++Gregorian(), \"Today\")" 
                          << std::endl;
	}

	std::cout << "----------------------------------------\n" << std::endl;
	std::cout << related;
 

        // Test of reccuring events ============================================

        /* Ge möjlighet att lägga in återkommande händelser, t.ex. att julafton sker
           24:e december varje år och fäktning är det varje fredag. Man ska kunna
           ange hur länge händelsen ska återkomma annars är defaultvärdet 100. */

	std::cout << std::endl << YELLOW << "\n ###### Test recurring events ##### \n" 
                  << std::endl;

	Calendar<Gregorian> recurring_cal;

        // Julafton 2014,12,24
	std::cout << "recurring_cal.add_yearly_event(Gregorian(2014,12,24), \"Julafton\", 4)" 
                  << std::endl;
	recurring_cal.add_yearly_event(Gregorian(2014,12,24), "Julafton", 4);

        // Fencing Training 
	std::cout << "recurring_cal.add_weekly(Gregorian(), \"Fencing Training\", 5)" 
                  << std::endl;
	recurring_cal.add_weekly_event(Gregorian(), "Fencing Training", 5);

	std::cout << " ----------------------------------------\n" << std::endl;
 
        // show recurring events 
	std::cout << recurring_cal;

	std::cout << " ----------------------------------------\n" << std::endl;

	if(recurring_cal.remove_event("Julafton", 24, 12, 2014)) {
	    std::cout << " recurring_cal.remove_event(\"Julafton\", 2014,12,24)" 
                      << std::endl;
	}

	std::cout << "----------------------------------------\n" << std::endl;

	std::cout << recurring_cal;

	recurring_cal.remove_event("Fencing Training");
	
        // Test of birthdays ===================================================

        /* Ge möjlighet att lägga till födelsedagar så att kalendern räknar ut hur
           gamla födelsedagsbarnen är. I vår gregorianska kalender gäller att födel-
           se dagar 29/2 fyller år 28/2 nästa år. */

	std::cout << std::endl << CYAN << "\n ####### Test birthdays ####### \n" << std::endl;

	recurring_cal.add_birthday(Gregorian(1988, 7, 20), "Joakim", 3);
	recurring_cal.add_birthday(Gregorian(1988, 12, 16), "Pascal", 3);

	std::cout << "recurring_cal.add_birthday(Gregorian(1988, 7, 20), \"Joakim\", 10);" 
                  << std::endl;
	std::cout << "recurring_cal.add_birthday(Gregorian(1988, 12, 16), \"Pascal\", 10);" 
                  << std::endl;
	std::cout << "recurring_cal.add_birthday(Gregorian(2012, 2, 29), \"Leap boy\", 13)" 
                  << std::endl;

	recurring_cal.add_birthday(Gregorian(2012, 2, 29), "Leap boy", 9);

	std::cout << "\t----------------------------------------\n" << std::endl;
	std::cout << recurring_cal;
//

// ############## Extra2.2 #####################################################

	std::cout << std::endl << RESET << "\n\t**** Extrauppgift 2.2 **** \n" 
                  << std::endl;

	cal.set_date(2007,12,2);

        // 2000-12-20: Min andra cykel
        // 2000-12-24: Julafton
        cal.add_event(" Julafton", 24);
        cal.add_event(" Min andra cykel", 20, 12, 2007);

	cal.set_format(Calendar<Gregorian>::cal);
	std::cout << "----------------------------------------" << std::endl;
	std::cout << cal;
	
	cal.set_format(Calendar<Gregorian>::iCalendar);
	std::cout << "----------------------------------------\n" << std::endl;
	std::cout << cal;
	std::cout << "----------------------------------------\n" << std::endl;

	return 1;
//

};
