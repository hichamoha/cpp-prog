#include <iostream>
#include <sstream>

#include "dragon_factory.h"
#include "dragon.h"
#include "game.h"

namespace camelot {
  //constructor
  DragonFactory::DragonFactory(Environment * env, int freq) : 
                                frequency(freq), age(0) 
  {
    this->current_room = env;
    this->hp = 1000;
    this->strength = 0;

    current_room->enter(*this);
  }

  // action() ................................................................
  void DragonFactory::action() 
  {
    age++;
    if (age % frequency == 0) {
      //std::shared_ptr<Dragon> drag = std::make_shared<Dragon>(current_room, 3*age, 2*age);
      Dragon * drag = new Dragon(current_room, 3*age, 2*age); //FIXME unique_ptr,shared_ptr
      current_room->enter(*drag);
    }
  }

  // get_name() ..........................................................   
  std::string DragonFactory::get_name() const {
        return "Dragon factory";
    }

  // get_type() .........................................................
  std::string DragonFactory::get_type() const {
        return "DragonFactory";
    }

  // go() .............fight()  ..............talk_to()    ..............
  void DragonFactory::go(std::string) {
    }

  // fight()  
  void DragonFactory::fight(Actor &) {

    }

  //talk_to()
  void DragonFactory::talk_to(Actor &) {

    }

  // dataToFile()......................................................
  // to serialize, translate data to file format, to help save() 
  std::string DragonFactory::dataToFile() const 
  {
        std::ostringstream oss;
        oss << "frequency=" << frequency;
        oss << ",age=" << age;

        return oss.str();
    }
}

