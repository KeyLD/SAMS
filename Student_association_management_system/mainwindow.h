#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define NO_RESULT -1

#include <QMainWindow>
#include <QAction>
#include <QHBoxLayout>
#include "keylist.h"
#include "student.h"
#include "association.h"
#include "otherclass.h"
#include "searchbox.h"
#include "hashtable.h"
#include "changeset.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QTimer;
class QTreeWidget;
class QFile;
QT_END_NAMESPACE

extern QString path;
extern KeyList *student_list;
extern KeyList *association_list;

extern HashTable *student_ID_search;

extern HashTable *association_ID_search;
extern HashTable *association_name_search;

extern QMap<int,StudentNode> *student_DB;
extern QMap<int,AssociationNode> *association_DB;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void OpenUrl(const QString &link);
    void ShowStudent();                    //在主界面右侧显示学生信息
    void ShowAssociation();                //在主界面右侧显示社团信息
    void ShowDeleteStudentDialog();        //在ChangeSet界面删除学生
    void ShowDeleteAssociationDialog();    //在ChangeSet界面删除社团
    void ShowChangeAssociationDialog();    //在ChangeSet界面修改社团信息
    void ShowJoinDialog();                 //在ChangeSet界面加入社团
    void ShowExitDialog();                 //在ChangeSet界面推出社团
    void CloseInformation();               //关闭右侧界面

    //void StudentRadar(const QString &strText);
    //void AssociationRadar(const QString &strText);

    //void doneCompletion();
    //void preventSuggest();
    //void autoSuggest();

    void on_toolBox_currentChanged(int index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;

    SearchBox *student_searchbox;
    SearchBox *association_searchbox;

    void IndexFileInit();
    void DBFileInit();

    void ShowAddStudentDialog();
    void ShowStudentInformationDialog();   //新生对话框确认学生信息

    void ShowAddAssociationDialog();
    void ShowAssociationInformationDialog(); //新生对话框确认社团信息

    void AddStudent(Student &student);
    void DeleteStudent(const QString &student);
    void JionAssociation(const QString &ass);
    void QuitAssociation(const QString &ass);
    void acceptChangeStudent();

    void AddAssociation(Association &association);
    void DeleteAssociation(const QString &association);
    bool ChangeAssociation(const QString &association);
    void acceptChangeAssociation();

    void DeleteOperation();
    void ChangeOperation();
    void StudentExitAssociation(const QString &student,const QString &association);

    int getIdx(bool judge,QString edited);
    void readIntoFiles();

    void ShowInformation(const QString &information);
    void ShowError(const QString &error);

    QAction *SwitchPage;


};

#endif // MAINWINDOW_H
