#include "changeset.h"
#include "ui_changeset.h"
#include "searchbox.h"

ChangeSet::ChangeSet(int _obj,int _op,QWidget *parent) :
    obj(_obj),
    op(_op),
    QDialog(parent),
    ui(new Ui::ChangeSet)
{
    ui->setupUi(this);

    switch (obj) {
    case STUDENT:
        student_search = new SearchBox(IS_STUDENT,this);

        layout = new QFormLayout();
        layout->addRow(new QLabel(QString("请输入学生姓名或学号:"),this),student_search);
        ui->student_widget->setLayout(layout);

        ui->main_Layout->removeWidget(ui->association_widget);

        break;
    case ASSOCIATION:
        association_search = new SearchBox(IS_ASSOCIATION,this);

        layout =new QFormLayout();
        layout->addRow(new QLabel(QString("请输入社团名称或编号:"),this),association_search);
        ui->association_widget->setLayout(layout);

        ui->main_Layout->removeWidget(ui->student_widget);
        break;
    case STUDENT_AND_ASSOCIATION:
        student_search = new SearchBox(IS_STUDENT,this);

        layout = new QFormLayout();
        layout->addRow(new QLabel(QString("请输入学生姓名或学号:"),this),student_search);
        ui->student_widget->setLayout(layout);

        association_search = new SearchBox(IS_ASSOCIATION,this);

        layout =new QFormLayout();
        layout->addRow(new QLabel(QString("请输入社团名称或编号:"),this),association_search);
        ui->association_widget->setLayout(layout);

        break;
    }
    connect(ui->accept_pushButton,&QPushButton::clicked,this,&ChangeSet::OperationSet);
    connect(ui->cancel_pushButton,&QPushButton::clicked,this,&QDialog::reject);
}

ChangeSet::~ChangeSet()
{
    delete ui;
}

void ChangeSet::OperationSet()
{
    switch (op) {
    case DELETE:
        if(DeleteOperation()) {
            ShowHint(QString("Hint"),QString("删除成功"));
            QDialog::reject();
        }
        break;
    case CHANGE:
        if(ChangeOperation()) {
            ShowHint(QString("Hint"),QString("修改成功"));
            QDialog::reject();
        }
        break;
    case JOIN:
        if(JoinOperation(student_search->text(),association_search->text())) {
            ShowHint(QString("Hint"),QString("加入成功"));
            QDialog::reject();
        }
        break;
    case EXIT:
        if(ExitOperation(student_search->text(),association_search->text())) {
            ShowHint(QString("Hint"),QString("退出成功"));
            QDialog::reject();
        }
        break;
    }
}

bool ChangeSet::DeleteOperation() //传至main中的函数操作
{
    if(obj == STUDENT ){

    } else if(obj == ASSOCIATION) {

    }
    return false;
}

bool ChangeSet::ChangeOperation()
{
    if(obj == STUDENT ){

    } else if(obj == ASSOCIATION) {

    }
    return false;
}

bool ChangeSet::JoinOperation(QString student, const QString &association)
{
    if(!student[0].isNumber()) {    //如果是姓名  则截取其学号
        int pos;
        QRegExp rx("(?:\\()(\\d+)(?:\\))");
        pos = rx.indexIn(student);
        if(pos>-1) {
            student = rx.cap(1);
        } else {
            ShowHint(QString("Hint"),QString("此学生姓名不存在!请重新输入!"));
            return false;
        }
    }

    int st_idx = student_ID_search->Search(student);     //得到该学生索引
    if(st_idx == NO_RESULT ) {
        ShowHint(QString("Error"),QString("此学生不存在!请重新输入！"));
        return false;
    }
    int ass_idx;
    if(association[0].isNumber()) {                      //得到该社团索引
        ass_idx = association_ID_search->Search(association);
    } else {
        ass_idx = association_name_search->Search(association);
    }
    if(ass_idx == NO_RESULT ) {
        ShowHint(QString("Error"),QString("此社团不存在!请重新输入"));
        return false;
    }

    auto st_it = student_DB->find(st_idx);
    auto ass_it = association_DB->find(ass_idx);

    bool has_joined = false;

    for(auto it=st_it->joined_association.begin();it!=st_it->joined_association.end();it++) {
        if((*it) == ass_it->name) {
            st_it->joined_association.erase(it);
            has_joined = true;
            break;
        }
    }

    if(has_joined) {
        ShowHint(QString("Warning"),QString("该同学已加入该社团。"));
        return true;
    }

    ass_it->other_member.append(QString(st_it->ID));

    return true;
}

bool ChangeSet::ExitOperation(QString student, const QString &association)
{

    if(!student[0].isNumber()) {    //如果是姓名  则截取其学号
        int pos;
        QRegExp rx("(?:\\()(\\d+)(?:\\))");
        pos = rx.indexIn(student);
        if(pos>-1) {
            student = rx.cap(1);
        } else {
            ShowHint(QString("Hint"),QString("此学生姓名不存在!请重新输入!"));
            return false;
        }
    }

    int st_idx=student_ID_search->Search(student);     //得到该学生索引
    if(st_idx == NO_RESULT ) {
        ShowHint(QString("Error"),QString("此学生学号不存在!请重新输入！"));
        return false;
    }

    int ass_idx;
    if(association[0].isNumber()) {                      //得到该社团索引
        ass_idx = association_ID_search->Search(association);
    } else {
        ass_idx = association_name_search->Search(association);
    }
    if(ass_idx == NO_RESULT ) {
        ShowHint(QString("Error"),QString("此社团不存在!请重新输入"));
        return false;
    }


    auto st_it = student_DB->find(st_idx);
    auto ass_it = association_DB->find(ass_idx);

    bool has_joined = false;

    for(auto it=st_it->joined_association.begin();it!=st_it->joined_association.end();it++) {
        if((*it) == ass_it->name) {
            st_it->joined_association.erase(it);
            has_joined = true;
            break;
        }
    }

    //qDebug()<<"delete success";

    if(!has_joined) {
        ShowHint(QString("Warning"),QString("该同学并未加入该社团。"));
        return true;
    }

    if(ass_it->chairman == st_it->ID ) {
        ass_it->chairman = ass_it->vice_chairman;
        ass_it->vice_chairman = QString("暂无");
    } else if(ass_it->vice_chairman == st_it->ID) {
        ass_it->vice_chairman = QString("暂无");
    } else if(ass_it->secretary == st_it->ID ) {
        ass_it->secretary = QString("暂无");
    } else {
        for(auto it =ass_it->other_member.begin();it!=ass_it->other_member.end();it++) {
            if((*it) == st_it->ID) {
                ass_it->other_member.erase(it);
                break;
            }
        }
    }
    //qDebug()<<"exit success";
    return true;
}

void ChangeSet::ShowHint(const QString &type,const QString &title)   //弹出提示
{
    QMessageBox::information(NULL, type, title, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}


