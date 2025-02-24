#ifndef FILEBACKUP_H
#define FILEBACKUP_H
#include<QString>
void BackUpEmployee();
void BackUpSalary();
void BackUpAttendce();
void BackUpSal_Posi();
bool BackUpFile(const QString& path_pre,const QString& path_back);
void RestoreEmployee();//恢复员工信息表
void RestoreSalary();//恢复工资表
void RestoreAttendce();//恢复考勤信息表
void RestoreSal_Posi();//恢复岗位工资表
#endif // FILEBACKUP_H
