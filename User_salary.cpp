#include "User_salary.h"
#include "ui_user_salary.h"
#include"io_base.h"
#include"FindUser.h"
#include"QLabel"
#include<QDateTime>
QString id_my_salary;//这里好像不太对
User_salary::User_salary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User_salary)
{
    ui->setupUi(this);
    //DisplayUserSalaryData(ui->table_salary);//这里不能直接展示，没有账号信息
}

User_salary::~User_salary()
{
    delete ui;
}

void User_salary::on_btn_back_user_clicked()
{
    emit Show_User_Widget();
    this->close();

}

void User_salary::on_btn_quit_clicked()
{
    qApp->quit();

}
void User_salary::DisplayUserSalaryData()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date(); // 从 QDateTime 中提取 QDate
    QString year = QString::number(currentDate.year());
    QTableWidget *salaryTable = ui->table_salary;
    qDebug()<<id_my_salary;
    QVector<Salary> salarys = FindSalary_user(id_my_salary,year);
    qDebug()<<salarys[0].salary_position;
    salaryTable->setRowCount(salarys.size());
    if(salarys.isEmpty())
    {
        return;
    }
    for (int i = 0; i < salarys.size();i++)
    {
        Salary& salary = salarys[i];
        salaryTable->setItem(i, 0, new QTableWidgetItem(salary.time.year));
        salaryTable->setItem(i, 1, new QTableWidgetItem(salary.time.mon));
        salaryTable->setItem(i, 2, new QTableWidgetItem(QString::number(salary.basic_salary)));
        salaryTable->setItem(i, 3, new QTableWidgetItem(QString::number(salary.salary_position)));
        salaryTable->setItem(i, 4, new QTableWidgetItem(QString::number(salary.salary_Performance)));
        salaryTable->setItem(i, 5, new QTableWidgetItem(QString::number(salary.House)));
        salaryTable->setItem(i, 6, new QTableWidgetItem(QString::number(salary.reward)));
        salaryTable->setItem(i, 7, new QTableWidgetItem(QString::number(salary.pay_salary)));
        salaryTable->setItem(i, 8, new QTableWidgetItem(QString::number(salary.fund)));
        salaryTable->setItem(i, 9, new QTableWidgetItem(QString::number(salary.tax)));
        salaryTable->setItem(i, 10, new QTableWidgetItem(QString::number(salary.attend_redu)));
        salaryTable->setItem(i, 11, new QTableWidgetItem(QString::number(salary.real_salary)));
    }
    // 调整表格大小
    salaryTable->resizeColumnsToContents();
}
void SetIdFromUserToSal(QString& id)//从用户最初界面得到工号
{
    id_my_salary = id;//利用了一个全局变量
}

void User_salary::on_btn_attendence_clicked()
{
    //ui->table_salary->clearContents();
    //ui->table_salary->setRowCount(0); // 清空行数
    //ui->table_salary->setColumnCount(0); // 清空列数
    ui->table_salary->clear();
    DisplayUserAttend(ui->table_salary);
}
void DisplayUserAttend(QTableWidget *salaryTable)//显示自己的考勤信息
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date(); // 从 QDateTime 中提取 QDate
    QString year = QString::number(currentDate.year());
    QString mon_pre = QString::number(currentDate.month()-1);
    QString mon_now = QString::number(currentDate.month());
    qDebug()<<id_my_salary;
    QVector<Attendance> attends = FindAttend_user(id_my_salary,year);//这里改
    salaryTable->setRowCount(attends.size()+1);
    salaryTable->setColumnCount(5);
    if(attends.isEmpty())
    {
        return;
    }
    salaryTable->setHorizontalHeaderLabels({"迟到次数", "早退次数", "年份", "月份", "加班总时长"});
    for (int i = 0; i < attends.size();i++)
    {
        Attendance& attend = attends[i];
        qDebug()<<attend.late;
        salaryTable->setItem(i, 0, new QTableWidgetItem(QString::number(attend.late)));
        salaryTable->setItem(i, 1, new QTableWidgetItem(QString::number(attend.exit_early)));
        salaryTable->setItem(i, 2, new QTableWidgetItem(attend.time.year));
        salaryTable->setItem(i, 3, new QTableWidgetItem(attend.time.mon));
        salaryTable->setItem(i, 4, new QTableWidgetItem(QString::number(attend.overtime)));
    }
    // 调整表格大小
    salaryTable->resizeColumnsToContents();
}

void User_salary::on_btn_show_pre_clicked()
{
    ui->table_salary->clear();
    ui->table_salary->setColumnCount(12);
    ui->table_salary->setHorizontalHeaderLabels({"年份", "月份", "基本工资", "岗位工资", "绩效工资","房改补助","奖励","应发工资","公积金","扣税","考勤扣除","实发工资"});
    DisplayUserSalaryData();
}
