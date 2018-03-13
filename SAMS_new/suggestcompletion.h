#ifndef SUGGESTCOMPLETION_H
#define SUGGESTCOMPLETION_H
#define IS_STUDENT true
#define IS_ASSOCIATION false


#include <QtWidgets>
#include <QObject>
#include "otherclass.h"
#include "keylist.h"


QT_BEGIN_NAMESPACE
class QLineEdit;
class QTimer;
class QTreeWidget;
QT_END_NAMESPACE

extern QString path;
extern KeyList *student_list;
extern KeyList *association_list;

class SuggestCompletion :
        public QObject
{
    Q_OBJECT

public:
    SuggestCompletion(bool is_student = IS_STUDENT ,QLineEdit *parent = 0);
    ~SuggestCompletion();
    void setBelong(const bool &tmp_judge);
    bool belongStudent();
    bool belongAssociation();

    bool eventFilter(QObject *obj, QEvent *ev) override;
    void showCompletion(const QStringList &choices);


public slots:
    void doneCompletion();
    void preventSuggest();
    void autoSuggest();


private:
    bool judge;   //true is student, false is association
    QLineEdit *editor;
    QTreeWidget *popup;
    QTimer *timer;

};
//! [1]

#endif // SUGGESTCOMPLETION_H
