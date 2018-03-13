#ifndef CHANGESET_H
#define CHANGESET_H

#define NO_RESULT -1

#define STUDENT 1
#define ASSOCIATION 2
#define STUDENT_AND_ASSOCIATION 3

#define DELETE 1
#define CHANGE 2
#define JOIN 3
#define EXIT 4

#include <QDialog>
#include <QPushButton>
#include "otherclass.h"
#include "searchbox.h"
#include "keylist.h"
#include "hashtable.h"
#include "student.h"
#include "association.h"

extern QString path;
extern KeyList *student_list;
extern KeyList *association_list;

extern HashTable *student_ID_search;

extern HashTable *association_ID_search;
extern HashTable *association_name_search;

extern RBTree<int,StudentNode> *student_DB;
extern RBTree<int,AssociationNode> *association_DB;

namespace Ui {
class ChangeSet;
}

class ChangeSet : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeSet(int _obj,int _op,QWidget *parent = 0);
    ~ChangeSet();

public slots:
    void changeStudent(Student &student);
    void changeAssociation(Association &association);

private slots:
    void OperationSet();

private:
    Ui::ChangeSet *ui;
    int obj;
    int op;
    QFormLayout *layout;
    SearchBox *student_search;
    SearchBox *association_search;

    bool DeleteOperation();
    bool ChangeOperation();
    bool JoinOperation(QString student,const QString &association);
    bool ExitOperation(QString student,const QString &association);

    void ShowHint(const QString &type,const QString &title);
    int getIdx(int judge, QString edited);
    void StudentExitAssociation(const QString &student, const QString &association);
};

#endif // CHANGESET_H
