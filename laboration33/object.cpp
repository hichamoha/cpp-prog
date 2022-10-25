#include <iostream>
#include <sstream>

#include "object.h"
#include "food.h"
#include "bag.h"
#include "excalibur.h"
#include "key.h"

/* NOTE: Objects should always be owned by exactly one of the following:
         an Environment, a Container, an Actor
         In that way it is easier to make sure that no objects are causing
         MEMORY LEAK or unexpected null references. We thereby implement
         the ownership semantics from unique_ptr; there is always exactly 
         one object owning another object.
         If an object is to be deleted, only the owning object is allowed 
         to do that and it is also responsible for removing the pointer to 
         to that object */ 

namespace camelot {

    int Object::instances;

    // constructor
    Object::Object() : id(instances) {
        instances++;
    }
    // operator==() .............................................
    bool Object::operator==(Object & obj) const {
        return obj.id == this->id;
    }

    // loadObj() ....................................................
    /*
     * OBJ1:Gold bag::17kg,50liter,100kr
     * OBJ10:Gold bag::17kg,50liter,100kr
     * OBJ12:Gold bag::17kg,50liter,100kr
     * OBJ14:Gold bag:OBJ15:17kg,50liter,100kr
     * OBJ2:Gold bag::17kg,50liter,100kr
     * OBJ3:Gold bag::17kg,50liter,100kr
     * OBJ4:Gold bag::17kg,50liter,100kr
     * OBJ7:Key (cave):1kg,1liter,50kr
     * OBJ5:Mat:5kg,16liter,94kr,47food
     * OBJ8:excalibur:5kg,5liter,1000kr
     * OBJ6:Key (e1):1kg,1liter,50kr
     * OBJ7:Key (cave):1kg,1liter,50kr
     */
    Object * Object::loadObj(std::string line) 
    {

        line = line.substr(line.find_first_of(':')+1);
        std::string type = line.substr(0,line.find_first_of(':'));

        if (type == "Gold bag") {
            return new Bag();
            // Ladda in object
        }
        else if (type == "Mat") {
            std::string tmp = line.substr(line.find_last_of(',')+1);
            tmp = tmp.substr(0,tmp.length()-4);
            std::istringstream stream(tmp);
            int food;
            stream >> food;
            return new Food(food);
        }
        //  Excalibur:5kg,5liter,1000kr,1000strength,0.95ratio
        //else if (type == "The sword Excalibur") {
        else if (type == "Excalibur") {
            std::string ratio = line.substr(line.find_last_of(',')+1);
            ratio = ratio.substr(0,4);

            std::string strength = line;
            strength = strength.substr(strength.find_first_of(',')+1);
            strength = strength.substr(strength.find_first_of(',')+1);
            strength = strength.substr(strength.find_first_of(',')+1);
            strength = strength.substr(0,strength.find_first_of('s'));
            int str;
            float rat;
            std::istringstream stream(strength);
            stream >> str;
            std::istringstream iss(ratio);
            iss >> rat;
            return new Excalibur(str, rat);
        }
        else if (type.substr(0,3) == "Key") {
            std::string name = line.substr(line.find_first_of('(')+1);
            name = name.substr(0,name.find_first_of(')'));
            return new Key(name);
        }
        else {
            std::cout << "Got type:" << type << std::endl;
            std::cout << "From line:" << line << std::endl;
        }
        return nullptr;
    }
}
