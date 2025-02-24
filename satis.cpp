//#include "login.h"
#include <QApplication>
#include"FindUser.h"
#include"inquiry_base_information.h"
#include"Filebackup.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include<satatis.h>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarSet>
#include <QLayout>
#include<fstream>
#include<iostream>
#include<sstream>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include<QMap>
#include"io_base.h"
#include<QtMath>
QT_CHARTS_USE_NAMESPACE

// 男女比例
// 函数读取文件并返回男性和女性的数量
std::pair<int, int> readGenderCounts(const QString &filePath) {
    int maleCount = 0;
    int femaleCount = 0;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 处理文件打开失败的情况
        return {0, 0};
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 2) {
            QString gender = parts[0].trimmed().toUpper();
            int count = parts[1].toInt();
            if (gender == "M") {
                maleCount += count;
            } else if (gender == "F") {
                femaleCount += count;
            }
        }
    }

    file.close();
    return {maleCount, femaleCount};
}

// 绘制扇形图的函数
void drawGenderPieChart(const QString &filePath, QWidget *parent) {
    int maleCount = 0;
    int femaleCount = 0;
    //auto [maleCount, femaleCount] = readGenderCounts(filePath);
    std::cout<<maleCount<<"\n";
    // 如果没有数据，就不绘制图表
    QVector<Employee> employ = ReadEmployee();
    for(int i = 0 ;i < employ.size();i++)
    {
        if(employ[i].sex == "男"&&employ[i].Status == 1)
        {
            maleCount++;
        }
        if(employ[i].sex == "女"&&employ[i].Status == 1)
        {
            femaleCount++;
        }
    }

    // 创建扇形图系列
    QPieSeries *series = new QPieSeries();
    series->append("男性", maleCount);
    series->append("女性", femaleCount);

    // 创建图表
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("男女比例扇形图");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // 创建图表视图
    QChartView *chartView = new QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 设置 chartView 的位置和大小
    chartView->setGeometry(100, 80, 500, 400);

    // 显示图表视图
    chartView->show();
}


// 总体考勤情况，x轴为月份（个人较为麻烦）
// 读取函数
QList<QPair<int, QPair<int, int>>> readAttendanceData(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};

    QTextStream in(&file);
    QList<QPair<int, QPair<int, int>>> data;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 5) {
            int month = parts[4].toInt(); // 月份是从1到12的整数
            int late = parts[1].toInt();
            int leaveEarly = parts[2].toInt();
            data.append(qMakePair(month, qMakePair(late, leaveEarly)));
        }
    }
    file.close();
    return data;
}

// 绘制图表
void drawAttendanceChart(const QString &filePath, QWidget *parent) {
    QList<QPair<int, QPair<int, int>>> data = readAttendanceData(filePath);

    if (data.isEmpty())
        return;

    // 创建系列
    QLineSeries *lateSeries = new QLineSeries();
    QLineSeries *leaveEarlySeries = new QLineSeries();

    // 添加数据到系列
    for (const auto &pair : data) {
        lateSeries->append(pair.first, pair.second.first);
        leaveEarlySeries->append(pair.first, pair.second.second);
    }

    // 创建图表
    QChart *chart = new QChart();
    chart->addSeries(lateSeries);
    chart->addSeries(leaveEarlySeries);
    chart->setTitle("员工考勤折线图");
    chart->createDefaultAxes();

    // 设置系列标签
    lateSeries->setName("迟到次数");
    leaveEarlySeries->setName("早退次数");

//    // 设置X轴标签（月份）
//    QStringList months;
//    for (int i = 1; i <= 12; ++i)
//        months << QString::number(i);
//    chart->axisX()->setCategories(months);
    // 设置X轴标签（月份）
        QStringList months;
        for (int i = 1; i <= 12; ++i)
            months << QString::number(i);

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(months);
        chart->setAxisX(axisX, lateSeries);  // 将轴添加到图表中

    // 创建视图
    QChartView *chartView = new QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 将视图添加到布局中
    // 设置 chartView 的位置和大小
    chartView->setGeometry(800, 900, 1000, 400);

    // 显示图表视图
    chartView->show();
}

