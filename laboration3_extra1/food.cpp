#include "food.h"

namespace camelot {
    // constructor
    Food::Food(int food) 
    {
        food_left = food;
    }

    // destructor
    //Food::~Food() {delete this;}

    // health_increase()
    int Food::health_increase() 
    {
        int tmp = food_left;
        food_left = 0;
        return tmp;
    }

    // weight()
    int Food::weight() const 
    {
        return food_left/10+1;
    }
 
    // volume()
    int Food::volume() const 
    {
        return food_left/3+1;
    }

    // price()
    int Food::price() const 
    {
        return food_left*2;
    }

    // type()
    std::string Food::type() const {
        return "Mat";
    }

    // saveObj()
    void Food::saveObj(std::fstream & ofs) 
    {
        ofs << "OBJ" << id << ":" << type(); 
        ofs << ":" << weight() << "kg," << volume() 
            << "liter," << price() << "kr," 
            << food_left << "food" << std::endl;
    }

}
