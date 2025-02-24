#ifndef ADMIN_SALARY_MANAGE_H
#define ADMIN_SALARY_MANAGE_H

#include <QWidget>
#include<QTableWidget>
#include<base_lei.h>
namespace Ui {
class Admin_salary_manage;
}

class Admin_salary_manage : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_salary_manage(QWidget *parent = nullptr);
    ~Admin_salary_manage();
    void DisplaySalaryPreData(QTableWidget *salaryTable);//展示上一个月信息
    void DisplaySalaryNowData(QTableWidget *salaryTable);//展示当前月份信息
    QTableWidget* GetNowTable();

private slots:
    void on_btn_back_admin_clicked();



    void on_btn_quit_clicked();


    void on_table_mon_now_itemChanged(QTableWidgetItem *item);



    void on_comboBox_currentIndexChanged(int index);

   // void on_comboBox_2_currentIndexChanged(int index);

    void ShowSalaryInfo();

    void on_btn_attend_clicked();


signals:
    void Show_Admin_Widget();

private:
    bool isItemChangedConnected = true;
    Ui::Admin_salary_manage *ui;
};
QVector<Salary> New_Salary(QString mon,double base_sal);//修改基本工资,函数重载
QVector<Salary> New_Salary(QString id,QString mon,double posi_sal);//修改岗位工资
QVector<Sal_Posi> New_Sal_Posi(QString id,double posi_sal);//修改岗位工资表
void ChangeInfoShow(Ui::Admin_salary_manage *ui);
#endif // ADMIN_SALARY_MANAGE_H
