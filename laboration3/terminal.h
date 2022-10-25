#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <map>

namespace camelot {
    class Terminal {
      public:
        int parser();
        static bool add_function(std::string, int (*)(std::string));
        static const std::map<std::string, int (*)(std::string)> get_functions();
        static void print(std::string);
      private:
        static std::map<std::string, int (*)(std::string)> functions;
    };
}

#endif // TERMINAL_H

