#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>

QString path = "/home/key/Code/c++_code/qt/Student_association_management_system/resource/";
KeyList *student_list;
KeyList *association_list;

HashTable *student_ID_search;

HashTable *association_ID_search;
HashTable *association_name_search;

QMap<int,StudentNode> *student_DB;
QMap<int,AssociationNode> *association_DB;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
