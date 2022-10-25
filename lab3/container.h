#ifndef CONTAINER_H
#define CONTAINER_H


namespace rollspel
{
  class Container : public Object
  {
  public:
    // vikt innan behållare går sönder
    virtual int hold_weight() const = 0;
    // volym innan container blir full
    virtual int hold_volume() const = 0;
    // lägg objekt i container
    virtual bool add(Object &) = 0;
    // ta bort objekt från container
    virtual bool remove(Object &) = 0;
	    
  protected:
  private:


  };

}
#endif // CONTAINER_H
