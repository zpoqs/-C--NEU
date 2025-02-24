#ifndef INQUIRY_BASE_INFORMATION_H
#define INQUIRY_BASE_INFORMATION_H
#include <QString>
#include "base_lei.h"

    //精确查询
    QVector<Employee> inq_name(QString s);//姓名
    QVector<Employee>  inq_id(QString s);//工号
    QVector<Employee>  inq_depart(QString s);//部门
    QVector<Employee>  inq_postition(int s);//职位
    //模糊查询
    //名字当中的某个字
    QVector<Employee>  inq_iname(QString s);
    //工号中的某个子串
    QVector<Employee>  inq_iid(QString s);
    //组合查询精确
     QVector<Employee>  inq_position_dept(int s1,QString s2);
     QVector<Employee>  inq_name_position(QString s1,int s2);
     QVector<Employee>  inq_name_dept(QString s1,QString s2);
     //模糊的组合查询
     QVector<Employee>  inq_phone_plus_email(QString s1,QString s2);
     QVector<Employee>  inq_name_plus_address(QString s1,QString s2);

#endif // INQUIRY_BASE_INFORMATION_H
