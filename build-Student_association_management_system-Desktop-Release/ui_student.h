/********************************************************************************
** Form generated from reading UI file 'student.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENT_H
#define UI_STUDENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Student
{
public:
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout_2;
    QLabel *ID_label;
    QLineEdit *ID_lineEdit;
    QLabel *name_label;
    QLineEdit *name_lineEdit;
    QLabel *sex_label;
    QFrame *sex_frame;
    QRadioButton *sex_man_radioButton;
    QRadioButton *sex_woman_radioButton;
    QLabel *grade_label;
    QLineEdit *grade_lineEdit;
    QLabel *major_label;
    QLineEdit *major_lineEdit;
    QLabel *introduce_label;
    QTextEdit *introduce_textEdit;
    QWidget *widget_2;
    QFormLayout *formLayout;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *accept_pushButton;
    QPushButton *cancel_pushButton;
    QPushButton *reset_pushButton;

    void setupUi(QDialog *Student)
    {
        if (Student->objectName().isEmpty())
            Student->setObjectName(QStringLiteral("Student"));
        Student->resize(502, 482);
        Student->setMinimumSize(QSize(502, 482));
        horizontalLayout_2 = new QHBoxLayout(Student);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        groupBox = new QGroupBox(Student);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(341, 361));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        ID_label = new QLabel(groupBox);
        ID_label->setObjectName(QStringLiteral("ID_label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, ID_label);

        ID_lineEdit = new QLineEdit(groupBox);
        ID_lineEdit->setObjectName(QStringLiteral("ID_lineEdit"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, ID_lineEdit);

        name_label = new QLabel(groupBox);
        name_label->setObjectName(QStringLiteral("name_label"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, name_label);

        name_lineEdit = new QLineEdit(groupBox);
        name_lineEdit->setObjectName(QStringLiteral("name_lineEdit"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, name_lineEdit);

        sex_label = new QLabel(groupBox);
        sex_label->setObjectName(QStringLiteral("sex_label"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, sex_label);

        sex_frame = new QFrame(groupBox);
        sex_frame->setObjectName(QStringLiteral("sex_frame"));
        sex_frame->setFrameShape(QFrame::StyledPanel);
        sex_frame->setFrameShadow(QFrame::Raised);
        sex_man_radioButton = new QRadioButton(sex_frame);
        sex_man_radioButton->setObjectName(QStringLiteral("sex_man_radioButton"));
        sex_man_radioButton->setGeometry(QRect(30, 0, 61, 21));
        sex_woman_radioButton = new QRadioButton(sex_frame);
        sex_woman_radioButton->setObjectName(QStringLiteral("sex_woman_radioButton"));
        sex_woman_radioButton->setGeometry(QRect(170, 0, 61, 21));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, sex_frame);

        grade_label = new QLabel(groupBox);
        grade_label->setObjectName(QStringLiteral("grade_label"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, grade_label);

        grade_lineEdit = new QLineEdit(groupBox);
        grade_lineEdit->setObjectName(QStringLiteral("grade_lineEdit"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, grade_lineEdit);

        major_label = new QLabel(groupBox);
        major_label->setObjectName(QStringLiteral("major_label"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, major_label);

        major_lineEdit = new QLineEdit(groupBox);
        major_lineEdit->setObjectName(QStringLiteral("major_lineEdit"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, major_lineEdit);

        introduce_label = new QLabel(groupBox);
        introduce_label->setObjectName(QStringLiteral("introduce_label"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, introduce_label);

        introduce_textEdit = new QTextEdit(groupBox);
        introduce_textEdit->setObjectName(QStringLiteral("introduce_textEdit"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, introduce_textEdit);

        widget_2 = new QWidget(groupBox);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        formLayout = new QFormLayout(widget_2);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);


        formLayout_2->setWidget(6, QFormLayout::LabelRole, widget_2);

        plainTextEdit = new QPlainTextEdit(groupBox);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        formLayout_2->setWidget(6, QFormLayout::FieldRole, plainTextEdit);


        horizontalLayout->addLayout(formLayout_2);


        formLayout_3->setWidget(0, QFormLayout::LabelRole, groupBox);

        widget = new QWidget(Student);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(98, 341));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        accept_pushButton = new QPushButton(widget);
        accept_pushButton->setObjectName(QStringLiteral("accept_pushButton"));

        verticalLayout->addWidget(accept_pushButton);

        cancel_pushButton = new QPushButton(widget);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));

        verticalLayout->addWidget(cancel_pushButton);

        reset_pushButton = new QPushButton(widget);
        reset_pushButton->setObjectName(QStringLiteral("reset_pushButton"));

        verticalLayout->addWidget(reset_pushButton);


        formLayout_3->setWidget(0, QFormLayout::FieldRole, widget);


        horizontalLayout_2->addLayout(formLayout_3);


        retranslateUi(Student);

        QMetaObject::connectSlotsByName(Student);
    } // setupUi

    void retranslateUi(QDialog *Student)
    {
        Student->setWindowTitle(QApplication::translate("Student", "Dialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Student", "\345\255\246\347\224\237\344\277\241\346\201\257\345\241\253\345\206\231", Q_NULLPTR));
        ID_label->setText(QApplication::translate("Student", "  \345\255\246\345\217\267   ", Q_NULLPTR));
        name_label->setText(QApplication::translate("Student", "  \345\247\223\345\220\215   ", Q_NULLPTR));
        sex_label->setText(QApplication::translate("Student", "  \346\200\247\345\210\253  ", Q_NULLPTR));
        sex_man_radioButton->setText(QApplication::translate("Student", "\347\224\267", Q_NULLPTR));
        sex_woman_radioButton->setText(QApplication::translate("Student", "\345\245\263", Q_NULLPTR));
        grade_label->setText(QApplication::translate("Student", "  \345\271\264\347\272\247  ", Q_NULLPTR));
        major_label->setText(QApplication::translate("Student", "  \344\270\223\344\270\232  ", Q_NULLPTR));
        introduce_label->setText(QApplication::translate("Student", "  \347\244\276\345\233\242  ", Q_NULLPTR));
        label->setText(QApplication::translate("Student", "  \347\256\200\344\273\213  ", Q_NULLPTR));
        accept_pushButton->setText(QApplication::translate("Student", "\347\241\256\350\256\244", Q_NULLPTR));
        cancel_pushButton->setText(QApplication::translate("Student", "\345\217\226\346\266\210", Q_NULLPTR));
        reset_pushButton->setText(QApplication::translate("Student", "\351\207\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Student: public Ui_Student {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENT_H
