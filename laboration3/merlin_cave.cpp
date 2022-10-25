#include "merlin_cave.h"
#include <iostream>

namespace camelot {
    
    // Constructs an empty Merlin cave
    MerlinCave::MerlinCave() {
    }

    /* If we give the objects an id directly from this vector there might be a 
       problem when we try to pick up something that has already been picked up
       by someone else. */

    // description()
    std::string MerlinCave::description() const 
    {
        std::string description = Environment::description();
        description += " \n\t We are in Merlin Cave!";

        return description;
    }

}
