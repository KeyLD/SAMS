#ifndef JIONORQUIT_H
#define JIONORQUIT_H
#define IS_STUDENT true
#define IS_ASSOCIATION false
#define DELETE 1
#define CHANGE 2
#define JOIN 3
#define EXIT 4

#include <QDialog>
#include "otherclass.h"
#include "searchbox.h"

extern QString path;
extern QList<NodeIndex> *student_list;
extern QList<NodeIndex> *association_list;

extern QMap<QString,int> *student_ID_search;

extern QMap<QString,int> *association_ID_search;
extern QMap<QString,int> *association_name_search;

extern QMap<int,StudentNode> *student_DB;
extern QMap<int,AssociationNode> *association_DB;


namespace Ui {
class JionOrQuit;
}

class JionOrQuit : public QDialog
{
    Q_OBJECT

public:
    explicit JionOrQuit(QWidget *parent = 0);
    ~JionOrQuit();

private:
    Ui::JionOrQuit *ui;
    SearchBox *student_search;
    SearchBox *association_search;
};

#endif // JIONORQUIT_H
