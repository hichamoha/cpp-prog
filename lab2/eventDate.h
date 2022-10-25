// Class EventDate håller händelser (såsom julafton, födelsedag) kopplade till datum

# include "julian.h"
# include "gregorian.h"

namespace lab2
{
  template <typename T>
  class EventDate
  {
  public:
    std::string event;
    T* date;

    EventDate();
    EventDate(const EventDate & );
    EventDate(std::string, int , int , int);	
    ~EventDate();

    T& get_dateOfEvent();
  };

  template <typename T>
    EventDate<T>::EventDate()
    {
      event = "";
      date = new T();
    }

  template <typename T>
    EventDate<T>::EventDate(const EventDate & ed)
    {
      date = new T(ed.date);
      event = ed.event;
    }

  template <typename T>
    EventDate<T>::EventDate(std::string title, int day, int month, int year)
    {
	  event = title;
   	  date = new T(year,month,day);
    }

  template <typename T>	
    EventDate<T>::~EventDate()
    {
	  delete date;
    }

  template <typename T>
    T& EventDate<T>::get_dateOfEvent()
    {
	  return *date;
    }  


}
