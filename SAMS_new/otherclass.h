#ifndef NODEINDEX_H
#define NODEINDEX_H

#include <QString>
#include <QDate>

class NodeIndex
{
public:
    NodeIndex() {}
    NodeIndex(const int &_index,
              const QString &_ID,
              const QString &_name)
    {
        index = _index;
        ID = _ID;
        name = _name;
        next = NULL;
    }

    int index;
    QString ID;
    QString name;

    NodeIndex *next;
};

class StudentNode
{
public:
    StudentNode() {}
    StudentNode(const int &_index,
                const QString &_ID,
                const QString &_name,
                const bool &_sex,
                const QString &_grade,
                const QString &_major,
                const QStringList &_joined_association = QStringList(),
                const QString &_introduce = QString("无"))
    {
        index = _index;
        ID = _ID;
        name = _name;
        sex = _sex;
        grade = _grade;
        major = _major;
        joined_association = _joined_association;
        introduce = _introduce;
    }

    int index;
    QString ID;
    QString name;
    bool sex;
    QString grade;
    QString major;
    QStringList joined_association;
    QString introduce;

    //StudentNode *next;


    bool operator <(const StudentNode &cmp) const { return index < cmp.index; }
};

class AssociationNode
{
public:
    AssociationNode() {}
    AssociationNode(const int &_index,
                    const QString &_ID,
                    const QString &_name,
                    const QDate &_created_time,
                    const QString &_chairman,
                    const QString &_vice_chairman = QString("暂缺"),
                    const QString &_secretary = QString("暂缺"),
                    const QStringList &_other_member = QStringList(),
                    const QString &_introduce = QString("无"))
    {
        index = _index;
        ID = _ID;
        name = _name;
        created_time = _created_time;
        chairman = _chairman;
        vice_chairman = _vice_chairman;
        secretary = _secretary;
        other_member = _other_member;
        introduce = _introduce;
    }

    int index;
    QString ID;
    QString name;
    QDate created_time;
    QString chairman;
    QString vice_chairman;
    QString secretary;
    QStringList other_member;
    QString introduce;

    bool operator <(const AssociationNode &cmp) const { return index < cmp.index; }
};

#endif // NODEINDEX_H

/*
 * 包含的数据结构与总思想
 *
 * 链表存储 索引文件  index -> ID name
 *
 * 红黑树而非 动态数组  index -> AssociationNode 因为涉及了很多的删除操作
 * 红黑树而非 动态数组  index -> StudentNode
 * 红黑树  student 的 id 和 name -> index
 * 红黑树  association 的 id 和 name -> index
 *
 */
