#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <vector>

#include "object.h"
#include "environment.h"
#include "weapon.h"
#include "default_weapon.h"
#include "container.h"
#include "bag.h"

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
                                const std::map<std::string, Object *> &);

            virtual void action() = 0;  // action()
            virtual std::string get_type() const = 0;  // type()
            virtual std::string get_name() const = 0;  // name()

            virtual void go(std::string);
            virtual bool pick_up(Object *);
            virtual bool drop(Object *);
            virtual void talk_to(Actor &) = 0;

            virtual Weapon * weapon();
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
 
            // shared_ptr<Container> container;
            Weapon * current_weapon;
            //DefaultWeapon *current_weapon;
            Environment * current_room;
            Container * container;       // FIXME 
            //Bag *container;

            /* NOTE: Classes with PURE VIRTUALS are ABSTRACT base classes.
               We cannot (directly) create objects of a type that is an 
               abstract base class. (like Container and Weapon are abstract !!!)
               see Lippman p610 */

        private:
            static int str2int(std::string);  // it must handle error ?
    };
}
#endif // ACTOR_H
