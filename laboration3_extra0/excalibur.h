#ifndef EXCALIBUR_H
#define EXCALIBUR_H

#include "weapon.h"

namespace camelot {

    class Excalibur : public Weapon  {

        public:
            Excalibur(unsigned int, float); // Weapon(attack_strength, hit_ratio)

            virtual int weight() const;
            virtual int volume() const;
            virtual int price() const;
            virtual std::string type() const;
             
            //float hit_ratio() const;
    };

}

#endif
