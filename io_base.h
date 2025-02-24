#ifndef IO_BASE_H
#define IO_BASE_H

#include <QFile>
#include <QTextStream>
#include"base_lei.h"
Employee GetEmployee(QString line);
QVector<Employee> ReadEmployee();
Salary GetSalary(QString line);
QVector<Salary> ReadSalary();
Attendance GetAttendance(QString line);
QVector<Attendance> ReadAttendance();
int WriteEmployeeToFile(QVector<Employee> user);//将员工信息写回文件
QVector<Salary> Salary_New_Mon();//更新一个月的信息
QString SalaryToString(Salary& salary);//调用arg方法直接将一个salary对象转换为字符串
void AddSalaryToFile();//每月固定时间添加工资基本信息
int WriteSalaryToFile(QVector<Salary> salary);//将工资信息写入文件
QVector<Sal_Posi> ReadSal_Posi();
Sal_Posi GetSal_Posi(QString line);//岗位工资
int WriteSal_PosiToFile(QVector<Sal_Posi> user);//将岗位工资信息写回文件
QString Sal_PosiToString(Sal_Posi& sal_Posi);//调用arg方法直接将一个对象转换为字符串
QVector<Salary> Per_Sal_New();//为新员工添加工资信息
void AddNewPerSalary(QVector<Salary> sa_user);//将新员工的工资信息追加到文件里，应该是很多人，如果是批量录入
bool AddInfoToFile(const QString& path_from, const QString& path_to);//追加文件从另外的文件
#endif // IO_BASE_H
