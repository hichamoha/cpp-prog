
#include <iostream>
#include <sstream>
//#include <memory>

#include "environment.h"
#include "game.h"

namespace camelot {

    int Environment::instances;

    // constructor
    Environment::Environment() : id (instances) {

        instances++;

        //create vectors of pointers to objects and actors
        objects = new std::vector<Object *>;
        //objects = std::move(new std::vector<std::unique_ptr<Object>>);
        actors = new std::vector<Actor *>;
        //actors = std::move(new std::vector<std::unique_ptr<Actor>>);

        Game::add_environment(*this);
    }

    // destructor ............................................................
    // when an environment is destroyed everything in it need to be deleted
    Environment::~Environment() {
 
      // delete actors vector
      //for (std::vector<Actor *>::iterator it = actors->begin(); it != actors->end(); ++it) {
      //      delete *it;
      //  } actors->clear(); 
      //for (auto it_act : actors) {delete *it_act;} actors->clear();  //TODO  
      actors->clear();
      delete actors;

      // delete objects vector
      //std::vector<Object *>::iterator it = objects->begin();
      //for (; it != objects->end(); ++it) {delete *it;} objects->clear();
      //for (auto it_obj : objects) {delete *it_obj;} objects->clear();
      objects->clear();
      delete objects;

      // Delete exit map
      //clean_exits();
            
    }

/*
// clean_exits()  FIXME
   void Environment::clean_exits()
   {
     for (auto keyvalue : exits)
     {
       delete keyvalue.second;  
     }
     exits.clear(); // Removes all the elements (pointers to 'exits') from the map container  
                    // (exits are destroyed before by 'delete'), 
                    // leaving the container with a size of 0.
   }
*/

// description() ............................................................
    std::string Environment::description() const {
        std::stringstream ss;
        //ss << " ENVIRONMENT DESCRIPTION " << std::endl;
        ss << "Objects:" << std::endl;
        for (size_t i = 0; i < objects->size(); ++i) {
            ss << " \t " << objects->at(i)->id << "  " 
              << objects->at(i)->type() 
              << std::endl;
        }
        
        ss << "Actors:" << std::endl;
        for (size_t i = 0; i < actors->size(); ++i) {
            ss << " \t " << actors->at(i)->id << "  "
              //<< actors->at(i)->get_type() 
              << actors->at(i)->get_name()
              << std::endl;
        }
 
        ss << "Exits:" << std::endl;
        std::vector<std::string> exit_names = get_exit_names();
 
        for (size_t i = 0; i < exit_names.size(); ++i) {
            ss << " \t " << exit_names[i] << std::endl;
        }
 
        return ss.str();  //returns a copy of the string that stream holds
    }

// add_exit() ...............................................................
    /**
     * Adds the specified exit with the given name (preferably a point
     * of the compass) to this environment.
     *
     * return: True if the exit was added or false if an exit with the 
     * same value already existed
     */
    bool Environment::add_exit(std::string name, Exit *exit) 
    //bool Environment::add_exit(std::string name, std::unique_ptr<Exit> exit)
    {
        std::pair<std::string, Exit *> p(name, exit);
        std::pair<std::map<std::string,Exit *>::iterator, bool> ret = exits.insert(p);

        return ret.second;
    }

// get_exit() ...............................................................
    /**
     * Returns the exit with the given name, if there is a such.
     *
     * param: name The name of the exit
     * return: The exit with the given name
     */
    Exit * Environment::get_exit(std::string name) const 
    {
        std::map<std::string, Exit *>::const_iterator it = exits.find(name);

        if (it != exits.end()) {
            return it->second;
        }
        else {
            std::cout << " \n\tNo such exit" << std::endl;
            return 0;
            // Throw exception or something, needs a return
        }
    }

// get_exit_names() ..........................................................
    /*
     Returns a list of all available exits in this environment.
     return: List of exits
     */
    std::vector<std::string> Environment::get_exit_names() const 
    {
        std::map<std::string, Exit *>::const_iterator it;
        std::vector<std::string> ret_exits;

        for (it = exits.begin(); it != exits.end(); ++it) {
            ret_exits.push_back(it->first);
        }

        return ret_exits;
    }

// enter() .................................................................
    /* Lets the specified actor enter this environment.
       param actor The actor to enter
     */
    void Environment::enter(Actor &actor) 
    {
        actors->push_back(&actor);
    }

// leave() .................................................................
    /**
     * Lets an actor leave this environment.
     *
     * param: actor The actor to leave
     */
    void Environment::leave(Actor &actor) 
    {
        std::vector<Actor *>::iterator it = actors->begin();
        for (; it != actors->end(); ++it) {

            if (&(**it) == &actor) {
                actors->erase(it);  //erasing from STL containers invalidates 
                                   //any iterator associated with them
                return;
            }
        }
    }

// pick_up() .................................................................
    /**
     * Someone picks up an object that is owned by this environment.
     * That means this environment must hand over the object in
     * question.
     *
     * param: obj The object that is being picked up
     * return: True if the object really was held by this environment,
     * otherwise false.
     */
    bool Environment::pick_up(Object *obj) 
    {
        std::vector<Object *>::iterator it = objects->begin();
        for (; it != objects->end(); ++it) {

            if (**it == *obj) {
                objects->erase(it);//erasing from STL containers invalidates 
                                   //any iterator associated with them
                return true;
            }
        }
        return false;
    }

// drop() ...................................................................
    /**
     * Someone drops an object in this environment. That means this
     * environment must take care of it.
     *
     * param: obj The object that is being dropped
     */ 
    void Environment::drop(Object *obj) {

        if (obj != nullptr)
            objects->push_back(obj);  // push_back() stores a copy of the pointer XXX
        else 
            throw;
    }

// saveEnv() ...................................................................
    // an output file stream to write/save to
    void Environment::saveEnv(std::fstream &ofs) {

        std::cout << " \t Saving environment " << id << std::endl;

        ofs << "ENV" << id << ":";
        bool first = true;

             //first = true;
        for (size_t i = 0; i < objects->size(); ++i) {

            if (first)
                first = false;
            else
                ofs << ",";
            ofs << "OBJ" << objects->at(i)->id;
        }

        ofs << ":";
        first = true;
        for (size_t i = 0; i < actors->size(); ++i) {

            if (first)
                first = false;
            else
                ofs << ",";
            ofs << "ACT" << actors->at(i)->id;
        }

        ofs << ":";
        first = true;
        for (std::map<std::string, Exit *>::iterator it = exits.begin(); 
             it != exits.end(); ++it) {

            if (first)
                first=false;
            else
                ofs << ",";
            ofs << "EXI" << it->second->id << "=" << it->first;
        }

        ofs << std::endl;

        for (size_t i = 0; i < objects->size(); ++i) {
            objects->at(i)->saveObj(ofs);
        }

        //for (auto it : exits) {
        for (std::map<std::string, Exit *>::iterator it = exits.begin(); 
             it != exits.end(); ++it) {
            it->second->saveExi(ofs, it->first);
        }
 
    }

// get_objects() ....................................................................
    // return a vector of pointers to Object
    std::vector<Object *> Environment::get_objects() {
        return *objects;
    }

// get_actors() ....................................................................
    // return a vector of pointers to Actor
    std::vector<Actor *> Environment::get_actors() {
        return *actors;
    }

 // loadEnv() ........................................................................   
    Environment * Environment::loadEnv(std::string) {
        return new Environment;
    }

}
