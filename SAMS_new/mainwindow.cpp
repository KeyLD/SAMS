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

    ui->information_tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头
    ui->information_widget->hide();    //事先将信息窗口关闭


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

    //右边信息窗口
    connect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::ChangeOperation);
    connect(ui->delete_pushButton,&QPushButton::clicked,this,&MainWindow::DeleteOperation);
    connect(ui->finish_pushButton,&QPushButton::clicked,this,&MainWindow::CloseInformation);

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
    //qDebug()<<"start";
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
    int cnt;
    QString str;
    QStringList must_list;
    QStringList option_list;

    student_ID_search = new HashTable;

    association_ID_search = new HashTable;
    association_name_search = new HashTable;

    student_DB = new RBTree<int,StudentNode>;
    association_DB = new RBTree<int,AssociationNode>;

    QFile student_DB_file(path+"studentDB");
    if(!student_DB_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open student DB file failed." << endl;
        return ;
    }

    cnt=0;
    while(!student_DB_file.atEnd()) {


        str = student_DB_file.readLine();

        switch (cnt) {
        case 0:
            must_list = str.split(QRegExp("\\s+"));

            student_ID_search->Insert(must_list[1],must_list[0].toInt());
            break;
        case 1:
            option_list = str.split(QRegExp("\\s+"));

            student_DB->insert(must_list[0].toInt(),StudentNode(must_list[0].toInt(),must_list[1],
                    must_list[2],(must_list[3]==QString("男")?true:false),must_list[4],
                    must_list[5],option_list[0].split(","),option_list[1]));
            break;
        case 2:
            cnt = -1;
            break;
        }
        cnt++;
    }


    QFile association_DB_file(path+"associationDB");
    if(!association_DB_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open association DB file failed." << endl;
        return ;
    }

    cnt=0;
    while (!association_DB_file.atEnd()) {

        str = association_DB_file.readLine();

        switch (cnt) {
        case 0:
            must_list = str.split(QRegExp("\\s+"));

            association_ID_search->Insert(must_list[1],must_list[0].toInt());
            association_name_search->Insert(must_list[2],must_list[0].toInt());
            break;
        case 1:
            option_list = str.split(QRegExp("\\s+"));

            association_DB->insert(must_list[0].toInt(),AssociationNode(must_list[0].toInt(),must_list[1],
                    must_list[2],QDate::fromString(must_list[3],"yyyy-M-d"),must_list[4],must_list[5],must_list[6],
                    option_list[0].split(","),option_list[1]));
            break;
        case 2:
            cnt = -1;
            break;
        }
        cnt++;
    }

    student_DB_file.close();
    association_DB_file.close();
}


//学生相关操作函数

