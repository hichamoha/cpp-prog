/*
 * Driver for cprog11lab22c.
 * Original written 2006-10-03 by Gunnar Kreitz <gkreitz>
 * modified by alba and zalenski
 *
 * If you need to modify this file to solve the assignment, you're most likely
 * solving it the wrong way.
 */

#include "julian.h"
#include "gregorian.h"
#include "kattistime.h"
#include "gregorian.h"
#include "julian.h"
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <sstream>

using std::size_t;
using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

using lab2::Julian;
using lab2::Gregorian;
using lab2::Date;

static int linenr = 0;

// Anonymous namespace for local variables and functions
namespace {
	std::vector<Date *> dates;

	size_t read_idx_or_die() {
		size_t ret;
		//! if(scanf("%zu", &ret) != 1) {
		//! 	assert(!"Tried to read idx but failed");
		//! }
        cin >> ret;
		assert(ret < dates.size());
		return ret;
	}

	int read_int_or_die() {
		int ret;
		//! if(scanf("%d", &ret) != 1) {
		//! 	assert(!"Tried to read int but failed");
		//! }
        cin >> ret;
		return ret;
	}

	template<class D> void new_date() {
		int y, m, d;
        string tmp;
		try {
            getline(cin, tmp);
            stringstream ss(tmp);
            ss >> y >> m >> d;
			if(ss) {
				dates.push_back(new D(y,m,d));
			} else {
				dates.push_back(new D());
			}
			cout << "D" << dates.size() - 1  << ":" << *dates[dates.size()-1] << endl;
		} catch (std::out_of_range oor) {
			cout <<"exception_in_constructor " << tmp << endl;
		}
	}

	template<class D> void new_date_copy() {
		const size_t idx = read_idx_or_die();
		try {
			dates.push_back(new D(*const_cast<const Date*>(dates[idx])));
			cout << "D" << dates.size() - 1  << "(D" << idx << ") " << *dates[dates.size()-1] << endl;
		} catch (std::out_of_range oor) {
			cout <<"exception_in_constructor " << endl;
		}
	}
}

