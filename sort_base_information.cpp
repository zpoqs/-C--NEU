#include "inquiry_base_salary.h"
#include"base_lei.h"
#include"io_base.h"
#include<QVector>
#include<QDebug>
#include <QFile>
#include <QTextStream>
#include <QList>
#include<QString>
#include"sort_base_information.h"

bool comparename(const Employee &e1, const Employee &e2)
{
    return e1.name < e2.name;
}
bool compareid(const Employee &e1, const Employee &e2)
{
    return e1.id < e2.id;
}
bool comparetime(const Employee &e1, const Employee &e2)
{
    return e1.Date_birth < e2.Date_birth;
}
//按照姓名排序
QVector<Employee> sort_name(QVector<Employee>&t)
{
    QVector<Employee> sort;
    foreach (const Employee &emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    qSort(sort.begin(), sort.end(), comparename);
    return sort;
}
//按照工号排序
QVector<Employee> sort_id(QVector<Employee>&t)
{
    QVector<Employee> sort;
    foreach (const Employee &emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    qSort(sort.begin(), sort.end(), compareid);//排序函数
    return sort;
}
//按照出生日期排序
QVector<Employee> sort_time(QVector<Employee>&t)
{
    QVector<Employee> sort;
    foreach (const Employee &emp, t)//遍历t并将t的元素复制到sort中去
    {
            sort.append(emp);
    }
    qSort(sort.begin(), sort.end(), comparetime);
    return sort;
}
