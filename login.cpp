#include "login.h"
#include "ui_login.h"
#include<QDebug>
#include"FindUser.h"
#include"check.h"
#include<QMessageBox>
#include"User.h"
#include"Admin.h"
#include"Filebackup.h"
login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    connect(&adm,SIGNAL(Show_login_Widget()),this,SLOT(show_again()));
    setWindowTitle("登录界面");
    connect(&userr,SIGNAL(Show_login_Widget()),this,SLOT(show_again()));
    connect(&find_pwd,SIGNAL(Show_login_Widget()),this,SLOT(show_again()));



}

login::~login()
{
    delete ui;
}

void login::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->password->setEchoMode(QLineEdit::Normal);

    }
    else
    {
        ui->password->setEchoMode(QLineEdit::Password);
    }

}


void login::on_Btn_userlog_clicked()
{
    QString id,password;
    int result = Get_Login_Info(ui,id,password);//判断是不是有效信息
    if(result == 0)
    {
        return;
    }
    Employee employee = FindUserByidInEmp(id);
    if(employee.id == "0"||employee.Status == 0)
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该用户不存在。"),QMessageBox::Yes);
        ui->useid->clear();
        ui->password->clear();
        return;
    }
    if(employee.Password != password)
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的密码错误，请重新输入"),QMessageBox::Yes);
        ui->password->clear();
        return;
    }
    Set_Id(id);//为用户界面传送id
    userr.show();
    this->hide();
}
void login::on_Brn_adminlog_clicked()
{
    QString id,password;
    int result = Get_Login_Info(ui,id,password);//判断是不是有效信息
    if(result == 0)
    {
        return;
    }
    Employee employee = FindUserByidInEmp(id);
    if(employee.id == "0"||employee.Status == 0)
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该用户不存在。"),QMessageBox::Yes);
        ui->useid->clear();
        ui->password->clear();
        return;
    }
    qDebug()<<employee.Dept;
    if(employee.Dept !="财务部")
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您无权限进入管理员系统。"),QMessageBox::Yes);
        ui->useid->clear();
        ui->password->clear();
        return;
    }
    if(employee.Password != password)
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的密码错误，请重新输入"),QMessageBox::Yes);
        ui->password->clear();
        return;
    }
    Set_Adm_Id(id);//为管理员工界面传入账号
    BackUpEmployee();
    BackUpSalary();
    BackUpAttendce();
    BackUpSal_Posi();
    adm.show();
    this->hide();


}

void login::on_Btn_exit_clicked()
{
    qApp->quit();
}

void login::on_Btn_fogpawod_clicked()
{
    find_pwd.show();
    this->hide();

}
void login::show_again()
{
    ui->useid->clear();
    ui->password->clear();
    this->show();
}
int Get_Login_Info(Ui::login *ui,QString &userid,QString &password)
{
    if(ui->useid->text().isEmpty())
    {
        ui->useid->setFocus();
        return 0;
    }
    if(ui->password->text().isEmpty())//bool值
    {
        ui->password->setFocus();
        return 0;
    }
    userid = ui->useid->text().toUtf8().data();
    password = ui->password->text().toUtf8().data();
    if(Check_Password_Right(userid)==0 || Check_Password_Right(password)==0)
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，用户名，密码，只能输入A~Z,a~z,0~9。"),QMessageBox::Yes);
        return 0;
    }
    return 1;
}
