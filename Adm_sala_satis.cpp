#include "Adm_sala_satis.h"
#include "ui_adm_sala_satis.h"
#include"satatis.h"
#include"FindUser.h"
#include<QDateTime>
Adm_sala_satis::Adm_sala_satis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Adm_sala_satis)
{
    ui->setupUi(this);
    DisplayResult_Statis();

}
void Adm_sala_satis::DisplayResult_Statis()
{
    readRewardsAndCreateBarChart("D:/5942c++/keshecpp/工资表.csv", this);
    QMap<QString, int> totalSalaries = calculateTotalSalaryPerEmployee("D:/5942c++/keshecpp/工资表.csv");
    createSalaryBarChart(totalSalaries, this);
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date(); // 从 QDateTime 中提取 QDate
    QString year = QString::number(currentDate.year());
    QString mon_pre = QString::number(currentDate.month()-1);
    QString mon_now = QString::number(currentDate.month());
    QVector<Salary> lastMonthSalaries;
    if(mon_now =="1")
    {
        lastMonthSalaries= FindSalary_Mon(QString::number(currentDate.year()-1),"12");
    }
    else
    {
        lastMonthSalaries = FindSalary_Mon(year,mon_pre);//找到上一个月的工资
    }

    createSalaryLastBarChart(lastMonthSalaries, this);
    QMap<QString, int> monthlySums = calculateMonthlyOvertimeSums("D:/5942c++/keshecpp/员工考勤表.csv");
    createOvertimeChart(monthlySums, this);
    drawAttendanceChart("D:/5942c++/keshecpp/员工考勤表.csv",this);

}

Adm_sala_satis::~Adm_sala_satis()
{
    delete ui;
}

void Adm_sala_satis::on_btn_back_clicked()//返回
{
    emit Show_Admin_Widget();
    this->close();
}

void Adm_sala_satis::on_pushButton_2_clicked()
{
    qApp->quit();
}
