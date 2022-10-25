#ifndef ROOM_H
#define ROOM_H

#include "inside.h"

namespace camelot {
    class Room : public Inside {
        public:
            Room();

            Room(std::shared_ptr<Exit> ,std::shared_ptr<Exit> , std::shared_ptr<Exit> , std::shared_ptr<Exit>);
            //Room(Exit *, Exit *, Exit *, Exit *);

            virtual std::string description() const;
        private:
    };
}

#endif // ROOM_H