// 各部门人数
// 读取文件并统计部门人数
QMap<QString, int> countEmployeesByDepartment(const QString &filePath) {
    QMap<QString, int> departmentCount;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                QStringList fields = line.split(",");
                if (fields.size() >= 4) {
                    QString department = fields[3].trimmed(); // 部门信息在第四列
                    departmentCount[department]++;
                }
            }
        }
    }
    return departmentCount;
}


void drawBarChart(const QMap<QString, int> &departmentCount, QWidget *parent) {
    QtCharts::QHorizontalBarSeries *series = new QtCharts::QHorizontalBarSeries();

    for (const QString &department : departmentCount.keys()) {
        QtCharts::QBarSet *set = new QtCharts::QBarSet(department);
        *set << departmentCount[department];
        series->append(set);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("各部门员工人数");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->legend()->setVisible(true);

    QtCharts::QBarCategoryAxis *axisY = new QtCharts::QBarCategoryAxis();
    axisY->append(departmentCount.keys());
    chart->createDefaultAxes();
    chart->setAxisY(axisY, series);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);
    // 设置 chartView 的位置和大小
    chartView->setGeometry(600, 0, 900, 500);

    // 显示图表视图
    chartView->show();

}
// 调用函数

QVector<int> extractAndSubtractFrom2024()
{
    QVector<Employee> em = ReadEmployee();
    QVector<int> diff ;
    for(int i = 0;i < em.size();i++)
    {
        if(em[i].Status == 1)
        {
            QString first = em[i].Date_birth.left(4);
            int year = first.toUInt();
            int result = 2024 - year;
            diff.push_back(result);
        }
    }
    return diff;
}


void createPieAgeChart(QVector<int>& differences,QWidget* parent) {
    // 创建一个QPieSeries对象
    std::cout << "接收到的年龄差异数据：" << std::endl;
        for (int diff : differences) {
            std::cout << diff << std::endl;
        }

    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    QVector<int> intervals(5, 0); // 初始化5个区间的计数为0
    for (int diff : differences) {
        // 确保差值在有效范围内
        if (diff >= 0 && diff <= 45) {
            // 计算差值属于哪个区间
            int index = diff / 9; // 每个区间9年
            if (index < intervals.size()) {
                intervals[index]++; // 增加对应区间的计数
            }
            // 注意：如果diff是45，它将落在最后一个区间，因为index将会是4（45除以9等于5，但索引从0开始）
        }
    }

    // 将区间计数添加到QPieSeries中
    for (int i = 0; i < intervals.size(); ++i) {
        // 注意调整标签以反映新的区间范围
        QString label = QString("%1 - %2").arg(2024 - i * 9).arg(2024 - (i + 1) * 9 + 1);
        // 如果i是最后一个区间（index为4），则结束年份应为2016（因为2024 - 4*9 = 2016）
        // 但由于arg方法会处理+1的情况，所以这里不需要特别处理
        series->append(label, intervals[i]);
    }

    // 创建一个QChart对象，并将QPieSeries添加到其中
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("员工年龄分布（按五年区间）");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // 创建一个QChartView对象，并将QChart添加到其中
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart,parent);
    chartView->setRenderHint(QPainter::Antialiasing);
    // 设置 chartView 的位置和大小
    chartView->setGeometry(600, 500, 900, 500);

    // 显示图表视图
    chartView->show();
}

// 在主函数中调用这个函数

// 在职人数
std::unordered_map<int, int> countEmployeeStatuses(const QString &fileName, int k) {
    std::unordered_map<int, int> statuses;
    statuses[1] = 0; // 在职
    statuses[0] = 0; // 不在职

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return statuses;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(","); // 假设字段由逗号分隔
        if (fields.size() > 10) {
            bool ok;
            int status = fields[10].toInt(&ok); // 读取第11列作为状态
            if (ok && (status == 1 || status == 0)) {
                statuses[status]++;
            }
        }
    }
    file.close();
    return statuses;
}

void createPieChart(const std::unordered_map<int, int> &statuses, QWidget *parent) {
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

    // 添加在职和不在职的切片
    int inOffice = statuses.count(1) ? statuses.at(1) : 0;
    int notInOffice = statuses.count(0) ? statuses.at(0) : 0;
    series->append("在职", inOffice);
    series->append("不在职", notInOffice);

    // 创建一个图表
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("员工在职状态");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // 创建一个图表视图
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 设置 chartView 的位置和大小
    chartView->setGeometry(100, 500, 500, 400);

    // 显示图表视图
    chartView->show();
}

