#ifndef FOOD_H
#define FOOD_H

#include "object.h"

namespace rollspel
{
  class Food : public Object
  {
  public:
    virtual int weight() const; 
    virtual int volume() const;
    virtual int price() const; 
  protected:
  private:  






  };
}
#endif // FOOD_H
