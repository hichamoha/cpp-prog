#include "bag.h"
#include <iostream>
#include <cstdlib>       /* rand(), srand() */
#include <fstream>

namespace camelot {
    //constructor
    Bag::Bag() 
    {
        objects = new std::vector<Object *>();

        /* NOTE: Call to rand() returns a value >= 0
           and < RAND_MAX, which is then converted to a number 
           >= 0 and < 150 using modulo arithmetic (operator %)
 
           // generates unsigned random integers in c++11
           // create default engine as source of randomness  
           // std::default_random_engine e; 
           // use engine to generate integral numbers between 100 and 150
           // uniform_real_distribution<double> u(100, 150); */

        // generate random number between 100 and 150
        hold_weight = std::rand() % 150 + 100;
        // generate random number between 100 and 150 ?!
        hold_volume = std::rand() % 50 + 100;
    }
    
    //destructor
    Bag::~Bag() {
        objects->clear();
        delete this->objects;
    }

    // weight()
    int Bag::weight() const {
        return 17;
    }
    
    // volume()
    int Bag::volume() const {
        return 50;
    }

    // price()
    int Bag::price() const {
        return 100;
    }

    // type()
    std::string Bag::type() const {
        return "Gold bag";
    }

    // get_hold_weight()
    int Bag::get_hold_weight() const {
        return this->hold_weight;
    }

    // get_hold_volume()
    int Bag::get_hold_volume() const {
        return this->hold_volume;
    }

// add() ..............................................................................
    bool Bag::add(Object & object) {
        int held_volume = 0;
        int held_weight = 0;

        for (std::vector<Object *>::const_iterator it = objects->begin(); 
             it != objects->end(); ++it) {
            held_volume += (*it)->volume();
            held_weight += (*it)->weight();
        }

        if (held_volume + object.volume() > get_hold_volume() ||
                held_weight + object.weight() > get_hold_weight()) {
            return false;
        } else {
            this->objects->push_back(&object);
            return true;
        }
    }
// remove() ..........................................................................
    bool Bag::remove(Object & object) {
        std::vector<Object *>::iterator it;

        for (it = objects->begin(); it != objects->end(); it++) {
            if ((*it) == &object) {
                objects->erase(it);
                return true;
            }
        }
        return false;
    }
// saveObj() .............................................................................
    // creates an instance of ofstream (writing to files)
    // this output file stream is without name 
 
    void Bag::saveObj(std::fstream & ofs) 
    {
        ofs << "OBJ" << id << ":" << type() << ":"; 
        bool first = true;
        
        // for (auto it : objects) {
        for (std::vector<Object *>::iterator it = objects->begin(); 
             it != objects->end(); it++) {
            std::cout << "Saving Object: " << (*it)->id << std::endl;
            if (first)
                first = false;
            else 
                ofs << ",";
            ofs << "OBJ" << (*it)->id;
        }
        ofs << ":" << weight() << "kg," << volume() << "liter," 
                    << price() << "kr" << std::endl;
        
        // for (auto it : objects) {
        for (std::vector<Object *>::iterator it = objects->begin(); 
             it != objects->end(); it++) {
            (*it)->saveObj(ofs);
        }

    }
}
