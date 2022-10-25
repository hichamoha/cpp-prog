#ifndef MERLIN_CAVE_H
#define MERLIN_CAVE_H

#include "inside.h"

namespace camelot {
    class MerlinCave : public Inside {
        public:
            MerlinCave();

            virtual std::string description() const;
        private:
    };
}

#endif // MERLIN_CAVE_H

