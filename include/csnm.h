#ifndef CSNM_H
#define CSNM_H

#include "defs.h"
#include "node.h"
#include "literal.h"

#include <map>

namespace csnm
{
    class csnm
    {
    public:
        csnm();
        csnm(node* root);
        virtual ~csnm();

        void add_node(node* n);
        void check();
        //ToDo Solve


    private:
        node* root;
        std::map<std::string, node*> nodes;
        std::map<std::string, literal> literals; 
    };
}

#endif