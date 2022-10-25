#ifndef HUMAN_H
#define HUMAN_H

#include "actor.h"
#include "food.h"

namespace camelot {

    class Food;

    class Human : public Actor {

      public:
            Human(bool, int); 

            virtual void action();
            virtual std::string get_type() const;
            virtual std::string dataToFile() const;

            void eat(Food &);

      protected:
            bool has_heart;
            int max_health;  // maximalt kroppspoäng-liv  
    };
}
#endif // HUMAN_H
