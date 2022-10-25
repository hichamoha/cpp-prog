#include "weapon.h"
#include <stdexcept>

namespace camelot {
    //constructor
    Weapon::Weapon(unsigned int attack, float ratio) {
        this->strength = attack;
        if (ratio >= 0 && ratio <= 1) {
            this->ratio = ratio;
        }
        else {
            // Shouldnt happen
            this->ratio = 0;
            throw std::out_of_range(" Index out of range !");
        }
    }
  
    // type() ......................................................
    std::string Weapon::type() const {
        return "Weapon";
    }

    // attack_strength() ...........................................
    int Weapon::attack_strength() const {
        return strength;
    }

    // hit_ratio() ................................................
    float Weapon::hit_ratio() const {
        return ratio;
    }

    // saveObj() ....................................................
    void Weapon::saveObj(std::fstream & ofs) {
        ofs << "OBJ" << id << ":" << type(); 
        ofs << ":" << weight() << "kg," << volume() << "liter," 
             << price() << "kr," << strength << "strength," 
             << ratio << "ratio" << std::endl;

    }
}
