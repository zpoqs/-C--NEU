#include <QFile>
#include <QTextStream>
#include <utility> // 包含 std::pair
#include <QString>
#include <QDebug>
#include"io_base.h"
#include<fstream>
#include<istream>
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
#include"satatis.h"
// 男女数量
std::pair<int, int> calculateGenderRatio(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
        return {0, 0}; // 返回默认计数（0男，0女）
    }

    QTextStream in(&file);
    int maleCount = 0;
    int femaleCount = 0;

    // 第一行是标题行，跳过
    QString line = in.readLine();

    while (!in.atEnd()) {
        line = in.readLine();
        if (!line.isEmpty()) {
            QStringList fields = line.split(","); // 字段由逗号分隔
            if (fields.size() > 2) { // 确保有足够的字段
                QString gender = fields[2].trimmed(); // 提取第三列并去除首尾空格
                if (gender == "男") {
                    maleCount++;
                } else if (gender == "女") {
                    femaleCount++;
                }
            }
        }
    }

    file.close();

    // 返回男性和女性的数量
    return {maleCount, femaleCount};
}

// 部门人数
QMap<QString, int> countDepartmentMembers(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
        return QMap<QString, int>(); // 返回一个空的QMap
    }

    QTextStream in(&file);
    QMap<QString, int> departmentCounts;
    // 初始化部门计数为0
    departmentCounts["财务部"] = 0;
    departmentCounts["技术部"] = 0;
    departmentCounts["销售部"] = 0;
    departmentCounts["人力资源部"] = 0;
    departmentCounts["市场部"] = 0;

    // 第一行是标题行，跳过
    QString line = in.readLine();

    while (!in.atEnd()) {
        line = in.readLine();
        if (!line.isEmpty()) {
            QStringList fields = line.split(","); // 字段由逗号分隔
            if (fields.size() > 3) { // 确保有足够的字段来获取部门信息
                QString department = fields[3].trimmed(); // 部门信息是第四列
                // 更新部门人数
                departmentCounts[department]++;
            }
        }
    }

    file.close();

    // 返回各部门的人数
    return departmentCounts;
}

// 实发工资（年）
QVector<Salary> FindSalary_user(QString id);//找到一个人一年的全部工资

// 实发工资（月）
std::unordered_map<std::string, double> getLastMonthSalaryForEachEmployee(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return {};
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    // 如果文件行数小于20，则无法计算
    if (lines.size() < 20) {
        std::cerr << "File does not contain enough lines." << std::endl;
        return {};
    }

    // 仅处理最后20行
    lines.resize(20);

    std::unordered_map<std::string, double> lastMonthSalaries;
    for (const auto& line : lines) {
        std::istringstream iss(line);
        std::string id, salaryStr;
        double salary;

        // 读取ID（第一列）
        std::getline(iss, id, ',');

        // 跳过其他列直到第十三列（实发工资）
        for (int i = 0; i < 12; ++i) {
            if (!(iss.peek() == ',' || iss.eof())) {
                std::getline(iss, id, ','); // 跳过其他字段
            }
        }

        // 读取实发工资（假设在第十三列）
        std::getline(iss, salaryStr);
        salary = std::stod(salaryStr);

        // 假设ID是有效的，更新或插入最后一个月的工资
        lastMonthSalaries[id] = salary;
    }

    return lastMonthSalaries;
}

// 奖励
// 定义奖励区间的统计map
std::map<std::string, int> countRewardsInRange(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return {};
    }

    // 跳过标题行
    std::string line;
    std::getline(file, line);

    // 奖励区间的边界
    int ranges[] = {500, 1000, 1500, 2000};
    std::map<std::string, int> rewardCounts;
    // 初始化map，将每个区间作为key，初始值为0
    for (int i = 0; i < 3; ++i) {
        std::ostringstream oss;
        oss << ranges[i] << "-" << ranges[i + 1];
        rewardCounts[oss.str()] = 0;
    }

    // 读取数据，每20行统计一次
    int linesRead = 0;
    while (std::getline(file, line)) {
        // 读取第八列（索引为7，因为从0开始计数）
        std::istringstream iss(line);
        std::string value;
        for (int i = 0; i < 7; ++i) {
            std::getline(iss, value, ','); // 跳过前七列
        }
        std::getline(iss, value, ','); // 读取第八列

        // 转换为整数并检查是否在有效范围内
        int reward;
        try {
            reward = std::stoi(value);
            if (reward >= 500 && reward < 2000) {
                // 确定奖励所在的区间
                for (int i = 0; i < 3; ++i) {
                    if (reward >= ranges[i] && reward < ranges[i + 1]) {
                        // 更新对应区间的计数
                        rewardCounts[std::to_string(ranges[i]) + "-" + std::to_string(ranges[i + 1])]++;
                        break;
                    }
                }
            }
        } catch (const std::invalid_argument& e) {
            // 如果转换失败，可以记录错误或跳过此行
            std::cerr << "Invalid reward value: " << value << std::endl;
        } catch (const std::out_of_range& e) {
            // 如果值超出int范围，可以记录错误或跳过此行
            std::cerr << "Reward value out of range: " << value << std::endl;
        }

        // 每20行统计一次，重置linesRead
        if (++linesRead % 20 == 0) {
            // 清除linesRead，以便下一个月重新开始计数
            linesRead = 0;
        }
    }

    // 处理最后不足20行的月份（如果有的话）
    return rewardCounts;
}

// 各部门迟到早退人数
// 假设的部门枚举，用于映射部门名称
enum class Department {
    HR,
    Finance,
    Tech,
    Sales,
    Marketing
};

// 函数声明，用于将部门名称映射到枚举
Department getDepartmentFromName(const std::string& name);



// 考勤（个人）
    QVector<Attendance> FindAttend_user(QString id);//找到一个人一年的所有考勤记录

// 个人每月加班时间
