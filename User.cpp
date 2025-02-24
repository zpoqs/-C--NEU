#include "User.h"
#include "ui_user.h"
#include<QDebug>
QString Id_initial;//用户登录时的账号
User::User(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    qDebug()<<Id_initial;
    connect(&user_per_mag,SIGNAL(Show_User_Widget()),this,SLOT(show_User_again()));
    connect(&user_sal,SIGNAL(Show_User_Widget()),this,SLOT(show_User_again()));
    ui->help->setText("1.您可以修改自己的手机号，\n"
                      "邮箱，密码\n"
                      "2.个人工资管理将展示您一年的工资信息\n"
                      "同时，您可以选择查看自己的考勤记录\n"
                      "3.感谢您的使用。");
}

User::~User()
{
    delete ui;
}

void User::on_btn_back_login_clicked()
{
    emit Show_login_Widget();
    this->close();
}


void User::on_btn_quit_clicked()
{
    qApp->quit();
}

void User::on_btn_user_mag_clicked()
{
    SetIdFromUserToMag(Id_initial);
    user_per_mag.show();
    user_per_mag.Show_info();
    this->hide();
}
void Set_Id(const QString& id)
{
    Id_initial = id;
}
void User::show_User_again()
{
    this->show();
}

void User::on_btn_sly_mag_clicked()
{
    SetIdFromUserToSal(Id_initial);
    user_sal.show();
    user_sal.DisplayUserSalaryData();
    this->hide();
}
