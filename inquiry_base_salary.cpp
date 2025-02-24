#include "inquiry_base_salary.h"
#include"base_lei.h"
#include"io_base.h"
#include<QVector>
#include<QDebug>
#include <QFile>
#include <QTextStream>
#include <QList>
#include<QString>

//按工号查询工资
QVector<Salary> inq_id_salary(QString s1,QString s2,QString s3)
{
    QString s="";//如果没有输入月份的话就将某一个成员一年的工资信息
    QVector<Salary>list= ReadSalary();
    QVector<Salary>inquiry;
    if(s3.QString::compare(s)==0)
    {
        for(int i = 0; i < list.size(); i++)
        {
            if(s1.QString::compare(list[i].id)==0&&s2.QString::compare(list[i].time.year)==0)
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
    }
    else
    {
        for(int i = 0; i < list.size(); i++)
        {
            if(s1.QString::compare(list[i].id)==0&&s2.QString::compare(list[i].time.year)==0&&s3.QString::compare(list[i].time.mon)==0)
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
    }
}
//按照岗位工资查询
QVector<Salary> inq_position_salary(double s1,QString s2,QString s3)
{
     QString s="";
     QVector<Salary>list= ReadSalary();
     QVector<Salary>inquiry;
    if(s3.QString::compare(s)==0)
    {
        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].salary_position==s1&&s2.QString::compare(list[i].time.year)==0)
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
    }
    else
    {
            for(int i = 0; i < list.size(); i++)
            {
                if(list[i].salary_position==s1&&s2.QString::compare(list[i].time.year)==0&&s3.QString::compare(list[i].time.mon)==0)
                {
                    inquiry.append(list[i]);
                }
            }
            return inquiry;
    }
}
//按照绩效工资查询
QVector<Salary> inq_performance_salary(double s1,QString s2,QString s3)
{
    QString s="";
    QVector<Salary>list= ReadSalary();
    QVector<Salary>inquiry;
   if(s3.QString::compare(s)==0)
   {
       for(int i = 0; i < list.size(); i++)
       {
           if(list[i].salary_Performance==s1&&s2.QString::compare(list[i].time.year)==0)
           {
               inquiry.append(list[i]);
           }
       }
       return inquiry;
   }
   else
   {
           for(int i = 0; i < list.size(); i++)
           {
               if(list[i].salary_Performance==s1&&s2.QString::compare(list[i].time.year)==0&&s3.QString::compare(list[i].time.mon)==0)
               {
                   inquiry.append(list[i]);
               }
           }
           return inquiry;
   }
}
//按照应发工资查询
QVector<Salary> inq_pay_salary(double s1,QString s2,QString s3)
{
    QString s="";
    QVector<Salary>list= ReadSalary();
    QVector<Salary>inquiry;
   if(s3.QString::compare(s)==0)
   {
       for(int i = 0; i < list.size(); i++)
       {
           if(list[i].pay_salary==s1&&s2.QString::compare(list[i].time.year)==0)
           {
               inquiry.append(list[i]);
           }
       }
       return inquiry;
   }
   else
   {
           for(int i = 0; i < list.size(); i++)
           {
               if(list[i].pay_salary==s1&&s2.QString::compare(list[i].time.year)==0&&s3.QString::compare(list[i].time.mon)==0)
               {
                   inquiry.append(list[i]);
               }
           }
           return inquiry;
   }
}
//按照实发工资查询
QVector<Salary> inq_real_salary(double s1,QString s2,QString s3)
{
    QString s="";
    QVector<Salary>list= ReadSalary();
    QVector<Salary>inquiry;
   if(s3.QString::compare(s)==0)
   {
       for(int i = 0; i < list.size(); i++)
       {
           if(list[i].real_salary==s1&&s2.QString::compare(list[i].time.year)==0)
           {
               inquiry.append(list[i]);
           }
       }
       return inquiry;
   }
   else
   {
           for(int i = 0; i < list.size(); i++)
           {
               if(list[i].real_salary==s1&&s2.QString::compare(list[i].time.year)==0&&s3.QString::compare(list[i].time.mon)==0)
               {
                   inquiry.append(list[i]);
               }
           }
           return inquiry;
   }
}
//按照公积金查询
QVector<Salary> inq_fund_salary(double s1,QString s2,QString s3)
{
    QString s="";
    QVector<Salary>list= ReadSalary();
    QVector<Salary>inquiry;
   if(s3.QString::compare(s)==0)
   {
       for(int i = 0; i < list.size(); i++)
       {
           if(list[i].fund==s1&&s2.QString::compare(list[i].time.year)==0)
           {
               inquiry.append(list[i]);
           }
       }
       return inquiry;
   }
   else
   {
           for(int i = 0; i < list.size(); i++)
           {
               if(list[i].fund==s1&&s2.QString::compare(list[i].time.year)==0&&s3.QString::compare(list[i].time.mon)==0)
               {
                   inquiry.append(list[i]);
               }
           }
           return inquiry;
   }
}
//按照房改补助查询
QVector<Salary> inq_house_salary(double s1,QString s2,QString s3)
{
    QString s="";
    QVector<Salary>list= ReadSalary();
    QVector<Salary>inquiry;
   if(s3.QString::compare(s)==0)
   {
       for(int i = 0; i < list.size(); i++)
       {
           if(list[i].House==s1&&s2.QString::compare(list[i].time.year)==0)
           {
               inquiry.append(list[i]);
           }
       }
       return inquiry;
   }
   else
   {
           for(int i = 0; i < list.size(); i++)
           {
               if(list[i].House==s1&&s2.QString::compare(list[i].time.year)==0&&s3.QString::compare(list[i].time.mon)==0)
               {
                   inquiry.append(list[i]);
               }
           }
           return inquiry;
   }
}
//组合查询
//工号和实发工资
QVector<Salary> inq_id_real_salary(QString s1,double s2,QString s3,QString s4)
{
    QString s="";
    QVector<Salary>list= ReadSalary();
    QVector<Salary>inquiry;
    if(s.QString::compare(s4)==0)
    {
        for(int i = 0; i < list.size(); i++)
        {
            if(s1.QString::compare(list[i].id)==0&&list[i].real_salary==s2&&s3.QString::compare(list[i].time.year)==0)
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
    }
    else
    {
        for(int i = 0; i < list.size(); i++)
        {
            if(s1.QString::compare(list[i].id)==0&&list[i].real_salary==s2&&s3.QString::compare(list[i].time.year)==0&&s4.QString::compare(list[i].time.mon)==0)
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
    }

}
//岗位工资和绩效工资
QVector<Salary> inq_Posi_performance_salary(double s1,double s2,QString s3,QString s4)
{
    QString s="";
    QVector<Salary>list= ReadSalary();
    QVector<Salary>inquiry;
    if(s.QString::compare(s4)==0)
    {
        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].salary_position==s1&&list[i].salary_Performance==s2&&s3.QString::compare(list[i].time.year)==0)
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
    }
    else
    {
        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].salary_position==s1&&list[i].salary_Performance==s2&&s3.QString::compare(list[i].time.year)==0&&s4.QString::compare(list[i].time.mon)==0)
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
    }
}
//应发工资和扣税
QVector<Salary> inq_pay_tax_salary(double s1,double s2,QString s3,QString s4)
{
    QString s="";
    QVector<Salary>list= ReadSalary();
    QVector<Salary>inquiry;
    if(s.QString::compare(s4)==0)
    {
        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].pay_salary==s1&&list[i].tax==s2&&s3.QString::compare(list[i].time.year)==0)
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
    }
    else
    {
        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].pay_salary==s1&&list[i].tax==s2&&s3.QString::compare(list[i].time.year)==0&&s4.QString::compare(list[i].time.mon)==0)
            {
                inquiry.append(list[i]);
            }
        }
        return inquiry;
    }
}

