#include "hashtable.h"
#include <QDebug>

HashTable::HashTable()
{
    Init();
}

HashTable::~HashTable()
{
    delete []hash_array;
}

void HashTable::Init()
{
    len = 100;
    hash_array = new HashNode [len];
    for(int i = 0;i < len; i++) {
        hash_array[i].hash = -1;
    }
    size = 0;
    max_cnt = 1;
}

int HashTable::Search(const QString &key)
{
    int reflect = Reflect(key);
    int pos = reflect;
    //qDebug()<<"hash "<<hash_array[pos].hash;
    for(int i = 1 ; hash_array[pos].hash != reflect && i < max_cnt ; i++ ){
        pos = (pos + 1) % len;
    }
    //qDebug()<<QString("pos %1 ").arg(pos);
    //qDebug()<<QString("reflect %1").arg(reflect);
    //qDebug()<<QString("value %1").arg(hash_array[pos].value);
    if(hash_array[pos].hash == reflect)
        return hash_array[pos].value;
    else
        return NO_RESULT;
}

void HashTable::Insert(const QString &key,const int &value)
{
    int reflect = Reflect(key);
    int pos = reflect;
    if(hash_array[pos].hash==-1) {
        hash_array[pos].hash = reflect;
        hash_array[pos].value = value;
        hash_array[pos].key = key;
        hash_array[pos].count = 1;
    } else {
        int cnt = 1;
        do
        {
            pos = (pos+1)%len;
            cnt++;
        } while(hash_array[pos].hash!=-1&&cnt<len);
        if(cnt==len) {
            int old_len = len;
            len *= 2;
            HashNode *tmp_hash = new HashNode[len]; //新申请两倍空间

            HashNode *swap_tmp;// 交换地址
            swap_tmp = tmp_hash;
            tmp_hash = hash_array;
            hash_array = swap_tmp;

            for(int i=0;i<old_len;i++)
                Insert(tmp_hash[i].key,tmp_hash[i].value);
            Insert(key,value);
            delete tmp_hash;
        } else {
            hash_array[pos].hash = reflect;
            hash_array[pos].key = key;
            hash_array[pos].value = value;
            hash_array[pos].count = cnt;
            max_cnt = max_cnt>cnt?max_cnt:cnt;
        }
    }
    size++;
}

bool HashTable::Delete(const QString &key)
{
    int reflect = Reflect(key);
    int pos = reflect;
    for(int i = 0 ; hash_array[i].hash != reflect && i < max_cnt ; i++ ){
        pos = (pos + 1) % len;
    }
    if(hash_array[pos].hash == reflect) {
        hash_array[pos].hash = -1;
        //  选择性更新max_cnt 如果数据量非常小  可以不更新 更新反而会得不偿失
        size--;
        return true;
    } else {
        return false;
    }
}

int HashTable::Size()
{
    return size;
}

int HashTable::Reflect(QString key)
{
    int reflect = 0;
    std::string str = key.toStdString().c_str();
    const char* ch = str.c_str();
    for(int i=0;i<key.length();i++)
        reflect = (reflect + ch[i] - '0'+len*2)%len;
    //需测试
    qDebug()<<key<<"        "<<reflect;
    return reflect;
}

int HashTable::Length()
{
    return len;
}
