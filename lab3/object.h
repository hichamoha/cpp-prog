#ifndef OBJECT_H	
#define OBJECT_H

namespace rollspel
{
  class Object
  {
  public:
    Object();
    virtual ~Object();

    virtual int weight() const = 0; 
    virtual int volume() const = 0;
    virtual int price() const = 0; 

  protected:
  private:
  };


}

#endif // OBJECT_H
