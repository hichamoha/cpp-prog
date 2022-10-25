#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

namespace rollspel
{
  class Environment 
  {
  public:
    Environment();
    virtual ~Environment(); // ho aggiunto virtual, ma non e' abstract!?

    virtual std::vector<std::string> directions() const; //returnera vilka exits
                                                         //som finns
    virtual Object& neighbor(std::string) const; //returnera granne i given 
                                        //riktning(t.ex.referens till objekt)  
    virtual std::string description() const; // returnera beskrivning av vad 
     //miljön innehåller, vilka object man kan ta och vilka actors som 
     //befinner sig på platsen.  

    virtual void enter(Character& ); // actor kommer till platsen
    virtual void leave(Character& ); // actor går from platsen
    virtual bool pick_up(Object& ); // någon tar upp ett föremål som finns
    virtual void drop(Object& ); // någon lägger ner ett föremål på platsen	
		
  protected:
    std::vector<Object *> * objects;
    std::vector<Character *> * actors;

    // varje instans av en miljöklass ha en beskrivande text
    std::map<std::string, Environment *> neighbors;
    std::map<std::string, Exit *> exits;

  private:  

	
  };
}
#endif  //ENVIRONMENT_H
