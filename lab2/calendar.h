//       2.3 (polymorfi, pekare till basklass, strömmar)
//I den här uppgiften kommer du att skriva en klass Calendar 


#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"
#include "julian.h"
#include "gregorian.h"
#include "eventDate.h"

#include <stdexcept>
#include <iostream>
#include "stdlib.h"
#include <list>

namespace lab2
{
  template <typename T>
  class Calendar
  {
  public:
    Calendar();
    //Calendar() : eventlist()
    //{  actual_date = new T();  }

    Calendar(int y,int m,int d) : eventlist()
    {  actual_date = new T(y,m,d);  }

    Calendar(const Calendar<T>& );
    ~Calendar();
    Calendar<T>& operator=(const Calendar<T>& );

    template <typename U>  Calendar(const Calendar<U>& );
    template <typename U>  Calendar& operator=(const Calendar<U>& );

    bool set_date(int y,int m,int d);

    bool add_event(std::string eventname);
    bool add_event(std::string eventname,int day);
    bool add_event(std::string eventname,int day,int month);
    bool add_event(std::string eventname,int day,int month,int year);

    bool remove_event(std::string eventname);
    bool remove_event(std::string eventname,int day);
    bool remove_event(std::string eventname,int day,int month);
    bool remove_event(std::string eventname,int day,int month,int year);

    std::list<EventDate<T>> get_eventlist() const
    {  return eventlist;  }

    /*
    Typename Description: http://pages.cs.wisc.edu/~driscoll/typename.html
    There are two key concepts needed to understand the description of typename,
    and they are qualified and dependent names. Before a qualified dependent type,
    you need typename. "typename" states that the name that follows should be 
    treated as a type. 
    The typename keyword, is needed because iterator is a dependent type on P. 
    The compiler can't guess if iterator refers to a value or a type, so it 
    assume it's a value unless you yell typename. It's needed whenever there is 
    a type dependent on a template argument, in a context that either types or 
    values would be valid. For instance, as base classes typename is not needed 
    since a base class must be a type.
    
    begin() and end() return iterators of type list<EventDate<T>>::iterator
    c++11 standard: auto iter = il.begin()
  
    */
   typename std::list<EventDate<T>>::const_iterator get_list_begin() const
   {  return eventlist.begin();  }

    typename std::list<EventDate<T>>::const_iterator get_list_end() const
    {  return eventlist.end();  }

    // T* get_actual_date() const  //########
    // {  return actual_date;  }

    data get_actualdate() const;
    std::ostream& autoprint(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Date& d);

  private:
    std::list<EventDate<T>> eventlist;  // with map<> could be faster !!!!
    void cancel();
    T* actual_date;
  
  };
  //============================================================================
  
  template <typename T>
  Calendar<T>::Calendar() : eventlist()
  {  actual_date = new T();  }
 
  // copy constructor
  template <typename T>
  Calendar<T>::Calendar(const Calendar<T>& other) : eventlist()
  {
    data tempDate = other.get_actualdate();
    T modDate(tempDate.year,tempDate.month,tempDate.day);
    actual_date = new T(modDate);

    if (!other.get_eventlist().empty())
    {
      //typename std::list<EventDate<T>>::iterator it;
      //for (it=other.get_list_begin(); it!=other.get_list_end(); it++)

  //NB: begin() and end() return iterators of type list<EventDate<T>>::iterator
     //c++11 standard: auto iter = il.begin()
      for (auto it=other.get_list_begin(); it!=other.get_list_end(); it++) 
      {
        add_event(it->event, it->date->day(),it->date->month(),it->date->year());
      }  
    }
  }

  template <typename T>
  Calendar<T>::~Calendar()
  {
    cancel();
    delete actual_date;
  }

  template <typename T>
  void Calendar<T>::cancel()
  {
    eventlist.clear();
    
  }
    
  // Overloaded assignment operator
  template <typename T>
  Calendar<T>& Calendar<T>::operator=(const Calendar<T>& right)
  {
    if (&right==this)
      return *this;

    delete actual_date;
    cancel(); 

    data tempDate = right.get_actualdate();
    T modDate(tempDate.year,tempDate.month,tempDate.day);
    actual_date = new T(modDate);

    if (!right.get_eventlist().empty())
    {
      //typename std::list<EventDate<T>>::iterator it;
      //for (it=right.get_list_begin(); it!=right.get_list_end(); it++)
      for (auto it=right.get_list_begin(); it!=right.get_list_end(); it++)
      {
        add_event(it->event, it->date->day(),it->date->month(),it->date->year());
      }  
    }
    
    return *this; 
  }

  // copy constructor with another date type
  template <typename T>
  template <typename U>  
  Calendar<T>::Calendar(const Calendar<U>& other) : eventlist()
  {
    data tempDate = other.get_actualdate();
    U modDate(tempDate.year,tempDate.month,tempDate.day);
    actual_date = new T(modDate);

    if (!other.get_eventlist().empty())
    {
      //typename std::list<EventDate<U>>::iterator it;
      //for (it=other.get_list_begin(); it!=other.get_list_end(); it++)
      for (auto it=other.get_list_begin(); it!=other.get_list_end(); it++)
      {
        T our(*it->date);   // cast it to T calendar dates
        add_event(it->event, our.day(),our.month(),our.year());
      }  
     }
  }  

