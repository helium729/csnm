#include "csnm.h"

namespace csnm
{
    csnm::csnm()
    {
    }

    csnm::csnm(node* root)
    {
        this->root = root;
    }

    csnm::~csnm()
    {
    }

    void csnm::add_node(node* n)
    {
        std::string nid = n->id;
        //check if node already exists
        if (this->nodes.find(nid) != this->nodes.end())
        {
            //if children is not empty, throw error
            if (n->children.size() != 0)
            {
                throw "Node already exists";
            }
            else 
            {
                this->nodes[nid] = n;
            }
        }
        else
        {
            //add node to nodes
            this->nodes[nid] = n;
        }
        if (nid == "_")
        {
            this->root = n;
        }
        for (int i = 0; i < n->children.size(); i++)
        {
            nodes.insert(std::pair<std::string, node*>(n->children[i]->id, nullptr));
        }

        return;
    }

    void csnm::check()
    {
        //check if root exists
        if (this->root == NULL)
        {
            throw "Root node does not exist";
        }
        //go through nodes with DFS
        std::vector<node*> stack;
        node * now;
        stack.push_back(this->root);
        while (stack.size() != 0)
        {
            now = stack.back();
            //set check state
            now->checked = true;
            //check if node is literal
            if (now->children.size() == 0)
            {
                now->type = l;
                //check if literal is already defined
                if (this->literals.find(now->id) != this->literals.end())
                {
                    now->l_value = &(this->literals[now->id]);
                }
                else 
                {
                    //add literal to literals
                    literal l(now->id);
                    this->literals[now->id] = l;
                    now->l_value = &(this->literals[now->id]);
                }
                stack.pop_back();
            }
            else
            {
                stack.pop_back();
                //for each child
                for (int i = 0; i < now->children.size(); i++)
                {
                    //check if child is checked
                    if (now->children[i]->checked == false)
                    {
                        //if not, push to stack
                        stack.push_back(now->children[i]);
                    }

                }
            }
        }
        //end of DFS

        //erase useless nodes
        std::vector<std::string> erase_list;
        //for each node
        for (auto it = this->nodes.begin(); it != this->nodes.end(); it++)
        {
            //check if it is checked
            if (it->second->checked == false)
            {
                //if not, add to erase list
                erase_list.push_back(it->first);
            }
        }
        //erase nodes
        for (int i = 0; i < erase_list.size(); i++)
        {
            this->nodes.erase(erase_list[i]);
        }
        //end of erase useless nodes
    
        //ToDo: Check for circular references

    }
}