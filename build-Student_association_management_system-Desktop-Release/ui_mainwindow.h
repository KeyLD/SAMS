/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFormLayout *formLayout_2;
    QTabWidget *tabWidget;
    QWidget *association_tab;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *add_association_pushButton;
    QPushButton *delete_association_pushButton;
    QPushButton *revise_assocition_pushButton;
    QWidget *student_tab;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *add_student_pushButton;
    QPushButton *delete_student_pushButton;
    QPushButton *student_join_pushButton;
    QPushButton *student_exit_pushButton;
    QWidget *search_tab;
    QHBoxLayout *horizontalLayout;
    QToolBox *toolBox;
    QWidget *page;
    QWidget *layoutWidget;
    QVBoxLayout *search_association_verticalLayout;
    QLabel *label;
    QWidget *page_2;
    QWidget *layoutWidget1;
    QVBoxLayout *search_student_Layout;
    QLabel *label_2;
    QWidget *home_widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *home_label;
    QWidget *information_widget;
    QHBoxLayout *horizontalLayout_4;
    QSplitter *splitter;
    QLabel *information_title_label;
    QTableWidget *information_tableWidget;
    QTableWidget *list_tableWidget;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QLabel *link_label;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(662, 473);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(662, 473));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        formLayout_2 = new QFormLayout(centralWidget);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(0, 251));
        tabWidget->setStyleSheet(QLatin1String("QTabBar::tab{width:68px}\n"
""));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        association_tab = new QWidget();
        association_tab->setObjectName(QStringLiteral("association_tab"));
        horizontalLayout_2 = new QHBoxLayout(association_tab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        add_association_pushButton = new QPushButton(association_tab);
        add_association_pushButton->setObjectName(QStringLiteral("add_association_pushButton"));
        add_association_pushButton->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(add_association_pushButton);

        delete_association_pushButton = new QPushButton(association_tab);
        delete_association_pushButton->setObjectName(QStringLiteral("delete_association_pushButton"));
        delete_association_pushButton->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(delete_association_pushButton);

        revise_assocition_pushButton = new QPushButton(association_tab);
        revise_assocition_pushButton->setObjectName(QStringLiteral("revise_assocition_pushButton"));
        revise_assocition_pushButton->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(revise_assocition_pushButton);


        horizontalLayout_2->addLayout(verticalLayout);

        tabWidget->addTab(association_tab, QString());
        student_tab = new QWidget();
        student_tab->setObjectName(QStringLiteral("student_tab"));
        horizontalLayout_3 = new QHBoxLayout(student_tab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        add_student_pushButton = new QPushButton(student_tab);
        add_student_pushButton->setObjectName(QStringLiteral("add_student_pushButton"));
        add_student_pushButton->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(add_student_pushButton);

        delete_student_pushButton = new QPushButton(student_tab);
        delete_student_pushButton->setObjectName(QStringLiteral("delete_student_pushButton"));
        delete_student_pushButton->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(delete_student_pushButton);

        student_join_pushButton = new QPushButton(student_tab);
        student_join_pushButton->setObjectName(QStringLiteral("student_join_pushButton"));
        student_join_pushButton->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(student_join_pushButton);

        student_exit_pushButton = new QPushButton(student_tab);
        student_exit_pushButton->setObjectName(QStringLiteral("student_exit_pushButton"));
        student_exit_pushButton->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(student_exit_pushButton);


        horizontalLayout_3->addLayout(verticalLayout_2);

        tabWidget->addTab(student_tab, QString());
        search_tab = new QWidget();
        search_tab->setObjectName(QStringLiteral("search_tab"));
        horizontalLayout = new QHBoxLayout(search_tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        toolBox = new QToolBox(search_tab);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 182, 264));
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 163, 237));
        search_association_verticalLayout = new QVBoxLayout(layoutWidget);
        search_association_verticalLayout->setSpacing(6);
        search_association_verticalLayout->setContentsMargins(11, 11, 11, 11);
        search_association_verticalLayout->setObjectName(QStringLiteral("search_association_verticalLayout"));
        search_association_verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(151, 21));

        search_association_verticalLayout->addWidget(label);

        toolBox->addItem(page, QString::fromUtf8("\346\220\234\347\264\242\347\244\276\345\233\242"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 100, 30));
        layoutWidget1 = new QWidget(page_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 153, 225));
        search_student_Layout = new QVBoxLayout(layoutWidget1);
        search_student_Layout->setSpacing(6);
        search_student_Layout->setContentsMargins(11, 11, 11, 11);
        search_student_Layout->setObjectName(QStringLiteral("search_student_Layout"));
        search_student_Layout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(151, 16));

        search_student_Layout->addWidget(label_2);

        toolBox->addItem(page_2, QString::fromUtf8("\346\220\234\347\264\242\345\255\246\347\224\237"));

        horizontalLayout->addWidget(toolBox);

        tabWidget->addTab(search_tab, QString());

        formLayout_2->setWidget(0, QFormLayout::LabelRole, tabWidget);

        home_widget = new QWidget(centralWidget);
        home_widget->setObjectName(QStringLiteral("home_widget"));
        sizePolicy.setHeightForWidth(home_widget->sizePolicy().hasHeightForWidth());
        home_widget->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(home_widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        home_label = new QLabel(home_widget);
        home_label->setObjectName(QStringLiteral("home_label"));
        home_label->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(home_label);

        information_widget = new QWidget(home_widget);
        information_widget->setObjectName(QStringLiteral("information_widget"));
        sizePolicy.setHeightForWidth(information_widget->sizePolicy().hasHeightForWidth());
        information_widget->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(information_widget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        splitter = new QSplitter(information_widget);
        splitter->setObjectName(QStringLiteral("splitter"));
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Vertical);
        information_title_label = new QLabel(splitter);
        information_title_label->setObjectName(QStringLiteral("information_title_label"));
        splitter->addWidget(information_title_label);
        information_tableWidget = new QTableWidget(splitter);
        information_tableWidget->setObjectName(QStringLiteral("information_tableWidget"));
        splitter->addWidget(information_tableWidget);
        list_tableWidget = new QTableWidget(splitter);
        list_tableWidget->setObjectName(QStringLiteral("list_tableWidget"));
        splitter->addWidget(list_tableWidget);

        horizontalLayout_4->addWidget(splitter);

        widget_5 = new QWidget(information_widget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        sizePolicy.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy);
        widget_5->setMaximumSize(QSize(101, 341));
        verticalLayout_4 = new QVBoxLayout(widget_5);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButton_2 = new QPushButton(widget_5);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_4->addWidget(pushButton_2);

        pushButton = new QPushButton(widget_5);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_4->addWidget(pushButton);


        horizontalLayout_4->addWidget(widget_5);


        verticalLayout_3->addWidget(information_widget);


        formLayout_2->setWidget(0, QFormLayout::FieldRole, home_widget);

        link_label = new QLabel(centralWidget);
        link_label->setObjectName(QStringLiteral("link_label"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, link_label);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 662, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\255\246\347\224\237\347\244\276\345\233\242\347\256\241\347\220\206\347\263\273\347\273\237", Q_NULLPTR));
        add_association_pushButton->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\347\244\276\345\233\242", Q_NULLPTR));
        delete_association_pushButton->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\347\244\276\345\233\242", Q_NULLPTR));
        revise_assocition_pushButton->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\347\244\276\345\233\242\344\277\241\346\201\257", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(association_tab), QApplication::translate("MainWindow", "\347\244\276\345\233\242", Q_NULLPTR));
        add_student_pushButton->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\255\246\347\224\237", Q_NULLPTR));
        delete_student_pushButton->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\255\246\347\224\237", Q_NULLPTR));
        student_join_pushButton->setText(QApplication::translate("MainWindow", "\345\212\240\345\205\245\347\244\276\345\233\242", Q_NULLPTR));
        student_exit_pushButton->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\244\276\345\233\242", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(student_tab), QApplication::translate("MainWindow", "\345\255\246\347\224\237", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\347\244\276\345\233\242\347\274\226\345\217\267\346\210\226\345\220\215\347\247\260", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "\346\220\234\347\264\242\347\244\276\345\233\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\255\246\347\224\237\345\255\246\345\217\267\346\210\226\345\247\223\345\220\215", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "\346\220\234\347\264\242\345\255\246\347\224\237", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(search_tab), QApplication::translate("MainWindow", "\346\220\234\347\264\242", Q_NULLPTR));
        home_label->setText(QApplication::translate("MainWindow", "              \346\254\242\350\277\216\344\275\277\347\224\250\345\255\246\347\224\237\347\244\276\345\233\242\347\256\241\347\220\206\347\263\273\347\273\237", Q_NULLPTR));
        information_title_label->setText(QApplication::translate("MainWindow", "            \345\255\246\347\224\237\344\270\252\344\272\272\344\277\241\346\201\257       ", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271", Q_NULLPTR));
        link_label->setText(QApplication::translate("MainWindow", "<html><head/><body><p>             Developer &amp; Designer : <a href=\"http://www.nodekey.com\"><span style=\" text-decoration: underline; color:#0000ff;\">Key</span></a></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
