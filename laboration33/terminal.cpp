#include "terminal.h"
#include <iostream>

//terminal color codes only for linux
#define RESET  "\033[0;0m"
#define RED    "\033[0;31m"
#define YELLOW "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BOLD   "\033[1m\033[0;0m"

namespace camelot {
  /* Skapa en map och låt namnet på varje kommando vara nyckel till en pointer
     till kommandot. 
     NOTE: (See Lippman page 577) In C++, function tables are easy to implement
     using a map. In this case, we'll use a string corresponding to the 'name' 
     as the KEY; the VALUE will be the function that implements that 'command'. */

  // maps a 'commando-name' to a POINTER TO A FUNCTION taking a string and return an int
  std::map<std::string, int (*)(std::string)> Terminal::functions;

// parser() .......................................................................
/* parser takes a command entered by the player, interprets it, and then execute 
   it. parser must recognize words.*/

  int Terminal::parser() {

    std::string words;
    std::cout << ">>> ";
    // use getline to read the input (a line at a time)
    getline(std::cin, words);
    // eof tests for end-of-file
    if (std::cin.eof()) {
      return 1;

            /* NOTE: the main function is allowed to terminate without a return.
               Status Indicator: a zero return indicate ssuccess; 
                                 most other values indicate failure.*/
   }

   // use istringstream to process each word in the current line
   std::string command = words.substr(0, words.find_first_of(' '));
   std::string argument = words.substr(words.find_first_of(' ')+1);
        
   auto map_it = functions.find(command);
   //std::map<std::string, int (*)(std::string)>::iterator map_it = 
        //                                               functions.find(command);

   /* NOTE: find() searches the container,map, for an element with a key equivalent 
      to command and returns an ITERATOR to it if found, otherwise it returns 
      an iterator to map::end (off-the-end iterator).
   */
   // compare the current iterator to the off-the-end iterator
   if (map_it != functions.end()) {
     // derefrence the iterator to return the value: argument
     return map_it->second(argument);
   }
   else {
     std::cout << " \t No such command" << std::endl;
   }
   return 0;
  }

// add_function() ..............................................................
    /*
     * Add a static member function to the list of available functions.
     * NOTE: the function HAVE to be a static member function or an ordinary 
       function (outside of a class)
     * std::pair couples together a pair of values, which may be of different
       types. The individual values can be accessed through it public members
       first and second. 
     * std::map is an associative container that store elements formed by a 
       combination of a key value and a mapped value, following a specific order.
       When we fetch an element from a map, we get an object of type pair.
     */
  bool Terminal::add_function(std::string str, int (*pf)(std::string)) { 
                               //pf is a function pointer

    // Declaring and initializing ret (Lippman p 433)
    // ret holds the value returned  by insert(), which is a 'pair'
    std::pair<std::map<std::string, int (*)(std::string)>::iterator, bool> ret;

    /* when we insert into a map, we must remember that the element 
       type is a pair. Under the new standard c++11, the easiest way to 
       create a pair is to use brace initialization inside the argument list.
       functions.insert({str, pf});
    */
    //ret = Terminal::functions.insert(make_pair(str, pf));
    ret = Terminal::functions.insert({str, pf}); // FIXME C++11
    //ret = Terminal::functions.insert(std::pair<std::string, 
      //                                         int (*)(std::string)>(str, pf));
    return ret.second;
    }

// get_functions() ..............................................................
    const std::map<std::string, int (*)(std::string)> Terminal::get_functions() {
        return functions;
    }

// print() .....................................................................
    void Terminal::print(std::string s) {

        unsigned int cols = 80;  // the last column on the screen
        ///////
        //s.insert(0, "| ");
        s.insert(0, "  ");
        unsigned int row = 0;    // counter of letters in the string
                                 // in every row
        
        for (unsigned int i = 0; i <= s.length(); i++, row++) {
            if (row == cols) {
                //s.insert(i, " |\n");
                s.insert(i, "  \n");
                //s.insert(i+3, "| ");
                s.insert(i+3, "  ");
                row = 0;
                i = i+3;
            }
            else if (s[i] == '\n') {
                s.insert(i, cols-row, ' ');
                //s.insert(i   + (cols-row), " |");
                s.insert(i   + (cols-row), "  ");
                //s.insert(i+3 + (cols-row), "| ");
                s.insert(i+3 + (cols-row), "  ");
                i = i + 3 + (cols-row);
                row = 0;
            }
        }// end for

        s.append(cols-row +2, ' ');
        //s.append("|");
        s.append(" ");
        /////////////
        std::string line = "";
        line.append(cols+2, '.'); // add newline of "-" 

        //std::cout << YELLOW << line << std::endl;
        std::cout << RESET << s << std::endl;
        std::cout << YELLOW << line << std::endl;
    }// end print()
}
