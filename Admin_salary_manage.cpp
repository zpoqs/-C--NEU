#include "Admin_salary_manage.h"
#include "ui_admin_salary_manage.h"
#include"io_base.h"
#include"FindUser.h"
#include<QDateTime>
#include<QMessageBox>
#include"sort_salary.h"
#include"inquiry_base_salary.h"
#include"check.h"
Admin_salary_manage::Admin_salary_manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin_salary_manage)
{
    ui->setupUi(this);
    DisplaySalaryPreData(ui->table_mon_pre);
    DisplaySalaryNowData(ui->table_mon_now);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Admin_salary_manage::ShowSalaryInfo);
    connect(ui->qurry_1, &QLineEdit::textChanged, this, &Admin_salary_manage::ShowSalaryInfo);
    connect(ui->qurry_2, &QLineEdit::textChanged, this, &Admin_salary_manage::ShowSalaryInfo);
    connect(ui->qurry_3, &QLineEdit::textChanged, this, &Admin_salary_manage::ShowSalaryInfo);
    connect(ui->qurry_4, &QLineEdit::textChanged, this, &Admin_salary_manage::ShowSalaryInfo);



//    QDateTime currentDateTime = QDateTime::currentDateTime();
//    int year = currentDateTime.date().year();
//    int month = currentDateTime.date().month();
//    int day = currentDateTime.date().day();
//    qDebug()<<year;

}

Admin_salary_manage::~Admin_salary_manage()
{
    delete ui;
}
QTableWidget* Admin_salary_manage::GetNowTable()
{
    return ui->table_mon_now;
}


