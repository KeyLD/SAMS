/********************************************************************************
** Form generated from reading UI file 'association.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASSOCIATION_H
#define UI_ASSOCIATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Association
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *ID_label;
    QLineEdit *ID_lineEdit;
    QLabel *name_label;
    QLineEdit *name_lineEdit;
    QLabel *created_time_label;
    QDateEdit *created_time_dateEdit;
    QLabel *chairman_label;
    QLineEdit *chairman_lineEdit;
    QLabel *vice_chairman_label;
    QLineEdit *vice_chairman_lineEdit;
    QLabel *secretary_label;
    QLineEdit *secretary_lineEdit;
    QLabel *other_member_label;
    QPlainTextEdit *other_member_plainTextEdit;
    QPlainTextEdit *introduce_plainTextEdit;
    QLabel *introduce_label;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *accept_pushButton;
    QPushButton *reject_pushButton;
    QPushButton *reset_pushButton;

    void setupUi(QDialog *Association)
    {
        if (Association->objectName().isEmpty())
            Association->setObjectName(QStringLiteral("Association"));
        Association->resize(502, 482);
        Association->setMinimumSize(QSize(502, 482));
        horizontalLayout = new QHBoxLayout(Association);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(Association);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(321, 361));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        ID_label = new QLabel(widget);
        ID_label->setObjectName(QStringLiteral("ID_label"));
        ID_label->setMinimumSize(QSize(90, 23));

        formLayout->setWidget(0, QFormLayout::LabelRole, ID_label);

        ID_lineEdit = new QLineEdit(widget);
        ID_lineEdit->setObjectName(QStringLiteral("ID_lineEdit"));
        ID_lineEdit->setMinimumSize(QSize(223, 23));

        formLayout->setWidget(0, QFormLayout::FieldRole, ID_lineEdit);

        name_label = new QLabel(widget);
        name_label->setObjectName(QStringLiteral("name_label"));
        name_label->setMinimumSize(QSize(90, 23));

        formLayout->setWidget(1, QFormLayout::LabelRole, name_label);

        name_lineEdit = new QLineEdit(widget);
        name_lineEdit->setObjectName(QStringLiteral("name_lineEdit"));
        name_lineEdit->setMinimumSize(QSize(223, 23));

        formLayout->setWidget(1, QFormLayout::FieldRole, name_lineEdit);

        created_time_label = new QLabel(widget);
        created_time_label->setObjectName(QStringLiteral("created_time_label"));
        created_time_label->setMaximumSize(QSize(90, 24));

        formLayout->setWidget(2, QFormLayout::LabelRole, created_time_label);

        created_time_dateEdit = new QDateEdit(widget);
        created_time_dateEdit->setObjectName(QStringLiteral("created_time_dateEdit"));
        created_time_dateEdit->setMinimumSize(QSize(223, 24));

        formLayout->setWidget(2, QFormLayout::FieldRole, created_time_dateEdit);

        chairman_label = new QLabel(widget);
        chairman_label->setObjectName(QStringLiteral("chairman_label"));
        chairman_label->setMinimumSize(QSize(90, 23));

        formLayout->setWidget(3, QFormLayout::LabelRole, chairman_label);

        chairman_lineEdit = new QLineEdit(widget);
        chairman_lineEdit->setObjectName(QStringLiteral("chairman_lineEdit"));
        chairman_lineEdit->setMinimumSize(QSize(223, 23));

        formLayout->setWidget(3, QFormLayout::FieldRole, chairman_lineEdit);

        vice_chairman_label = new QLabel(widget);
        vice_chairman_label->setObjectName(QStringLiteral("vice_chairman_label"));
        vice_chairman_label->setMinimumSize(QSize(83, 23));

        formLayout->setWidget(4, QFormLayout::LabelRole, vice_chairman_label);

        vice_chairman_lineEdit = new QLineEdit(widget);
        vice_chairman_lineEdit->setObjectName(QStringLiteral("vice_chairman_lineEdit"));
        vice_chairman_lineEdit->setMinimumSize(QSize(223, 23));

        formLayout->setWidget(4, QFormLayout::FieldRole, vice_chairman_lineEdit);

        secretary_label = new QLabel(widget);
        secretary_label->setObjectName(QStringLiteral("secretary_label"));
        secretary_label->setMinimumSize(QSize(83, 23));

        formLayout->setWidget(5, QFormLayout::LabelRole, secretary_label);

        secretary_lineEdit = new QLineEdit(widget);
        secretary_lineEdit->setObjectName(QStringLiteral("secretary_lineEdit"));
        secretary_lineEdit->setMinimumSize(QSize(223, 23));

        formLayout->setWidget(5, QFormLayout::FieldRole, secretary_lineEdit);

        other_member_label = new QLabel(widget);
        other_member_label->setObjectName(QStringLiteral("other_member_label"));
        other_member_label->setMinimumSize(QSize(90, 31));

        formLayout->setWidget(6, QFormLayout::LabelRole, other_member_label);

        other_member_plainTextEdit = new QPlainTextEdit(widget);
        other_member_plainTextEdit->setObjectName(QStringLiteral("other_member_plainTextEdit"));
        other_member_plainTextEdit->setMinimumSize(QSize(223, 94));

        formLayout->setWidget(6, QFormLayout::FieldRole, other_member_plainTextEdit);

        introduce_plainTextEdit = new QPlainTextEdit(widget);
        introduce_plainTextEdit->setObjectName(QStringLiteral("introduce_plainTextEdit"));
        introduce_plainTextEdit->setMinimumSize(QSize(223, 99));

        formLayout->setWidget(8, QFormLayout::FieldRole, introduce_plainTextEdit);

        introduce_label = new QLabel(widget);
        introduce_label->setObjectName(QStringLiteral("introduce_label"));
        introduce_label->setMinimumSize(QSize(90, 31));

        formLayout->setWidget(8, QFormLayout::LabelRole, introduce_label);


        verticalLayout_2->addLayout(formLayout);


        horizontalLayout->addWidget(widget);

        widget_2 = new QWidget(Association);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        accept_pushButton = new QPushButton(widget_2);
        accept_pushButton->setObjectName(QStringLiteral("accept_pushButton"));

        verticalLayout->addWidget(accept_pushButton);

        reject_pushButton = new QPushButton(widget_2);
        reject_pushButton->setObjectName(QStringLiteral("reject_pushButton"));

        verticalLayout->addWidget(reject_pushButton);

        reset_pushButton = new QPushButton(widget_2);
        reset_pushButton->setObjectName(QStringLiteral("reset_pushButton"));

        verticalLayout->addWidget(reset_pushButton);


        horizontalLayout->addWidget(widget_2);


        retranslateUi(Association);

        QMetaObject::connectSlotsByName(Association);
    } // setupUi

    void retranslateUi(QDialog *Association)
    {
        Association->setWindowTitle(QApplication::translate("Association", "\345\241\253\345\206\231\347\244\276\345\233\242\344\277\241\346\201\257", Q_NULLPTR));
        ID_label->setText(QApplication::translate("Association", "  \347\244\276\345\233\242\347\274\226\345\217\267  ", Q_NULLPTR));
        name_label->setText(QApplication::translate("Association", "  \347\244\276\345\233\242\345\220\215\347\247\260  ", Q_NULLPTR));
        created_time_label->setText(QApplication::translate("Association", "  \346\210\220\347\253\213\346\227\266\351\227\264  ", Q_NULLPTR));
        chairman_label->setText(QApplication::translate("Association", "  \344\274\232\351\225\277\345\255\246\345\217\267  ", Q_NULLPTR));
        vice_chairman_label->setText(QApplication::translate("Association", " \345\211\257\344\274\232\351\225\277\345\255\246\345\217\267", Q_NULLPTR));
        secretary_label->setText(QApplication::translate("Association", "  \347\247\230\344\271\246\345\255\246\345\217\267 ", Q_NULLPTR));
        other_member_label->setText(QApplication::translate("Association", "  \345\205\266\344\273\226\346\210\220\345\221\230  ", Q_NULLPTR));
        introduce_label->setText(QApplication::translate("Association", "    \347\256\200\344\273\213    ", Q_NULLPTR));
        accept_pushButton->setText(QApplication::translate("Association", "\347\241\256\350\256\244", Q_NULLPTR));
        reject_pushButton->setText(QApplication::translate("Association", "\345\217\226\346\266\210", Q_NULLPTR));
        reset_pushButton->setText(QApplication::translate("Association", "\351\207\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Association: public Ui_Association {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASSOCIATION_H
