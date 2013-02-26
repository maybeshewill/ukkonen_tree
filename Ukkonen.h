#pragma once

#include <utility>

#include "Node.h"
#include "Parser.h"

typedef pair<Node*, int> ActivePoint;
typedef pair<bool, Node*> SplitResult;

class BaseUkkonen
{
protected:
    Node*                   dummy;
    Node*                   root;
    ActivePoint             point;
    BaseParser*             parser;


    ActivePoint             update(Node *node, int begin, int end);
    ActivePoint             canonize(Node *node, int begin, int end);
    SplitResult             testAndSplit(Node *node, int begin, int end, string word);
    void                    printTree(Node *node, int start, int end, string prefix);

    Node*                   getEdge(Node *node, string symbol);
    Node*                   checkEdge(Node *node, string symbol);
    void                    link(Node *node, int begin, int end, Node *to);

public:
    void init();
    void build();
    void clear();

    BaseUkkonen(BaseParser* initParser):
            dummy(NULL)
        ,   root(NULL)
        ,   parser(initParser)
    {
        point.first = NULL;
        point.second = 0;
    }

    virtual ~BaseUkkonen()
    {
        clear();
    }
};