void UpdateSalaryInfo(QVector<Salary> salarys,QTableWidget *salaryTable)
{
    for (int i = 0; i < salarys.size();i++)
    {
        Salary& salary = salarys[i];
        Employee per = FindUserByidInEmp(salary.id);
        qDebug()<<per.Status;
        // 在表格中显示员工信息
//        while (employee.Status == 0 && per< employees.size() - 1)
//        {
//            per++; // 移动到下一个员工
//            if (per < employees.size())
//            {
//                employee = employees[per]; // 更新employee对象
//                salary = salarys[per];
//            }
//        }
        //salaryTable->setRowCount(i + 1); // 增加表格行数
        salaryTable->setItem(i, 0, new QTableWidgetItem(per.id));
        salaryTable->setItem(i, 1, new QTableWidgetItem(per.name));
        for(int col= 0;col < 2;col++)
        {
            QTableWidgetItem *itemToColor = salaryTable->item(i, col);
            if (itemToColor)
            {
                if(per.Status == 0)
                {
                    itemToColor->setBackground(Qt::red);
                }
            }
        }
        salaryTable->setItem(i, 2, new QTableWidgetItem(per.Dept));
        if(per.Position==1)
        {
            salaryTable->setItem(i, 3, new QTableWidgetItem("普通员工"));
        }
        else
        {
            salaryTable->setItem(i, 3, new QTableWidgetItem("主管"));
        }
        salaryTable->setItem(i, 4, new QTableWidgetItem(salary.time.year));
        salaryTable->setItem(i, 5, new QTableWidgetItem(salary.time.mon));
        salaryTable->setItem(i, 6, new QTableWidgetItem(QString::number(salary.basic_salary)));
        salaryTable->setItem(i, 7, new QTableWidgetItem(QString::number(salary.salary_position)));
        salaryTable->setItem(i, 8, new QTableWidgetItem(QString::number(salary.salary_Performance)));
        salaryTable->setItem(i, 9, new QTableWidgetItem(QString::number(salary.House)));
        salaryTable->setItem(i, 10, new QTableWidgetItem(QString::number(salary.reward)));
        salaryTable->setItem(i, 11, new QTableWidgetItem(QString::number(salary.pay_salary)));
        salaryTable->setItem(i, 12, new QTableWidgetItem(QString::number(salary.fund)));
        salaryTable->setItem(i, 13, new QTableWidgetItem(QString::number(salary.tax)));
        salaryTable->setItem(i, 14, new QTableWidgetItem(QString::number(salary.attend_redu)));
        salaryTable->setItem(i, 15, new QTableWidgetItem(QString::number(salary.real_salary)));
    }
    // 调整表格大小
    salaryTable->resizeColumnsToContents();
}
void Admin_salary_manage::DisplaySalaryPreData(QTableWidget *salaryTable)//显示上一个月的工资信息
{
    salaryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置整个表为不可编辑
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date(); // 从 QDateTime 中提取 QDate
    QString year = QString::number(currentDate.year());
    QString mon_pre = QString::number(currentDate.month()-1);
    QString mon_now = QString::number(currentDate.month());
    QVector<Salary> salarys;
    if(mon_now =="1")
    {
        salarys = FindSalary_Mon(QString::number(currentDate.year()-1),"12");
    }
    else
    {
        salarys = FindSalary_Mon(year,mon_pre);//找到上一个月的工资
    }
    salaryTable->setRowCount(salarys.size());
    if(salarys.isEmpty())
    {
        return;
    }
    UpdateSalaryInfo(salarys,salaryTable);

}
void Admin_salary_manage::DisplaySalaryNowData(QTableWidget *salaryTable)//显示当前月份的工资信息
{
    //重要，在更新表格时断开与信息改变信号的连接，之后完成后在接上
//    if(isItemChangedConnected)
//    {
//        disconnect(ui->table_mon_now, &QTableWidget::itemChanged, this, &Admin_salary_manage::on_table_mon_now_itemChanged);
//        isItemChangedConnected = false;
//    }
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date(); // 从 QDateTime 中提取 QDate
    QString year = QString::number(currentDate.year());
    QString mon_now = QString::number(currentDate.month());
    QVector<Salary> salarys = FindSalary_Mon(year,mon_now);//找到当前月的工资
    salaryTable->setRowCount(salarys.size());
    if(salarys.isEmpty())
    {
        return;
    }
    for (int i = 0; i < salarys.size();i++)
    {
        Salary& salary = salarys[i];
        Employee per = FindUserByidInEmp(salary.id);
        qDebug()<<per.Status;
        salaryTable->setItem(i, 0, new QTableWidgetItem(per.id));
        salaryTable->setItem(i, 1, new QTableWidgetItem(per.name));
        for(int col= 0;col < 2;col++)
        {
            QTableWidgetItem *itemToColor = salaryTable->item(i, col);
            if (itemToColor)
            {
                if(per.Status == 0)
                {
                    itemToColor->setBackground(Qt::red);
                }
            }
        }
        salaryTable->setItem(i, 2, new QTableWidgetItem(per.Dept));
        if(per.Position==1)
        {
            salaryTable->setItem(i, 3, new QTableWidgetItem("普通员工"));
        }
        else
        {
            salaryTable->setItem(i, 3, new QTableWidgetItem("主管"));
        }
        salaryTable->setItem(i, 4, new QTableWidgetItem(salary.time.year));
        salaryTable->setItem(i, 5, new QTableWidgetItem(salary.time.mon));
        salaryTable->setItem(i, 6, new QTableWidgetItem(QString::number(salary.basic_salary)));
        salaryTable->setItem(i, 7, new QTableWidgetItem(QString::number(salary.salary_position)));
        QTableWidgetItem *item = salaryTable->item(i, 6);
        if (item)
        {
            item->setFlags(item->flags() | Qt::ItemIsEditable);
        }
        QTableWidgetItem *item1 = salaryTable->item(i, 7);
        if (item1)
        {
            item1->setFlags(item1->flags() | Qt::ItemIsEditable);
        }
        salaryTable->setItem(i, 8, new QTableWidgetItem(QString::number(salary.salary_Performance)));
        salaryTable->setItem(i, 9, new QTableWidgetItem(QString::number(salary.House)));
        salaryTable->setItem(i, 10, new QTableWidgetItem(QString::number(salary.reward)));
        salaryTable->setItem(i, 11, new QTableWidgetItem(QString::number(salary.pay_salary)));
        salaryTable->setItem(i, 12, new QTableWidgetItem(QString::number(salary.fund)));
        salaryTable->setItem(i, 13, new QTableWidgetItem(QString::number(salary.tax)));
        salaryTable->setItem(i, 14, new QTableWidgetItem(QString::number(salary.attend_redu)));
        salaryTable->setItem(i, 15, new QTableWidgetItem(QString::number(salary.real_salary)));
        for (int col = 0; col < salaryTable->columnCount(); col++)// 设置第六列和第七列为可编辑
        {
            QTableWidgetItem *item = salaryTable->item(i, col);
            if (col == 6 || col == 7)
            {
                if (item)
                {
                    item->setFlags(item->flags() | Qt::ItemIsEditable);//可编辑
                }
            }
            else
            {
                if (item)
                {
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);//不可编辑
                }
            }
        }
    }
    // 调整表格大小
    salaryTable->resizeColumnsToContents();