  // Overloaded assignment operator with another date type
  template <typename T>
  template <typename U>  
  Calendar<T>& Calendar<T>::operator=(const Calendar<U>& right)
  {
    delete actual_date;
    cancel(); 

    data tempDate = right.get_actualdate();
    U modDate(tempDate.year,tempDate.month,tempDate.day);
    actual_date = new T(modDate);

    if (!right.get_eventlist().empty())
    {
      //typename std::list<EventDate<T>>::iterator it;
      //for (it=right.get_list_begin(); it!=right.get_list_end(); it++)
      for (auto it=right.get_list_begin(); it!=right.get_list_end(); it++)
      {
        T our(*it->date);   // cast it to T calendar dates
        add_event(it->event, our.day(),our.month(),our.year());
      }  
    }
    
    return *this;   
  }

  template <typename T>
  bool Calendar<T>::set_date(int y,int m,int d)
  {
    try{  
      T ogiltig(y,m,d);
    
    }catch (std::out_of_range e){
        return false;
     }

    delete actual_date;
    actual_date = new T(y,m,d);
    return true;
  }

  /*
 bool add_event() kan ta en till fyra parametrar: händelse (string) och 
 parametrarna dag, månad, år (int). 
 Om någon av de senare parametrarna saknas så används aktuellt datum. 
 Om datumet är ogiltigt ska false returneras. 
 Om händelsen (strängen) redan finns i kalendern på det angivna datumet ska 
 false returneras och ingenting nytt läggas in.

  */
    
  template <typename T>
  bool Calendar<T>::add_event(std::string eventname)
  {
    return add_event(eventname,actual_date->day(),
                     actual_date->month(),actual_date->year());
  }
    
  template <typename T>
  bool Calendar<T>::add_event(std::string eventname,int day)
  {
    return add_event(eventname,day,
                     actual_date->month(),actual_date->year());
  }
    
  template <typename T>
  bool Calendar<T>::add_event(std::string eventname,int day,int month)
  {
    return add_event(eventname,day,month,actual_date->year());
  }
  
  template <typename T>
  bool Calendar<T>::add_event(std::string name,int day,int month,int year)
  {
     try{  
        T ogiltig(year,month,day);
    
     }catch (std::out_of_range e){
          return false;
      }

      EventDate<T> newevent(name,day,month,year);

      if (!eventlist.empty())
      {
        //typename std::list<EventDate<T>>::iterator it;
        //for (it=eventlist.begin(); it!=eventlist.end(); it++)
        for (auto it=eventlist.begin(); it!=eventlist.end(); it++)
        {
          // Om händelsen (strängen) redan finns i kalendern
          if ( *it->date==*newevent.date && it->event==name )  
            return false;

          if ( *it->date > *newevent.date )
	    {
              eventlist.insert(it,newevent);
	      return true;	
            }  
        }      
      }
      
      eventlist.push_back(newevent);
      return true;

  }

  /*
  remove_event med samma parametrar som add_event. Om det inte går
  att ta bort händelsen returneras false.

  */
  template <typename T>
  bool Calendar<T>::remove_event(std::string eventname)
  {
    return remove_event(eventname,actual_date->day(),
                     actual_date->month(),actual_date->year());
  }

  template <typename T>
  bool Calendar<T>::remove_event(std::string eventname,int day)
  {
    return remove_event(eventname,day,
                     actual_date->month(),actual_date->year());
  }

  template <typename T>
  bool Calendar<T>::remove_event(std::string eventname,int day,int month)
  {
    return remove_event(eventname,day,month,actual_date->year());
  }

  template <typename T>
  bool Calendar<T>::remove_event(std::string name,int day,int month,int year)
  {
     try{  
        T ogiltig(year,month,day);
    
     }catch (std::out_of_range e){
          return false;
      }

      T tDate(year,month,day);

      if (!eventlist.empty())
      {
        //typename std::list<EventDate<T>>::iterator it;
        //for (it=eventlist.begin(); it!=eventlist.end(); it++)
        for (auto it=eventlist.begin(); it!=eventlist.end(); it++)
        {
          // Om händelsen (strängen) finns i kalendern
          if ( *it->date==tDate && it->event==name )  
          {
            eventlist.erase(it);   
            return true;
          }
        }      
      }
      //Om det inte går att ta bort händelsen returneras false.
      return false;

  }


  template <typename T>
  data Calendar<T>::get_actualdate() const
  {
    data tDate;

    tDate.year = actual_date->year();
    tDate.month = actual_date->month();
    tDate.day = actual_date->day();
    
    return tDate;
  }

  /*
   Man ska kunna skriva ut kalendern m.hj.a utskriftsoperatorn. 
   Enbart händelser efter aktuellt datum ska skrivas ut.

  */
  template <typename T>
  std::ostream& Calendar<T>::autoprint(std::ostream& os) const
  {
    if (!eventlist.empty())
    {
      //typename std::list<EventDate<T>>::iterator it;
      //for (it=eventlist.begin(); it!=eventlist.end(); it++)
      for (auto it=eventlist.begin(); it!=eventlist.end(); it++)
      {
        // Om händelsen (strängen) finns i kalendern
        if ( *it->date > *actual_date )  
        {
          os << *it->date << " : " << it->event << std::endl;   
        } 
      }
    }
    return os;     
  }

  template <typename T>
  std::ostream& operator<<(std::ostream& os, const Calendar<T>& cal)
  {
    cal.autoprint(os);
    return os;
  }

}
#endif

