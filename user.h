#ifndef USER_H
#define USER_H

#include <QWidget>
#include"User_per_manage.h"
#include"User_salary.h"
namespace Ui {
class User;
}

class User : public QWidget
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();
    void Get_Id();
private:
    Ui::User *ui;
    User_per_manage user_per_mag;
    User_salary user_sal;

signals:
    void Show_login_Widget();
private slots:
    void on_btn_back_login_clicked();

    void on_btn_quit_clicked();
    void on_btn_user_mag_clicked();
    void show_User_again();
    void on_btn_sly_mag_clicked();
};
void Set_Id(const QString& id);//得到用户输入的账号
#endif // USER_H
