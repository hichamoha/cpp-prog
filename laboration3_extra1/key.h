#ifndef KEY_H
#define KEY_H

#include "object.h"

#include <string>

namespace camelot {

    /**
     * A key may be used for locking and unlocking doors. It utilises
     * a special keycode which has to agree with the corresponding 
     * code for the door.
     */
    class Key : public Object {
        public:
            Key(std::string);
            virtual int weight() const;
            virtual int volume() const;
            virtual int price() const;
            virtual std::string type() const;
            virtual bool operator==(Key &) const;

            std::string get_key_code() const;

            virtual void saveObj(std::fstream &);

        private:
            std::string key_code;

    };

}

#endif /* KEY_H */
