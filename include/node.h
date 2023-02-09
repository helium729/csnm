#ifndef NODE_H
#define NODE_H

#include "literal.h"
#include <vector>

namespace csnm
{
    //l = literal
    //o = operator
    enum node_type{l, o};

    class node
    {
    public:
        node(std::string id);
        node(std::string id, literal* l_value);
        node(std::string id, literal_operator o_value);
        virtual ~node();

        std::string id;
        node_type type;
        bool reversed;
        literal* l_value;
        literal_operator o_value;
        std::vector<node *> children;

        bool checked = false;

        void push_down_reverse();
        literal_state get_state();
    };
}

#endif