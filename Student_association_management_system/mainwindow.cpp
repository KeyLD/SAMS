#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "association.h"
#include "student.h"
#include "otherclass.h"
#include "searchbox.h"
#include "keylist.h"
#include "changeset.h"
#include <QDebug>
#include <QIODevice>
#include <QList>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QListWidget>
#include <QKeyEvent>
#include <QStringListModel>
#include <QDesktopServices>
#include <QTreeWidgetItem>
#include <QTimer>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->information_tableWidget->horizontalHeader()->setStretchLastSection(true);  //拉伸后拉长最后一列
    //ui->information_tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头
    ui->information_widget->hide();    //事先将信息窗口关闭
    //从 索引文件 读入数据到链表，再根据增加删除操作及时对链表进行更改    搜索 lineEdit变化时进行匹配，并显示出来   这里先用QList代替

    student_searchbox = new SearchBox(IS_STUDENT);
    ui->search_student_Layout->addWidget(student_searchbox);

    association_searchbox = new SearchBox(IS_ASSOCIATION);
    ui->search_association_verticalLayout->addWidget(association_searchbox);

    IndexFileInit();  //打开索引文件并将索引文件载入链表
    DBFileInit();     //打开数据文件并将其载入哈希表和红黑树

    //学生
    connect(ui->add_student_pushButton, &QPushButton::clicked, this, &MainWindow::ShowAddStudentDialog);
    connect(ui->delete_student_pushButton,&QPushButton::clicked,this,&MainWindow::ShowDeleteStudentDialog);
    connect(ui->student_join_pushButton,&QPushButton::clicked,this,&MainWindow::ShowJoinDialog);
    connect(ui->student_exit_pushButton,&QPushButton::clicked,this,&MainWindow::ShowExitDialog);

    //社团
    connect(ui->add_association_pushButton,&QPushButton::clicked,this,&MainWindow::ShowAddAssociationDialog);
    connect(ui->delete_association_pushButton,&QPushButton::clicked,this,&MainWindow::ShowDeleteAssociationDialog);
    connect(ui->revise_assocition_pushButton,&QPushButton::clicked,this,&MainWindow::ShowChangeAssociationDialog);

    //搜索
    connect(student_searchbox, &QLineEdit::returnPressed,this, &MainWindow::ShowStudent);
    connect(association_searchbox,&QLineEdit::returnPressed,this,&MainWindow::ShowAssociation);

    //底部
    connect(ui->link_label,&QLabel::linkActivated,this,&MainWindow::OpenUrl);

}

MainWindow::~MainWindow()
{
    readIntoFiles();
    delete student_ID_search;
    delete association_ID_search;
    delete association_name_search;

    delete association_list;
    delete association_DB;
    delete student_list;
    delete student_DB;

    delete ui;
}


//初始化函数

void MainWindow::IndexFileInit()
{
    QString str;
    QStringList str_list;

    QFile student_index_file(path+"student-index");  //打开索引文件
    if(!student_index_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open student index file failed." << endl;
        return ;
    }

    student_list = new KeyList;//索引链表

    while (!student_index_file.atEnd())  {  //载入数据
        str = student_index_file.readLine();
        str_list = str.split(QRegExp("\\s+"));

        student_list->push_back(NodeIndex(str_list[0].toInt(),str_list[1],str_list[2])); //成功

    }

    //下同

    QFile association_index_file(path+"association-index");
    if(!association_index_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open association index file failed." << endl;
        return ;
    }

    association_list = new KeyList;

    while (!association_index_file.atEnd()) {
        str = association_index_file.readLine();
        str_list = str.split(QRegExp("\\s+"));
        association_list->push_back(NodeIndex(str_list[0].toInt(),str_list[1],str_list[2]));
    }
    student_index_file.close();
    association_index_file.close();
}

