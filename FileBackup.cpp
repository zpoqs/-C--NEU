#include"Filebackup.h"
#include<QFile>
#include<QDebug>
void BackUpEmployee()
{
    QString path_pre = "D:/5942c++/keshecpp/员工信息表.csv";
    QString path_back = "D:/5942c++/keshecpp/员工信息表_backup.csv";
    bool result = BackUpFile(path_pre,path_back);
    if(result)
    {
        qDebug()<<"文件备份成功";
    }
    else
        qDebug()<<"文件备份失败";
}
void BackUpSalary()
{
    QString path_pre = "D:/5942c++/keshecpp/工资表.csv";
    QString path_back = "D:/5942c++/keshecpp/工资表_backup.csv";
    bool result = BackUpFile(path_pre,path_back);
    if(result)
    {
        qDebug()<<"文件备份成功";
    }
    else
        qDebug()<<"文件备份失败";

}
void BackUpAttendce()
{
    QString path_pre = "D:/5942c++/keshecpp/员工考勤表.csv";
    QString path_back = "D:/5942c++/keshecpp/员工考勤表_backup.csv";
    bool result = BackUpFile(path_pre,path_back);
    if(result)
    {
        qDebug()<<"文件备份成功";
    }
    else
        qDebug()<<"文件备份失败";
}
void BackUpSal_Posi()
{
    QString path_pre = "D:/5942c++/keshecpp/岗位工资表.csv";
    QString path_back = "D:/5942c++/keshecpp/岗位工资表_backup.csv";
    bool result = BackUpFile(path_pre,path_back);
    if(result)
    {
        qDebug()<<"文件备份成功";
    }
    else
        qDebug()<<"文件备份失败";
}
bool BackUpFile(const QString& path_pre,const QString& path_back)
{
    if (!QFile::exists(path_pre)) //先判断文件存不存在
    {
        qDebug() << "原文件文件不存在";
        return false;
    }
    if (QFile::exists(path_back)) // 判断目标文件是否存在
    {
        if (!QFile::remove(path_back)) // 如果存在则删除
        {
            qDebug() << "Failed to remove destination file:" << path_back;
            return false;
        }
    }
    if (!QFile::copy(path_pre, path_back))
    {
        return false;
    }
    return true;
}
void RestoreEmployee()//恢复员工信息表
{
    QString path_pre = "D:/5942c++/keshecpp/员工信息表.csv";
    QString path_back = "D:/5942c++/keshecpp/员工信息表_backup.csv";
    bool result = BackUpFile(path_back,path_pre);
    if(result)
    {
        qDebug()<<"文件恢复成功";
    }
    else
        qDebug()<<"文件恢复失败";
}
void RestoreSalary()//恢复工资表
{
    QString path_pre = "D:/5942c++/keshecpp/工资表.csv";
    QString path_back = "D:/5942c++/keshecpp/工资表_backup.csv";
    bool result = BackUpFile(path_back,path_pre);
    if(result)
    {
        qDebug()<<"文件恢复成功";
    }
    else
        qDebug()<<"文件恢复失败";
}
void RestoreAttendce()//恢复考勤信息表
{
    QString path_pre = "D:/5942c++/keshecpp/员工考勤表.csv";
    QString path_back = "D:/5942c++/keshecpp/员工考勤表_backup.csv";
    bool result = BackUpFile(path_back,path_pre);
    if(result)
    {
        qDebug()<<"文件恢复成功";
    }
    else
        qDebug()<<"文件恢复失败";
}
void RestoreSal_Posi()//恢复岗位工资表
{
    QString path_pre = "D:/5942c++/keshecpp/岗位工资表.csv";
    QString path_back = "D:/5942c++/keshecpp/岗位工资表_backup.csv";
    bool result = BackUpFile(path_back,path_pre);
    if(result)
    {
        qDebug()<<"文件恢复成功";
    }
    else
        qDebug()<<"文件恢复失败";
}
