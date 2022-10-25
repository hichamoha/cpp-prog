#ifndef WEAPON_H
#define WEAPON_H

#include "object.h"

namespace camelot {

    class Weapon : public Object  {

        public:
            // Destructor: 
            // Base classes ordinarily should define a virtual destructor.
            virtual ~Weapon() {};

            Weapon(unsigned int, float); // Weapon(attack_strength, hit_ratio)

            virtual int weight() const = 0;
            virtual int volume() const = 0;
            virtual int price() const = 0;

            virtual std::string type() const;
            virtual int attack_strength() const;
            virtual float hit_ratio() const;

            virtual void saveObj(std::fstream &);


        protected:
            unsigned int strength;
            float ratio;
    };

}

#endif
