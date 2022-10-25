#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <iomanip>
#include <functional>

#include "commands.h"

namespace camelot {
    Player * Commands::player;

// constructor .................................................................
    Commands::Commands(Player * pl) {
        Commands::player = pl; // define and initialize a static data member

        Terminal::add_function(std::string("exit"), &Commands::exit);
        Terminal::add_function(std::string("quit"), &Commands::exit);
        Terminal::add_function(std::string("go"), &Commands::go);
        Terminal::add_function(std::string("fight"), &Commands::fight);
        Terminal::add_function(std::string("pick_up"), &Commands::pick_up);
        Terminal::add_function(std::string("drop"), &Commands::drop);
        Terminal::add_function(std::string("talk_to"), &Commands::talk_to);
        Terminal::add_function(std::string("help"), &Commands::help);
        Terminal::add_function(std::string("inventory"), &Commands::inventory);
        Terminal::add_function(std::string("use"), &Commands::use);
        Terminal::add_function(std::string("save"), &Commands::save);
        Terminal::add_function(std::string("load"), &Commands::load);
    }
// exit() ......................................................................
    int Commands::exit(std::string) {
        return 1;
    }
// save() ......................................................................
    int Commands::save(std::string) {
        return 2;
    }
// load() ......................................................................
    int Commands::load(std::string) {
        return 3;
    }
// go() ........................................................................
    int Commands::go(std::string direction) {
        player->go(direction);
        return 0;
    }
  
//// fight() .....................................................................
    // parameter is the string 'id' of the actor to fight with  
    int Commands::fight(std::string act_id) {
        //Actor *opponent = get_actor(player->current_room->actors, stoi(act_id));
        Actor *opponent = get_actor(player->current_room->actors, stringToInt(act_id));
        if (opponent != 0) {
            // Player begins to fight
            fight(*player, *opponent);
        }
        else {
            std::cout << "\n\t No person like this is here" << std::endl;
        }
        return 0;
    }

//


/*// fight() .....................................................................
     
    // NOTE: A lambda expression is a mechanism for specifying a function object.
    // The primary use for a lambda is to specify a simple action to be performed 
    // by some function. If an action is neither common nor simple, I recommend
    // using a named FUNCTION OBJECT or function.(Stroustrup)
    // The type of a lambda cannot be named, so you either have to use a standard 
    // conversion to another type or use templates. 
      
    // 
    int Commands::fight(std::string act_id) {

        //#### 1. using an UNAMED LAMBDA
        auto nb_lambda = [act_id] (int nb) {
        //std::function<int(int)> nb_lambda = [act_id] (int nb) -> int { // No known conversion 
        // from function<> to 'int' FIXME
                             
                             std::istringstream stream(act_id);
                             stream >> nb;
                             return nb; 
                           };

        //### 2. usnig a named function object (FUNCTOR) FIXME
        //struct int_id {
        //std::string str;
        //int_id(std::string s) : str(s) {}
        //int operator()(int nb) {std::istringstream stream(str);
        //                          stream >> nb; return nb;}
        //};
        
        //Actor *opponent = get_actor(player->current_room->actors, int_id(act_id));
        //Actor *opponent = get_actor(player->current_room->actors, stringToInt(act_id));
        Actor *opponent = get_actor(player->current_room->actors, nb_lambda);

        // NOTE: Polymorfic function wrapper - std::function can store, copy and invoke any
        // callable target-functions, lambda expressions (anonymos functions) or other function objects.

        //#### 3. Using a function pointer
        //int (*func_pointer) (int) = nb_lambda; // store a lambda
        //Actor *opponent = get_actor(player->current_room->actors, func_pointer); //invalid conversion FIXME

        if (opponent != 0) {
            // Player begins to fight
            fight(*player, *opponent);
        }
        else {
            std::cout << "Ingen sådan person här inne" << std::endl;
        }
        return 0;
    }

*/

/* fight() with Lambda function ................................................
 
    // error: no matching function for call to 
     // ‘Commands::get_actor(std::vector<camelot::Actor*>*&, 
                             //Commands::fight(std::string)::<lambda()>)’
    //Because lambdas are temporary (rvalue) functions, you can only pass them by
    // const (lvalue) reference or by rvalue reference.
    // Each lambda has its own class type.
    //a lambda function that doesn't capture anything can be implicitly converted 
    //to a regular function pointer, which can be converted to other type.
    //You have to specify the return type only when the body consists of more 
    //than a single return statement. 
 
    int Commands::fight(std::string actor) {
        Actor *opponent = get_actor(player->current_room->actors, 
                           //[actor](int n) -> int mutable {
                           [actor] () mutable {
                             int n;
                             std::istringstream(actor) >> n;
                             //stream >> n;
                             return n; 
                           });

        if (opponent != 0) {
            // Player begins to fight
            fight(*player, *opponent);
        }
        else {
            std::cout << "Ingen sådan person här inne" << std::endl;
        }
        return 0;
    }
*/

// fight() ---------------------------------------------------------------------
    void Commands::fight(Actor &attacker, Actor &defender) 
    {
        std::cout << " Fight:\t" << attacker.get_name() << " vs " 
                  << defender.get_name() << std::endl;

        std::stringstream s;

        for (unsigned int round = 0; attacker.hp > 0 && defender.hp > 0; round++) 
        {
            s << " \nAttacker Health Points HP:   " << attacker.hp << std::endl;
            s << " Defender Health Points HP:   " << defender.hp << std::endl;

            if ((round & 1) == 0) {  // Bitwise AND to have only bit 1 turned on

                // Even, attackers turn  ##########################
                /* NOTE: Call to rand() returns a value >= 0 and < RAND_MAX. 
                   The most common, but incorrect, way to obtain a random 
                   floating-point from rand is to divide the result of rand()
                   by RAND_MAX which is the upper limit that rand can return.
                   see Lippman p750. */
                 
                // generates unsigned random integers in C++11  
                   // std::default_random_engine e(time(0)); 
                   // uniform_real_distribution<double> u(0, 1);// 
                   // if (u(e) <= attacker.weapon()->hit_ratio()) {

                   // Attacker perform random moves/hits 
                   // std::default_random_engine e; 
                   // e() calls the object to produce the next random number
                if (std::rand()/RAND_MAX <= attacker.weapon()->hit_ratio()) { 
                    int hitAtt = attacker.weapon()->attack_strength() * attacker.strength;

                    attacker.hp += defender.hp; // FIXME
                    defender.hp -= hitAtt;
                    s << "\n\t" << attacker.get_name() << " hit " << defender.get_name() 
                      //<< " and he lost " << hitAtt << "hp"
                      << "\n\t" << defender.get_name() << " lost " << hitAtt << "hp" 
                      << std::endl;
                }
                else {
                    s << " You missed!" << std::endl;
                }
            }
            else {
                // Defenders turn
                if (std::rand()/RAND_MAX <= defender.weapon()->hit_ratio()) {
                    int hitDef = defender.weapon()->attack_strength() * defender.strength;

                    attacker.hp -= hitDef;
                    s << "\n\t" << defender.get_name() << " hit " << attacker.get_name() 
                      //<< " and he lost " << hitDef << "hp" 
                      << "\n\t" << attacker.get_name() << " lost " << hitDef << "hp"
                      << std::endl;
                }
                else {
                    s << "\n\t" << defender.get_name() << " missed!" << std::endl;
                }

            }
        } ////////////// end for

        if (defender.hp <= 0) {
            //s << " \t Attacker won!" << std::endl;
            s << " \n\t" << attacker.get_name() << " won this fight!" << std::endl;
            delete &defender;
        }
        else {
            //s << " \t You lost and died!" << std::endl;
            s << " \n\t" << attacker.get_name() <<" lost and died!" << std::endl;
            delete &attacker;
        }
        Terminal::print(s.str());  // s is stringstream type
                                  // str() returns a copy of the string that s holds
    }

// pick_up() -------------------------------------------------------------------    
    int Commands::pick_up(std::string object) {
        try {
            Object * obj = get_object(player->current_room->objects, 
                                      stringToInt(object));
            if (obj != 0) {
                if (player->current_room->pick_up(obj)) {
                    if (player->pick_up(obj)) {
                        std::cout << "\t picked up " << obj->type() << std::endl;
                        return 0;
                    }
                    else {
                        std::stringstream string;
                        string << "Couldnt fit " << obj->type() << " into bag" 
                               << std::endl;
                        string << "Bag stats: " << player->container->type() 
                               << std::endl;
                        string << "    Volume Left: " 
                               << player->container->get_volume_left() 
                               << std::endl;
                        string << "    Weight Left: " 
                               << player->container->get_weight_left() 
                               << std::endl;
                        string << std::endl;
                        string << "Object: " << obj->type() << std::endl;
                        string << "    Volume: " << obj->volume() << std::endl;
                        string << "    Weight: " << obj->weight() << std::endl;
                        Terminal::print(string.str());

                        player->current_room->drop(obj);
                        return 0;
                    }
                }
            }
        }
        catch (...) {
        }
        std::cout << "No such item" << std::endl;
        return 0;
    }
// drop() ......................................................................    
    int Commands::drop(std::string object) {
        try {
            Object * obj = get_object(player->container->get_objects(), 
                                      stringToInt(object));
            if (obj != 0) {
                if (player->drop(obj)) {
                    player->current_room->drop(obj);
                    return 0;
                }
            }
        }
        catch (...) {}
        std::cout << "\n\t No such item" << std::endl;
        return 0;
    }
   
// talk_to() ...................................................................
    int Commands::talk_to(std::string actor) {
        Actor * act = get_actor(player->current_room->actors, stringToInt(actor));
        if (act != 0) {
            player->talk_to(*act);
        }
        else {
            std::cout << " \n\t No person like this is here" << std::endl;
        }
        return 0;
    }
//
/* talk_to() with lambda  .......................................................
    int Commands::talk_to(std::string actor) {
         auto nb_lambda = [actor] (int n) mutable {
        //std::function<int(int n)> nb_lambda = [&actor] (int n) -> int {
                             //int n;
                             std::istringstream stream(actor);
                             stream >> n;
                             return n; 
                           };
         
        Actor * act = get_actor(player->current_room->actors, nb_lambda);
        //Actor * act = get_actor(player->current_room->actors, stringToInt(actor));
        if (act != 0) {
            player->talk_to(*act);
        }
        else {
            std::cout << "Ingen sådan person här inne" << std::endl;
        }
        return 0;
    }
*/
// help() ......................................................................
    int Commands::help(std::string) 
    {
        const std::map<std::string, int (*)(std::string)>& functions = Terminal::get_functions();
        std::map<std::string, int (*)(std::string)>::const_iterator it;

        for (it = functions.begin(); it != functions.end(); it++) {
            std::cout << it->first << std::endl;
        }

        return 0;
    }
//


// inventory() .................................................................
    int Commands::inventory(std::string) 
    {
        std::vector<Object *>::iterator it = player->container->get_objects()->begin();

        for (; it != player->container->get_objects()->end(); ++it) {
            std::cout << (*it)->id << "\t" << (*it)->type() << std::endl;
        }
        return 0;
    }
// use() -----------------------------------------------------------------------
    /*
     Lets the player use objects, either the objects alone or in
     combination with other things such as keys on exits.
     
     param: arg The specified argument
     return: 0 if successfully used
     */
    // TODO: make sure the item being used is either in invetory or in the same room
    int Commands::use(std::string arg) {
        if (arg == "use") {
            arg = ""; // ugly hack for the words size to be 0
        }

        // split arg string on whitespace into words vector
        std::istringstream iss(arg);
        std::vector<std::string> words;

        copy(std::istream_iterator<std::string>(iss),
                std::istream_iterator<std::string>(),
                std::back_inserter<std::vector<std::string> >(words));

        // get objects from arg words, if possible
        int id;
        std::vector<Object *> objs;

        for (std::vector<std::string>::iterator it = words.begin(); 
             it != words.end(); ++it) {
            std::istringstream stream(*it);
            if (stream >> id) {
                objs.push_back(get_object(player->container->get_objects(), id));
                // please notice that indices might get out of sync here
            }
        }

        switch (words.size()) {
            case 0:
                std::cerr << "\t What do you want to use?" << std::endl;
                return -1;
            case 1:
                {
                    Weapon * weapon = dynamic_cast<Weapon *>(objs[0]);
                    if (weapon != 0) {
                        std::cout << "\t Changing weapon to: " 
                                  << weapon->type() << std::endl;
                        player->current_weapon = weapon;
                    }

                    Food * food = dynamic_cast<Food *>(objs[0]);
                    if (food != 0) {
                        player->eat(*food);
                    }

                    Container * bag = dynamic_cast<Container *>(objs[0]);
                    if (bag != 0) {
                        int held_volume = 0;
                        int held_weight = 0;
                        for (std::vector<Object *>::const_iterator it = 
                             player->container->get_objects()->begin(); 
                             it != player->container->get_objects()->end(); 
                             ++it) {
                            held_volume += (*it)->volume();
                            held_weight += (*it)->weight();
                        }

                        if (held_weight <= bag->get_hold_weight() 
                            && held_volume <= bag->get_hold_volume()) {
                            std::cout << "Changing bag" << std::endl;
                            while (player->container->get_objects()->size() > 0) 
                            {
                                Object * o = player->container->get_objects()
                                                   ->at(player->container
                                                              ->get_objects()
                                                              ->size()); 
                                                              // Get the item
                                bag->add(*o); // add it to the new bag
                                player->container->remove(*o); 
                                 // remove it from the old
                            }
                            player->current_room->drop(player->container);
                            player->container = bag;
                        }
                        else {
                            std::stringstream string;
                            string << "You cant fit everything in this bag" 
                                   << std::endl;
                            string << "Old bag: " << player->container->type() 
                                   << std::endl;
                            string << "    Volume: " 
                                   << player->container->get_hold_volume() 
                                   << std::endl;
                            string << "    Weight: " 
                                   << player->container->get_hold_weight() 
                                   << std::endl;
                            string << std::endl;
                            string << "New bag: " << bag->type() << std::endl;
                            string << "    Volume: " << bag->get_hold_volume() 
                                   << std::endl;
                            string << "    Weight: " << bag->get_hold_weight() 
                                   << std::endl;
                            Terminal::print(string.str());
                        }
                    }
                    break;
                }
            // Here to unlock exit with the key: "use (key) (exit)"
            case 2: 
                {
                    // Keys
                    Key * key = dynamic_cast<Key *>(objs[0]);
                    if (key != 0) {
                        Exit * exit = dynamic_cast<Exit *>(player->get_room()
                                                           ->get_exit(words[1]));
                        if (exit != 0) {
                            exit->toggle_lock(key);
                        }
                    }

                    // Do the same for other type of objects here
                    // ...
                    break;
                }
            default:
                return -1;
        }

        return 0;
    }

// stringToInt() ---------------------------------------------------------------
    int Commands::stringToInt(std::string s) 
    {
        int nb;
        //int nb = -4711;
        //std::istringstream stream(s);
        nb = std::stoi(s); // c++11
        //std::istringstream(s) >> nb;

        //if (!(stream >> nb)) {
            // TODO: fixa ett riktigt exception
           // throw -4711;
        //}
        return nb;
    }

// get_object() ................................................................
    Object * Commands::get_object(std::vector<Object *> * objects, int id) 
    {
        std::vector<Object *>::const_iterator it = objects->begin();
        for (; it != objects->end(); ++it) {
            if ((*it)->id == id) {
                return *it;
            }
        }
        return 0;
    }
//
// get_actor() .................................................................
    //template <typename T> 
    //Actor *Commands::get_actor(std::vector<T *> * actors, T id)
    //Actor* Commands::get_actor(std::vector<Actor*>*actors, std::function<int (int)> id)
    Actor *Commands::get_actor(std::vector<Actor *> * actors, int id) 
    {
        std::vector<Actor *>::const_iterator it = actors->begin();
        //std::cerr << " ciao get_actor" << std::endl; //##################
        for (; it != actors->end(); ++it) {
            if ((*it)->id == id) {
               return *it;
            }
        }
        std::cerr << " get_actor" << std::endl;
        return 0;
    }
//
}

