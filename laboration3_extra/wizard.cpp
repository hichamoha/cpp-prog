#include <iostream>
#include <sstream>
#include <memory>

#include "wizard.h"

namespace camelot {
// constructor1
    Wizard::Wizard(Environment * env, bool has_heart, int max_health, int max_magic)
        : Human(has_heart, max_health), magic(max_magic), max_magic(max_magic) 
    {
            this->hp = 150;
            this->strength = 3;
            this->current_room = env;

            //this->wand = new Wand(50, 0.9);
            this->wand = std::make_shared<Wand>(50, 0.9);  //XXX
            //std::cout << " A magician has been born, with full magic power.. Kazaaam!" 
            //         << std::endl;

            env->enter(*this);  // ##################
    }

// constructor2
    Wizard::Wizard(Environment * env, int hp, int strength, bool has_heart, 
                   int max_health, int magic, int max_magic)
            : Human(has_heart, max_health), magic(magic), max_magic(max_magic) 
    {
            this->hp = hp;
            this->strength = strength;
            this->current_room = env;

            this->wand = std::make_shared<Wand>(50, 0.9); //XXX
            //this->wand = new Wand(50, 0.9);

            current_room->enter(*this);
    }

// destructor
    Wizard::~Wizard() {
        container->remove(*wand);
        //delete wand; // XXX we give the responsability for this memory to shared_ptr
    }

// action() ........................................................................
    void Wizard::action() {
        magic += 5;
        if (magic >= max_magic)
            magic = max_magic;
    }

// weapon() .....................................................................
    std::shared_ptr<Weapon> Wizard::weapon()
    //Weapon * Wizard::weapon() 
    {
        if (magic >= wand->magic_cost()) {
            magic -= wand->magic_cost();
            //we must EXPLICITLY bind a shared_ptr to the pointer we want to return.
            //return std::shared_ptr<Wand>(wand);  //FIXME
            return wand;
        }
        else {
            // Not enough magic to use wand, using default-weapon
            return current_weapon;
        }
    }

// get_type() ..................................................................
    std::string Wizard::get_type() const {
        return "Wizard";
    }

// get_name() .................................................................
    std::string Wizard::get_name() const {
        return "Lady Morgana";
    }

// talk_to() ...............................................................
    void Wizard::talk_to(Actor &)  {
        std::cout << "zoom zoom zoom" << std::endl;
    }

// dataToFile() ...............................................................
 /* In computer science, in the context of data storage and transmission, 
    Serialization is the process of translating of DATA STRUCTURE or OBJECT 
    state into a format that can be stored(for example, in a FILE or memory 
    buffer, or transmitted across a network connection link) and resurrected 
    later in the same or another computer environment. On most modern Operating
    system, files are organized into one-dimensioned ARRAYS of bytes. 
 */
    std::string Wizard::dataToFile() const 
    {
        std::ostringstream oss;

        oss << Human::dataToFile();
        oss << ",magic=" << magic;
        oss << ",max_magic=" << max_magic;

        return oss.str();
    }
}
