#include "excalibur.h"
#include <stdexcept>

namespace camelot {
    // constructor
    Excalibur::Excalibur(unsigned int attack, float ratio) : Weapon(attack, ratio) {
        // this->strength = attack;
        // if (ratio >= 0 && ratio <= 1) {
            // this->ratio = ratio;
        // }
        // else {
            // // Shouldnt happen
            // this->ratio = 0;
            // throw std::out_of_range("index out of range");
        // }
    }

    int Excalibur::weight() const {
        return 5;
    }

    // volume()
    int Excalibur::volume() const {
        return 5;
    }

    // price()
    int Excalibur::price() const {
        return 1000;
    }

    // type()
    std::string Excalibur::type() const {
       return "Excalibur";
    }
       
       
}
