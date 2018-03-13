#ifndef SEARCHBOX_H
#define SEARCHBOX_H


#include <QLineEdit>
#include "suggestcompletion.h"

class SearchBox: public QLineEdit
{
    Q_OBJECT

public:
    SearchBox(bool is_student = IS_STUDENT,QWidget *parent = 0);


private:
    SuggestCompletion *completer;
    bool judge;
};

#endif // SEARCHBOX_H
