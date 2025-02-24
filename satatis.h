#ifndef SATATIS_H
#define SATATIS_H
#include<QString>
#include<QWidget>
#include<unordered_map>
#include"io_base.h"
void drawGenderPieChart(const QString &filePath, QWidget *parent);
void drawAttendanceChart(const QString &filePath, QWidget *parent);
void drawBarChart(const QMap<QString, int> &departmentCount, QWidget *parent);
void createPieAgeChart(QVector<int>& differences, QWidget *parent);
void createPieChart(const std::unordered_map<int, int> &statuses, QWidget *parent);
void readRewardsAndCreateBarChart(const QString &fileName, QWidget *parent);
void createSalaryBarChart(const QMap<QString, int> &totalSalaries, QWidget *parent);
void createSalaryLastBarChart(QVector<Salary> &lastMonthSalaries,QWidget *parent);
void createOvertimeChart(const QMap<QString, int> &monthlySums, QWidget *parent);
QMap<QString, int> countEmployeesByDepartment(const QString &filePath) ;
QVector<int> extractAndSubtractFrom2024() ;
std::unordered_map<int, int> countEmployeeStatuses(const QString &fileName, int k);
QMap<QString, int> calculateTotalSalaryPerEmployee(const QString &fileName);
QMap<QString, int> calculateLastMonthSalaries(const QString &fileName) ;
QMap<QString, int> calculateMonthlyOvertimeSums(const QString &fileName);
#endif // SATATIS_H
