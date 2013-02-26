#pragma once

#include <map>
#include <string>

using namespace std;

struct Node
{
    int begin, end;

    Node* suffix;
    Node* parent;
    map<string, Node*> edges;

    Node(): 
            begin(-1)
        ,   end(0)
        ,   suffix(NULL)
        ,   parent(NULL)
        ,   edges(map<string,Node*>())
    {}

    Node(Node* parent):
            begin(-1)
        ,   end(0)
        ,   suffix(NULL)
        ,   parent(parent)
        ,   edges(map<string, Node*>())
    {}

    ~Node()
    {
        for (map<string, Node*>::iterator it = edges.begin(); it != edges.end(); ++it)
        {
            if (it->second)
                delete it->second;
        }
    }
};
