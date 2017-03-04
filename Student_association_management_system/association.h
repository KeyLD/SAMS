#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <QDialog>
#include <QDate>
#include "otherclass.h"
#include "keylist.h"
#include "hashtable.h"

extern QString path;
extern KeyList *student_list;
extern KeyList *association_list;

extern HashTable *student_ID_search;

extern HashTable *association_ID_search;
extern HashTable *association_name_search;

extern QMap<int,StudentNode> *student_DB;
extern QMap<int,AssociationNode> *association_DB;

namespace Ui {
class Association;
}

class Association : public QDialog
{
    Q_OBJECT

public:
    explicit Association(QWidget *parent = 0);
    QString GetSerialNumber();
    QString GetName();
    QDate GetCreatedTime();
    QString GetChairman();
    QString GetViceChairman();
    QString GetSecretary();
    QStringList GetOtherMember();
    QString GetIntroduce();
    ~Association();

signals:
    void ReceiveData(Association &);

public slots:
    void AssociationAccept();


private:
    Ui::Association *ui;

    QMap<QString,QString> *students;
    int index;
    QString serial_number;
    QString name;
    QDate created_time;
    QString introduction;
    QString chairman;
    QString vice_chairman;
    QString secretary;
    QStringList other_member;

    bool InitStudents();
    bool HasRepeatID(QString &);
    bool HasRepeatName(QString &);
    bool CheckExist(const QString& student_ID);
    bool CheckOnlyNumber(const QString &str);
    void ShowWarning(const QString& warning);
    void Reset();

};

#endif // ASSOCIATION_H