void MainWindow::AddStudent(Student &student)
{
    QFile index_file(path+"student-index");
    if(!index_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
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

    //将学生加入的社团  记录在社团数据红黑树中  默认为普通成员
    for(int i=0;i<student.getJionedAssociation().size()-1;i++){
        int idx = getIdx(IS_ASSOCIATION,student.getJionedAssociation()[i]);
        auto it = association_DB->find(idx);
        it->other_member.push_front(student.getID()+"|"+student.getName()+",");
    }

    //格式同步
    student.AutoJoinedComplete();

    //将新学生载入 索引链表
    student_list->push_back(NodeIndex(index,student.getID(),student.getName()));
    index_file.close(); //索引文件处理完毕

    //将新学生载入 数据红黑树
    student_DB->insert(index,StudentNode(index,student.getID(),student.getName(),student.getSex(),
                                         student.getGrade(),student.getMajor(),student.getJionedAssociation(),
                                         student.getIntroduce()));
    //将新学生载入 索引哈希表
    student_ID_search->Insert(student.getID(),index);
    // student_name_search->insert(student.GetName(),index);  不再被需要

}

void MainWindow::ShowAddStudentDialog()
{
    Student *new_student = new Student(NULL,this);
    new_student->setAttribute(Qt::WA_DeleteOnClose);
    connect(new_student, &Student::ReceiveData, this, &MainWindow::AddStudent);
    new_student -> show();
}

void MainWindow::ShowStudent()
{
    int idx = getIdx(IS_STUDENT,student_searchbox->text());
    if(idx== NO_RESULT){
        ShowError(QString("此学生不存在"));
        return ;
    }

    QStringList str_list;
    QStringList header;
    auto it =student_DB->find(idx);

    if(it==student_DB->end()) {
        ShowError(QString("此学生不存在"));
        return ;
    }

    ui->information_tableWidget->setColumnCount(1);   //设置列数
    ui->information_tableWidget->setRowCount(6);      //设置行数

    ui->information_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    ui->information_tableWidget->horizontalHeader()->setStretchLastSection(true); //自动适应宽度！！！！

    header<<"   学号   "<<"   姓名   "<<"   性别   "<<"   年级   "<<"   专业   "<<"   简介   ";
    ui->information_tableWidget->setVerticalHeaderLabels(header);


    ui->information_tableWidget->setItem(0,0,new QTableWidgetItem(it->ID));
    ui->information_tableWidget->setItem(1,0,new QTableWidgetItem(it->name));
    ui->information_tableWidget->setItem(2,0,new QTableWidgetItem((it->sex?"男":"女")));
    ui->information_tableWidget->setItem(3,0,new QTableWidgetItem(it->grade));
    ui->information_tableWidget->setItem(4,0,new QTableWidgetItem(it->major));
    ui->information_tableWidget->setItem(5,0,new QTableWidgetItem(it->introduce));

    //设置所有社团显示
    ui->list_tableWidget->setColumnCount(2);   //设置列数
    ui->list_tableWidget->setRowCount(it->joined_association.length());      //设置行数

    ui->list_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    ui->list_tableWidget->horizontalHeader()->setStretchLastSection(true); //自动适应宽度！！！！

    header.clear();                          //设置列表头
    for(int i = 0; i < it->joined_association.length(); i++) {
        header<<QString("   %1   ").arg(i+1);
    }
    ui->list_tableWidget->setVerticalHeaderLabels(header);

    header.clear();
    header<<"   社团   "<<"   职位   ";
    ui->list_tableWidget->setHorizontalHeaderLabels(header);


    for(int i = 0; i < it->joined_association.length(); i++) {
        str_list = it->joined_association[i].split("|");
        ui->list_tableWidget->setItem(i,0,new QTableWidgetItem(str_list[0]));
        ui->list_tableWidget->setItem(i,1,new QTableWidgetItem(str_list[1]));//设置
    }

    ui->information_title_label->setText(QString("            学生信息"));
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

void MainWindow::acceptChangeStudent()
{
    //qDebug()<<"success";

    QStringList str_list;
    Student *change_student = new Student(NULL,this);

    // ID和name不允许修改
    // 可修改成通过 学生姓名或学号  得到全部信息
    change_student->setSex((ui->information_tableWidget->item(2,0)->text()==QString("男")?true:false));
    change_student->setGrade(ui->information_tableWidget->item(3,0)->text());
    change_student->setMajor(ui->information_tableWidget->item(4,0)->text());
    change_student->setIntroduce(ui->information_tableWidget->item(5,0)->text());

    for(int i=0;i<ui->list_tableWidget->rowCount();i++)
        str_list<<ui->list_tableWidget->item(i,0)->text();
    change_student->setJionedAssociation(str_list);

    if(change_student->JudgeLegal(CHECK_LEGAL,*change_student)) {
        int idx = getIdx(IS_STUDENT,student_searchbox->text());

        str_list.clear();
        for(int i=0;i<ui->list_tableWidget->rowCount();i++)
            str_list<<ui->list_tableWidget->item(i,0)->text()+"|"+ui->list_tableWidget->item(i,1)->text();
        change_student->setJionedAssociation(str_list);

        /******       修改数据红黑树          *********/
        auto it =student_DB->find(idx);
        it->sex=change_student->getSex();
        it->grade=change_student->getGrade();
        it->joined_association=change_student->getJionedAssociation();
        it->introduce=change_student->getIntroduce();
        ShowInformation(QString("修改成功"));

        //操作返回
        ui->change_pushButton->setText(QString("修改"));
        disconnect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::acceptChangeStudent);
        connect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::ChangeOperation);
    } else {
        qDebug()<<"修改失败";
    }
    ShowStudent();
}