int main(int argc, char **argv) {

    std::string command;
    std::string line;
    while(std::cin >> line >> command) {
        linenr++;
        cout << "L" << linenr << ";";

		if(command == "julian") {
			new_date<Julian>();
		} else if(command == "juliancopy") {
			new_date_copy<Julian>();
		} else if(command == "gregorian") {
			new_date<Gregorian>();
		} else if(command == "gregoriancopy") {
			new_date_copy<Gregorian>();
		} else if(command == "copy") {
			const size_t from = read_idx_or_die();
			const size_t to = read_idx_or_die();
			try {
				(*dates[to]) = *const_cast<const Date*>(dates[from]);
                cout << "D" << to  << "=D" << from << " " << *dates[to] << endl;
			} catch (std::out_of_range oor) {
				cout << " D" << to << "exception_when_copying from D" << from << " to D" << to << endl;
			}
		} else if(command == "delete") {
			const size_t idx = read_idx_or_die();
            cout << "D" <<  idx << " deleted " << *const_cast<const Date*>(dates[idx]) <<endl;
			delete dates[idx];
			dates[idx] = 0;
		} else if(command == "print") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " printed " << *const_cast<const Date*>(dates[idx]) << endl;
		} else if(command == "year") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " year=" <<const_cast<const Date*>(dates[idx])->year() << endl;
		} else if(command == "month") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " month=" <<const_cast<const Date*>(dates[idx])->month() << endl;
		} else if(command == "day") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " day=" <<const_cast<const Date*>(dates[idx])->day() << endl;
		} else if(command == "week_day") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " week_day=" <<const_cast<const Date*>(dates[idx])->week_day() << endl;
		} else if(command == "days_per_week") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " days_per_week=" <<const_cast<const Date*>(dates[idx])->days_per_week() << endl;
		} else if(command == "days_this_month") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " days_this_month=" <<const_cast<const Date*>(dates[idx])->days_this_month() << endl;
		} else if(command == "months_per_year") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " months_per_year=" <<const_cast<const Date*>(dates[idx])->months_per_year() << endl;
		} else if(command == "week_day_name") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " week_day_name=" <<const_cast<const Date*>(dates[idx])->week_day_name() << endl;
		} else if(command == "month_name") {
			const size_t idx = read_idx_or_die();
			cout << " D" << idx << " month_name=" <<const_cast<const Date*>(dates[idx])->month_name() << endl;
		} else if(command == "d++") {
			const size_t idx = read_idx_or_die();
			try {
				++(*dates[idx]);
				cout << "D" << idx << " ++ " << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << " D" << idx << " exception_in_++" << endl;
			}
		} else if(command == "d--") {
			const size_t idx = read_idx_or_die();
			try {
				--(*dates[idx]);
				cout << "D" << idx << " -- " << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << " D" << idx << " exception_in_--" << endl;
			}
		} else if(command == "d+=") {
			const size_t idx = read_idx_or_die();
			const int val = read_int_or_die();
			try {
				(*dates[idx]) += val;
				cout << "D" << idx << " += " << val << " " << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << " D" << idx <<" exception_in_+=" << endl;
			}
		} else if(command == "d-=") {
			const size_t idx = read_idx_or_die();
			const int val = read_int_or_die();
			try {
				(*dates[idx]) -= val;
				cout << "D" << idx << " -= " << val << " " << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << " D" << idx << ";" <<"exception_in_-=" << endl;
			}
		} else if(command == "chained") {
			const size_t idx = read_idx_or_die();
			try {
				/*
				 * Subtracts two days. The reason for doing it this very odd way
				 * is to test that prefix and postfix increment/decrement seem to
				 * work properly when chained.
				 *
				 * I know it's ugly, but adding parenthesis or spaces doesn't really
				 * help all that much. Sorry.
				 */
				----------++++++++--++--++--++(*dates[idx]);
				cout << "D" << idx << " ----------++++++++--++--++--++ " << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << " D" << idx << " " <<"exception_in_++--++" << endl;
			}
		} else if(command == "add_year") {
			const size_t idx = read_idx_or_die();
			int val = 0;
			try {
                string tmp;
                getline(cin, tmp);
                stringstream ss;
                ss << tmp;
                ss >> val;
				if(ss) {
					dates[idx]->add_year(val);
				} else {
					dates[idx]->add_year();
				}
				cout << "D" << idx << " added " << val << " years " << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << " D" << idx << " " <<"exception_in_add_year" << endl;
			}
		} else if(command == "add_month") {
			const size_t idx = read_idx_or_die();
			int val = 0;
			try {
                string tmp;
                getline(cin, tmp);
                stringstream ss;
                ss << tmp;
                ss >> val;
				if(ss) {
					dates[idx]->add_month(val);
				} else {
					dates[idx]->add_month();
				}
				cout << "D" << idx << " added " << val << " months " << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << " D" << idx << ";" <<"exception_in_add_month" << endl;
			}
		} else if(command == "d==") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << " D" << lhs << " == D" << rhs 
                 << (((*const_cast<const Date*>(dates[lhs])) == (*const_cast<const Date*>(dates[rhs]))) ? " TRUE" : " FALSE") << endl;
		} else if(command == "d!=") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << " D" << lhs << " != D" << rhs 
                 << (((*const_cast<const Date*>(dates[lhs])) != (*const_cast<const Date*>(dates[rhs]))) ? " TRUE" : " FALSE") << endl;
		} else if(command == "d<") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << " D" << lhs << "<D" << rhs 
                 << (((*const_cast<const Date*>(dates[lhs])) < (*const_cast<const Date*>(dates[rhs]))) ? " TRUE":" FALSE") << endl;
		} else if(command == "d<=") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << " D" << lhs << "<=D" << rhs 
                 <<(((*const_cast<const Date*>(dates[lhs])) <= (*const_cast<const Date*>(dates[rhs]))) ? " TRUE":" FALSE") << endl;
		} else if(command == "d>") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << " D" << lhs << ">D" << rhs 
                 <<(((*const_cast<const Date*>(dates[lhs])) > (*const_cast<const Date*>(dates[rhs]))) ? " TRUE":" FALSE") << endl;
		} else if(command == "d>=") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << " D" << lhs << ">=D" << rhs 
                 <<(((*const_cast<const Date*>(dates[lhs])) >= (*const_cast<const Date*>(dates[rhs]))) ? " TRUE":" FALSE") << endl;
		} else if(command == "d-") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << " D" << lhs << "-D" << rhs << " = "  
                 <<((*const_cast<const Date*>(dates[lhs])) - (*const_cast<const Date*>(dates[rhs]))) << endl;
		} else if(command == "mod_julian_day") {
			const size_t lhs = read_idx_or_die();
			cout << " D" << lhs << " mod_julian_day=" <<const_cast<const Date*>(dates[lhs])->mod_julian_day() << endl;
		} else if(command == "set_k_time") {
			time_t time = 0;
			if(!(std::cin >> time))
				assert(!"Can't read time");
			set_k_time(time);
            cout << "D set_k_time " << time << endl;
		} else {
			assert(!"Unknown command");
		}
	}

	return 0;
}
