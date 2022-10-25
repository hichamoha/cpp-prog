#ifndef DEFAULTWEAPON_H
#define DEFAULTWEAPON_H

#include "weapon.h"

namespace camelot {
    class DefaultWeapon : public Weapon {

        public:
            DefaultWeapon();

            int weight() const;
            int volume() const;
            int price() const;
    };
}

#endif // DEFAULTWEAPON_H
