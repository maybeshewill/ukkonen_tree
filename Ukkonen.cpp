#include <iostream>

#include "Ukkonen.h"

void BaseUkkonen::link(Node* node, int begin, int end, Node* to)
{
    string symbol = parser->getWord(begin);
    node->edges[symbol] = to;
    to->begin = begin;
    to->end = end;
}

Node* BaseUkkonen::checkEdge(Node* node, string symbol)
{
    if ( node == dummy )
        return root;
    else
        return getEdge(node, symbol);
}

Node* BaseUkkonen::getEdge(Node* node, string symbol)
{
    if ( node->edges.find(symbol) != node->edges.end() )
        return node->edges[symbol];
    else
        return NULL;
}

void BaseUkkonen::clear()
{
    if (root)
        delete root;
    if (dummy) 
        delete dummy;
}

SplitResult BaseUkkonen::testAndSplit(Node* node, int begin, int end, string symbol)
{
    if (end <= begin)
    {
        if ( ( node->edges.find(symbol) == node->edges.end() ) && (node != dummy) )
            return make_pair(false, node);
        else
            return make_pair(true, node);
    }
    else
    {
        Node* current = checkEdge(node, parser->getWord(begin));

        string temp = parser->getWord(current->begin + end - begin);
        if (symbol == temp)
        {
            return make_pair(true, node);
        }

        Node* newNode = new Node(node);
        current->parent = newNode;

        link(node, current->begin, current->begin + end - begin, newNode);
        link(newNode, current->begin + end - begin, current->end, current);

        return make_pair(false, newNode);
    }
}

ActivePoint BaseUkkonen::update(Node* node, int begin, int end)
{
    SplitResult splitRes;
    Node* oldR = root;

    string symbol = parser->getWord(end);
    splitRes = testAndSplit(node, begin, end, symbol);

    while ( !splitRes.first )
    {
        Node* node1 = new Node(splitRes.second);
        link(splitRes.second, end, parser->totalLength, node1);

        if (oldR != root)
            oldR->suffix = splitRes.second;
        oldR = splitRes.second;

        ActivePoint newPoint = canonize(node->suffix, begin, end);
        node = newPoint.first;
        begin = newPoint.second;

        splitRes = testAndSplit(node, begin, end, parser->getWord(end));
    }

    if (oldR != root)
        oldR->suffix = splitRes.second;

    return make_pair(node, begin);
}

ActivePoint BaseUkkonen::canonize(Node* node, int begin, int end)
{
    if (end <= begin)
    {
        return make_pair(node, begin);
    }
    else
    {
        Node* current = checkEdge(node, parser->getWord(begin));

        while (end - begin >= current->end - current->begin)
        {
            begin += current->end - current->begin;
            
            node = current;

            if ( end > begin)
            {
                current = checkEdge(node, parser->getWord(begin));
            }
        }
        return make_pair(node, begin);
    }
}

void BaseUkkonen::build()
{
    for (int i = 0; i < parser->totalLength; ++i)
    {
        point = update(point.first, point.second, i);
        point = canonize(point.first, point.second, i + 1);
    }
}

void BaseUkkonen::init()
{   
    clear();
 
    dummy = new Node();
    root = new Node();
    root->suffix = dummy;

    point = make_pair(root, 0);

    build();

    printTree(root, 0, 0, "");
    return;
}

void BaseUkkonen::printTree(Node *node, int start = 0, int end = 0, string prefix = "")
{
    cout << prefix;
    for (int i = start; i < end && i < parser->totalLength; i++)
    {
        cout << parser->getWord(i);
    }
    cout << " [ " << node << " ]";
    if (node->suffix != NULL)
        cout << " Suffix = " << node->suffix;
    cout << endl;

    for (map<string, Node*>::iterator it = node->edges.begin(); it != node->edges.end(); ++it)
    {
        Node* printed = it->second;
        if (printed != NULL)
        {
            printTree(printed, printed->begin,
                      printed->end, prefix + "   ");
        }
    }
}
