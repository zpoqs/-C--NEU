#include"FindUser.h"
Employee FindUserByidInEmp(QString id)//在员工信息表找到一个人的信息
{
    int index = 0;//表示当前是第几个元素
    QVector<Employee> user = ReadEmployee();
    while(index < user.size())
    {
        if(user[index].id == id)
        {
            return user[index];
        }
        index++;//非常重要，否则死循环了
    }
    return Employee();//如果没找到就返回空对象
}
QVector<Salary> FindSalary_Mon(QString year,QString mon)//查找到某个月的工资
{
    QVector<Salary> salarys = ReadSalary();
    QVector<Salary> sa_mon;
    int size = salarys.size();
    for(int i = 0;i < size;i++)
    {
        const Salary& sa = salarys[i];
        if(year == sa.time.year&&mon == sa.time.mon)
        {
            sa_mon.push_back(sa);
        }
    }
    return sa_mon;
}
QVector<Salary> FindSalary_user(QString id,QString year)//找到一个人一年的全部工资
{
    QVector<Salary> salarys = ReadSalary();
    QVector<Salary> sa_user;


    for(int i = 0;i < salarys.size();i++)
    {
        const Salary& sa = salarys[i];
        if(sa.id == id&&sa.time.year == year)
        {
            sa_user.push_back(sa);
        }
    }
    return sa_user;
}
QVector<Attendance> FindAttend_user(QString id,QString year)//找到一个人一年的所有考勤记录
{
    QVector<Attendance> attends = ReadAttendance();
    QVector<Attendance> attend_user;
    //int year=2024;
    int size = attends.size();
    for(int i = 0;i < size;i++)
    {
        const Attendance& attend = attends[i];
        if(attend.id == id&&attend.time.year == year)
        {
            attend_user.push_back(attend);
        }
    }
    return attend_user;
}
Attendance FindAttend_user_Mon(QString id,QString mon,QString year)//找到一个人一个月的所有考勤记录
{
    QVector<Attendance> attends = ReadAttendance();
    Attendance attend_user;
    //int year=2024;
    int size = attends.size();
    for(int i = 0;i < size;i++)
    {
        const Attendance& attend = attends[i];
        if(attend.id == id&&attend.time.year == year&&attend.time.mon == mon)
        {
            attend_user = attend;
            break;
        }
    }
    return attend_user;
}

double FindSal_Posi(QString dept,int posi)//找到一个部门的原始岗位工资
{
    QVector<Sal_Posi> sal_pos = ReadSal_Posi();
    int size = sal_pos.size();
    double sa = 0.0;
    for(int i = 0;i < size;i++)
    {
        if(sal_pos[i].Dept == dept&&sal_pos[i].Position == posi)
        {
            sa = sal_pos[i].salary_position;
        }
    }
    return sa;
}
double FindDept_co(QString dept,int posi)//找到一个部门的部门系数
{
    QVector<Sal_Posi> sal_pos = ReadSal_Posi();
    int size = sal_pos.size();
    double co = 0.0;
    for(int i = 0;i < size;i++)
    {
        if(sal_pos[i].Dept == dept&&sal_pos[i].Position == posi)
        {
            co = sal_pos[i].department_coefficient;
        }
    }
    return co;
}
int FindSalaryInVector(QString id,QVector<Salary> sa)//在一个Vector里找看有没有这个人的工资
{
    for(int i = 0;i < sa.size();i++)
    {
        if(sa[i].id == id)
        {
            return 1;//已经有这个id
        }
    }
    return 0;
}
double FindBasic_Salary(QString year,QString mon)//找到基本工资
{

    QVector<Salary> sa = FindSalary_Mon(year,mon);
    return sa[0].basic_salary;
}
