#include "Find_password.h"
#include "ui_find_password.h"
#include"send_email.h"
#include"check.h"
#include"FindUser.h"
Find_Password::Find_Password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Find_Password)
{
    ui->setupUi(this);
}

Find_Password::~Find_Password()
{
    delete ui;
}

void Find_Password::on_btn_back_log_clicked()
{
    emit Show_login_Widget();
    this->close();

}

void Find_Password::on_pushButton_clicked()
{
    if(ui->id->text().isEmpty())
    {
        ui->id->setFocus();
        return;
    }
    if(ui->emailbox->text().isEmpty())
    {
        ui->emailbox->setFocus();
        return;
    }
    QString Regist_MailBox = ui->emailbox->text().toUtf8().data();
    QString UserId = ui->id->text().toUtf8().data();
    if(!Check_EmailBox_Input(Regist_MailBox))
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，或者不为支持的邮箱类型。（目前仅支持qq）"),QMessageBox::Yes);
        Regist_MailBox = "";
        return;
    }
    Employee user = FindUserByidInEmp(UserId);
    if(user.id =="")
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该工号不存在"),QMessageBox::Yes);
        return;
    }
    if(user.Email != Regist_MailBox){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该邮箱与该工号不匹配"),QMessageBox::Yes);
        return;
    }
    QString Password = user.Password;
    //BasicSmtp *sendmail = new PasswordSmtp();
    PasswordSmtp *sendmail = new PasswordSmtp();
    sendmail->tcpSocket = new QTcpSocket();
    sendmail->Password = Password;
    if (sendmail->tcpSocket == nullptr)
    {
        qDebug() << "Failed to allocate memory for tcpSocket";
        return;
        // 处理内存分配失败的情况
    }
    //sendmail->SetValue(Password);//设置密码
    //sendmail->SetValue(Password);//设置密码
    //sendmail->Password = Password;
    sendmail->ReceiverEmailAddress = Regist_MailBox;
    sendmail->tcpSocket->connectToHost("smtp.qq.com",25);
    sendmail->tcpSocket->waitForConnected(3000);
    sendmail->CheckConnectState();
    delete sendmail->tcpSocket;
    delete sendmail;
    return;
}

void Find_Password::on_quit_clicked()
{
    qApp->quit();
}
