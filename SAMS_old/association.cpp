#include "association.h"
#include "ui_association.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QRegExp>

Association::Association(AssociationNode *association,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Association)
{
    if(association != NULL) {
        serial_number = association->ID;
        name = association->name;
        created_time = association->created_time;
        chairman = association->chairman;
        vice_chairman = association->vice_chairman;
        secretary = association->secretary;
        introduce = association->introduce;
        other_member = association->other_member;
        is_change = true;
    } else
        is_change = false;

    ui->setupUi(this);

    ui->created_time_dateEdit->setDisplayFormat("yyyy.M.d");
    ui->other_member_plainTextEdit->setPlainText(QString("请输入学生编号，并分别用空白符隔开每个学生，若同一个社团中间包含空格则无法检索。"));
    ui->ID_lineEdit->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
    ui->chairman_lineEdit->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
    ui->vice_chairman_lineEdit->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
    ui->secretary_lineEdit->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));


    connect(ui->accept_pushButton,&QPushButton::clicked,this,&Association::AssociationAccept);
    connect(ui->reject_pushButton,&QPushButton::clicked,this,&QDialog::reject);
    connect(ui->reset_pushButton,&QPushButton::clicked,this,&Association::Reset);
}

Association::~Association()
{
    delete ui;
}

//可进行大重构
// public api
QString Association::getSerialNumber() { return serial_number; }
QString Association::getName() { return name; }
QDate Association::getCreatedTime() { return created_time; }
QString Association::getChairman() { return chairman; }
QString Association::getViceChairman() { return vice_chairman; }
QString Association::getSecretary() { return secretary; }
QStringList Association::getOtherMember() { return other_member; }
QString Association::getIntroduce() { return introduce; }


void Association::setCreatedTime(const QString &_created_time) { created_time = QDate::fromString(_created_time,"yyyy-M-d"); }
void Association::setChairman(const QString &_chairman) { chairman = _chairman; }
void Association::setViceChairman(const QString &_vice_chairman) { vice_chairman = _vice_chairman; }
void Association::setSecretary(const QString &_secretary) { secretary = _secretary; }
void Association::setOtherMember(const QStringList &_other_member) { other_member = _other_member; }
void Association::setIntroduce(const QString &_introduce) { introduce = _introduce; }

bool Association::JudgeLegal(const int &judge, Association &association)
{
    if(judge == ADD_LEGAL ){
        association.serial_number.remove(QRegExp("\\s+")); //社团的序列号必须保持各不相同
        if(association.serial_number == "") {
            ShowWarning(QString("请输入社团编号。"));
            return false;
        } else if(HasRepeatID(association.serial_number)) {
            ShowWarning(QString("此社团编号已存在，请重新输入。"));
            ui->ID_lineEdit->setText(QString(""));
            return false;
        }
        if(!CheckOnlyNumber(association.serial_number)) {
            ShowWarning(QString("社团编号只允许输入数字，请重新输入。"));
            ui->ID_lineEdit->setText(QString(""));
            return false;
        }

        association.name.remove(QRegExp("\\s+"));  //社团的名称必须保持各不相同
        if(association.name == "") {
            ShowWarning(QString("请输入社团名称。"));
            return false;
        } else if(HasRepeatName(association.name)) {
            ShowWarning(QString("此社团名称已存在，请重新输入。"));
            ui->name_lineEdit->setText(QString(""));
            return false;
        }


        association.chairman.remove(QRegExp("\\s+"));
        if(association.chairman == "") {
            ShowWarning(QString("请输入社团团长学号"));
            ui->chairman_lineEdit->setText(QString(""));
            return false;
        } else if(!CheckOnlyNumber(association.chairman)) {
            ShowWarning(QString("社团会长学号只允许输入数字，请重新输入。"));
            ui->chairman_lineEdit->setText(QString(""));
            return false;
        } else if(!CheckExist(association.chairman)) {
            ShowWarning(QString("社团会长在学生中不存在，请重新输入"));
            ui->chairman_lineEdit->setText(QString(""));
            return false;
        }


        association.vice_chairman.remove(QRegExp("\\s+"));
        if(association.vice_chairman == "") {
            association.vice_chairman = QString("无|无");
        } else if(!CheckOnlyNumber(association.vice_chairman)) {
            ShowWarning(QString("社团副会长学号只允许输入数字，请重新输入。"));
            ui->vice_chairman_lineEdit->setText(QString(""));
            return false;
        } else if(!CheckExist(association.vice_chairman)) {
            ShowWarning(QString("社团副会长在学生中不存在，请重新输入"));
            ui->vice_chairman_lineEdit->setText(QString(""));
            return false;
        }


        association.secretary.remove(QRegExp("\\s+"));
        if(association.secretary == "") {
            association.secretary = QString("无|无");
        } else if(!CheckOnlyNumber(association.secretary)) {
            ShowWarning(QString("社团秘书学号只允许输入数字，请重新输入。"));
            ui->secretary_lineEdit->setText(QString(""));
            return false;
        } else if(!CheckExist(association.secretary)) {
            ShowWarning(QString("此秘书在学生中不存在，请重新输入"));
            ui->secretary_lineEdit->setText(QString(""));
            return false;
        }



        for(int i = 0;i<association.other_member.size()-1;i++) {
            if(!CheckExist(association.other_member[i])) {
                ShowWarning(QString("该学号学生不存在，请重新输入:"+association.other_member[i]));
                ui->other_member_plainTextEdit->setPlainText(QString(""));
                return false;
            }
        }

    }



    association.introduce.remove(QRegExp("\\s+"));
    if(association.introduce == "")
        association.introduce = "无";

    return true;
}

