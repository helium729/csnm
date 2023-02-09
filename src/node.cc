#include "node.h"

namespace csnm
{
    node::node(std::string id)
    {
        this->id = id;
    }

    node::node(std::string id, literal* l_value)
    {
        this->id = id;
        this->type = l;
        this->l_value = l_value;
    }

    node::node(std::string id, literal_operator o_value)
    {
        this->id = id;
        this->type = o;
        this->o_value = o_value;
    }

    node::~node()
    {
    }

    void node::push_down_reverse()
    {
        if (!this->reversed)
            return;
        if (this->type == l)
            return;

        if (this->o_value == AND)
            this->o_value = OR;
        else if (this->o_value == OR)
            this->o_value = AND;
        //for each node in children
        for (std::vector<node *>::iterator it = this->children.begin(); it != this->children.end(); ++it)
        {
            //if its a literal
            if ((*it)->type == l)
            {
                //reverse it
                (*it)->reversed = !(*it)->reversed;      
            }
            //if its an operator
            else
            {
                //reverse it
                (*it)->reversed = !(*it)->reversed;
                //push down the reverse
                (*it)->push_down_reverse();
            }
        }
    }

    literal_state node::get_state()
    {
        if (this->type == l)
        {
            if (this->reversed)
                return (!(*(this->l_value)));
            else
                return this->l_value->get_state();
        }
        else 
        {
            std::string s("temp_id");
            literal temp1(s);
            literal temp2(s);
            switch(this->o_value)
            {
                case AND:
                    if(children.size() == 0)
                        throw std::exception();
                    temp1.set_state(children[0]->get_state());
                    for (std::vector<node *>::iterator it = this->children.begin() + 1; it != this->children.end(); ++it)
                    {
                        node * n = *it;
                        temp2.set_state(n->get_state());
                        temp1.set_state(temp1 & temp2);
                    }
                    if (this->reversed)
                        return (!temp1);
                    else
                        return temp1.get_state();
                case OR:
                    if(children.size() == 0)
                        throw std::exception();
                    temp1.set_state(children[0]->get_state());
                    for (std::vector<node *>::iterator it = this->children.begin() + 1; it != this->children.end(); ++it)
                    {
                        node * n = *it;
                        temp2.set_state(n->get_state());
                        temp1.set_state(temp1 | temp2);
                    }
                    if (this->reversed)
                        return (!temp1);
                    else
                        return temp1.get_state();                     
                default:
                    throw std::exception();
            }
        }
    }
}