#include "inquiry_base_salary.h"
#include"base_lei.h"
#include"io_base.h"
#include<QVector>
#include<QDebug>
#include <QFile>
#include <QTextStream>
#include <QList>
#include<QString>
#include"sort_salary.h"
//岗位工资
bool compareposition_salary(const Salary&s1,const Salary&s2)
{
    return s1.salary_position<s2.salary_position;
}
QVector<Salary> sort_Position(QVector<Salary>&t)
{
    QVector<Salary> sort;
    foreach (const Salary&emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    std::sort(sort.begin(), sort.end(), compareposition_salary);
    return sort;
}
//绩效工资
bool compareper_salary(const Salary&s1,const Salary&s2)
{
    return s1.salary_Performance<s2.salary_Performance;
}
QVector<Salary> sort_performance(QVector<Salary>&t)
{
    QVector<Salary> sort;
    foreach (const Salary&emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    std::sort(sort.begin(), sort.end(), compareper_salary);
    return sort;
}
//房改补助
bool comparehouse(const Salary&s1,const Salary&s2)
{
    return s1.House<s2.House;
}
QVector<Salary> sort_house(QVector<Salary>&t)
{
    QVector<Salary> sort;
    foreach (const Salary&emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    std::sort(sort.begin(), sort.end(), comparehouse);
    return sort;
}
//应发工资
bool comparepay_salary(const Salary&s1,const Salary&s2)
{
    return s1.pay_salary<s2.pay_salary;
}
QVector<Salary> sort_pay(QVector<Salary>&t)
{
    QVector<Salary> sort;
    foreach (const Salary&emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    std::sort(sort.begin(), sort.end(), comparepay_salary);
    return sort;
}
//实发工资
bool comparereal_salary(const Salary&s1,const Salary&s2)
{
    return s1.real_salary<s2.real_salary;
}
QVector<Salary> sort_real(QVector<Salary>&t)
{
    QVector<Salary> sort;
    foreach (const Salary&emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    std::sort(sort.begin(), sort.end(), comparereal_salary);
    return sort;
}
//公积金
bool comparefund(const Salary&s1,const Salary&s2)
{
    return s1.fund<s2.fund;
}
QVector<Salary> sort_fund(QVector<Salary>&t)
{
    QVector<Salary> sort;
    foreach (const Salary&emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    std::sort(sort.begin(), sort.end(), comparefund);
    return sort;
}
//扣税
bool comparetax(const Salary&s1,const Salary&s2)
{
    return s1.tax<s2.tax;
}
QVector<Salary> sort_tax(QVector<Salary>&t)
{
    QVector<Salary> sort;
    foreach (const Salary&emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    std::sort(sort.begin(), sort.end(), comparetax);
    return sort;
}
//奖励
bool comparereward(const Salary&s1,const Salary&s2)
{
    return s1.reward<s2.reward;
}
QVector<Salary> sort_reward(QVector<Salary>&t)
{
    QVector<Salary> sort;
    foreach (const Salary&emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    std::sort(sort.begin(), sort.end(), comparereward);
    return sort;
}
//考勤扣除
bool compareattend(const Salary&s1,const Salary&s2)
{
    return s1.attend_redu<s2.attend_redu;
}
QVector<Salary> sort_attend(QVector<Salary>&t)
{
    QVector<Salary> sort;
    foreach (const Salary&emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    std::sort(sort.begin(), sort.end(), compareattend);
    return sort;
}