void MainWindow::DBFileInit()
{
    QString str;
    QStringList str_list;

    student_ID_search = new HashTable;

    association_ID_search = new HashTable;
    association_name_search = new HashTable;

    student_DB = new QMap<int,StudentNode>;
    association_DB = new QMap<int,AssociationNode>;

    QFile student_DB_file(path+"studentDB");
    if(!student_DB_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open student DB file failed." << endl;
        return ;
    }

    while (!student_DB_file.atEnd()) {
        str = student_DB_file.readLine();
        str_list = str.split(QRegExp("\\s+"));


        student_DB->insert(str_list[0].toInt(),StudentNode(str_list[0].toInt(),str_list[1],
                str_list[2],(str_list[3]==QString("男")?true:false),str_list[4].toInt(),
                str_list[5],str_list[6].split(","),str_list[7]));


        //qDebug()<<str_list[1];
        student_ID_search->Insert(str_list[1],str_list[0].toInt());

        // student_name_search->insert(str_list[2],str_list[0].toInt());不再被需要
    }

    QFile association_DB_file(path+"associationDB");
    if(!association_DB_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open association DB file failed." << endl;
        return ;
    }

    while (!association_DB_file.atEnd()) {
        str = association_DB_file.readLine();
        str_list = str.split(QRegExp("\\s+"));

        association_DB->insert(str_list[0].toInt(),AssociationNode(str_list[0].toInt(),str_list[1],
                str_list[2],QDate::fromString(str_list[3],"yyyy-MM-dd"),str_list[4],str_list[5],str_list[6],str_list[7].split(","),
                str_list[8]));
        association_ID_search->Insert(str_list[1],str_list[0].toInt());
        association_name_search->Insert(str_list[2],str_list[0].toInt());
    }
    student_DB_file.close();
    association_DB_file.close();

}



//学生相关操作函数

void MainWindow::ShowAddStudentDialog()
{
    Student *new_student = new Student(this);
    new_student->setAttribute(Qt::WA_DeleteOnClose);
    connect(new_student, &Student::ReceiveData, this, &MainWindow::AddStudent);
    new_student -> show();
}

void MainWindow::ShowStudent()
{
    int idx = getIdx(IS_STUDENT,student_searchbox->text());
    if(idx== NO_RESULT){
        return ;
    }

    QStringList str_list;
    QStringList header;
    StudentNode student = (*student_DB)[idx];

    ui->information_tableWidget->setColumnCount(1);   //设置列数
    ui->information_tableWidget->setRowCount(6);      //设置行数

    ui->information_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    ui->information_tableWidget->horizontalHeader()->setStretchLastSection(true); //自动适应宽度！！！！

    header<<"   学号   "<<"   姓名   "<<"   性别   "<<"   年级   "<<"   专业   "<<"   简介   ";
    ui->information_tableWidget->setVerticalHeaderLabels(header);


    ui->information_tableWidget->setItem(0,0,new QTableWidgetItem(student.ID));
    ui->information_tableWidget->setItem(1,0,new QTableWidgetItem(student.name));
    ui->information_tableWidget->setItem(2,0,new QTableWidgetItem((student.sex?"男":"女")));
    ui->information_tableWidget->setItem(3,0,new QTableWidgetItem(QString("%1").arg(student.grade)));
    ui->information_tableWidget->setItem(4,0,new QTableWidgetItem(student.major));
    ui->information_tableWidget->setItem(5,0,new QTableWidgetItem(student.introduce));

    //设置所有社团显示
    ui->list_tableWidget->setColumnCount(2);   //设置列数
    ui->list_tableWidget->setRowCount(student.joined_association.length());      //设置行数

    ui->list_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    ui->list_tableWidget->horizontalHeader()->setStretchLastSection(true); //自动适应宽度！！！！

    header.clear();                          //设置列表头
    for(int i = 0; i < student.joined_association.length(); i++) {
        header<<QString("   %1   ").arg(i+1);
    }
    ui->list_tableWidget->setVerticalHeaderLabels(header);

    header.clear();
    header<<"   社团   "<<"   职位   ";
    ui->list_tableWidget->setHorizontalHeaderLabels(header);

    for(int i = 0; i < student.joined_association.length(); i++) {
        str_list = student.joined_association[i].split("|");
        ui->list_tableWidget->setItem(i,0,new QTableWidgetItem(str_list[0]));
        ui->list_tableWidget->setItem(i,1,new QTableWidgetItem(str_list[1]));//设置
    }

    ui->information_widget->show();
}

void MainWindow::ShowStudentInformationDialog()
{
    ui->information_widget->show();

}

void MainWindow::ShowDeleteStudentDialog()
{
    ChangeSet *delete_student = new ChangeSet(STUDENT,DELETE,this);
    delete_student->setAttribute(Qt::WA_DeleteOnClose);
    //可选择是否将删除操作放在MainWindow里
    delete_student->show();
}

