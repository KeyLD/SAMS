#ifndef STUDENT_H
#define STUDENT_H

#define ADD_LEGAL 0
#define CHECK_LEGAL 1

#include <QDialog>
#include "otherclass.h"
#include "hashtable.h"

extern QString path;

extern HashTable *student_ID_search;

extern HashTable *association_ID_search;
extern HashTable *association_name_search;

namespace Ui {
class Student;
}

class Student : public QDialog
{
    Q_OBJECT

public:
    explicit Student(StudentNode *student = NULL,QWidget *parent = 0);
    ~Student();
    QString getID();
    QString getName();
    bool getSex();
    QString getGrade();
    QString getMajor();
    QString getIntroduce();
    QStringList getJionedAssociation();

    void setSex(const bool &_sex);
    void setGrade(const QString _grade);
    void setMajor(const QString &_major);
    void setIntroduce(const QString &_introduce);
    void setJionedAssociation(const QStringList &_joined_association);

    void setAll();

    bool JudgeLegal(const int &judge,Student &student);
    void AutoJoinedComplete();

signals:
    void ReceiveData(Student &);
    void ChangeData(Student &);

public slots:
    void StudentAccept();

private:
    Ui::Student *ui;

    bool is_change;
    int index;
    QString ID;
    QString name;
    bool sex;        //true is man,false is woman
    QString grade;
    QString major;
    QString introduce;
    QStringList joined_association;

    bool HasRepeatID(QString);
    void ShowWarning(QString);
    void Reset();

};

#endif // STUDENT_H
