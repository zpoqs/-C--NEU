#ifndef SORT_SALARY_H
#define SORT_SALARY_H
#include"base_lei.h"
//按照岗位工资排序
bool compareposition_salary(const Salary&s1,const Salary&s2);
QVector<Salary> sort_Position(QVector<Salary>&t);
//绩效工资
bool compareper_salary(const Salary&s1,const Salary&s2);

QVector<Salary> sort_performance(QVector<Salary>&t);
//房改补助
bool comparehouse(const Salary&s1,const Salary&s2);

QVector<Salary> sort_house(QVector<Salary>&t);
//应发工资
bool comparepay_salary(const Salary&s1,const Salary&s2);

QVector<Salary> sort_pay(QVector<Salary>&t);
//实发工资
bool comparereal_salary(const Salary&s1,const Salary&s2);

QVector<Salary> sort_real(QVector<Salary>&t);
//公积金
bool comparefund(const Salary&s1,const Salary&s2);

QVector<Salary> sort_fund(QVector<Salary>&t);
//扣税
bool comparetax(const Salary&s1,const Salary&s2);

QVector<Salary> sort_tax(QVector<Salary>&t);
//奖励
bool comparereward(const Salary&s1,const Salary&s2);

QVector<Salary> sort_reward(QVector<Salary>&t);
//考勤扣除
bool compareattend(const Salary&s1,const Salary&s2);

QVector<Salary> sort_attend(QVector<Salary>&t);
#endif // SORT_SALARY_H
