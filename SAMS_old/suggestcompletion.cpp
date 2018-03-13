#include "suggestcompletion.h"


SuggestCompletion::SuggestCompletion(bool is_student,QLineEdit *parent):
    judge(is_student),QObject(parent), editor(parent)
{

    popup = new QTreeWidget;
    popup->setWindowFlags(Qt::Popup);
    popup->setFocusPolicy(Qt::NoFocus);
    popup->setFocusProxy(parent);
    popup->setMouseTracking(true);

    popup->setColumnCount(1);
    popup->setUniformRowHeights(true);
    popup->setRootIsDecorated(false);
    popup->setEditTriggers(QTreeWidget::NoEditTriggers);
    popup->setSelectionBehavior(QTreeWidget::SelectRows);
    popup->setFrameStyle(QFrame::Box | QFrame::Plain);
    popup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    popup->header()->hide();

    popup->installEventFilter(this);

    connect(popup, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            SLOT(doneCompletion()));

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), SLOT(autoSuggest()));
    connect(editor, SIGNAL(textEdited(QString)), timer, SLOT(start()));

}

SuggestCompletion::~SuggestCompletion()
{
    delete popup;
}

bool SuggestCompletion::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj != popup)
        return false;

    if (ev->type() == QEvent::MouseButtonPress) {
        popup->hide();
        editor->setFocus();
        return true;
    }

    if (ev->type() == QEvent::KeyPress) {

        bool consumed = false;
        int key = static_cast<QKeyEvent*>(ev)->key();
        switch (key) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            doneCompletion();
            consumed = true;

        case Qt::Key_Escape:
            editor->setFocus();
            popup->hide();
            consumed = true;

        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Home:
        case Qt::Key_End:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            break;

        default:
            editor->setFocus();
            editor->event(ev);
            popup->hide();
            break;
        }

        return consumed;
    }

    return false;
}

void SuggestCompletion::showCompletion(const QStringList &choices)
{

    if (choices.isEmpty())
        return;

    const QPalette &pal = editor->palette();
    QColor color = pal.color(QPalette::Disabled, QPalette::WindowText);

    popup->setUpdatesEnabled(false);
    popup->clear();
    for (int i = 0; i < choices.count(); ++i) {
        QTreeWidgetItem * item;
        item = new QTreeWidgetItem(popup);
        item->setText(0, choices[i]);
        item->setTextColor(0, color);
    }
    popup->setCurrentItem(popup->topLevelItem(0));
    popup->resizeColumnToContents(0);
    popup->setUpdatesEnabled(true);

    popup->move(editor->mapToGlobal(QPoint(0, editor->height())));
    popup->setFocus();
    popup->show();
}

void SuggestCompletion::doneCompletion()
{
    timer->stop();
    popup->hide();
    editor->setFocus();
    QTreeWidgetItem *item = popup->currentItem();
    if (item) {
        editor->setText(item->text(0));
        QMetaObject::invokeMethod(editor, "returnPressed");
    }
}

void SuggestCompletion::autoSuggest()
{
    QString str = editor->text();
    bool is_name = true;
    if(str[0].isNumber())
        is_name = false;
    QStringList choices;
    QString tmp_str;
    if(belongStudent()) {
        if(is_name) {
            FOR_ALL_KEYLIST(student_list) {
                tmp_str = it->name+"("+it->ID+")";
                if(tmp_str.indexOf(str) != -1) {
                    choices<<tmp_str;
                }
            }
        } else {
            FOR_ALL_KEYLIST(student_list) {
                if(it->ID.indexOf(str) != -1) {
                    choices<<(it->ID);
                }
            }
        }

    } else {
        if(is_name) {
            FOR_ALL_KEYLIST(association_list) {
                if(it->name.indexOf(str) != -1) {
                    choices<<(it->name);
                }
            }
        } else {
            FOR_ALL_KEYLIST(association_list) {
                if(it->ID.indexOf(str) != -1) {
                    choices<<(it->ID);
                }
            }
        }
    }
    showCompletion(choices);
}

void SuggestCompletion::preventSuggest()
{
    timer->stop();
}

bool SuggestCompletion::belongStudent()
{
    return judge == IS_STUDENT;
}

bool SuggestCompletion::belongAssociation()
{
    return judge == IS_ASSOCIATION;
}
