#ifndef LITERAL_H
#define LITERAL_H

#include <string>
#include <exception>
#include "defs.h"

namespace csnm
{
    enum literal_state{confirmed_1, confirmed_0, guessed_1, guessed_0, unknown};
    enum literal_operator{AND, OR};

    class literal
    {
    public:
        literal(){};
        literal(std::string & id);
        literal(std::string & id, literal_state state);
        virtual ~literal();
        std::string get_id();
        literal_state get_state();
        void set_state(literal_state state);
        literal_state operator!();
        literal_state operator&(literal & l);
        literal_state operator|(literal & l);
        
    private:
        std::string id;
        literal_state state;
    };
}

#endif