#include "player.h"
#include "terminal.h"

#include <iostream>
#include <sstream>

namespace camelot {
// constructor1
    Player::Player(Environment *room) : Human(false, 500) 
    {
        this->current_room = room;
        this->hp = 100;
        this->strength = 2;
    }
// constructor2
    Player::Player(Environment * room, int hp, int strength, 
                   bool has_heart, int max_health) : Human(has_heart, max_health)  
    {
            this->current_room = room;
            this->hp = hp;
            this->strength = strength;
    }
// destructor
    Player::~Player() {
        // Player has lost :(
        // check the destructor when player is dead...it isn't used !? FIXME
        std::cerr << " Destrukting player" << std::endl;
        //delete current_room;
    }
// action() -----------------------------------------------------------------------
    void Player::action(){
        std::stringstream s;
        s << " \n\t HP = " << hp;
        Terminal::print(s.str()); //######### FIXME
    }
// get_type() ..................................................................
    std::string Player::get_type() const{
        return "Player";
    }
// get_name() ..................................................................
    std::string Player::get_name() const{
        return "Merlin";
    }

// fight()
    void Player::fight(Actor &){}

// talk_to() ...................................................................
    void Player::talk_to(Actor & actor){
        if (&actor == this) {
            std::cout << " \t Hello Emrys !?" << std::endl;
            return;
        }
        std::cout << " Hello " << actor.get_name() << std::endl;
        actor.talk_to(*this);
    }
// get_room() ..................................................................
    Environment * Player::get_room() const {
        return current_room;
    }
// dataToFile() .................................................................
    std::string Player::dataToFile() const {
        return Human::dataToFile();
    }
}
