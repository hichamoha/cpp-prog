#include <stdexcept>

class BadFileFormatException : public std::runtime_error {
    public:
        // constructor
        BadFileFormatException() : std::runtime_error(" Try Again, Bad file format") {}
        /* std::Runtime_error: Problem that can be detected 
           only at run time. Lippman p197 */
};