void MainWindow::ShowDeleteAssociationDialog()
{
    ChangeSet *delete_association = new ChangeSet(ASSOCIATION,DELETE,this);
    delete_association->setAttribute(Qt::WA_DeleteOnClose);

    delete_association->show();
}

void MainWindow::ShowJoinDialog()
{
    ChangeSet *student_join_association = new ChangeSet(STUDENT_AND_ASSOCIATION,JOIN,this);
    student_join_association->setAttribute(Qt::WA_DeleteOnClose);

    student_join_association->show();
}

void MainWindow::ShowExitDialog()
{
    ChangeSet *student_exit_association = new ChangeSet(STUDENT_AND_ASSOCIATION,EXIT,this);
    student_exit_association->setAttribute(Qt::WA_DeleteOnClose);

    student_exit_association->show();
}

//社团操作相关函数

void MainWindow::ShowAddAssociationDialog()
{
    Association *new_association = new Association(this);
    new_association->setAttribute(Qt::WA_DeleteOnClose);
    connect(new_association, &Association::ReceiveData, this, &MainWindow::AddAssociation);
    new_association->show();
}

void MainWindow::ShowAssociation()
{
    int idx = getIdx(IS_ASSOCIATION,association_searchbox->text());
    if(idx==-1){
        return ;
    }

    QStringList header;
    QStringList str_list;
    AssociationNode association = (*association_DB)[idx];

    ui->information_tableWidget->setColumnCount(1);   //设置列数
    ui->information_tableWidget->setRowCount(7);      //设置行数

    ui->information_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    ui->information_tableWidget->horizontalHeader()->setStretchLastSection(true); //自动适应宽度！！！！

    header<<"   编号   "<<"   名称   "<<"  成立时间  "<<"   会长   "<<"   副会长   "<<"   秘书   "<<"   简介   ";
    ui->information_tableWidget->setVerticalHeaderLabels(header);


    ui->information_tableWidget->setItem(0,0,new QTableWidgetItem(association.ID));
    ui->information_tableWidget->setItem(1,0,new QTableWidgetItem(association.name));
    ui->information_tableWidget->setItem(2,0,new QTableWidgetItem(association.created_time.toString(QString("yyyy-MM-dd"))));

    ui->information_tableWidget->setItem(3,0,new QTableWidgetItem(association.chairman));
    ui->information_tableWidget->setItem(4,0,new QTableWidgetItem(association.vice_chairman));
    ui->information_tableWidget->setItem(5,0,new QTableWidgetItem(association.secretary));
    ui->information_tableWidget->setItem(6,0,new QTableWidgetItem(association.introduce));

    ui->information_title_label->setText(QString("            社团信息"));


    //设置其他成员显示
    ui->list_tableWidget->setColumnCount(2);   //设置列数
    ui->list_tableWidget->setRowCount(association.other_member.length());      //设置行数

    ui->list_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    ui->list_tableWidget->horizontalHeader()->setStretchLastSection(true); //自动适应宽度！！！！

    header.clear();                          //设置列表头
    for(int i = 0; i < association.other_member.length(); i++) {
        header<<QString("   %1   ").arg(i+1);
    }
    ui->list_tableWidget->setVerticalHeaderLabels(header);

    header.clear();
    header<<"   学号   "<<"   姓名   ";
    ui->list_tableWidget->setHorizontalHeaderLabels(header);

    for(int i = 0; i < association.other_member.length(); i++) {
        str_list = association.other_member[i].split("|");
        ui->list_tableWidget->setItem(i,0,new QTableWidgetItem(str_list[0]));  //设置学号
        ui->list_tableWidget->setItem(i,1,new QTableWidgetItem(str_list[1]));  //设置姓名
    }


    ui->information_widget->show();
}

void MainWindow::ShowAssociationInformationDialog()
{
    ui->home_widget->hide();
    ui->information_widget->show();
    ui->information_title_label->setText(QString("社团信息"));
}

