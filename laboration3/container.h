#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>

#include "object.h"

namespace camelot {

    class Container : public Object  {
      
    public:
        // Weight before container breaks
        virtual int get_hold_weight() const = 0;
            
        // Volume capacity of container
        virtual int get_hold_volume() const = 0;

        virtual int get_weight_left() const;
        virtual int get_volume_left() const;
            
        // Add an object to this container
        virtual bool add(Object &) = 0;
            
        // Remove an object from this container
        virtual bool remove(Object &) = 0;


        virtual std::vector<Object *> * get_objects();

        // virtual void saveCon(std::fstream & ofs);

    protected:
        int hold_weight;
        int hold_volume;

        std::vector<Object *> * objects;

    };

}

#endif // CONTAINER_H
