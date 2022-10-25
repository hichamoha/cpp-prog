#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "object.h"
#include "environment.h"
#include "container.h"
#include "weapon.h"

namespace rollspel
{
  class Character
  {
  public:
    const int info;
   
    Character();
    virtual ~Character();

    virtual std::string type() const = 0; // returnerar namnet på arten
    virtual std::string name() const = 0; // returnerar namnet på varelsen
    virtual void action() const = 0;      // aktörens tur att agera 
                                          // eller kan göra t.ex. run()  

    virtual void go(std::string);     // go direction, gå åt håll
    virtual void fight(Character &);  // slåss med
    virtual bool pick_up(Object &);   // ta upp sak
    virtual bool drop(Object &);      // släpp sak på marken
    virtual void talk_to(Character &) = 0; // konversera med

    virtual Weapon *get_weapon();
    void save(std::fstream &);
    static Character* load(const std::string,
                       const std::map<std::string ,Environment *> &,
                       const std::map<std::string ,Object *> &);

  protected:
     static int instances;
     int points;
     int strength;
     
     Container *container;
     Environment *current_room;
     Weapon *current_weapon;
  private:
    static int str2int(std::string);  // måste hantera fel?	
  };

}

#endif
