#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include"Admin.h"
#include"User.h"
#include"Find_password.h"
QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
private slots:

    void on_checkBox_clicked(bool checked);

    void on_Btn_userlog_clicked();

    void on_Brn_adminlog_clicked();

    void on_Btn_exit_clicked();

    void on_Btn_fogpawod_clicked();
    void show_again();

private:
    Ui::login *ui;
    Admin adm;
    User userr;
    Find_Password find_pwd;
};

int Get_Login_Info(Ui::login *ui,QString &userid,QString &password);

#endif // LOGIN_H
