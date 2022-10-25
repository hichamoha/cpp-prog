#include "container.h"
#include <iostream>
#include <memory>

namespace camelot {

    // get_objects() ........................................................
    // return a vector of objects
    //std::vector<std::shared_ptr<Object >>* Container::get_objects()
    //std::shared_ptr<std::vector<Object *>> Container::get_objects()
    std::shared_ptr<std::vector<std::shared_ptr<Object>>> Container::get_items()
    //std::vector<std::shared_ptr<Object>> Container::get_objects()
    //std::vector<Object *> * Container::get_objects() 
    {
        return items;
    }

    //get_weight_left() ......................................................
    int Container::get_weight_left() const {
        int held_weight = 0;
        for (std::vector<std::shared_ptr<Object> >::const_iterator it = items->begin();
        //for (std::vector<Object *>::const_iterator it = objects->begin(); 
                it != items->end(); ++it) {
            held_weight += (*it)->weight();
        }

        return get_hold_weight() - held_weight;
    }

    // get_volume_left .....................................................
    int Container::get_volume_left() const {
        int held_volume = 0;

        for (std::vector<std::shared_ptr<Object> >::const_iterator it = items->begin();
        //for (std::vector<Object *>::const_iterator it = objects->begin(); 
                it != items->end(); ++it) {
            held_volume += (*it)->volume();
        }

        return get_hold_volume() - held_volume;
    }
}
