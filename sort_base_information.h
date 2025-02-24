#ifndef SORT_BASE_INFORMATION_H
#define SORT_BASE_INFORMATION_H
#include "base_lei.h"
bool comparename(const Employee &e1, const Employee &e2);

bool compareid(const Employee &e1, const Employee &e2);

bool comparetime(const Employee &e1, const Employee &e2);

//按照姓名排序
QVector<Employee> sort_name(QVector<Employee>&t);
//按照工号排序
QVector<Employee> sort_id(QVector<Employee>&t);
//按照出生日期排序
QVector<Employee> sort_time(QVector<Employee>&t);


#endif // SORT_BASE_INFORMATION_H