//社团操作相关函数
void MainWindow::AddAssociation(Association &association) //这里传过来的都是学号
{
    QFile index_file(path+"association-index");
    if(!index_file.open(QIODevice::ReadOnly | QIODevice::Text )) {
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

    int idx = getIdx(IS_STUDENT,association.getChairman());
    auto it = student_DB->find(idx);
    it->joined_association.push_front(association.getName()+"|会长");


    if(association.getViceChairman()!="无|无") {
        idx = getIdx(IS_STUDENT,association.getViceChairman());
        it = student_DB->find(idx);
        it->joined_association.push_front(association.getName()+"|副会长");
    }


    if(association.getSecretary()!="无|无"){
        idx = getIdx(IS_STUDENT,association.getSecretary());
        it = student_DB->find(idx);
        it->joined_association.push_front(association.getName()+"|秘书");

    }

    for(int i=0;i<association.getOtherMember().size()-1;i++) {
        idx = getIdx(IS_STUDENT,association.getOtherMember()[i]);
        it = student_DB->find(idx);
        it->joined_association.push_front(association.getName()+"|普通成员");
    }


    //格式同步
    association.AutoOtherComplete();


    //将新社团载入 索引链表
    association_list->push_back(NodeIndex(index,association.getSerialNumber(),association.getName()));

    index_file.close(); //索引文件处理完毕


    //将新社团载入 数据红黑树
    association_DB->insert(index,AssociationNode(index,association.getSerialNumber(),association.getName(),
                                                 association.getCreatedTime(),association.getChairman(),
                                                 association.getViceChairman(),association.getSecretary(),
                                                 association.getOtherMember(),association.getIntroduce()));

    //将新社团载入 索引哈希表
    association_ID_search->Insert(association.getSerialNumber(),index);
    association_name_search->Insert(association.getName(),index);
}

void MainWindow::ShowAddAssociationDialog()
{
    Association *new_association = new Association(NULL,this);
    new_association->setAttribute(Qt::WA_DeleteOnClose);
    connect(new_association, &Association::ReceiveData, this, &MainWindow::AddAssociation);
    new_association->show();
}

void MainWindow::ShowAssociation()
{
    int idx = getIdx(IS_ASSOCIATION,association_searchbox->text());

    if(idx==-1){
        ShowError(QString("此社团不存在"));
        return ;
    }

    QStringList header;
    QStringList str_list;
    auto it = association_DB->find(idx);

    if(it ==association_DB->end() ){
        ShowError(QString("此社团不存在"));
        return ;
    }

    bool is_Null_list = false;
    if(it->other_member.size()==1&&it->other_member[0]==QString(""))
        is_Null_list = true;

    ui->information_tableWidget->setColumnCount(1);   //设置列数
    ui->information_tableWidget->setRowCount(4);      //设置行数

    ui->information_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    ui->information_tableWidget->horizontalHeader()->setStretchLastSection(true); //自动适应宽度！！！！

    header<<"   编号   "<<"   名称   "<<"  成立时间  "<<"   简介   ";
    ui->information_tableWidget->setVerticalHeaderLabels(header);


    ui->information_tableWidget->setItem(0,0,new QTableWidgetItem(it->ID));
    ui->information_tableWidget->setItem(1,0,new QTableWidgetItem(it->name));
    ui->information_tableWidget->setItem(2,0,new QTableWidgetItem(it->created_time.toString(QString("yyyy-M-d"))));
    ui->information_tableWidget->setItem(3,0,new QTableWidgetItem(it->introduce));

    ui->list_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    ui->list_tableWidget->horizontalHeader()->setStretchLastSection(true); //自动适应宽度！！！！



    //设置其他成员显示
    ui->list_tableWidget->setColumnCount(2);   //设置列数
    if(is_Null_list)
        ui->list_tableWidget->setRowCount(3);
    else
        ui->list_tableWidget->setRowCount(it->other_member.length()+3);      //设置行数


    header.clear();                          //设置列表头
    header<<"   会长   "<<"   副会长   "<<"   秘书   ";
    if(!is_Null_list)
        for(int i = 0; i < it->other_member.length(); i++) {
            header<<QString("  普通成员  ");
        }
    ui->list_tableWidget->setVerticalHeaderLabels(header);

    header.clear();
    header<<"   学号   "<<"   姓名   ";
    ui->list_tableWidget->setHorizontalHeaderLabels(header);


    str_list = it->chairman.split("|");
    ui->list_tableWidget->setItem(0,0,new QTableWidgetItem(str_list[0]));
    ui->list_tableWidget->setItem(0,1,new QTableWidgetItem(str_list[1]));

    str_list = it->vice_chairman.split("|");
    ui->list_tableWidget->setItem(1,0,new QTableWidgetItem(str_list[0]));
    ui->list_tableWidget->setItem(1,1,new QTableWidgetItem(str_list[1]));

    str_list = it->secretary.split("|");
    ui->list_tableWidget->setItem(2,0,new QTableWidgetItem(str_list[0]));
    ui->list_tableWidget->setItem(2,1,new QTableWidgetItem(str_list[1]));

    if(!is_Null_list)
        for(int i = 0; i < it->other_member.length(); i++) {
            str_list = it->other_member[i].split("|");
            ui->list_tableWidget->setItem(i+3,0,new QTableWidgetItem(str_list[0]));  //设置学号
            ui->list_tableWidget->setItem(i+3,1,new QTableWidgetItem(str_list[1]));  //设置姓名
        }

    ui->information_title_label->setText(QString("            社团信息"));
    ui->information_widget->show();
}

void MainWindow::ShowAssociationInformationDialog()
{
    ui->home_widget->hide();
    ui->information_widget->show();
    ui->information_title_label->setText(QString("社团信息"));
}

void MainWindow::ShowChangeAssociationDialog()
{
    ChangeSet *change_association = new ChangeSet(ASSOCIATION,CHANGE,this);
    change_association->setAttribute(Qt::WA_DeleteOnClose);

    change_association->show();
}

void MainWindow::acceptChangeAssociation()
{
    QStringList str_list;
    Association *change_association = new Association(NULL,this);

    // ID和name不允许修改
    // 可修改成通过 学生姓名或学号  得到全部信息
    change_association->setCreatedTime(ui->information_tableWidget->item(2,0)->text());
    change_association->setIntroduce(ui->information_tableWidget->item(3,0)->text());

    change_association->setChairman(ui->list_tableWidget->item(0,0)->text());
    change_association->setViceChairman(ui->list_tableWidget->item(1,0)->text());
    change_association->setSecretary(ui->list_tableWidget->item(2,0)->text());

    for(int i=3;i<ui->list_tableWidget->rowCount();i++)
        str_list<<ui->list_tableWidget->item(i,0)->text();
    change_association->setOtherMember(str_list);

    if(change_association->JudgeLegal(CHECK_LEGAL,*change_association)) {
        int idx = getIdx(IS_ASSOCIATION,association_searchbox->text());
        /******       修改数据红黑树          *********/
        auto it =association_DB->find(idx);
        it->created_time=change_association->getCreatedTime();
        it->chairman=ui->list_tableWidget->item(0,0)->text()+"|"+ui->list_tableWidget->item(0,1)->text();
        it->vice_chairman=ui->list_tableWidget->item(1,0)->text()+"|"+ui->list_tableWidget->item(1,1)->text();
        it->secretary=ui->list_tableWidget->item(2,0)->text()+"|"+ui->list_tableWidget->item(2,1)->text();
        for(int i=3;i<ui->list_tableWidget->rowCount();i++)
            it->other_member<<(ui->list_tableWidget->item(i,0)->text()+"|"+ui->list_tableWidget->item(i,1)->text());
        it->introduce=change_association->getIntroduce();
        ShowInformation(QString("修改成功"));

        //操作返回
        ui->change_pushButton->setText(QString("修改"));
        disconnect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::acceptChangeAssociation);
        connect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::ChangeOperation);
    } else {
        qDebug()<<"修改失败";
    }
    ShowAssociation();
}

