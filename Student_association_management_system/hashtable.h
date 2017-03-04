#ifndef HASHTABLE_H
#define HASHTABLE_H

#define NO_RESULT -1

#include <QString>

class HashNode
{
public:
    HashNode() {}
    QString key;
    int hash;
    int count;
    int value;
};

class HashTable
{
public:
    HashTable();
    ~HashTable();
    void Init();
    int Search(const QString &key);
    void Insert(const QString &key,const int &value);
    bool Delete(const QString &key);
    int Size();
    int Length();

private:
    int size;
    int len;
    int max_cnt;
    HashNode *hash_array;
    int Reflect(QString key);
};

#endif // HASHTABLE_H
