#include "inside.h"

namespace camelot {

    /**
     * Constructs a new empty inside environment with no exits.
     */
    Inside::Inside() {
    }

    /**
     * Constructs a new inside environment.
     *
     * @param east The east exit
     * @param west The west exit
     * @param north The north exit
     * @param south The south exit
     */
    Inside::Inside(std::shared_ptr<Exit> east, std::shared_ptr<Exit> west, std::shared_ptr<Exit> north, std::shared_ptr<Exit> south) {
    //Inside::Inside(Exit *east, Exit *west, Exit *north, Exit *south) {

        if (east != 0) {
            std::pair<std::string, std::shared_ptr<Exit>> e("east", east);
            //std::pair<std::string, Exit *> e("east", east);
            exits.insert(e);
        }
        if (west != 0) {
            std::pair<std::string, std::shared_ptr<Exit>> w("west", west);
            //std::pair<std::string, Exit *> w("west", west);
            exits.insert(w);
        }
        if (north != 0) {
            std::pair<std::string, std::shared_ptr<Exit>> n("north", north);
            //std::pair<std::string, Exit *> n("north", north);
            exits.insert(n);
        }
        if (south != 0) {
            std::pair<std::string, std::shared_ptr<Exit>> s("south", south);
            //std::pair<std::string, Exit *> s("south", south);
            exits.insert(s);
        }
    }
/*
    Inside::~Inside()
    {
       for (auto keyvalue : exits)
       {
         delete keyvalue.second;  
       }
       exits.clear(); // Removes all elements from the map container (which are destroyed), 
                    // leaving the container with a size of 0.
    }
*/
}
