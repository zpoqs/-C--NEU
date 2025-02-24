#include"io_base.h"
#include<QDebug>
#include<QDateTime>
#include"FindUser.h"
#include"check.h"
Employee GetEmployee(QString line)
{
    if(line == "")
    {
        return Employee();
    }
    QStringList parts = line.split(","); //数据以，分割
    if (parts.size() < 11&&parts.size()!=1)
    {
        qDebug()<<parts.size();
        throw std::runtime_error("Invalid employee data format"); // 抛出异常，通知调用者数据格式错误
    }
    int positionValue = parts[4].toInt(); //将字符串转换为整型
    int statusValue = parts[10].toInt();
    Employee Employee(parts[0], parts[1], parts[2], parts[3], positionValue, parts[5],
        parts[6], parts[7], parts[8], parts[9], statusValue);
    return Employee;
}
QVector<Employee> ReadEmployee()
{
    QVector<Employee> Emplpyees;
    QFile file("D:/5942c++/keshecpp/员工信息表.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))// 处理文件打开失败的情况
    {
        qDebug() << "文件打开失败\n";
        return Emplpyees;
    }

    QTextStream in(&file);
//    in.setCodec("UTF-8"); // 设置文件编码格式
//    in.setAutoDetectUnicode(true); // 自动检测编码格式

    QString line;
    if (!in.atEnd())
    {
        in.readLine(); // 读取并丢弃标题行
    }
    while (!in.atEnd())//返回bool
    {
        try//处理异常
        {
            line = in.readLine();//读取一行
            Employee Emplpyee = GetEmployee(line);
            if(Emplpyee.id != "0")
            {
                Emplpyees.push_back(Emplpyee);
            }
        }
        catch(const std::runtime_error &e)
        {
            qDebug() << "Runtime error caught: " << e.what();
            continue;
        }

    }
    file.close();
    return Emplpyees;
}
QString EmployeeToString(Employee& employee)//调用arg方法直接将一个对象转换为字符串
{
    return QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11").arg(employee.id).arg(employee.name)
            .arg(employee.sex).arg(employee.Dept).arg(employee.Position).arg(employee.Address).arg(employee.Date_birth)
            .arg(employee.Phone).arg(employee.Email).arg(employee.Password).arg(employee.Status);
}
int WriteEmployeeToFile(QVector<Employee> user)//将员工信息写回文件
{
    int i = 0;
    QFile file("D:/5942c++/keshecpp/员工信息表.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "文件打开失败\n";
        return 0;
    }
    QTextStream out(&file);
    QString str =  "工号,姓名,性别,部门,职位,住址,出生日期,手机号,邮箱,密码,任职状态(1在0否)\n";
    out <<str;
    int size = user.size();
    while(i < size)
    {
        QString line = EmployeeToString(user[i]);
        out<<line<<"\n";
        i++;
    }
    file.close();
    return 1;
}
bool AddInfoToFile(const QString& path_from, const QString& path_to)//追加文件从另外的文件
{
    QFile sourceFile(path_from);//从什么文件来
    if (!sourceFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "无法打开源文件:" << path_from;
        return false;
    }
    QFile targetFile(path_to);//追加到哪里去
    if (!targetFile.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "无法打开目标文件:" << path_to;
        sourceFile.close();
        return false;
    }
    QTextStream in(&sourceFile);
    QTextStream out(&targetFile);
    in.setCodec("UTF-8"); // 设置文件编码格式
    in.setAutoDetectUnicode(true); // 自动检测编码格式
    if (!in.atEnd())
    {
        in.readLine(); // 读取并丢弃标题行
    }
    while (!in.atEnd())
    {
        QString line = in.readLine();
        out << line << "\n";
    }
    sourceFile.close();
    targetFile.close();
    qDebug() << "内容追加成功" ;
    return true;
}


//void DisplayEmplpyees(const QVector<Emplpyee>& Emplpyees) {
//    for (const Emplpyee& Emplpyee : Emplpyees) {
//        qDebug() << Emplpyee.toString(); // 调用Emplpyee类的toString函数并打印到控制台
//    }
//}

Salary GetSalary(QString line)
{
    if(line == "")
    {
        return Salary();
    }
    QStringList fields = line.split(","); // 字段由逗号分隔
//    int size = fields.size();
//    qDebug()<<size;
    if (fields.size() < 13&&fields.size()!=1)
    {
        throw std::runtime_error("Invalid salary data format"); // 抛出异常，通知调用者数据格式错误
    }
    QString id = fields[0].trimmed();//去掉首尾空格
    QString year = fields[1].trimmed();
    QString mon = fields[2].trimmed();
    double basic_salary = fields[3].toDouble();
    double salary_pos = fields[4].toDouble();
    double salary_perf = fields[5].toDouble();
    double house = fields[6].toDouble();
    double rew = fields[7].toDouble();
    double pay_salary = fields[8].toDouble();//应发工资
    double fund_val = fields[9].toDouble();//公积金
    double tax_val = fields[10].toDouble();
    double attend_red = fields[11].toDouble();
    double real_sal = fields[12].toDouble();

    Salary salary(id, year, mon, basic_salary, salary_pos, salary_perf, house, rew,
                          fund_val, pay_salary, tax_val, attend_red, real_sal);
    return salary;
}
QVector<Salary> ReadSalary()
{
    QVector<Salary> salarys;
    QFile file("D:/5942c++/keshecpp/工资表.csv");//D:/5942c++/keshecpp/工资表.csv

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // 处理文件打开失败的情况
        qDebug() << "文件打开失败\n";
        return salarys;
    }
    QTextStream in(&file);
    QString line;
    if (!in.atEnd())
    {
        in.readLine(); // 读取并丢弃标题行
    }
    while (!in.atEnd())//返回bool
    {
        try//异常处理
        {
            line = in.readLine();//读取一行
            Salary salary = GetSalary(line);
            if(salary.id != "")
            {
                salarys.push_back(salary);
            }

        }
        catch(const std::runtime_error &e)
        {
            qDebug() << "Runtime error caught: " << e.what();
            continue;
        }
    }
    file.close();
    return salarys;
}
int WriteSalaryToFile(QVector<Salary> salary)//将工资信息写入文件
{
    int i = 0;
    QFile file("D:/5942c++/keshecpp/工资表.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "文件打开失败\n";
        return 0;
    }
    QTextStream out(&file);
    QString str =  "工号,年份,月份,基本工资,岗位工资,绩效工资,房改补助,奖励,应发工资,公积金,扣税,考勤扣除,实发工资\n";
    out <<str;
    int size = salary.size();
    while(i < size)
    {
        QString line = SalaryToString(salary[i]);
        out<<line<<"\n";
        i++;
    }
    file.close();
    return 1;
}
void AddSalaryToFile()//每月固定时间添加工资基本信息
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date(); // 从 QDateTime 中提取 QDate
    int day = currentDate.day();
    QString mon_now = QString::number(currentDate.month());
    int result = Check_Mon_Once(mon_now);
    if(day == 12 && result == 0)//设置默认时间向系统添加初始工资信息
    {
        QFile file("D:/5942c++/keshecpp/工资表.csv");
        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            qDebug() << "文件打开失败工资表\n";
            return;
        }
        QTextStream out(&file);
        QVector<Salary> sal_this_mon = Salary_New_Mon();
        for(int i = 0;i < sal_this_mon.size();i++)
        {
            QString line = SalaryToString(sal_this_mon[i]);
            out<<line<<"\n";
        }
        file.close();
    }
}
QString SalaryToString(Salary& salary)//调用arg方法直接将一个salary对象转换为字符串
{
    return QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13").arg(salary.id).arg(salary.time.year)
            .arg(salary.time.mon).arg(salary.basic_salary).arg(salary.salary_position).arg(salary.salary_Performance).arg(salary.House)
            .arg(salary.reward).arg(salary.pay_salary).arg(salary.fund).arg(salary.tax).arg(salary.attend_redu).arg(salary.real_salary);
}
QVector<Salary> Salary_New_Mon()//更新一个月的信息
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date(); // 从 QDateTime 中提取 QDate
    QString year = QString::number(currentDate.year());
    QString mon_pre = QString::number(currentDate.month()-1);
    QString mon_now = QString::number(currentDate.month());
    QVector<Salary> sal_premon;
    if(mon_now == "1")
    {
        sal_premon = FindSalary_Mon(QString::number(currentDate.year()-1),"12");
    }
    else
    {
         sal_premon= FindSalary_Mon(year,mon_pre);
    }
    QVector<Salary> sal_nowmon;
    for(int i = 0;i < sal_premon.size();i++)
    {
        const Salary& sa = sal_premon[i];
        Employee em = FindUserByidInEmp(sa.id);
        if(em.Status == 1)
        {
            Salary sa_now(sa.id,year,mon_now,sa.basic_salary,sa.salary_position);
            sa_now.getReward();
            sa_now.getHouse();
            sa_now.getAttend_redu();
            sa_now.getPay_salary();
            sa_now.getFund();
            sa_now.getSalary_Performance();
            sa_now.getTax();
            sa_now.getReal_salary();

            sal_nowmon.push_back(sa_now);
        }
        else if(em.id == "")
        {
            break;
        }
    }
    return sal_nowmon;
}
void AddNewPerSalary(QVector<Salary> sa_user)//将新员工的工资信息追加到文件里，应该是很多人，如果是批量录入
{
    QFile file("D:/5942c++/keshecpp/工资表.csv");
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "文件打开失败工资表\n";
        return;
    }
    QTextStream out(&file);
    for(int i = 0;i < sa_user.size();i++)
    {
        QString line = SalaryToString(sa_user[i]);
        out<<line<<"\n";
    }
    file.close();
}
QVector<Salary> Per_Sal_New()//为新员工添加工资信息
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date(); // 从 QDateTime 中提取 QDate
    QString year = QString::number(currentDate.year());
    QString mon_pre = QString::number(currentDate.month()-1);
    QString mon_now = QString::number(currentDate.month());
    QVector<Salary> sa_pre_user;
    QVector<Salary> sa_new_user;
    QVector<Employee> user_all = ReadEmployee();//如果有新加的职员且没有工资信息的
    if(mon_now == "1")
    {
        sa_pre_user = FindSalary_Mon(QString::number(currentDate.year()-1),"12");
    }
    else
    {
        sa_pre_user = FindSalary_Mon(year,mon_pre);
    }
    QVector<Salary> sa_now_mon = FindSalary_Mon(year,mon_now);

    for(int i = 0;i < user_all.size();i++)
    {
        if(user_all[i].Status == 1)
        {
            int result = FindSalaryInVector(user_all[i].id,sa_pre_user);
            int result2 = FindSalaryInVector(user_all[i].id,sa_now_mon);
            if(result == 0&&result2 ==0)
            {
                double sal_posi = FindSal_Posi(user_all[i].Dept,user_all[i].Position);
                Salary sa_now(user_all[i].id,year,mon_now,sa_pre_user[0].basic_salary,sal_posi);
                //添加之时自动计算,就目前已有的工资进行计算
                sa_now.getReward();
                sa_now.getHouse();
                sa_now.getAttend_redu();
                sa_now.getPay_salary();
                sa_now.getFund();
                sa_now.getSalary_Performance();
                sa_now.getTax();
                sa_now.getReal_salary();

                sa_new_user.push_back(sa_now);
            }
        }
    }
    return sa_new_user;
}

