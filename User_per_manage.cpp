#include "User_per_manage.h"
#include "ui_user_per_manage.h"
#include<QMessageBox>
#include"check.h"
#include"FindUser.h"
QString id_my;
User_per_manage::User_per_manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User_per_manage)
{
    ui->setupUi(this);
}

User_per_manage::~User_per_manage()
{
    delete ui;
}
void SetIdFromUserToMag(QString& id)//从用户最初界面得到工号
{
    id_my = id;//利用了一个全局变量
}

void User_per_manage::on_btn_back_clicked()
{
    emit Show_User_Widget();
    this->close();
}

void User_per_manage::on_btn_save_password_clicked()
{
    QString password_pre,password_new,password_sure;
    if(!ui->password_pre->text().isEmpty())
    {
        password_pre = ui->password_pre->text().toUtf8().data();
    }
    else
    {
        ui->password_pre->setFocus();
        return;
    }
    if(!ui->password_new->text().isEmpty())
    {
        password_new = ui->password_new->text().toUtf8().data();
    }
    else
    {
        ui->password_new->setFocus();
        return;
    }
    if(!ui->password_sure->text().isEmpty())
    {
        password_sure = ui->password_sure->text().toUtf8().data();
    }
    else
    {
        ui->password_sure->setFocus();
        return;
    }
    if(!Check_Password_Right(password_new) || !Check_Password_Right(password_sure)|| !Check_Password_Right(password_pre))
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，用户名，密码，只能输入A~Z,a~z,0~9。"),QMessageBox::Yes);
        ui->password_pre->setFocus();
        ui->password_new->setFocus();
        ui->password_sure->setFocus();
        return;
    }
    if(password_sure != password_new)
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("两次密码输入不一致，请重新输入"),QMessageBox::Yes);
        ui->password_sure->setFocus();
        return;
    }
    Employee user = FindUserByidInEmp(id_my);
    if(user.Password != password_pre)
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("原密码输入不正确，请重新输入"),QMessageBox::Yes);
        ui->password_pre->setFocus();
        return;
    }
    QVector<Employee> em = ReadEmployee();
    for(int i = 0;i < em.size();i++)
    {
        if(em[i].id==id_my)
        {
            em[i].Password = password_new;
            break;
        }
    }
    WriteEmployeeToFile(em);
    QMessageBox::information(nullptr, "提示","您的密码已成功修改");
}


void User_per_manage::on_btn_save_phone_clicked()
{
    QString phone = "0",email_box="0";
    if(!ui->phone->text().isEmpty())
    {
        phone = ui->phone->text().toUtf8().data();
    }
    if(!ui->emailbox->text().isEmpty())
    {
        email_box = ui->emailbox->text().toUtf8().data();
    }
    if(ui->phone->text().isEmpty()&&ui->emailbox->text().isEmpty())
    {
        ui->phone->setFocus();
        ui->emailbox->setFocus();
        return;
    }
    if(phone != "0")
    {
        std::string phone_num = phone.toStdString(); // 转换为std::string以用于验证
        if(!Check_Phone_Input(phone_num))
        {
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("手机号格式不正确，请重新输入"),QMessageBox::Yes);
            ui->phone->setFocus();
            return;
        }
    }
    if(email_box != "0")
    {
        if(!Check_EmailBox_Input(email_box))
        {
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您所输入的邮箱格式不正确，当前仅支持qq.com"),QMessageBox::Yes);
            ui->emailbox->setFocus();
            return;
        }
    }
    QVector<Employee> em = ReadEmployee();
    for(int i = 0;i < em.size();i++)
    {
        if(em[i].id==id_my)
        {
            if(email_box != "0")
            {
                em[i].Email = email_box;
            }
            if(phone != "0")
            {
                em[i].Phone = phone;
            }
            break;
        }
    }
    int result = WriteEmployeeToFile(em);
    if(result == 1)
    {
        QMessageBox::information(nullptr, "提示","您的信息已成功修改");
    }

}
void User_per_manage::Show_info()
{
    Employee user = FindUserByidInEmp(id_my);
    ui->id->setText(user.id);
    ui->name->setText(user.name);
    ui->dept->setText(user.Dept);
    if(user.Position==1)
    {
        ui->position->setText("普通员工");
    }
    else
    {
        ui->position->setText("主管");
    }
}
void User_per_manage::on_btn_quit_clicked()
{
    qApp->quit();
}
