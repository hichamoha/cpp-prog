#ifndef DRAGON_FACTORY_H
#define DRAGON_FACTORY_H

#include "actor.h"

namespace camelot {

    class DragonFactory : public Actor {
        public:
            DragonFactory(Environment *, int);

            virtual void action();

            virtual std::string get_name() const;
            virtual std::string get_type() const;
            virtual void go(std::string);
            virtual void fight(Actor &);
            virtual void talk_to(Actor &);

            virtual std::string dataToFile() const;

        private:
            unsigned int frequency;
            unsigned int age;
    };
}
#endif // DRAGON_FACTORY_H
