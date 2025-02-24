#include "inquiry_base_information.h"
#include"base_lei.h"
#include"io_base.h"
#include<QVector>
#include<QDebug>
#include <QFile>
#include <QTextStream>
#include <QList>
#include<QString>
//精确查询
QVector<Employee>inq_name(QString s)
{
       QVector<Employee>list= ReadEmployee();
       QVector<Employee>inquiry;
           for(int i = 0; i < list.size(); i++)
           {
               if(s.QString::compare(list[i].name)==0)//用compare替代strcmp
               {
                   inquiry.append(list[i]);
               }
           }
           return inquiry;
}
QVector<Employee> inq_id(QString s)
{
    QVector<Employee>list= ReadEmployee();
    QVector<Employee>inquiry;
        for(int i = 0; i < list.size(); i++)
        {
            if(s.QString::compare(list[i].id)==0)//用compare替代strcmp
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
}

QVector<Employee> inq_depart(QString s)
{
    QVector<Employee>list= ReadEmployee();
    QVector<Employee>inquiry;
        for(int i = 0; i < list.size(); i++)
        {
            if(s.QString::compare(list[i].Dept)==0)//用compare替代strcmp
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
}
QVector<Employee>inq_postition(int s)
{
    QVector<Employee>list= ReadEmployee();
    QVector<Employee>inquiry;
        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].Position==s)//用compare替代strcmp
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
}
//模糊查询
QVector<Employee>inq_iname(QString s)
{
        QVector<Employee> list = ReadEmployee();
        QVector<Employee> inquiry;

        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].name.contains(s, Qt::CaseInsensitive)) // 模糊查询，不区分大小写
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
}

QVector<Employee>inq_iid(QString s)
{
    QVector<Employee> list = ReadEmployee();
    QVector<Employee> inquiry;

    for(int i = 0; i < list.size(); i++)
    {
        if(list[i].id.contains(s, Qt::CaseInsensitive)) // 模糊查询，不区分大小写
        {
            inquiry.append(list[i]);
        }
    }
    return inquiry;
}
//精确的组合查询
QVector<Employee>  inq_position_dept(int s1,QString s2)
{
    QVector<Employee>list= ReadEmployee();
    QVector<Employee>inquiry;
        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].Position==s1&&s2.compare(list[i].Dept)==0)//用compare替代strcmp,但是不用说明作用域
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
}
QVector<Employee>  inq_name_position(QString s1,int s2)
{
    QVector<Employee>list= ReadEmployee();
    QVector<Employee>inquiry;
        for(int i = 0; i < list.size(); i++)
        {
            if(s1.compare(list[i].name)==0&&list[i].Position==s2)//用compare替代strcmp,但是不用说明作用域
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
}
QVector<Employee>  inq_name_dept(QString s1,QString s2)
{
    QVector<Employee>list= ReadEmployee();
    QVector<Employee>inquiry;
        for(int i = 0; i < list.size(); i++)
        {
            if(s1.compare(list[i].name)==0&&s2.compare(list[i].Dept)==0)//用compare替代strcmp,但是不用说明作用域
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
}
//模糊的组合查询
QVector<Employee>  inq_phone_plus_email(QString s1,QString s2)
{
    QVector<Employee> list = ReadEmployee();
    QVector<Employee> inquiry;

    for(int i = 0; i < list.size(); i++)
    {
        if(list[i].Phone.contains(s1, Qt::CaseInsensitive)&&list[i].Email.contains(s2, Qt::CaseInsensitive)) // 模糊查询，不区分大小写
        {
            inquiry.append(list[i]);
        }
    }
    return inquiry;
}
QVector<Employee>  inq_name_plus_address(QString s1,QString s2)
{
    QVector<Employee> list = ReadEmployee();
    QVector<Employee> inquiry;

    for(int i = 0; i < list.size(); i++)
    {
        if(list[i].name.contains(s1, Qt::CaseInsensitive)&&list[i].Address.contains(s2, Qt::CaseInsensitive)) // 模糊查询，不区分大小写
        {
            inquiry.append(list[i]);
        }
    }
    return inquiry;
}

