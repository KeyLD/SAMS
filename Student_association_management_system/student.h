#ifndef STUDENT_H
#define STUDENT_H

#include <QDialog>

extern QString path;

namespace Ui {
class Student;
}

class Student : public QDialog
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = 0);
    ~Student();
    QString GetID();
    QString GetName();
    bool GetSex();
    int GetGrade();
    QString GetMajor();
    QString GetIntroduce();
    QStringList GetJionedAssociation();

signals:
    void ReceiveData(Student &);

public slots:
    void StudentAccept();

private:
    Ui::Student *ui;

    int index;
    QString ID;
    QString name;
    bool sex;        //true is man,false is woman
    int grade;
    QString major;
    QString introduce;
    QStringList joined_association;

    bool HasRepeatID(QString);
    void ShowWarning(QString);
    void Reset();

};

#endif // STUDENT_H
