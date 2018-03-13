#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <exception>

QString path;
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
    path = QCoreApplication::applicationDirPath() + "/resource/";

    MainWindow w;

    w.show();

    return a.exec();
}
