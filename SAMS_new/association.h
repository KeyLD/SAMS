#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#define ADD_LEGAL 0
#define CHECK_LEGAL 1

#include <QDialog>
#include <QDate>
#include "otherclass.h"
#include "keylist.h"
#include "hashtable.h"
#include "rbtree.h"

extern HashTable *student_ID_search;

extern RBTree<int,StudentNode> *student_DB;

extern HashTable *association_ID_search;
extern HashTable *association_name_search;

namespace Ui {
class Association;
}

class Association : public QDialog
{
    Q_OBJECT

public:
    explicit Association(AssociationNode *association = NULL,QWidget *parent = 0);
    ~Association();
    QString getSerialNumber();
    QString getName();
    QDate getCreatedTime();
    QString getChairman();
    QString getViceChairman();
    QString getSecretary();
    QStringList getOtherMember();
    QString getIntroduce();

    void setCreatedTime(const QString &_created_time);
    void setChairman(const QString &_chairman);
    void setViceChairman(const QString &_vice_chairman);
    void setSecretary(const QString &_secretary);
    void setOtherMember(const QStringList &_other_member);
    void setIntroduce(const QString &_introduce);

    void setAll();

    bool JudgeLegal(const int &judge,Association &association);
    void AutoOtherComplete();

signals:
    void ReceiveData(Association &);
    void ChangeData(Association &);


public slots:
    void AssociationAccept();


private:
    Ui::Association *ui;

    bool is_change;

    int index;
    QString serial_number;
    QString name;
    QDate created_time;
    QString introduce;
    QString chairman;
    QString vice_chairman;
    QString secretary;
    QStringList other_member;

    bool HasRepeatID(QString &);
    bool HasRepeatName(QString &);
    bool CheckExist(const QString& student_ID);
    bool CheckOnlyNumber(const QString &str);
    void ShowWarning(const QString& warning);
    void Reset();
    QString getStdentName(const QString &edited);

};

#endif // ASSOCIATION_H