void readRewardsAndCreateBarChart(const QString &fileName, QWidget* parent) {
    // 初始化奖励区间的计数
    std::vector<int> rewardCounts(4, 0); // 假设最大奖励为2000，因此有4个区间（0-499, 500-999, 1000-1499,1500-2000）

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(","); // 假设字段由逗号分隔
        if (fields.size() > 7) { // 第8列是奖励，所以索引是7
            bool ok;
            int reward = fields[7].toInt(&ok); // 读取第8列的奖励值
            if (fields[2] == "4"&&ok && reward >= 0 && reward <= 10000) { // 假设奖励在0到10000之间
                int index = reward / 500; // 计算奖励所在的区间索引
                if (index < rewardCounts.size()) {
                    rewardCounts[index]++; // 增加对应区间的计数
                }
            }
        }
    }
    file.close();

    // 创建柱状图数据
    QtCharts::QBarSet *set = new QtCharts::QBarSet("奖励区间人数");
    QStringList categories;
    for (int i = 0; i < rewardCounts.size(); ++i) {
        QString category = QString("%1-%2").arg(i * 500).arg((i + 1) * 500 - 1);
        categories.append(category);
        *set << rewardCounts[i]; // 将每个区间的计数添加到柱状图中
    }

    // 创建柱状图
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(set);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("员工奖励区间人数");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // 设置X轴为类别轴
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 设置Y轴
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("人数");
    int maxCount = *std::max_element(rewardCounts.begin(), rewardCounts.end()); // 获取最大的计数值
    axisY->setRange(0, maxCount); // 设置Y轴范围为最大计数的上限
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 创建一个图表视图并显示
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);
    // 设置 chartView 的位置和大小
    chartView->setGeometry(0,700, 800, 600);

    // 显示图表视图
    chartView->show();
}

// 读取文件并计算每个员工的工资总和
QMap<QString, int> calculateTotalSalaryPerEmployee(const QString &fileName) {
    QMap<QString, int> totalSalaries;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return totalSalaries;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(","); // 假设字段由逗号分隔
        if (fields.size() > 12) {
            QString id = fields[0]; // 员工ID
            bool ok;
            int salary = fields[12].toInt(&ok); // 工资
            if (ok) {
                // 假设每行都是同一年的数据，可以通过其他逻辑来处理跨年的情况
                totalSalaries[id] += salary; // 累加工资
            }
        }
    }
    file.close();
    return totalSalaries;
}

void createSalaryBarChart(const QMap<QString, int> &totalSalaries, QWidget* parent) {
    // 初始化工资区间的计数
    std::vector<int> salaryCounts(6, 0); // 0-9999, 10000-19999, ..., 50000-59999

    // 遍历每个员工的工资总和，并计算区间人数
    for (QMap<QString, int>::const_iterator it = totalSalaries.cbegin(); it != totalSalaries.cend(); ++it) {
        int salary = it.value();
        qDebug() << "ID:" << it.key() << "Salary:" << salary; // 调试输出每个员工的ID和工资
        if (salary >= 0 && salary < 60000) {
            int index = salary / 10000; // 计算工资所在的区间索引
            if (index < salaryCounts.size()) {
                salaryCounts[index]++; // 增加对应区间的计数
            }
        }
    }

    // 创建柱状图数据
    QtCharts::QBarSet *set = new QtCharts::QBarSet("工资区间人数");
    QStringList categories;
    for (int i = 0; i < salaryCounts.size(); ++i) {
        QString category = QString("%1-%2").arg(i * 10000).arg((i + 1) * 10000 - 1);
        categories.append(category);
        *set << salaryCounts[i]; // 将每个区间的计数添加到柱状图中
        qDebug() << "Category:" << category << "Count:" << salaryCounts[i]; // 调试输出每个区间的类别和计数
    }

    // 创建柱状图
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(set);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("员工工资区间人数");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // 设置X轴为类别轴
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 设置Y轴
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("人数");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 创建一个图表视图并显示
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(700, 0, 1300, 400);

    // 显示图表视图
    chartView->show();



}
QMap<QString, int> calculateLastMonthSalaries(const QString &fileName) {
    QMap<QString, int> lastMonthSalaries; // 临时存储每个员工最后一个月的工资
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return lastMonthSalaries;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() > 2 && fields.size() > 12) {
            QString id = fields[0];
            bool ok;
            int salary = fields[12].toInt(&ok);
            if (ok) {
                // 存储每个员工最后一个月的工资
                lastMonthSalaries[id] = salary;
            } else {
                qDebug() << "Invalid salary value for ID:" << id << "Value:" << fields[12];
            }
        } else {
            qDebug() << "Invalid line format:" << line;
        }
    }
    file.close(); // 关闭文件
    return lastMonthSalaries;
}