void Association::Reset()
{
    ui->ID_lineEdit->setText(QString(""));
    ui->name_lineEdit->setText(QString(""));
    ui->created_time_dateEdit->setDate(QDate(1970,1,1));
    ui->chairman_lineEdit->setText(QString(""));
    ui->vice_chairman_lineEdit->setText(QString(""));
    ui->secretary_lineEdit->setText(QString(""));
    ui->other_member_plainTextEdit->setPlainText(QString(""));
    ui->introduce_plainTextEdit->setPlainText(QString(""));
}

void Association::ShowWarning(const QString &warning) //弹出警告信息
{
    QMessageBox::warning(NULL, "warning", warning, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

bool Association::HasRepeatID(QString &associationID)
{
    return association_ID_search->Search(associationID) != NO_RESULT;
}

bool Association::HasRepeatName(QString &association_name)
{
    return association_name_search->Search(association_name) != NO_RESULT;
}

void Association::AssociationAccept()
{

    Association association;

    association.serial_number = ui->ID_lineEdit->text(); //社团的序列号必须保持各不相同
    association.name = ui->name_lineEdit->text().remove(QRegExp("\\s+"));  //社团的名称必须保持各不相同
    association.created_time = ui->created_time_dateEdit->date();
    association.chairman = ui->chairman_lineEdit->text();
    association.vice_chairman = ui->vice_chairman_lineEdit->text();
    association.secretary = ui->secretary_lineEdit->text();

    //这里严重需要异常处理     不允许单行中间留空 !!!!!
    association.other_member = ui->other_member_plainTextEdit->toPlainText().simplified().split(QRegExp("\\s+"));
    association.introduce = ui->introduce_plainTextEdit->toPlainText();

    if(!JudgeLegal(ADD_LEGAL,association))
        return ;
    if(is_change)
        emit ChangeData(association);
    else
        emit ReceiveData(association);
    QDialog::accept();
}

bool Association::CheckExist(const QString &student_ID)
{
    if(getStdentName(student_ID)==QString("No Student"))
        return false;
    return true;
}

bool Association::CheckOnlyNumber(const QString &str)
{
    for(auto ch : str) {
        if(!ch.isNumber())
            return false;
    }
    return true;
}

void Association::setAll()
{
    ui->ID_lineEdit->setText(this->serial_number);
    ui->name_lineEdit->setText(this->name);
    ui->ID_lineEdit->setFocusPolicy(Qt::NoFocus); //不可编辑
    ui->name_lineEdit->setFocusPolicy(Qt::NoFocus); //不可编辑
    is_change = true;                              //标记这是设置框

    ui->chairman_lineEdit->setText(this->chairman);
    ui->vice_chairman_lineEdit->setText(this->vice_chairman);
    ui->secretary_lineEdit->setText(this->secretary);

    ui->other_member_plainTextEdit->setPlainText(this->other_member.join("\n"));
    ui->introduce_plainTextEdit->setPlainText(this->introduce);
}

void Association::AutoOtherComplete()
{ 
    chairman.append("|"+getStdentName(chairman));

    if(vice_chairman != "无|无")
        vice_chairman.append("|"+getStdentName(vice_chairman));

    if(secretary!="无|无")
        secretary.append("|"+getStdentName(secretary));

    for(int i=0;i<other_member.size();i++)
        if(other_member[i]!=QString("")){
            other_member[i].append("|"+getStdentName(other_member[i]));
        }
}

QString Association::getStdentName(const QString &edited)
{
    int idx = student_ID_search->Search(edited);
    if(idx == NO_RESULT ) {

        return QString("No Student");
    }
    return student_DB->find(idx)->name;
}
