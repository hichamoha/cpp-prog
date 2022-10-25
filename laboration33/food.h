#ifndef FOOD_H
#define FOOD_H

#include "object.h"

namespace camelot {

    class Food : public Object  {

        public:
            Food(int);
            virtual int health_increase();

            virtual int weight() const;
            virtual int volume() const;
            virtual int price() const;

            virtual std::string type() const;
            virtual void saveObj(std::fstream &);

        protected:
            int food_left;
    };

}

#endif
