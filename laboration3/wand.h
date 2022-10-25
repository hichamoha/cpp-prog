#ifndef WAND_H
#define WAND_H

#include "weapon.h"

namespace camelot {

    class Wand : public Weapon  {

        public:
            Wand(unsigned int, float); // Weapon(attack_strength, hit_ratio)
            virtual int weight() const;
            virtual int volume() const;
            virtual int price() const;
            virtual std::string type() const;
            virtual int magic_cost() const;
    };

}

#endif
