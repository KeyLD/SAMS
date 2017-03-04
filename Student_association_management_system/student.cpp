#include "student.h"
#include "ui_student.h"
#include <QFile>
#include <QRegExp>
#include <QMessageBox>
#include <QDebug>

Student::Student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    connect(ui->accept_pushButton,&QPushButton::clicked,this,&Student::StudentAccept);
    connect(ui->cancel_pushButton,&QPushButton::clicked,this,&QDialog::reject);
    connect(ui->reset_pushButton,&QPushButton::clicked,this,&Student::Reset);
}

Student::~Student()
{
    delete ui;
}

void Student::StudentAccept()  //数据接收与异常处理
{
    Student student;
    QString tmp;
    student.ID = ui->ID_lineEdit->text().remove(QRegExp("\\s+")); //运用正则表达式去掉字符串中的所有空格
    if(student.ID=="") { //学号为空的异常处理
        ShowWarning(QString("请填写学生学号。"));
        return ;
    }
    if(HasRepeatID(student.ID)) {   //如果填写了已存在的学号的异常处理
        ShowWarning(tr("此学号已存在，请重新填写"));
        Reset();
        return ;
    }

    student.name = ui->name_lineEdit->text().remove(QRegExp("\\s+"));
    if(student.name == ""){
        ShowWarning(QString("请输入学生姓名。"));
        return ;
    }

    for(auto ch : student.name) {  //检查字母与汉字以外的字符
        if(!ch.isLetter()) {
            ShowWarning(QString("学生姓名中请不要包含字母与汉字以外的字符。"));
            //Reset();
            return ;
        }
    }

    if(ui->sex_man_radioButton->isChecked())
        student.sex = true;
    else if(ui->sex_woman_radioButton->isChecked())
        student.sex = false;
    else {  //未选择性别
        ShowWarning(QString("请选择学生性别"));
        return;
    }

    bool ok;
    tmp = ui->grade_lineEdit->text().remove(QRegExp("\\s+"));
    if(tmp=="") { //为输入学生年纪的处理
        ShowWarning(QString("请输入学生年级。"));
        return ;
    }
    for(auto ch : tmp ) { //是否存在非数字字符
        if(!ch.isNumber()) {
            ShowWarning(QString("请不要输入非数字字符。"));
            return ;
        }
    }
    student.grade = tmp.toInt(&ok,10);

    student.major = ui->major_lineEdit->text().remove("\\s+");
    if(student.major=="") {
        ShowWarning(QString("请输入学生专业。"));
        return ;
    }
    for(auto ch : student.major) {
        if(!ch.isLetter()) {
            ShowWarning(QString("学生专业只允许填入汉字或者字母字符"));
            return ;
        }
    }

    student.introduce = ui->introduce_textEdit->toPlainText().remove("\\s+");
    if(student.introduce == "")
        student.introduce = "无";
    // 其余学生的处理   还需要添加  一开始就有社团的设定 （最好是下拉框
    emit ReceiveData(student);
    QDialog::accept();
}

// public api
QString Student::GetID() { return ID; }
QString Student::GetName() { return name; }
bool Student::GetSex() { return sex; }
int Student::GetGrade() { return grade; }
QString Student::GetMajor() { return major; }
QString Student::GetIntroduce() { return introduce; }
QStringList Student::GetJionedAssociation() { return joined_association; }

bool Student::HasRepeatID(QString studentID) //从索引文件中读取所有学生ID，判断ID是否已存在
{
    QFile file(path+"student-index");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open student index file failed." << endl;
        return false;
    }
    QString tmp;
    int pos;
    QRegExp rx("(?:\\s+)(\\d+)");
    while (!file.atEnd()) {
        tmp=file.readLine();
        pos=rx.indexIn(tmp);
        if(pos>-1){
            if(rx.cap(1)==studentID)
            {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

void Student::ShowWarning(QString warning) //弹出警告信息
{
    QMessageBox::warning(NULL, "warning", warning, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void Student::Reset()   //重置
{
    ui->ID_lineEdit->setText(tr(""));
    ui->name_lineEdit->setText(tr(""));

    // 一个解决不了的问题，无法重置单选框
    ui->sex_man_radioButton->setChecked(true);

    ui->grade_lineEdit->setText(tr(""));
    ui->major_lineEdit->setText(tr(""));
    ui->introduce_textEdit->setText(tr(""));
}