//    connect(ui->table_mon_now, &QTableWidget::itemChanged, this, &Admin_salary_manage::on_table_mon_now_itemChanged);
//    isItemChangedConnected = true;
}

void Admin_salary_manage::on_btn_back_admin_clicked()
{
    ui->table_mon_now->clear();//就这两行代码，非常重要，debug很长
    ui->table_mon_now->setHorizontalHeaderLabels({"工号", "姓名", "部门", "职位", "年份","月份","基本工资","岗位工资","绩效工资","房改补助","奖励","应发工资","公积金","扣税","考勤扣除","实发工资"});

    emit Show_Admin_Widget();
    this->close();

}


void Admin_salary_manage::on_btn_quit_clicked()
{
    qApp->quit();
}


void Admin_salary_manage::on_table_mon_now_itemChanged(QTableWidgetItem *item)
{
    if (item)
    {
        QString mon,money_basic,id;
        int row = item->row();
        int col = item->column();
        qDebug()<<row<<col;
        QString money_change = item->text();
        double money_new = money_change.toDouble();//改了的工资
        qDebug()<<money_new;

        QTableWidgetItem *item0 = ui->table_mon_now->item(row, 5);
        QTableWidgetItem *item1 = ui->table_mon_now->item(row+1, col);
        QTableWidgetItem *item2 = ui->table_mon_now->item(row, 0);
        if (item0 && item1 && item2)
        {
            mon = item0->text(); //当前月份
            money_basic = item1->text(); //基本工资
            id = item2->text(); //工号
            //qDebug()<<mon<<money_basic<<id;

        }
        else
        {
            //qDebug()<<"wrong";
            return;
        }

        if(col == 6)
        {
            QMessageBox msgBox;
            msgBox.setText("您确认要将整个公司的基本工资调整吗？");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();
            if (ret == QMessageBox::Ok)
            {

                QVector<Salary> salary = New_Salary(mon,money_new);
                int result = WriteSalaryToFile(salary);
                if(result == 1)
                {
                    QMessageBox::information(nullptr, "提示","公司基本工资已修改");
                }
                ui->table_mon_now->blockSignals(true);
                DisplaySalaryNowData(ui->table_mon_now);
                ui->table_mon_now->blockSignals(false);
                return;
            }
            else
            {
                ui->table_mon_now->blockSignals(true);//非常重要，否则一直出现消息框
                ui->table_mon_now->setItem(row, col, new QTableWidgetItem(money_basic));
                ui->table_mon_now->blockSignals(false);
                return;
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("您确认要将该部门改职位的员工的岗位工资修改吗？");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();
            if (ret == QMessageBox::Ok)
            {
                QVector<Salary> salary = New_Salary(id,mon,money_new);
                int result1 = WriteSalaryToFile(salary);
                QVector<Sal_Posi> sal= New_Sal_Posi(id,money_new);
                int result2 = WriteSal_PosiToFile(sal);
                if(result1 == 1&&result2 == 1)
                {
                    QMessageBox::information(nullptr, "提示","该部门该职位员工岗位工资已修改");
                }
                qDebug()<<money_change;
                ui->table_mon_now->blockSignals(true);
                DisplaySalaryNowData(ui->table_mon_now);
                ui->table_mon_now->blockSignals(false);
            }
            else
            {
                ui->table_mon_now->blockSignals(true);//非常重要，否则一直出现消息框
                Employee em = FindUserByidInEmp(id);
                double sal_pre = FindSal_Posi(em.Dept,em.Position);
                ui->table_mon_now->setItem(row, col, new QTableWidgetItem(QString::number(sal_pre)));
                ui->table_mon_now->blockSignals(false);
                return;
            }
        }
        QString newValue = item->text();
        qDebug()<<row;
        qDebug()<<col;
        qDebug()<<newValue;
    }
}
QVector<Sal_Posi> New_Sal_Posi(QString id,double posi_sal)//修改岗位工资表
{
    QVector<Sal_Posi> sal = ReadSal_Posi();
    int size = sal.size();
    Employee em = FindUserByidInEmp(id);
    QString dept = em.Dept;
    int posi = em.Position;
    for(int i = 0;i < size;i++)
    {
        if(sal[i].Dept == dept && sal[i].Position == posi)
        {
            sal[i].salary_position = posi_sal;
        }
    }
    return sal;
}
QVector<Salary> New_Salary(QString mon,double base_sal)//修改基本工资
{
    QVector<Salary> salary = ReadSalary();
    int size = salary.size();
    for(int i = 0;i < size;i++)
    {
        if(salary[i].time.mon == mon)
        {
            salary[i].basic_salary = base_sal;
        }
        salary[i].getReward();
        salary[i].getHouse();
        salary[i].getAttend_redu();
        salary[i].getPay_salary();
        salary[i].getFund();
        salary[i].getSalary_Performance();
        salary[i].getTax();
        salary[i].getReal_salary();//计算实时更新
    }
    return salary;
}
QVector<Salary> New_Salary(QString id,QString mon,double posi_sal)//修改岗位工资在工资表里
{
    QVector<Salary> salary = ReadSalary();
    int size = salary.size();
    Employee em = FindUserByidInEmp(id);
    QString dept = em.Dept;
    int posi = em.Position;
    for(int i = 0;i < size;i++)
    {
        if(salary[i].time.mon == mon)
        {
            Employee per = FindUserByidInEmp(salary[i].id);
            if(per.Dept == dept && per.Position == posi)
            {
                salary[i].salary_position = posi_sal;
            }
        }
        salary[i].getReward();
        salary[i].getHouse();
        salary[i].getAttend_redu();
        salary[i].getPay_salary();
        salary[i].getFund();
        salary[i].getSalary_Performance();
        salary[i].getTax();
        salary[i].getReal_salary();

    }
    return salary;
}


void Admin_salary_manage::on_comboBox_currentIndexChanged(int index)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date(); // 从 QDateTime 中提取 QDate
    QString year = QString::number(currentDate.year());
    QString mon_pre = QString::number(currentDate.month()-1);
    QString mon_now = QString::number(currentDate.month());
    QVector<Salary> salarys;
    if(mon_now =="1")
    {
        salarys = FindSalary_Mon(QString::number(currentDate.year()-1),"12");
    }
    else
    {
        salarys = FindSalary_Mon(year,mon_pre);//找到上一个月的工资
    }
    QVector<Salary> sal;
    switch(index)
    {
    case 0:
        break;
    case 1:
        sal = sort_Position(salarys);
        UpdateSalaryInfo(sal,ui->table_mon_pre);
        break;
    case 2:
        sal = sort_performance(salarys);
        UpdateSalaryInfo(sal,ui->table_mon_pre);
        break;
    case 3:
        sal = sort_house(salarys);
        UpdateSalaryInfo(sal,ui->table_mon_pre);
        break;
    case 4:
        sal = sort_pay(salarys);
        UpdateSalaryInfo(sal,ui->table_mon_pre);
        break;
    case 5:
        sal = sort_real(salarys);
        UpdateSalaryInfo(sal,ui->table_mon_pre);
        break;
    case 6:
        sal = sort_fund(salarys);
        UpdateSalaryInfo(sal,ui->table_mon_pre);
        break;
    case 7:
        sal = sort_tax(salarys);
        UpdateSalaryInfo(sal,ui->table_mon_pre);
        break;
    case 8:
        sal = sort_reward(salarys);
        UpdateSalaryInfo(sal,ui->table_mon_pre);
        break;
    case 9:
        sal = sort_attend(salarys);
        UpdateSalaryInfo(sal,ui->table_mon_pre);
        break;
    default:
        break;

    }
}

