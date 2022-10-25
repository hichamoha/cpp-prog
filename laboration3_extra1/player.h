#ifndef PLAYER_H
#define PLAYER_H

#include "human.h"
#include "environment.h"
#include <string>

namespace camelot {
    class Player: public Human 
    {
        friend class GameCommands;

        public:
            Player(Environment *);
            Player(Environment *, int, int, bool, int);
            ~Player();

            virtual void action();
            virtual std::string get_type() const;
            virtual std::string get_name() const;
            virtual void fight(Actor &);
            virtual void talk_to(Actor &);

            virtual Environment * get_room() const;
            virtual std::string dataToFile() const;
    };
}

#endif // PLAYER_H
