#ifndef BAG_H
#define BAG_H

#include <string>
#include "container.h"

namespace camelot {

    class Bag : public Container {

    public:
      //using Container::Container;  // inherit Container constructors   
      Bag();
      ~Bag();

      virtual int weight() const;
      virtual int volume() const;
      virtual int price() const;

      virtual std::string type() const;

      virtual int get_hold_weight() const;
      virtual int get_hold_volume() const;
      virtual bool add(Object &);
      virtual bool remove(Object &);

      virtual void saveObj(std::fstream & ofs);

    };


}

#endif // BAG_H
