#ifndef KEYLIST_H
#define KEYLIST_H

#define FOR_ALL_KEYLIST(LIST) for(NodeIndex *it=LIST->getHead();it!=NULL;it=it->next)

#include "otherclass.h"

class KeyList
{
public:
    KeyList();
    ~KeyList();
    NodeIndex *getHead();
    void init();
    void push_back(const NodeIndex &value);
    void clear();
    bool erase(const QString &value);
    bool isEmpty();
    NodeIndex* theNewestOne();

private:
    NodeIndex *head;
    NodeIndex *tail;

};

#endif // KEYLIST_H
