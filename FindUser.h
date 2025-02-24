#ifndef FINDUSER_H
#define FINDUSER_H

#include"io_base.h"
Employee FindUserByidInEmp(QString id);
QVector<Salary> FindSalary_Mon(QString year,QString mon);//查找到某个月的工资

double FindSal_Posi(QString dept,int posi);//找到一个部门的原始岗位工资
QVector<Salary> FindSalary_user(QString id,QString year);//找到一个人一年的全部工资
QVector<Attendance> FindAttend_user(QString id,QString year);//找到一个人一年的所有考勤记录
Attendance FindAttend_user_Mon(QString id,QString mon,QString year);//找到一个人一个月的所有考勤记录
double FindDept_co(QString dept,int posi);//找到一个部门的部门系数
int FindSalaryInVector(QString id,QVector<Salary> sa);//在一个Vector里找看有没有这个人的工资
double FindBasic_Salary(QString year,QString mon);//找到基本工资
#endif // FINDUSER_H