Attendance GetAttendance(QString line)//考勤信息
{
    Attendance attend;
    //qDebug()<<line;
    QStringList fields = line.split(","); // 字段由逗号分隔
    //qDebug()<<fields.size();
    if (fields.size() < 6&&fields.size()!=1)
    {
        throw std::runtime_error("Invalid attendence data format"); // 抛出异常，通知调用者数据格式错误
    }
    if(fields.size()==6)
    {
        QString id = fields[0];
        int late = fields[1].toInt();
        int exitEarly = fields[2].toInt();
        QString year = fields[3].trimmed();
        QString mon = fields[4];
        int overtime = fields[5].toInt();
        Attendance attendance(id, late, exitEarly,year,mon, overtime);
        attend = attendance;

    }
    return attend;
}
QVector<Attendance> ReadAttendance()
{
    QVector<Attendance> attendances;
    QFile file("D:/5942c++/keshecpp/员工考勤表.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) // 处理文件打开失败的情况
    {
        qDebug() << "文件打开失败\n";
        return attendances;
    }
    QTextStream in(&file);
    QString line;
    if (!in.atEnd())
    {
        in.readLine(); // 读取并丢弃标题行
    }
    while (!in.atEnd())//返回bool
    {
        try //异常处理
        {
            line = in.readLine();//读取一行
            Attendance attendance = GetAttendance(line);
            attendances.push_back(attendance);
        }
        catch(const std::runtime_error &e)
        {
            qDebug() << "Runtime error caught: " << e.what();
            continue;
        }

    }
    file.close();
    return attendances;
}
Sal_Posi GetSal_Posi(QString line)//岗位工资
{
     Sal_Posi sal_posi;
    //qDebug()<<line;
    QStringList fields = line.split(","); // 字段由逗号分隔
    //qDebug()<<fields.size();
    if (fields.size() < 4&&fields.size()!=1)
    {
        throw std::runtime_error("Invalid posi data format"); // 抛出异常，通知调用者数据格式错误
    }
    QString dept = fields[0];
    int position = fields[1].toInt();
    double salary_pos = fields[2].toDouble();
    double dept_co = fields[3].toDouble();
    if(fields.size()==4)
    {
        Sal_Posi sal_posi1(dept,position,salary_pos,dept_co);
        sal_posi = sal_posi1;
    }
    return sal_posi;
}
QVector<Sal_Posi> ReadSal_Posi()
{
    QVector<Sal_Posi> sal_posis;
    QFile file("D:/5942c++/keshecpp/岗位工资表.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) // 处理文件打开失败的情况
    {
        qDebug() << "文件打开失败\n";
        return sal_posis;
    }
    QTextStream in(&file);
    QString line;
    if (!in.atEnd())
    {
        in.readLine(); // 读取并丢弃标题行
    }
    while (!in.atEnd())//返回bool
    {
        try//异常处理
        {
            line = in.readLine();//读取一行
            Sal_Posi sal_posi = GetSal_Posi(line);
            sal_posis.push_back(sal_posi);
        }
        catch(const std::runtime_error &e)
        {
            qDebug() << "Runtime error caught: " << e.what();
            continue;
        }
    }
    file.close();
    return sal_posis;
}
QString Sal_PosiToString(Sal_Posi& sal_Posi)//调用arg方法直接将一个对象转换为字符串
{
    return QString("%1,%2,%3,%4").arg(sal_Posi.Dept).arg(sal_Posi.Position)
            .arg(sal_Posi.salary_position).arg(sal_Posi.department_coefficient);
}
int WriteSal_PosiToFile(QVector<Sal_Posi> user)//将岗位工资信息写回文件
{
    int i = 0;
    QFile file("D:/5942c++/keshecpp/岗位工资表.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "文件打开失败\n";
        return 0;
    }
    QTextStream out(&file);
    QString str =  "部门,职位(1普通员工2主管),岗位工资,部门系数\n";
    out <<str;
    int size = user.size();
    while(i < size)
    {
        QString line = Sal_PosiToString(user[i]);
        out<<line<<"\n";
        i++;
    }
    file.close();
    return 1;
}


//QFile outFile("data_modified.csv");
//   if(outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
//       QTextStream out(&outFile);
//       for (int row = 0; row < tableWidget.rowCount(); row++) {
//           for (int col = 0; col < tableWidget.columnCount(); col++) {
//               if(col == 0 && tableWidget.item(row, col)->text() == "主管") {
//                   out << "2";
//               } else {
//                   out << tableWidget.item(row, col)->text();
//               }
//               if(col < tableWidget.columnCount() - 1) {
//                   out << ",";
//               }
//           }
//           out << "\n";
//       }
//       outFile.close();
