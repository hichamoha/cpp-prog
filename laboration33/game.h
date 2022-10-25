#ifndef GAME_H
#define GAME_H

#include <vector>

#include "actor.h"
#include "terminal.h"
#include "commands.h"
#include "environment.h"

namespace camelot {
    class Game {
        public:
            Game();        
            ~Game(); 
 
            void run_game();       
            void initialize();
            static void remove_actor(Actor &);
            static void add_actor(Actor &);
            static void add_environment(Environment &);

        private:
            static std::vector<Actor *> * actors;
            static std::vector<Environment *> * envs;

            void run();
            void printStory();
            bool playerIsAlive();
            bool playerIsAlone();
            void save();
            void loadOrInit();
            void clear_game();

            Terminal terminal;
            Commands *commands;

            static Player *player;
    };

}

#endif // GAME_H
