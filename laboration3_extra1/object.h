#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <fstream>

namespace camelot {

  class Object {
  public:
      const int id;

      Object();
      virtual ~Object();
 
      //virtual ~Object() = default; // Dynamic binding for the destructor
            /* NOTE: Base classes ordinarily should define a virtual destructor.
               Virtual destrctors are needed even if they do not work */
            
            virtual int weight() const = 0;
            virtual int volume() const = 0;
            virtual int price() const = 0;
            virtual std::string type() const = 0;

            virtual bool operator==(Object &) const;
            /* NOTE: All read-only methodes are const declared */

            virtual void saveObj(std::fstream &) = 0; //pure virtual ?
            static Object *loadObj(std::string);

        protected:
            static int instances;

    };
}
#endif // OBJECT_H
