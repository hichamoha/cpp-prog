#include "actor.h"
#include "bag.h"
#include "default_weapon.h"
#include "game.h"
#include "commands.h"
#include "dragon_factory.h"
#include "goblin.h"
#include "dragon.h"
#include "wizard.h"

#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <memory>

namespace camelot 
    {
    int Actor::instances;

  // constructor ............................................................
    Actor::Actor() : id(instances) // Constructor initializer list
    {
        instances++;
        
        // auto current_weapon = new DefaultWeapon();
        current_weapon = std::make_shared<DefaultWeapon>();   //XXX
        //current_weapon = new DefaultWeapon();   // So everyone can try to fight,
        // ###### FIXME Remember to delete this in inherited classes constructors

        // container = make_shared<Container>();
        container = new Bag(); // XXX Derived-to-base conversion (Lippman 597)!?

        current_room = nullptr;

        Game::add_actor(*this);
    }

  // destructor --------------------------------------------------------------
    Actor::~Actor() 
    {   /*
        if (current_weapon->weight() == 0 && current_weapon->volume() == 0) {
            // In case its the default weapon, we dont want them laying around
            // TODO fix this with a cast perhaps?
            delete current_weapon;
        }
        */

        // since the actor exists no more we drop everything 
        // in the current room
        //std::vector<std::shared_ptr<Object>>::iterator it;
        //for (it = container->get_objects()->begin(); 
        //     it != container->get_objects()->end(); ++it) 
        std::vector<Object *>::iterator it;
        for (it = container->get_objects()->begin(); 
             it != container->get_objects()->end(); ++it) 
        {
            //current_room->drop(*it);
            current_room->drop(*it);
        }

        container->get_objects()->clear(); //TODO
        //clear() deletes all the elements in the vector, so it deletes only  
        //the pointers but the objects themselves stay in memory.

        current_room->drop(container);
        
        current_room->leave(*this);

        Game::remove_actor(*this);

        //delete current_weapon;
    }

  // pick_up() .................................................................
    bool Actor::pick_up(Object *object){
        return container->add(*object);
    }

  // drop() ..............................................................
    bool Actor::drop(Object *object) {
        return container->remove(*object);
    }

  // go() -----------------------------------------------------------------
    /*
     Takes this actor to the environment that the given exit leads
     to. However the exit must not be locked.
     
     param: exit_name The name of the exit to go through
     */
    void Actor::go(std::string exit_name) {

        Exit *exit = current_room->get_exit(exit_name);

        if (exit == 0) {
            std::cerr << "\t No such exit: " << exit_name << std::endl;
            return;
        }

        if (exit->is_locked() && this->get_type()=="Player" ) {
        //if (exit->is_locked()) { // && actor==player  XXX
            std::cerr << "\n\t Exit is locked..."
                      << "\n\t Unlock it in order to get through !" 
                      << std::endl;
            return;
        }

        Environment *new_room = exit->get_outfall();

        if (new_room == 0) {
            std::cerr << "\t That exit leads nowhere..." << std::endl;
            return;
        }

        // if everything is in order, let the actor follow the exit
        current_room->leave(*this);
        current_room = new_room;
        current_room->enter(*this);

        std::cerr << "\n\t" << get_name() << " entered " << exit_name 
                  << std::endl;
    }

  // fight() ............................................................
    void Actor::fight(Actor &opponent) {
        Commands::fight(*this, opponent);
    }

  // weapon() ............................................................
    std::shared_ptr<Weapon> Actor::weapon() {
    //Weapon * Actor::weapon() {
        if (current_weapon == 0) {
            std::cerr << " \t ERROR HERE. Actor::weapon() in actor.cpp" 
                      << std::endl;
        }
        return current_weapon; // caller must delete the memory !? 
    }

  // saveAct() ----------------------------------------------------------------
    void Actor::saveAct(std::fstream &ofs) 
    {
        ofs << "ACT" << id << ":" << get_type() << ":" << get_name() << ":";
        ofs << "current_room=" << current_room->id;
        ofs << ",container=" << container->id;
        ofs << ",hp=" << hp;
        ofs << ",strength=" << strength;

        if (dataToFile().length() > 0) { //#######  FIXME 
            ofs << "," << dataToFile();
        }

        // redundant
        ofs << ":OBJ" << container->id;
        ofs << std::endl;

        container->saveObj(ofs);
    }

  // loadAct() ----------------------------------------------------------------
    /* Loads an actor object from the specified string.
       param: line, A line describing the object to load
       return: A pointer to a the created instance
     */
    Actor* Actor::loadAct(const std::string line, 
                           const std::map<std::string, Environment *> & envs,
                           const std::map<std::string, Object *> & objs) 
    {
        std::istringstream input(line);
        std::vector<std::string> tokens;
        std::string token;

        /*getline() extracts characters from input, a line, and stores them into
          token until the delimitation character ':' is found.*/

        // divide every line by ':' in different tokens
        // the while loop reads the line using getline 
        while (std::getline(input, token, ':')) {
            tokens.push_back(token);
        }

        // extract properties (a map)
        std::map<std::string, std::string> properties;

        std::istringstream pss(tokens[3]);
        while (std::getline(pss, token, ',')) 
        {
            size_t eq_sign = token.find('=');
            // properties.insert({});
            properties.insert(std::pair<std::string, 
                              std::string>(token.substr(0, eq_sign), 
                              token.substr(eq_sign+1)));
        }

        // find type
        std::string & type = tokens[1];

        std::map<std::string, std::string>::iterator prop_it;
        std::map<std::string, Environment *>::const_iterator env_it;
        std::map<std::string, Object *>::iterator obj_it;

        // auto prop_it = properties.find("current_room")->second;
        std::string current_room_id = properties.find("current_room")->second;
        Environment * current_room = envs.find(current_room_id)->second;

        int hp = str2int(properties.find("hp")->second);
        int strength = str2int(properties.find("strength")->second);
        Actor *actor = nullptr;

        if (type == "Human") {
            // abstract!
        }
        else if (type == "Player") {
            bool has_heart = str2int(properties.find("has_heart")->second) != 0;
            int max_health = str2int(properties.find("max_health")->second);

            actor = new Player(current_room, hp, strength, has_heart, max_health);
        } 
        else if (type == "Wizard") {
            bool has_heart = str2int(properties.find("has_heart")->second) != 0;
            int max_health = str2int(properties.find("max_health")->second);
            int magic = str2int(properties.find("magic")->second);
            int max_magic = str2int(properties.find("max_magic")->second);

            
            actor = new Wizard(current_room, hp, strength, has_heart, 
                               max_health, magic, max_magic);
        } 
        else if (type == "Goblin") {
            actor = new Goblin(current_room, hp, strength);
        } 
        else if (type == "Dragon") {
            actor = new Dragon(current_room, hp, strength);
        }
        else if (type == "DragonFactory") {
            int frequency = str2int(properties.find("frequency")->second);

            actor = new DragonFactory(current_room, frequency);
        }
        else {
            std::cerr << "Unrecognized actor type: " << type << std::endl;
        }

        // set general Actor properties, not already set
        std::string container_id = properties.find("container")->second;
        Object * cont_obj = objs.find(container_id)->second;
 
        //Container *cont;
        /* NOTE: Pointer-Type dynamic_cast (Lippman 825): The dynamic_cast operator
           performs type conversions at run time. It guarantees the conversion
           of a pointer to a BASE class to a pointer to a DERIVED class (Downcasts) */

        // if (Derived *dp = dynamic_cast<Derived*>(bp)) {
        if (Container *cont = dynamic_cast<Container *>(cont_obj)) { 
            actor->container = cont;
        }

        return actor;
    }

// str2int() ...................................................................
    /*
      Quickly converts the specified string to an integer.
      param: str The string to convert
      return: The converted integer
     */
    int Actor::str2int(std::string str) 
    {
        std::istringstream iss(str);
        int number; 
        iss >> number;

        return number;
    }


}
