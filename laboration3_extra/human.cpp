#include <iostream>
#include <sstream>

#include "human.h"


namespace camelot {

    // constructor
    Human::Human(bool has_heart, int max_health) : 
           has_heart(has_heart), max_health(max_health) {
        hp = 100;
    }

    // action() ..........................................................
    void Human::action() {
        if (!has_heart) {
            // Undead, fast regen
            hp *= 2;
        }
        std::cout << "Ruuunning!" << std::endl;
    }

    // get_type() .....................................................
    std::string Human::get_type() const {
        return "Human";
    }

    // eat() ..........................................................
    void Human::eat(Food &food) {
        std::cout << "Yum, yum!...It is DELICIOUS ! " 
                  << std::endl;
        hp += food.health_increase();

        if (hp > max_health)
            hp = max_health;
    }

    // dataToFile() ...................................................
    /* gives the file format of 'has_heart' and 'max_health' that can be
       stored and resurrected later. */
    std::string Human::dataToFile() const 
    {
        std::ostringstream oss;

        oss << "has_heart=" << has_heart;
        oss << ",max_health=" << max_health;

        return oss.str();
    }

}

