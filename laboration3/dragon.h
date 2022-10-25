#ifndef DRAGON_H
#define DRAGON_H

#include "actor.h"
#include "food.h"

namespace camelot {
    
    class Dragon : public Actor {
        public:
            Dragon(Environment *, int, int);

            void eat(Actor &);
            void eat(Food &);

            virtual void action();
            virtual std::string get_type() const;
            virtual std::string get_name() const;
            virtual void fight(Actor &);
            virtual bool pick_up(Object *);
            virtual bool drop(Object *);
            virtual void talk_to(Actor &);

            virtual std::string dataToFile() const;
    };
}
#endif // DRAGON_H
