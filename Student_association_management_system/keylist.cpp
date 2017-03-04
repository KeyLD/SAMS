#include "keylist.h"
#include <QDebug>

KeyList::KeyList()
{
    init();
}

KeyList::~KeyList()
{
    NodeIndex *tmp;
    while (head->next != NULL) {
        tmp = head->next;
        head->next=tmp->next;
        delete tmp;
    }
    delete head;
}

void KeyList::init()
{
    head = new NodeIndex;
    head -> next = NULL;
    tail = head;
}


void KeyList::push_back(const NodeIndex &index)
{
    NodeIndex *tmp_insert;
    tmp_insert = new NodeIndex(index);

    /*
    tail->next = tmp_insert;
    tail = tmp_insert;
    */


    NodeIndex *tmp_next = head->next;
    head->next=tmp_insert;
    tmp_insert->next = tmp_next;


}

void KeyList::clear()
{
    NodeIndex *tmp;
    while (head->next != NULL) {
        tmp = head->next;
        head->next=tmp->next;
        delete tmp;
    }
    delete head;
}

bool KeyList::erase(const QString &index)
{
    bool is_ID = index[0].isNumber();
    NodeIndex *tmp;
    if(is_ID){
        while (head->next != NULL) {
            if(head->next->ID==index) {
                tmp = head->next;
                head->next = tmp->next;
                delete tmp;
                return true;
            }
        }
    } else {
        while (head->next != NULL) {
            if(head->next->name == index ) {
                tmp = head->next;
                head->next = tmp->next;
                delete tmp;
                return true;
            }
        }
    }
    return false;
}

bool KeyList::isEmpty()
{
    return head->next == NULL;
}

NodeIndex* KeyList::theNewestOne()
{
    return head->next;
}

NodeIndex* KeyList::getHead()
{
    return head->next;
}
