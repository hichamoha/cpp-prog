#ifndef COMMANDS_H
#define COMMANDS_H

#include "terminal.h"
#include "player.h"

#include <string>
#include <iostream>
#include <functional>

namespace camelot {

    class Commands {
        public:
            Commands(Player *);
            /* NOTE: The 'static' members of a class exist outside any OBJECT. 
               Objects do not contain data associated with static data members.
               We say a member is associated with the class by adding the keyword 
               'static' to its declaration.
               Similarly, static MEMBER FUNCTIONS are not bound to any object;
               they do not have a 'this' pointer. As a result, static member 
               functions may not be declared as const, and we may not refer to 
               'this' in the body of a static member.
               We can access a static member directly through the scope operation.
               We can use an object, reference or pointer of the class type to 
               access a static member.
               The keyword appears only with the declaration inside the class body.
               We must DEFINE and INITIALIZE each static data member outside the 
               the class body.*/

            static int exit(std::string);
            static int go(std::string);
                              static int fight(std::string); // FIXME
            static int pick_up(std::string);
            static int drop(std::string);
            static int talk_to(std::string);
            static int help(std::string);
            static int inventory(std::string);
            static int use(std::string);

            static int save(std::string);
            static int load(std::string);
               
            static void fight(Actor &, Actor &);

        private:
            static Player *player;

            static int stringToInt(std::string);

            static Object* get_object(std::vector<Object *> * , int);

            //template <typename T>
            //static Actor* get_actor(std::vector<Actor*>*, std::function<int (int)> );
        //template<class T> static Actor* get_actor(std::vector<T*>* , T);
            //template<class T> static Actor* get_actor(std::vector<T*>*& , const T&);
            static Actor* get_actor(std::vector<Actor *> * , int);

            /*###### get_actor() as a template function member
            template <typename T>
            //Actor *Commands::get_actor(std::vector<T *> * &actors, const T &id) 
            static Actor * get_actor(std::vector<Actor *> * actors, T id)
            //T *Commands::get_actor(std::vector<T *> * actors, T id)
            //Actor *Commands::get_actor(std::vector<Actor *> * actors, int id) 
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
            */

    };
    /* --------------------------------------------------------------------------
    // get_actor() .................................................................
    template <typename T>
    //Actor *Commands::get_actor(std::vector<Actor *> * &actors, const T &id) 
    Actor *Commands::get_actor(std::vector<Actor *> * actors, T id)
    //T *Commands::get_actor(std::vector<T *> * actors, T id)
    //Actor *Commands::get_actor(std::vector<Actor *> * actors, int id) 
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
    */
}
#endif
