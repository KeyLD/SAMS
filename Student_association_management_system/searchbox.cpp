#include "searchbox.h"

SearchBox::SearchBox(bool is_student,QWidget *parent):
    judge(is_student),QLineEdit(parent)
{
    completer = new SuggestCompletion(judge,this);

    adjustSize();
    //resize(400, height());
    setFocus();
}