void Admin_salary_manage::ShowSalaryInfo()//查询时操作
{
    QString s1 = ui->qurry_1->text();
    QString s2 = ui->qurry_2->text();
    int index = ui->comboBox_2->currentIndex();
    qDebug()<<index;
    switch(index)
    {
    case 0:
        break;
    case 1://工号
        if(ui->qurry_1->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            QVector<Salary> per = inq_id_salary(ui->qurry_1->text(),ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 2://岗位工资
        if(ui->qurry_1->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            if(!Check_Double(ui->qurry_1->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_1->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            double money = ui->qurry_1->text().toDouble();
            QVector<Salary> per = inq_position_salary(money,ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 3://绩效工资
        if(ui->qurry_1->text().isEmpty())//部门
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            if(!Check_Double(ui->qurry_1->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_1->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            double money = ui->qurry_1->text().toDouble();
            QVector<Salary> per = inq_performance_salary(money,ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 4://应发工资
        if(ui->qurry_1->text().isEmpty())//部门
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            if(!Check_Double(ui->qurry_1->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_1->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            double money = ui->qurry_1->text().toDouble();
            QVector<Salary> per = inq_pay_salary(money,ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 5://实发工资
        if(ui->qurry_1->text().isEmpty())//部门
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            if(!Check_Double(ui->qurry_1->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_1->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            double money = ui->qurry_1->text().toDouble();
            QVector<Salary> per = inq_real_salary(money,ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 6://公积金
        if(ui->qurry_1->text().isEmpty())//部门
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            if(!Check_Double(ui->qurry_1->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_1->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            double money = ui->qurry_1->text().toDouble();
            QVector<Salary> per = inq_fund_salary(money,ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 7://房改补助
        if(ui->qurry_1->text().isEmpty())//部门
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            if(!Check_Double(ui->qurry_1->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_1->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            double money = ui->qurry_1->text().toDouble();
            QVector<Salary> per = inq_house_salary(money,ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 8://工号+实发工资
        if(ui->qurry_1->text().isEmpty())//部门
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_2->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_2->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            if(!Check_Double(ui->qurry_2->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_2->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            double money = ui->qurry_2->text().toDouble();
            QVector<Salary> per = inq_id_real_salary(ui->qurry_1->text(),money,ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 9://岗位工资加绩效
        if(ui->qurry_1->text().isEmpty())//部门
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_2->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_2->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            if(!Check_Double(ui->qurry_1->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_1->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            if(!Check_Double(ui->qurry_2->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_2->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            double money1 = ui->qurry_1->text().toDouble();
            double money2 = ui->qurry_2->text().toDouble();
            QVector<Salary> per = inq_Posi_performance_salary(money1,money2,ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 10://应发工资加扣税
        if(ui->qurry_1->text().isEmpty())//部门
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_2->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_2->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else if(ui->qurry_3->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的年份");
            ui->qurry_3->setFocus();
            ui->comboBox_2->setCurrentIndex(0);
            return ;
        }
        else
        {
            if(!Check_Double(ui->qurry_1->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_1->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            if(!Check_Double(ui->qurry_2->text()))
            {
                QMessageBox::warning(this, "警告", "请输入有效的数字");
                ui->qurry_2->clear();
                ui->comboBox_2->setCurrentIndex(0);
                return;
            }
            double money1 = ui->qurry_1->text().toDouble();
            double money2 = ui->qurry_2->text().toDouble();
            QVector<Salary> per = inq_pay_tax_salary(money1,money2,ui->qurry_3->text(),ui->qurry_4->text());
            ChangeInfoShow(ui);
            UpdateSalaryInfo(per,ui->table_mon_pre);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    default:
        break;
    }
}
void ChangeInfoShow(Ui::Admin_salary_manage *ui)
{
    ui->table_mon_pre->clear();
    ui->table_mon_pre->setHorizontalHeaderLabels({"工号", "姓名", "部门", "职位", "年份","月份","基本工资","岗位工资","绩效工资","房改补助","奖励","应发工资","公积金","扣税","考勤扣除","实发工资"});
}

void Admin_salary_manage::on_btn_attend_clicked()//录入考勤信息
{
    if(ui->path_attend->text().isEmpty())
    {
        QMessageBox::information(nullptr, "提示","请输入文件有效路径信息");
        ui->path_attend->setFocus();
        return ;
    }
    QString path_from = ui->path_attend->text().trimmed();
    if (!QFile::exists(path_from)) //判断文件存不存在
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的文件路径出现错误，请重新输入"),QMessageBox::Yes);
        ui->path_attend->clear();
        qDebug() << "文件不存在";
        return;
    }
    bool result = AddInfoToFile(path_from,"D:/5942c++/keshecpp/员工考勤表.csv");
    if(result)
    {
        QVector<Salary> sa_all = ReadSalary();
        for(int i = 0;i < sa_all.size();i++)
        {
            if(sa_all[i].reward == 0&&sa_all[i].attend_redu == 0)
            {
                sa_all[i].getReward();
                sa_all[i].getHouse();
                sa_all[i].getAttend_redu();
                sa_all[i].getPay_salary();
                sa_all[i].getFund();
                sa_all[i].getSalary_Performance();
                sa_all[i].getTax();
                sa_all[i].getReal_salary();
            }
        }
        WriteSalaryToFile(sa_all);
    }
    ui->table_mon_now->blockSignals(true);//非常重要，否则一直出现消息框
    ui->table_mon_now->clear();//就这两行代码，非常重要，debug很长
    ui->table_mon_now->setHorizontalHeaderLabels({"工号", "姓名", "部门", "职位", "年份","月份","基本工资","岗位工资","绩效工资","房改补助","奖励","应发工资","公积金","扣税","考勤扣除","实发工资"});
    DisplaySalaryNowData(ui->table_mon_now);
    ui->table_mon_now->blockSignals(false);
}
