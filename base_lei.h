#ifndef BASE_LEI_H
#define BASE_LEI_H

#include <QStringList>
#include <QVector>
#include<cstdlib>
#include<QDebug>
class People
{
public:
   QString id;//工号
   QString name;
   QString sex;
   People()
   {
       id = "0";
       name = "0";
       sex ="0";
   }
   ~People(){}
   People(const QString& id,const QString& name,const QString& sex)
       :id(id),name(name),sex(sex){}
};
class Employee :public People
{
public:
    //QString id;//工号
    //QString name;
    //QString sex;
    QString Dept;//部门
    int Position;//职位（1员工，2主管)
    QString Address;//地址
    QString Date_birth;//出生日期
    QString Phone;//手机号
    QString Email;//邮箱
    QString Password;//密码
    int Status;//0为删除1为存在
    Employee(const QString& id, const QString& name, const QString& sex, const QString dept,
        const int position, QString address, const QString& date_birth, const QString& phone, const QString& email,
        const QString& password, int status)
        : People(id, name, sex), Dept(dept), Position(position), Address(address), Date_birth(date_birth),
        Phone(phone), Email(email), Password(password), Status(status) {}
    Employee(){}

    ~Employee() {}

};
class date
{
public:
    QString year,mon;
    date(QString year,QString mon)//这里是QString，如果后面用整型进行比较出错
        :year(year),mon(mon){}
    date(){}
    ~date(){}
};

class Salary_base
{
public:
    QString id;
    date time;
    double basic_salary;//基本工资
    Salary_base(QString id,QString year,QString mon,double basic_salary)
        :id(id),time(year,mon),basic_salary(basic_salary){}
    Salary_base(){}
    ~Salary_base(){}

};
class Salary:public Salary_base
{
public:
    double salary_position;//岗位工资
    double salary_Performance;//绩效工资
    double House;//房改补助
    double reward;//奖励
    double pay_salary;//应发工资
    double fund;//公积金
    double tax;//扣税
    double attend_redu;//考勤扣除
    double real_salary;//实发工资
    Salary(QString id, QString year, QString mon, double basic_salary,
               double salary_pos, double salary_perf, double house, double rew,
               double fund_val, double pay_salary,double tax_val, double attend_red, double real_sal)
            : Salary_base(id, year, mon,basic_salary) // 使用基类构造函数
            , salary_position(salary_pos)
            , salary_Performance(salary_perf)
            , House(house)
            , reward(rew)
            , pay_salary(pay_salary)
            , fund(fund_val)
            , tax(tax_val)
            , attend_redu(attend_red)
            , real_salary(real_sal){}
    double getSalary_Performance();//计算绩效
    double getHouse();
    double getReward();//计算奖励
    double getPay_salary();//计算应发工资
    double getFund();//计算公积金
    double getTax();//计算扣税
    double getAttend_redu();//计算考勤扣除
    double getReal_salary();//计算实发工资
    Salary(QString id, QString year, QString mon, double basic_salary,double salary_position)
        : Salary_base(id, year, mon,basic_salary),salary_position(salary_position)
    {
        salary_Performance = 0;
        House = 0;//房改补助
        reward = 0;//奖励
        pay_salary = 0;//应发工资
        fund = 0;//公积金
        tax = 0;//扣税
        attend_redu = 0;//考勤扣除
        real_salary = 0;//实发工资
    }
    Salary() {}
    ~Salary() {}
};
class Attendance
{
public:
    QString id;
    int late;//迟到
    int exit_early;//早退
    date time;
    int overtime;//加班总时长
    Attendance(QString id,int late,int exit_early,QString year,QString mon,int overtime)
        :id(id),late(late),exit_early(exit_early),time(year,mon),overtime(overtime){}
    Attendance(){}
    ~Attendance(){}
};
class Sal_Posi
{
public:
    QString Dept;//部门
    int Position;//职位（1员工，2主管)
    double salary_position;//岗位工资
    double department_coefficient;//部门系数
    Sal_Posi(QString dept,int posi,double sal_pos,double dept_co)
        :Dept(dept),Position(posi),salary_position(sal_pos),department_coefficient(dept_co){}
    Sal_Posi(){}
    ~Sal_Posi(){}

};

#endif // BASE_LEI_H