void MainWindow::AddStudent(Student &student)
{
    QFile index_file(path+"student-index");
    if(!index_file.open(QIODevice::ReadWrite)) {
        qDebug() << "Open student index file failed." << endl;
        return ;
    }
    QString tmp;
    int pos,index=1;
    QRegExp rx("(\\d+)(?:\\s+)");
    while (!index_file.atEnd()) {
        tmp=index_file.readLine();
    }
    pos=rx.indexIn(tmp);
    if(pos>-1) {
        index = rx.cap(0).toInt()+1;
    }

    //将新学生载入 索引文件
    QTextStream in(&index_file);
    in<<index<<"      "<<student.GetID()<<"      "<<student.GetName()<<endl;

    //将新学生载入 索引链表
    student_list->push_back(NodeIndex(index,student.GetID(),student.GetName()));
    index_file.close(); //索引文件处理完毕

    QFile DB_file(path+"studentDB");
    if(!DB_file.open(QIODevice::WriteOnly | QIODevice::Append )) {
        qDebug() << "Open student DB file failed." << endl;
        return ;
    }


    //将新学生载入 数据文件
    QTextStream DB_in(&DB_file);
    DB_in<<index<<" "+student.GetID()<<" "+student.GetName()<<(student.GetSex()?tr(" 男 "):tr(" 女 "))
        <<student.GetGrade()<<" "+student.GetMajor()<<tr(" 暂无 ")<<student.GetIntroduce()<<endl;

    //将新学生载入 数据红黑树
    student_DB->insert(index,StudentNode(index,student.GetID(),student.GetName(),student.GetSex(),
                                         student.GetGrade(),student.GetMajor(),student.GetJionedAssociation(),
                                         student.GetIntroduce()));
    //将新学生载入 索引哈希表
    student_ID_search->Insert(student.GetID(),index);
    // student_name_search->insert(student.GetName(),index);  不再被需要

    DB_file.close();
}

void MainWindow::AddAssociation(Association &association) //这里传过来的都是学号
{
    QFile index_file(path+"association-index");
    if(!index_file.open(QIODevice::ReadWrite)) {
        qDebug() << "Open association index file failed." << endl;
        return ;
    }
    QString tmp;
    int pos,index=1;
    QRegExp rx("(\\d+)(?:\\s+)");
    while (!index_file.atEnd()) {
        tmp=index_file.readLine();
    }
    pos=rx.indexIn(tmp);
    if(pos>-1) {
        index = rx.cap(0).toInt()+1;
    }

    //将新社团载入 索引文件
    QTextStream in(&index_file);
    in<<index<<"      "<<association.GetSerialNumber()<<"      "<<association.GetName()<<endl;

    //将新社团载入 索引链表
    association_list->push_back(NodeIndex(index,association.GetSerialNumber(),association.GetName()));

    index_file.close(); //索引文件处理完毕

    QFile DB_file(path+"associationDB");
    if(!DB_file.open(QIODevice::WriteOnly | QIODevice::Append )) {
        qDebug() << "Open association DB file failed." << endl;
        return ;
    }


    //将新社团载入 数据文件   可以放在析构函数处理
    QTextStream DB_in(&DB_file);
    DB_in<<index<<" "+association.GetSerialNumber()<<" "+association.GetName()
        <<"date    "+association.GetCreatedTime().toString("yyyy/MM/dd")
       <<" "+association.GetChairman()<<" "+association.GetViceChairman()<<" "+association.GetViceChairman()+" "
      <<association.GetOtherMember().join(" ")<<" "+association.GetIntroduce()<<endl;


    /*  这里的学生保存格式为   ：  姓名(学号)
    DB_in<<index<<" "+association.GetSerialNumber()<<" "+association.GetName()<<" "+association.GetCreatedTime().toString()+" "
         <<association.GetChairman()+"("+(*student_ID_search)[association.GetChairman()]+") "
         <<association.GetViceChairman()+"("+(*student_ID_search)[association.GetViceChairman()]+") "
         <<association.GetSecretary()+"("+(*student_ID_search)[association.GetSecretary()]+") ";

    for(auto str : association.GetOtherMember()) {
        DB_in<<str+"("+(*student_ID_search)[str]+") ";
    }
    DB_in<<association.GetIntroduce()<<endl;
    */

    //将新社团载入 数据红黑树
    association_DB->insert(index,AssociationNode(index,association.GetSerialNumber(),association.GetName(),
                                                 association.GetCreatedTime(),association.GetChairman(),
                                                 association.GetViceChairman(),association.GetSecretary(),
                                                 association.GetOtherMember(),association.GetIntroduce()));

    //将新社团载入 索引红黑树
    association_ID_search->Insert(association.GetSerialNumber(),index);
    association_name_search->Insert(association.GetName(),index);

    DB_file.close();
}

