#include "literal.h"

namespace csnm
{
    literal::literal(std::string & id)
    {
        this->id = id;
        this->state = unknown;
    }

    literal::literal(std::string & id, literal_state state)
    {
        this->id = id;
        this->state = state;
    }

    literal::~literal()
    {
    }

    std::string literal::get_id()
    {
        return this->id;
    }

    literal_state literal::get_state()
    {
        return this->state;
    }

    void literal::set_state(literal_state state)
    {
        this->state = state;
    }

    literal_state literal::operator!()
    {
        switch(this->state)
        {
            case confirmed_1:
                return confirmed_0;
            case confirmed_0:
                return confirmed_1;
            case guessed_1:
                return guessed_0;
            case guessed_0:
                return guessed_1;
            case unknown:
                return unknown;
            default:
                throw std::exception();
        }
    }

    literal_state literal::operator&(literal & l)
    {
        switch(this->state)
        {
            case confirmed_1:
                return l.get_state();
            case confirmed_0:
                return !l;
            case guessed_1:
                switch(l.get_state())
                {
                    case confirmed_1:
                        return guessed_1;
                    case confirmed_0:
                        return confirmed_0;
                    case guessed_1:
                        return guessed_1;
                    case guessed_0:
                        return guessed_0;
                    case unknown:
                        return unknown;
                    default:
                        throw std::exception();
                }
            case guessed_0:
                switch(l.get_state())
                {
                    case confirmed_1:
                        return guessed_0;
                    case confirmed_0:
                        return confirmed_0;
                    case guessed_1:
                        return guessed_0;
                    case guessed_0:
                        return guessed_0;
                    case unknown:
                        return unknown;
                    default:
                        throw std::exception();
                }
            case unknown:
                return unknown;
            default:
                throw std::exception();
        }
    }

    literal_state literal::operator|(literal & l)
    {
        switch(this->state)
        {
            case confirmed_1:
                return confirmed_1;
            case confirmed_0:
                return l.get_state();
            case guessed_1:
                switch(l.get_state())
                {
                    case confirmed_1:
                        return confirmed_1;
                    case confirmed_0:
                        return guessed_1;
                    case guessed_1:
                        return guessed_1;
                    case guessed_0:
                        return guessed_1;
                    case unknown:
                        return unknown;
                    default:
                        throw std::exception();
                }
            case guessed_0:
                switch(l.get_state())
                {
                    case confirmed_1:
                        return confirmed_1;
                    case confirmed_0:
                        return guessed_0;
                    case guessed_1:
                        return guessed_1;
                    case guessed_0:
                        return guessed_0;
                    case unknown:
                        return unknown;
                    default:
                        throw std::exception();
                }
            case unknown:
                return unknown;
            default:
                throw std::exception();
        }
    }
}