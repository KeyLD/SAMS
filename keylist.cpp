#include "keylist.h"
#include <QDebug>

KeyList::KeyList()
{
    init();
}

KeyList::~KeyList()
{
    clear();
}

void KeyList::init()
{
    head = new NodeIndex;
    head -> next = NULL;
    tail = head;
}


void KeyList::push_back(const NodeIndex &value)
{
    NodeIndex *tmp_insert;
    tmp_insert = new NodeIndex(value);

    tail->next = tmp_insert;
    tail = tmp_insert;
    tail->next=NULL;

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

bool KeyList::erase(const QString &value)
{
    bool is_ID = value[0].isNumber();
    NodeIndex *tmp;
    NodeIndex *pre = head;
    if(is_ID){
        while (pre->next != NULL) {
            if(pre->next->ID==value) {
                tmp = pre->next;
                pre->next = tmp->next;
                delete tmp;
                return true;
            }
            pre = pre->next;
        }
    } else {
        while (pre->next != NULL) {
            if(pre->next->name == value ) {
                tmp = pre->next;
                pre->next = tmp->next;
                delete tmp;
                return true;
            }
            pre = pre->next;
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
