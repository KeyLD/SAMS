/********************************************************************************
** Form generated from reading UI file 'changeset.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGESET_H
#define UI_CHANGESET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeSet
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *main_Layout;
    QWidget *student_widget;
    QWidget *association_widget;
    QWidget *button_box;
    QHBoxLayout *horizontalLayout;
    QPushButton *accept_pushButton;
    QPushButton *cancel_pushButton;

    void setupUi(QDialog *ChangeSet)
    {
        if (ChangeSet->objectName().isEmpty())
            ChangeSet->setObjectName(QStringLiteral("ChangeSet"));
        ChangeSet->resize(461, 284);
        horizontalLayout_2 = new QHBoxLayout(ChangeSet);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        main_Layout = new QVBoxLayout();
        main_Layout->setObjectName(QStringLiteral("main_Layout"));
        student_widget = new QWidget(ChangeSet);
        student_widget->setObjectName(QStringLiteral("student_widget"));

        main_Layout->addWidget(student_widget);

        association_widget = new QWidget(ChangeSet);
        association_widget->setObjectName(QStringLiteral("association_widget"));

        main_Layout->addWidget(association_widget);

        button_box = new QWidget(ChangeSet);
        button_box->setObjectName(QStringLiteral("button_box"));
        button_box->setMaximumSize(QSize(600, 51));
        horizontalLayout = new QHBoxLayout(button_box);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        accept_pushButton = new QPushButton(button_box);
        accept_pushButton->setObjectName(QStringLiteral("accept_pushButton"));
        accept_pushButton->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(accept_pushButton);

        cancel_pushButton = new QPushButton(button_box);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));
        cancel_pushButton->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(cancel_pushButton);


        main_Layout->addWidget(button_box);


        horizontalLayout_2->addLayout(main_Layout);


        retranslateUi(ChangeSet);

        QMetaObject::connectSlotsByName(ChangeSet);
    } // setupUi

    void retranslateUi(QDialog *ChangeSet)
    {
        ChangeSet->setWindowTitle(QApplication::translate("ChangeSet", "Dialog", Q_NULLPTR));
        accept_pushButton->setText(QApplication::translate("ChangeSet", "\347\241\256\350\256\244", Q_NULLPTR));
        cancel_pushButton->setText(QApplication::translate("ChangeSet", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChangeSet: public Ui_ChangeSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGESET_H
