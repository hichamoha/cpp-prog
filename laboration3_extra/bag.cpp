#include "bag.h"

#include <iostream>
#include <cstdlib>       /* rand(), srand() */
#include <fstream>
#include <memory>

namespace camelot {

    //constructor ..............................................................
    Bag::Bag() 
    { 
        //objects = std::make_shared<std::vector<Object *>>(); 
        //objects(new std::vector<std::shared_ptr<Object>>());
        items = std::make_shared<std::vector<std::shared_ptr<Object>>>();
        //objects = new std::vector<Object *>();  // XXX

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
    
    //destructor ...............................................................
    Bag::~Bag() {
        //objects->clear();
        //delete this->items;
    }

    // weight() ................................................................
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
    //bool Bag::add(std::shared_ptr<Object> object) {
    bool Bag::add(Object &object) {

        int held_volume = 0;
        int held_weight = 0;

        for (std::vector<std::shared_ptr<Object >>::const_iterator it = items->begin(); 
        //for (std::vector<Object *>::const_iterator it = items->begin(); 
             it != items->end(); ++it) 
        {
            held_volume += (*it)->volume();
            held_weight += (*it)->weight();
        }
  
        //if (held_volume + object->volume() > get_hold_volume() ||
        //        held_weight + object->weight() > get_hold_weight()) {
        
        if (held_volume + object.volume() > get_hold_volume() ||
                held_weight + object.weight() > get_hold_weight()) {
            return false;
        }
 
        else {
            //this->items->push_back(object);
            //this->items->push_back(std::move(&object));
                                std::cout << "\t Items before are " << this->items->size() << std::endl;
            std::shared_ptr<Object> sp(&object);
            this->items->push_back(sp);
            //this->items->emplace_back(sp);
            			std::cout << "\t Items after are " << this->items->size() << std::endl;
            //this->items->push_back(&object);  // no matching function
            return true;
        }
    }

// remove() ..........................................................................
    //bool Bag::remove(std::shared_ptr<Object> obj) {
    bool Bag::remove(Object &obj) {

        std::vector<std::shared_ptr<Object>>::iterator it;
        //std::vector<Object *>::iterator it;
        for (it = items->begin(); it != items->end(); it++) {
        //for (const auto& it : items) {
            std::shared_ptr<Object> sp(&obj);
            if ((*it) == sp)
            //if ((*it) == &obj) 
            {
                items->erase(it);  //WHAT HAPPEN WITH THE OBJECT IN MEMORY TODO
                return true;
            }
        }
        return false;
    }

// saveObj() .............................................................................
    // creates an instance of ofstream (writing to files)
    // this output file stream is without name 
 
    void Bag::saveObj(std::fstream &ofs) 
    {
        ofs << "OBJ" << id << ":" << type() << ":"; 
        bool first = true;
        
        // for (auto it : items) {
        for (std::vector<std::shared_ptr<Object >>::iterator it = items->begin();
        //for (std::vector<Object *>::iterator it = items->begin(); 
             it != items->end(); it++) {
            std::cout << "Saving Item: " << (*it)->id << std::endl;
            if (first)
                first = false;
            else 
                ofs << ",";
            ofs << "OBJ" << (*it)->id;
        }

        ofs << ":" << weight() << "kg," << volume() << "liter," 
                    << price() << "kr" << std::endl;
        
        // for (auto it : items) {
        for (std::vector<std::shared_ptr<Object >>::iterator it = items->begin();
        //for (std::vector<Object *>::iterator it = items->begin(); 
             it != items->end(); it++) {
            (*it)->saveObj(ofs);
        }

    }
}