//杂 函数

void MainWindow::ChangeOperation()
{
    ui->change_pushButton->setText(QString("确认修改"));
    disconnect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::ChangeOperation);

    ui->information_tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    // ui->list_tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);  学生社团之间的关系在这里不允许修改

    ui->information_tableWidget->item(0,0)->setFlags(ui->information_tableWidget->item(0,0)->flags() & (~Qt::ItemIsEditable));
    ui->information_tableWidget->item(1,0)->setFlags(ui->information_tableWidget->item(1,0)->flags() & (~Qt::ItemIsEditable));

    if(ui->information_title_label->text().simplified()==QString("学生信息")) {
        connect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::acceptChangeStudent);
    } else {
        connect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::acceptChangeAssociation);
    }
}

void MainWindow::DeleteOperation()
{
    if(ui->information_title_label->text().simplified()==QString("学生信息")) {

        QString str = student_searchbox->text();
        QStringList exit_ass;

        int idx = getIdx(IS_STUDENT,str);
        auto itt = student_DB->find(idx);

        //删除该学生在各个社团的记录
        for(auto it = itt->joined_association.begin();it!=itt->joined_association.end();it++) {
            exit_ass = it->split("|");
            StudentExitAssociation(str,exit_ass[0]);
        }

        //数据红黑树删除
        student_DB->erase(itt);
        //数据哈希删除
        student_ID_search->Delete(str);
        //索引链表删除
        student_list->erase(str);
    } else {
        QString str = association_searchbox->text();
        QStringList exit_st;
        int idx = getIdx(IS_ASSOCIATION,str);
        auto it = association_DB->find(idx);
        //删除该社团中每个学生的记录
        exit_st = it->chairman.split("|");
        StudentExitAssociation(exit_st[0],it->name);
        exit_st = it->vice_chairman.split("|");
        if(exit_st[0]!="无")
            StudentExitAssociation(exit_st[0],it->name);
        exit_st = it->secretary.split("|");
        if(exit_st[0]!="无")
            StudentExitAssociation(exit_st[0],it->name);
        for(auto itt = it->other_member.begin();itt!=it->other_member.end();itt++){
            exit_st = itt->split("|");
            StudentExitAssociation(exit_st[0],it->name);
        }
        //数据红黑树删除
        association_DB->erase(it);
        //数据哈希删除
        association_ID_search->Delete(str);
        association_name_search->Delete(str);
        //索引链表删除
        association_list->erase(str);
    }
    ShowInformation(QString("删除成功!"));
    CloseInformation();
}

