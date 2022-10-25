#include "dragon.h"
#include <iostream>
#include <cstdlib>

namespace camelot {
    // constructor
    Dragon::Dragon(Environment * current_room, int hp, int strength) 
    { 
        std::cout << " \t A new white dragon 'Aithusa' is brought into existence !" 
                  << std::endl;
        this->hp = hp;
        this->strength = strength;
        // TODO: Perhaps we should move this up the inheritance tree?
        // might fit better in actor or something 
        this->current_room = current_room;
    }

    // eat() ...............................................................
    void Dragon::eat(Actor & actor) {
        actor.fight(*this);
    }
    
    // eat()
    void Dragon::eat(Food &) {
        std::cout << "Blaah" << std::endl;
    }

    // action() ...............................................................
    void Dragon::action() 
    {
        std::vector<std::string> exit_names = current_room->get_exit_names();

        switch (std::rand() % 3) {
            case 1: 
                go(exit_names[std::rand() % exit_names.size()]);
                break;

            default:
                break;
        }
    }

    // get_type() ..........................................................
    std::string Dragon::get_type() const {
        return "Dragon";
    }
    // get_name() .........................................................
    std::string Dragon::get_name() const {
        return "Aithusa";
    }

    /*
     * I have no idea how we should implement this
     */
    // fight() .............................................................
    void Dragon::fight(Actor &) {
        return;
    }
    // pick_up()
    bool Dragon::pick_up(Object *) {
        std::cout << "IIIHH" << std::endl;
        return false;
    }
    // drop()
    bool Dragon::drop(Object *) {
        std::cout << "IHHHHIIII" << std::endl;
        return false;
    }
    // talk_to()
    void Dragon::talk_to(Actor &) {
        std::cout << "SHREEK!" << std::endl;
    }
    // dataToFile()
    std::string Dragon::dataToFile() const {
        return "";
    }

}
