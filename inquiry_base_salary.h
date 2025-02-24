#ifndef INQUIRY_BASE_SALARY_H
#define INQUIRY_BASE_SALARY_H
#include <QString>
#include "base_lei.h"
//按工号查询工资
QVector<Salary> inq_id_salary(QString s1,QString s2,QString s3);
//按照岗位工资查询
QVector<Salary> inq_position_salary(double s1,QString s2,QString s3);
//按照绩效工资查询
QVector<Salary> inq_performance_salary(double s1,QString s2,QString s3);
//按照应发工资查询
QVector<Salary> inq_pay_salary(double s1,QString s2,QString s3);
//按照实发工资查询
QVector<Salary> inq_real_salary(double s1,QString s2,QString s3);
//按照公积金查询
QVector<Salary> inq_fund_salary(double s1,QString s2,QString s3);
//按照房改补助查询
QVector<Salary> inq_house_salary(double s1,QString s2,QString s3);
//组合查询
//工号和实发工资
QVector<Salary> inq_id_real_salary(QString s1,double i,QString s2,QString s3);
//基本工资和绩效工资
QVector<Salary> inq_Posi_performance_salary(double s1,double s2,QString s3,QString s4);
//应发工资和扣税
QVector<Salary> inq_pay_tax_salary(double s1,double s2,QString s3,QString s4);
//查询某年某月的工资
#endif // INQUIRY_BASE_SALARY_H