void MainWindow::StudentExitAssociation(const QString &student, const QString &association)
{
    int student_idx = getIdx(IS_STUDENT,student);
    int association_idx = getIdx(IS_ASSOCIATION,association);
    auto student_it = student_DB->find(student_idx);
    auto association_it = association_DB->find(association_idx);

    QString student_ID = student_it->ID;
    QString association_name = association_it->name;

    QStringList tmp;

    for(auto it=student_it->joined_association.begin();it != student_it->joined_association.end();it++) {
        tmp =it->split("|");
        if(tmp[0]==association_name) {
            student_it->joined_association.erase(it);
            break;
        }
    }

    tmp = association_it->chairman.split("|");   //会长
    if(tmp[0]==student_ID) {
        association_it->chairman = association_it->vice_chairman;
        association_it->vice_chairman = QString("无|无");
        return ;
    }
    tmp = association_it->vice_chairman.split("|");   //副会长
    if(tmp[0]==student_ID) {
        association_it->vice_chairman = QString("无|无");
        return ;
    }
    tmp = association_it->secretary.split("|");   //秘书
    if(tmp[0]==student_ID) {
        association_it->secretary = QString("无|无");
        return ;
    }
    for(auto it=association_it->other_member.begin();it!=association_it->other_member.end();it++){
        tmp = it->split("|");
        if(tmp[0]==student_ID) {
            association_it->other_member.erase(it);
            break;
        }
    }
}

void MainWindow::ShowInformation(const QString &information)
{
    QMessageBox::information(NULL, "Hint", information, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void MainWindow::ShowError(const QString &error)
{
    QMessageBox::critical(NULL, "Hint", error, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
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
                    <<it->grade<<" "+it->major<<endl<<it->joined_association.join(",")<<" "+it->introduce<<endl<<endl;
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
        association_DB_in<<it->index<<" "+it->ID+" "<<it->name+" "<<it->created_time.toString("yyyy-M-d")+" "
                        <<it->chairman+" "<<it->vice_chairman+" "<<it->secretary<<endl
                       <<it->other_member.join(",")<<" "+it->introduce<<endl<<endl;
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
                return NO_RESULT;
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

void MainWindow::CloseInformation()
{
    ui->change_pushButton->setText(QString("修改"));
    disconnect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::acceptChangeStudent);
    disconnect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::acceptChangeAssociation);
    connect(ui->change_pushButton,&QPushButton::clicked,this,&MainWindow::ChangeOperation);
    ui->information_widget->hide();
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    if(index == 0){
        student_searchbox->setText(QString(""));
    } else {
        association_searchbox->setText(QString(""));
    }
    CloseInformation();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
    case 1:
        ui->information_widget->hide();
        break;
    case 2:
        student_searchbox->setText(QString(""));
        association_searchbox->setText(QString(""));
        CloseInformation();
        ui->toolBox->setCurrentIndex(0);
        break;
    }
}
