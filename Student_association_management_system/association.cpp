#include "association.h"
#include "ui_association.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QRegExp>

Association::Association(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Association)
{
    ui->setupUi(this);

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
QString Association::GetSerialNumber() { return serial_number; }
QString Association::GetName() { return name; }
QDate Association::GetCreatedTime() { return created_time; }
QString Association::GetChairman() { return chairman; }
QString Association::GetViceChairman() { return vice_chairman; }
QString Association::GetSecretary() { return secretary; }
QStringList Association::GetOtherMember() { return other_member; }
QString Association::GetIntroduce() { return introduction; }

void Association::Reset()
{
    ui->ID_lineEdit->setText(tr(""));
    ui->name_lineEdit->setText(tr(""));
    ui->created_time_dateEdit->setDate(QDate(1970,1,1));
    ui->chairman_lineEdit->setText(tr(""));
    ui->vice_chairman_lineEdit->setText(tr(""));
    ui->secretary_lineEdit->setText(tr(""));
    ui->other_member_plainTextEdit->setPlainText(tr(""));
    ui->introduce_plainTextEdit->setPlainText(tr(""));
}

bool Association::InitStudents()
{
    students = new QMap<QString,QString>;
    QFile file(path+"student-index");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Open student index file fail"<<endl;
        return false;
    }
    QString str;
    QStringList str_list;
    while (!file.atEnd()) {
       str = file.readLine();
       str_list = str.split(QRegExp("\\s+"));
       students->insert(str_list[1],str_list[2]);
    }
    file.close();
    return true;
}

void Association::ShowWarning(const QString &warning) //弹出警告信息
{
    QMessageBox::warning(NULL, "warning", warning, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

bool Association::HasRepeatID(QString &associationID)
{

    QFile file(path+"association-index");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open association index file failed." << endl;
        return false;
    }
    QString tmp;
    int pos;
    QRegExp rx("(?:\\s+)(\\d+)");
    while (!file.atEnd()) {
        tmp=file.readLine();
        pos=rx.indexIn(tmp);
        if(pos>-1){
            if(rx.cap(1)==associationID) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;

}

bool Association::HasRepeatName(QString &association_name)
{

    QFile file(path+"association-index");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open failed." << endl;
        return false;
    }
    QString tmp;
    int pos;
    QRegExp rx("(\\S+)(?:\n)");
    while (!file.atEnd()) {
        tmp=file.readLine();
        pos=rx.indexIn(tmp);
        if(pos>-1){
            if(rx.cap(1)==association_name) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;

}

void Association::AssociationAccept()
{

    Association association;

    association.serial_number = ui->ID_lineEdit->text().remove(QRegExp("\\s+")); //社团的序列号必须保持各不相同
    if(association.serial_number == "") {
        ShowWarning(QString("请输入社团编号。"));
        return ;
    } else if(HasRepeatID(association.serial_number)) {
         ShowWarning(QString("此社团编号已存在，请重新输入。"));
         ui->ID_lineEdit->setText(QString(""));
         return ;
    }
    if(!CheckOnlyNumber(association.serial_number)) {
        ShowWarning(QString("社团编号只允许输入数字，请重新输入。"));
        ui->ID_lineEdit->setText(QString(""));
        return ;
    }

    association.name = ui->name_lineEdit->text().remove(QRegExp("\\s+"));  //社团的名称必须保持各不相同
    if(association.name == "") {
        ShowWarning(QString("请输入社团名称。"));
        return ;
    } else if(HasRepeatName(association.name)) {
         ShowWarning(QString("此社团名称已存在，请重新输入。"));
         ui->name_lineEdit->setText(QString(""));
         return ;
    }

    if(!InitStudents()) { // 从此处开始初始化  若失败则直接返回
        return ;
    }

    association.chairman = ui->chairman_lineEdit->text().remove(QRegExp("\\s+"));
    if(association.chairman == "") {
        ShowWarning(QString("请输入社团团长学号"));
        ui->chairman_lineEdit->setText(QString(""));
        return ;
    } else if(!CheckOnlyNumber(association.chairman)) {
        ShowWarning(QString("社团会长学号只允许输入数字，请重新输入。"));
        ui->chairman_lineEdit->setText(QString(""));
        return ;
    } else if(!CheckExist(association.chairman)) {
        ShowWarning(QString("社团会长在学生中不存在，请重新输入"));
        ui->chairman_lineEdit->setText(QString(""));
        return ;
    }

    association.vice_chairman = ui->vice_chairman_lineEdit->text().remove(QRegExp("\\s+"));
    if(association.vice_chairman == "") {
        association.vice_chairman = QString("无");
    } else if(!CheckOnlyNumber(association.vice_chairman)) {
        ShowWarning(QString("社团副会长学号只允许输入数字，请重新输入。"));
        ui->vice_chairman_lineEdit->setText(QString(""));
        return ;
    } else if(!CheckExist(association.vice_chairman)) {
        ShowWarning(QString("社团副会长在学生中不存在，请重新输入"));
        ui->vice_chairman_lineEdit->setText(QString(""));
        return ;
    }

    association.secretary = ui->secretary_lineEdit->text().remove(QRegExp("\\s+"));
    if(association.secretary == "") {
      association.secretary = QString("无");
    } else if(!CheckOnlyNumber(association.secretary)) {
        ShowWarning(QString("社团秘书学号只允许输入数字，请重新输入。"));
        ui->secretary_lineEdit->setText(QString(""));
        return ;
    } else if(!CheckExist(association.secretary)) {
        ShowWarning(QString("此秘书在学生中不存在，请重新输入"));
        ui->secretary_lineEdit->setText(QString(""));
        return ;
    }

    //这里严重需要异常处理     不允许单行中间留空 !!!!!

    association.other_member = ui->other_member_plainTextEdit->toPlainText().simplified().split(QRegExp("\\s+"));
    for(auto str : association.other_member ) {
        if(!CheckExist(str)) {
            ShowWarning(QString("该学号学生不存在，请重新输入:"+str));
            ui->other_member_plainTextEdit->setPlainText(QString(""));
            return ;
        }
    }

    association.introduction = ui->introduce_plainTextEdit->toPlainText().remove(QRegExp("\\s+"));
    if(association.introduction == "")
        association.introduction = "无";

    emit ReceiveData(association);
    QDialog::accept();
}

bool Association::CheckExist(const QString &student_ID)
{

    auto it = students->find(student_ID);
    if(it == students->end())
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