void MainWindow::ShowChangeAssociationDialog()
{
    ChangeSet *change_association = new ChangeSet(ASSOCIATION,CHANGE,this);
    change_association->setAttribute(Qt::WA_DeleteOnClose);

    change_association->show();
}



//杂 函数

void MainWindow::ShowError(const QString &error)
{
    QMessageBox::critical(NULL,"Error",error,QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void MainWindow::OpenUrl(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::readIntoFiles()
{

    /*********************************************
     ************ 写回student-index ***************
     ********************************************/
    QFile student_index_file(path+"student-index");
    if(!student_index_file.open(QIODevice::WriteOnly)) {
        qDebug() << "Open student index file failed." << endl;
        return ;
    }

    QTextStream student_index_in(&student_index_file);
    FOR_ALL_KEYLIST(student_list) {
        student_index_in<<it->index<<" "<<it->ID<<" "<<it->name<<endl;
    }
    student_index_file.close();

    /*********************************************
     ********** 写回association-index *************
     ********************************************/
    QFile association_index_file(path+"association-index");
    if(!association_index_file.open(QIODevice::WriteOnly)) {
        qDebug() << "Open association index file failed." << endl;
        return ;
    }

    QTextStream association_index_in(&association_index_file);
    FOR_ALL_KEYLIST(association_list) {
        association_index_in<<it->index<<" "<<it->ID<<" "<<it->name<<endl;
    }
    association_index_file.close();



    /*********************************************
     ************** 写回studentDB *****************
     ********************************************/
    QFile student_DB_file(path+"studentDB");
    if(!student_DB_file.open(QIODevice::WriteOnly)) {
        qDebug() << "Open student DB file failed." << endl;
        return ;
    }

    QTextStream student_DB_in(&student_DB_file);
    //  待用手写红黑树更改
    for(auto it = student_DB->begin();it!=student_DB->end();it++) {
        student_DB_in<<it->index<<" "+it->ID+" "<<it->name+" "<<((it->sex)?QString("男 "):QString("女 "))
                    <<it->grade<<" "+it->major<<" "+it->joined_association.join(",")
                   <<" "+it->introduce<<endl;
    }
    student_DB_file.close();//写回完毕


    /*********************************************
     ************ 写回associationDB ***************
     ********************************************/
    QFile association_DB_file(path+"associationDB");
    if(!association_DB_file.open(QIODevice::WriteOnly)) {
        qDebug() << "Open association DB file failed." << endl;
        return ;
    }

    QTextStream association_DB_in(&association_DB_file);
    //  待用手写红黑树更改
    for(auto it = association_DB->begin();it!=association_DB->end();it++) {
        association_DB_in<<it->index<<" "+it->ID+" "<<it->name+" "<<it->created_time.toString("yyyy-MM-dd")+" "
                        <<it->chairman+" "<<it->vice_chairman+" "<<it->secretary+" "
                       <<it->other_member.join(",")<<" "+it->introduce<<endl;
    }

    association_DB_file.close(); //写回完毕

}

int MainWindow::getIdx(bool judge, QString edited)
{
    if(judge == IS_STUDENT) {
        if(!edited[0].isNumber()) {  //如果输入的是name  那么先将name转换成ID
            int pos;
            QRegExp rx("(?:\\()(\\d+)(?:\\))");
            pos = rx.indexIn(edited);
            if(pos>-1) {
                edited= rx.cap(1);
            } else {
                ShowError(QString("此学生姓名不存在，请重新输入。"));
                return -1;
            }
        }
        int idx = student_ID_search->Search(edited);
        if(idx == NO_RESULT ) {
            ShowError(QString("此学号不存在，请重新输入！"));
            return NO_RESULT;
        } else {
            return idx;
        }
    } else {
        if(!edited[0].isNumber()) {
            int idx = association_name_search->Search(edited);
            if(idx == NO_RESULT) {
                ShowError(QString("此社团名称不存在，请重新输入！"));
                return NO_RESULT;
            } else {
                return idx;
            }
        } else {
            int idx = association_ID_search->Search(edited);
            if(idx==NO_RESULT) {
                ShowError(QString("此社团编号不存在，请重新输入！"));
                return NO_RESULT;
            } else {
                return idx;
            }
        }
    }
}
