#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <vector>
#include <memory>

#include "object.h"
#include "environment.h"
#include "weapon.h"
#include "default_weapon.h"
#include "container.h"
#include "bag.h"

/*  Abstract Base Classes:
 When we deal with a class hierarchy, we usually never create base-class objects. 
 Rather, we use the base class only as a way to specify an interface, which derived 
 classes implement. We can make the creation of base-class objects impossible, 
 by turning the base class into an abstract class.

 An abstract class is a class with one or more members that are pure virtual functions. 
 We create a pure virtual function like this. */

namespace camelot {

    class Environment;
    
    class Actor {

        friend class Commands;
        friend class Game;

        public:
            const int id;

            Actor();
            virtual ~Actor(); 
            //virtual ~Actor() = default; // Dynamic binding for the destructor

            /* NOTE: Base classes ordinarily should define a virtual destructor.
               Virtual destrctors are needed even if they do not work */

            static Actor * loadAct(const std::string, 
                                const std::map<std::string,Environment *> &, 
                                const std::map<std::string, std::shared_ptr<Object >> &);
            //static Actor * loadAct(const std::string, 
            //                    const std::map<std::string,Environment *> &, 
            //                    const std::map<std::string, Object *> &);

            virtual void action() = 0;  // action()
            virtual std::string get_type() const = 0;  // type()
            virtual std::string get_name() const = 0;  // name()

            virtual void go(std::string);

            virtual bool pick_up(std::shared_ptr<Object>);
            //virtual bool pick_up(Object *);

            virtual bool drop(std::shared_ptr<Object>);
            //virtual bool drop(Object *);

            virtual void talk_to(Actor &) = 0;

            //virtual Weapon * weapon();
            virtual std::shared_ptr<Weapon> weapon();
            virtual void fight(Actor &);

            void saveAct(std::fstream &);
            virtual std::string dataToFile() const = 0;

        protected:
            static int instances;

            int hp;
            int strength;

            /* NOTE: A default initialized smart pointer holds a null pointer.
               We use a smart pointer in ways that are similar to using 
               a pointer. The safest way to allocate and use dynamic memory 
               is to call "make_shared". (Lippman p450) */
 
            std::shared_ptr<Weapon> current_weapon;
            //std::shared_ptr<Weapon> current_weapon(nullptr); // doesn't work !?
            //Weapon *current_weapon;
           
            Environment *current_room;

            // NOTE: When initialization must be separate from declaration, e.g. class members,  
            // initialize with nullptr to make your programming intent explicit.
            std::shared_ptr<Container> container;
            //std::shared_ptr<Container> container(nullptr); // doesn't work !?
            //Container *container;       // FIXME 
            
            /* NOTE: Classes with PURE VIRTUALS are ABSTRACT base classes.
               We cannot (directly) create objects of a type that is an 
               abstract base class. (like Container and Weapon are abstract !!!)
               see Lippman p610 */

        private:
            static int str2int(std::string);  // it must handle error ?
    };
}
#endif // ACTOR_H
