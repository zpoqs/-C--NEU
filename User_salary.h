#ifndef USER_SALARY_H
#define USER_SALARY_H

#include <QWidget>
#include<QTableWidget>
namespace Ui {
class User_salary;
}

class User_salary : public QWidget
{
    Q_OBJECT

public:
    explicit User_salary(QWidget *parent = nullptr);
    ~User_salary();
    void DisplayUserSalaryData();

signals:
    void Show_User_Widget();

private slots:
    void on_btn_back_user_clicked();

    void on_btn_quit_clicked();

    void on_btn_attendence_clicked();

    void on_btn_show_pre_clicked();

private:
    Ui::User_salary *ui;
};
void SetIdFromUserToSal(QString& id);//从用户最初界面得到工号
void DisplayUserAttend(QTableWidget *salaryTable);//显示自己的考勤信息


#endif // USER_SALARY_H
