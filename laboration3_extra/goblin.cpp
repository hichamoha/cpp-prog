#include "goblin.h"
#include "human.h"

#include <iostream>
#include <cstdlib>

namespace camelot {

    // constructor
    Goblin::Goblin(Environment *current_room, int hp, int strength) { 
        this->hp = hp;
        this->strength = strength;

        // TODO: Perhaps we should move this up the inheretance tree?
        // might fit better in actor or something 
        this->current_room = current_room;

        current_room->enter(*this);
    }

    // destructor
    //Goblin::~Goblin() { delete this;}

    // eat() .....................................................................
    void Goblin::eat(Actor &) {
        std::cout << "I dont like food, I have an insatiable lust for gold."
                  << "I love licking gold coins" << std::endl;
    }

    // eat()
    void Goblin::eat(Food &food) {
        hp += food.health_increase();
    }

    // action() ....................................................................
    void Goblin::action() {
        std::vector<std::string> exit_names = current_room->get_exit_names();

        switch (std::rand() % 5) {
            case 1: 
                go(exit_names[std::rand() % exit_names.size()]);
                break;

            case 2:
            {
                std::vector<Actor *> actors = current_room->get_actors();
                std::vector<Actor *>::iterator it = actors.begin();

                for (; it != actors.end(); ++it) {
                     Human *human = dynamic_cast<Human *>(*it); //transformare a Human for fighting

                     if (human != nullptr) 
                     {
                        fight(**it);
                        break;
                     }
                }
             }
                break;

            default:
                break;
        }

    }

    // get_type() ....................................................................
    std::string Goblin::get_type() const {
        return "Goblin";
    }

    // get_name()
    std::string Goblin::get_name() const {
        //return "The angry Goblin Gaius";
        return "The angry Goblin";
    }

    bool Goblin::pick_up(Object *) {
        std::cout << "I'm a mischievous, humanoid creature, I dont have any pockets" 
                  << std::endl;
        return false;
    }

    bool Goblin::drop(Object *) {
        std::cout << "Watch out! I can transform myself into a small bright ball of light" 
                  << std::endl;
        return false;
    }

    void Goblin::talk_to(Actor & actor) {
        std::cout << "you cannot wrestle me back into the box!" 
                  << "\nI will turn you into a half-donkey "<< std::endl;
        actor.fight(*this);
    }

    std::string Goblin::dataToFile() const {
        return "";
    }

}
