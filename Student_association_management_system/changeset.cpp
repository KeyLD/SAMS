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
        QString str = student_search->text();
        QStringList exit_ass;

        int idx = getIdx(STUDENT,str);
        auto itt = student_DB->find(idx);

        //删除该学生在各个社团的记录
        for(auto it = itt->joined_association.begin();it!=itt->joined_association.end();it++) {
            exit_ass = it->split("|");
            StudentExitAssociation(str,exit_ass[0]);
        }

        //数据红黑树删除
        student_DB->erase(itt);
        //qDebug()<<"map delete end";
        //数据哈希删除
        student_ID_search->Delete(str);
        //qDebug()<<"hash delete end";
        //索引链表删除
        student_list->erase(str);
        //qDebug()<<"list delete end";


    } else if(obj == ASSOCIATION) {
        QString str = association_search->text();
        QStringList exit_st;
        int idx = getIdx(ASSOCIATION,str);
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
    return false;
}

bool ChangeSet::ChangeOperation()
{
    if( obj == STUDENT ){
        QString str = student_search->text();
        int idx = getIdx(STUDENT,str);

        if(idx==NO_RESULT) {
            ShowHint(QString("Error"),QString("此学生不存在!请重新输入！"));
            return false;
        }
        auto st_it = student_DB->find(idx);

        Student *change_student = new Student(&(*st_it),this);
        change_student->setAttribute(Qt::WA_DeleteOnClose);
        connect(change_student,&Student::ChangeData,this,&ChangeSet::changeStudent);
        change_student->setAll();

        change_student->show();


    } else if( obj == ASSOCIATION ) {
        QString str = association_search->text();
        int idx = getIdx(ASSOCIATION,str);

        if(idx==NO_RESULT) {
            ShowHint(QString("Error"),QString("此社团不存在!请重新输入！"));
            return false;
        }

        auto ass_it = association_DB->find(idx);
        Association *change_association = new Association(&(*ass_it),this);
        change_association->setAttribute(Qt::WA_DeleteOnClose);
        connect(change_association,&Association::ChangeData,this,&ChangeSet::changeAssociation);
        change_association->setAll();

        change_association->show();

    }
    return true;
}

bool ChangeSet::JoinOperation(QString student, const QString &association)
{
    int st_idx = getIdx(IS_STUDENT,student);     //得到该学生索引
    if(st_idx == NO_RESULT ) {
        ShowHint(QString("Error"),QString("此学生不存在!请重新输入！"));
        return false;
    }
    int ass_idx  =getIdx(IS_ASSOCIATION,association);
    if(ass_idx == NO_RESULT ) {
        ShowHint(QString("Error"),QString("此社团不存在!请重新输入"));
        return false;
    }

    auto st_it = student_DB->find(st_idx);
    auto ass_it = association_DB->find(ass_idx);

    bool has_joined = false;

    for(auto it=st_it->joined_association.begin();it!=st_it->joined_association.end();it++) {
        if(it->split("|")[0] == ass_it->name) {
            has_joined = true;
            break;
        }
    }

    if(has_joined) {
        ShowHint(QString("Warning"),QString("该同学已加入该社团。"));
        return true;
    }

    st_it->joined_association.push_front(ass_it->name+"|普通成员");
    ass_it->other_member.push_front(st_it->ID+"|"+st_it->name);

    return true;
}

bool ChangeSet::ExitOperation(QString student, const QString &association)
{

    int st_idx=getIdx(STUDENT,student);     //得到该学生索引
    if(st_idx == NO_RESULT ) {
        ShowHint(QString("Error"),QString("此学生学号不存在!请重新输入！"));
        return false;
    }

    int ass_idx = getIdx(ASSOCIATION,association);
    if(ass_idx == NO_RESULT ) {
        ShowHint(QString("Error"),QString("此社团不存在!请重新输入"));
        return false;
    }

    auto st_it = student_DB->find(st_idx);
    auto ass_it = association_DB->find(ass_idx);

    bool has_joined = false;
    //QStringList str_list;

    for(auto it=st_it->joined_association.begin();it!=st_it->joined_association.end();it++) {
        if((it->split("|")[0]) == ass_it->name) {
            st_it->joined_association.erase(it);
            has_joined = true;
            break;
        }
    }



    if(!has_joined) {
        ShowHint(QString("Warning"),QString("该同学并未加入该社团。"));
        return true;
    }

    if(ass_it->chairman.split("|")[0] == st_it->ID ) {
        ass_it->chairman = ass_it->vice_chairman;
        ass_it->vice_chairman = QString("无|无");
    } else if(ass_it->vice_chairman.split("|")[0] == st_it->ID) {
        ass_it->vice_chairman = QString("无|无");
    } else if(ass_it->secretary.split("|")[0] == st_it->ID ) {
        ass_it->secretary = QString("无|无");
    } else {
        for(auto it =ass_it->other_member.begin();it!=ass_it->other_member.end();it++) {
            if((it->split("|")[0]) == st_it->ID) {
                ass_it->other_member.erase(it);
                break;
            }
        }
    }

    return true;
}

void ChangeSet::ShowHint(const QString &type,const QString &title)   //弹出提示
{
    QMessageBox::information(NULL, type, title, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

// 重复代码  copy from MainWindow  待重构 可利用信号槽

int ChangeSet::getIdx(int judge, QString edited)
{
    if(judge == STUDENT) {
        if(!edited[0].isNumber()) {  //如果输入的是name  那么先将name转换成ID
            int pos;
            QRegExp rx("(?:\\()(\\d+)(?:\\))");
            pos = rx.indexIn(edited);
            if(pos>-1) {
                edited= rx.cap(1);
            } else {
                //ShowError(QString("此学生姓名不存在，请重新输入。"));
                return NO_RESULT;
            }
        }
        int idx = student_ID_search->Search(edited);
        if(idx == NO_RESULT ) {
            //ShowError(QString("此学号不存在，请重新输入！"));
            return NO_RESULT;
        } else {
            return idx;
        }
    } else {
        if(!edited[0].isNumber()) {
            int idx = association_name_search->Search(edited);
            if(idx == NO_RESULT) {
                //ShowError(QString("此社团名称不存在，请重新输入！"));
                return NO_RESULT;
            } else {
                return idx;
            }
        } else {
            int idx = association_ID_search->Search(edited);
            if(idx==NO_RESULT) {
                //ShowError(QString("此社团编号不存在，请重新输入！"));
                return NO_RESULT;
            } else {
                return idx;
            }
        }
    }
}

void ChangeSet::StudentExitAssociation(const QString &student, const QString &association)
{
    int student_idx = getIdx(STUDENT,student);
    int association_idx = getIdx(ASSOCIATION,association);
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
        association_it->vice_chairman = QString("-1|暂缺");
        return ;
    }
    tmp = association_it->vice_chairman.split("|");   //副会长
    if(tmp[0]==student_ID) {
        association_it->vice_chairman = QString("-1|暂缺");
        return ;
    }
    tmp = association_it->secretary.split("|");   //秘书
    if(tmp[0]==student_ID) {
        association_it->secretary = QString("-1|暂缺");
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

void ChangeSet::changeAssociation(Association &association)
{

}

void ChangeSet::changeStudent(Student &student)
{

}
