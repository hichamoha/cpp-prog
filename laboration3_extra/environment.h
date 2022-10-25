#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "actor.h"
#include "exit.h"
#include "object.h"

namespace camelot {

    class Actor;
    class Object;

    class Environment {

        friend class Commands;

        public:
            const int id;

            Environment();

            virtual ~Environment();  // ho aggiunto virtual, ma non e' abstract!?
            //virtual ~Environment() = default; // Dynamic binding for the destructor
            /* NOTE: Base classes ordinarily should define a virtual destructor.
               Virtual destrctors are needed even if they do not work */

            

            /*description: Any implementation of this function should return a
              description of what the environment contains, what objects are 
              available and what actors are in the environment. 
              TODO: fixa så det här printas vid operator<<  */
            virtual std::string description() const;

            //virtual bool add_exit(std::string, Exit *);
            virtual bool add_exit(std::string, std::shared_ptr<Exit>);

            virtual std::shared_ptr<Exit> get_exit(std::string) const;
            //virtual Exit * get_exit(std::string) const;
            virtual std::vector<std::string> get_exit_names() const; //directions()

            virtual void enter(Actor &);
            virtual void leave(Actor &);

            virtual bool pick_up(std::shared_ptr<Object >);
            //virtual bool pick_up(Object *);

            virtual void drop(std::shared_ptr<Object>);
            //virtual void drop(Object *);

            virtual std::vector<std::shared_ptr<Object>> get_objects();
            //virtual std::vector<Object *> get_objects();

            virtual std::vector<Actor *> get_actors();

            virtual void saveEnv(std::fstream &);
            static Environment * loadEnv(std::string);

            //void clean_exits();  // FIXME

        protected:
            static int instances;

            // vectors: objects and actors
            //std::vector<Object *> * objects;
            std::shared_ptr<std::vector<std::shared_ptr<Object>>> objects;
            //std::vector<std::shared_ptr<Object>> *objects;

            std::vector<Actor *> * actors;
            // std::unique_ptr<std::vector<std::unique_ptr<Actor>>> actors;

            // maps: neighbors and exits
            std::map<std::string, Environment *> neighbors;
            //std::map<std::string, Exit *> exits;
            std::map<std::string, std::shared_ptr<Exit>> exits;
    };
}
#endif // ENVIRONTMENT_H
