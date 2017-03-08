#include "student.h"
#include "ui_student.h"
#include <QFile>
#include <QRegExp>
#include <QMessageBox>
#include <QDebug>

Student::Student(StudentNode *student,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student)
{
    if(student != NULL) {
        ID = student->ID;
        name = student->name;
        sex = student->sex;
        grade = student->grade;
        major = student->major;
        joined_association = student->joined_association;
        introduce = student->introduce;
        is_change = true;
    } else
        is_change = false;


    ui->setupUi(this);


    ui->joined_ass_Edit->setPlainText(QString("请输入社团编号或名称，并分别用空白符隔开每个社团，若同一个社团中间包含空格则无法检索。"));
    ui->ID_lineEdit->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
    ui->grade_lineEdit->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));

    connect(ui->accept_pushButton,&QPushButton::clicked,this,&Student::StudentAccept);
    connect(ui->cancel_pushButton,&QPushButton::clicked,this,&QDialog::reject);
    connect(ui->reset_pushButton,&QPushButton::clicked,this,&Student::Reset);
}

Student::~Student()
{
    delete ui;
}

// public api
QString Student::getID() { return ID; }
QString Student::getName() { return name; }
bool Student::getSex() { return sex; }
QString Student::getGrade() { return grade; }
QString Student::getMajor() { return major; }
QString Student::getIntroduce() { return introduce; }
QStringList Student::getJionedAssociation() { return joined_association; }

void Student::setSex(const bool &_sex) { sex = _sex; }
void Student::setGrade(const QString _grade) { grade = _grade; }
void Student::setMajor(const QString &_major) { major = _major; }
void Student::setIntroduce(const QString &_introduce) { introduce = _introduce; }
void Student::setJionedAssociation(const QStringList &_joined_association) { joined_association = _joined_association; }

void Student::StudentAccept()  //数据接收与异常处理
{
    Student student;

    student.ID = ui->ID_lineEdit->text();
    student.name = ui->name_lineEdit->text();

    if(ui->sex_man_radioButton->isChecked())
        student.sex = true;
    else if(ui->sex_woman_radioButton->isChecked())
        student.sex = false;
    else {  //未选择性别
        ShowWarning(QString("请选择学生性别"));
        return ;
    }

    student.grade = ui->grade_lineEdit->text();
    student.major = ui->major_lineEdit->text();
    student.joined_association = ui->joined_ass_Edit->toPlainText().split(QRegExp("\\s+"));
    student.introduce = ui->introduce_Edit->toPlainText();
    if(!JudgeLegal(ADD_LEGAL,student))
        return ;

    if(is_change)
        emit ChangeData(student);
    else
        emit ReceiveData(student);
    QDialog::accept();
}

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
    ui->ID_lineEdit->setText(QString(""));
    ui->name_lineEdit->setText(QString(""));

    // 一个解决不了的问题，无法重置单选框
    ui->sex_man_radioButton->setChecked(true);

    ui->grade_lineEdit->setText(QString(""));
    ui->major_lineEdit->setText(QString(""));
    ui->joined_ass_Edit->setPlainText(QString(""));
    ui->introduce_Edit->setPlainText(QString(""));
}

bool Student::JudgeLegal(const int &judge,Student &student)
{
    if(judge == ADD_LEGAL) {    //新增学生
        student.ID.remove(QRegExp("\\s+")); //运用正则表达式去掉字符串中的所有空格
        if(student.ID=="") { //学号为空的异常处理
            ShowWarning(QString("请填写学生学号。"));
            return false;
        } else if(HasRepeatID(student.ID)) {   //如果填写了已存在的学号的异常处理
            ShowWarning(QString("此学号已存在，请重新填写"));
            ui->ID_lineEdit->setText(QString(""));
            return false;
        }

        student.name.remove(QRegExp("\\s+"));
        if(student.name == ""){
            ShowWarning(QString("请输入学生姓名。"));
            return false;
        }

        for(auto ch : student.name) {  //检查字母与汉字以外的字符
            if(!ch.isLetter()) {
                ShowWarning(QString("学生姓名中请不要包含字母与汉字以外的字符。"));
                ui->name_lineEdit->setText(QString(""));
                return false;
            }
        }

    }

    student.grade.remove(QRegExp("\\s+"));
    if(student.grade=="") { //为输入学生年纪的处理
        ShowWarning(QString("请输入学生年级。"));
        return false;
    }
    for(auto ch : student.grade ) { //是否存在非数字字符
        if(!ch.isNumber()) {
            ShowWarning(QString("请不要输入非数字字符。"));
            ui->grade_lineEdit->setText(QString(""));
            return false;
        }
    }

    student.major.remove("\\s+");
    if(student.major=="") {
        ShowWarning(QString("请输入学生专业。"));
        return false;
    }
    for(auto ch : student.major) {
        if(!ch.isLetter()) {
            ShowWarning(QString("学生专业只允许填入汉字或者字母字符"));
            ui->major_lineEdit->setText(QString(""));
            return false;
        }
    }


    for(int i=0;i<student.joined_association.size();i++) {
        if(student.joined_association[i][0].isNumber()) {
            if( association_ID_search->Search(student.joined_association[i]) == NO_RESULT ) {
                ShowWarning(QString(student.joined_association[i]+"不存在，请重新输入"));
                ui->joined_ass_Edit->setPlainText(QString(""));
                return false;
            }
        } else {
            if( association_name_search->Search(student.joined_association[i]) == NO_RESULT ) {
                ShowWarning(QString(student.joined_association[i]+"不存在，请重新输入"));
                ui->joined_ass_Edit->setPlainText(QString(""));
                return false;
            }
        }
    }

    student.introduce.remove("\\s+");
    if(student.introduce == "")
        student.introduce = "无";

    return true;
}

void Student::setAll()
{
    ui->ID_lineEdit->setText(this->ID);
    ui->name_lineEdit->setText(this->name);
    ui->ID_lineEdit->setFocusPolicy(Qt::NoFocus); //不可编辑
    ui->name_lineEdit->setFocusPolicy(Qt::NoFocus); //不可编辑
    is_change = true;                              //标记这是设置框

    if(this->sex) {
        ui->sex_man_radioButton->setChecked(true);
    } else {
        ui->sex_man_radioButton->setChecked(true);
    }

    ui->grade_lineEdit->setText(this->grade);
    ui->major_lineEdit->setText(this->major);

    ui->introduce_Edit->setPlainText(this->introduce);
}

void Student::AutoJoinedComplete()
{
    for(int i=0;i<joined_association.size();i++)
        if(joined_association[i]!=QString(""))
            joined_association[i]+="|普通成员";
}

