#include "login.h"
#include <QApplication>
#include"FindUser.h"
#include"inquiry_base_information.h"
#include"Filebackup.h"
#include"satatis.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();
    AddSalaryToFile();

    return a.exec();
}




// 调用函数

//QVector<Salary> sa = ReadSalary();
//qDebug()<<sa[0].id;
//    for(int i = 0;i < sa.size();i++)
//    {
//        sa[i].getReward();
//        sa[i].getHouse();
//        sa[i].getAttend_redu();
//        sa[i].getPay_salary();
//        sa[i].getFund();
//        sa[i].getSalary_Performance();
//        sa[i].getTax();
//        sa[i].getReal_salary();
//    }
//    int result = WriteSalaryToFile(sa);
//    if(result == 1)
//        qDebug()<<"yes";