void createSalaryLastBarChart(QVector<Salary>&lastMonthSalaries, QWidget* parent) {
    // 寻找最低工资和最高工资
        int minSalary = INT_MAX;
        int maxSalary = INT_MIN;
        for (const Salary& salary : lastMonthSalaries) {
            if (salary.real_salary < minSalary)
                minSalary = salary.real_salary;
            if (salary.real_salary > maxSalary)
                maxSalary = salary.real_salary;
        }

        // 确定动态工资区间范围
        int interval = 1500;
        int numIntervals = (maxSalary - minSalary) / interval + 1;

        // 初始化工资区间的计数
        std::vector<int> salaryCounts(numIntervals, 0);
        // 遍历每个员工的最后一个月的工资，并计算区间人数
            for (const Salary& salary : lastMonthSalaries) {
                int index = (salary.real_salary - minSalary) / interval;
                if (index >= 0 && index < numIntervals) {
                    salaryCounts[index]++; // 增加对应区间的计数
                }
            }

    // 创建柱状图数据
    QtCharts::QBarSet *set = new QtCharts::QBarSet("工资区间人数");
    QStringList categories;
    for (int i = 0; i < salaryCounts.size(); ++i) {
        QString category = QString("%1-%2").arg(6000 + i * 1500).arg(6000 + (i + 1) * 1500 - 1);
        categories.append(category);
        *set << salaryCounts[i]; // 将每个区间的计数添加到柱状图中
        qDebug() << "Category:" << category << "Count:" << salaryCounts[i]; // 调试输出每个区间的类别和计数
    }

    // 创建柱状图
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(set);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("员工最后一个月工资区间人数");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // 设置X轴为类别轴
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 设置Y轴
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("人数");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 创建一个图表视图并显示
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(800, 500, 1000, 400);

    // 显示图表视图
    chartView->show();
}




// 加班时长（总体）
// 读取员工考勤表并计算每月加班时长之和
QMap<QString, int> calculateMonthlyOvertimeSums(const QString &fileName) {
    QMap<QString, int> monthlySums;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return monthlySums;

    QTextStream in(&file);
    // 第一行是标题，跳过
    in.readLine();
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(","); // 假设字段由逗号分隔
        if (fields.size() > 5) {
            QString month = fields[4]; // 月份
            bool ok;
            int overtime = fields[5].toInt(&ok); // 加班时长
            if (ok) {
                monthlySums[month] += overtime; // 累加该月份的加班时长
            }
        }
    }
    file.close();
    return monthlySums;
}
void createOvertimeChart(const QMap<QString, int> &monthlySums, QWidget* parent) {
    // 创建柱状图序列
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

    // 创建一个用于存储加班时长的 QBarSet
    QtCharts::QBarSet *set = new QtCharts::QBarSet("加班时长");

    // 用于存储月份
    QStringList categories;

    // 提取月份和对应的加班时长，并添加到序列中
    for (auto it = monthlySums.constBegin(); it != monthlySums.constEnd(); ++it) {
        QString month = it.key();
        int overtimeSum = it.value();
        *set << overtimeSum; // 将加班时长添加到 QBarSet
        categories << month; // 将月份添加到类别列表
    }

    series->append(set); // 将 QBarSet 添加到序列中

    // 创建图表
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("员工每月加班总时长");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // 设置X轴为月份
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 设置Y轴
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("加班总时长");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 创建一个视图来显示图表
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 设置图表视图的几何形状
    chartView->setGeometry(0, 80, 700, 600);
    chartView->show(); // 显示图表视图
}
