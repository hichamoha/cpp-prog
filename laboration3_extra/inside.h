#ifndef INSIDE_H
#define INSIDE_H

#include "environment.h"

namespace camelot {

    class Inside : public Environment  {

        public:
            Inside();
            //~Inside();

            Inside(std::shared_ptr<Exit> ,std::shared_ptr<Exit> , std::shared_ptr<Exit> , std::shared_ptr<Exit> );
            //Inside(Exit *, Exit *, Exit *, Exit *); 
    };
}

#endif // ENVIRONTMENT_H
