#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
	private:
		enum type_t = {human, dragon, wizard, monster};
		enum directions_t = {north, south, west, east};

		const int health;
		const std::tring name;
		const type_t type;
		 
		int remaining_health;
	
	public:
		Character(int health, std::string name, type_t type) :
			health(health),
			name(name),
			type(type),
			remaining_health(health) {};
		
		inline const int life() const { return health; }
		inline const int remaining_life() const 
                {  return remaining_health; }
          //---------- . -------------- . -----------------
		inline const type_t type() const { return type; }
		inline const std::string name() const { return name; }

		void action() = 0;
		void go(directions_t direction) = 0;
		void fight(Character character) = 0;
		void pick_up(Object item) = 0;
		void drop(Object item) = 0;
		void talk_to(Character character) = 0;

};

#endif
