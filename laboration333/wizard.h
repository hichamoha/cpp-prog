#ifndef WIZARD_H
#define WIZARD_H

#include "human.h"
#include "wand.h"
#include "default_weapon.h"

#include <memory>

namespace camelot {

    class Wizard : public Human {

        private:
            int magic;
            int max_magic;

            //Wand * wand;
            std::shared_ptr<Wand> wand;

        public: 
            ~Wizard();
            Wizard(Environment *, bool, int, int);
            Wizard(Environment *, int, int, bool, int, int, int);

            virtual std::shared_ptr<Weapon> weapon();
            //virtual Weapon * weapon();

            virtual std::string get_name() const;
            virtual std::string get_type() const;
            virtual void action();
            virtual void talk_to(Actor &);

            virtual std::string dataToFile() const;


    };

}

#endif // WIZARD_H
