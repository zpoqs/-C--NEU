#include "Adm_user_manage.h"
#include "ui_adm_user_manage.h"
#include"io_base.h"
#include<QMessageBox>
#include<FindUser.h>
#include"inquiry_base_information.h"
#include"sort_base_information.h"
#include"inquiry_base_information.h"
QString id_adm;

Adm_user_manage::Adm_user_manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Adm_user_manage)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);
    DisplayEmployeeData(ui->tableWidget);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this,  &Adm_user_manage::ShowUserInfo);
    connect(ui->qurry_1, &QLineEdit::textChanged, this, &Adm_user_manage::ShowUserInfo);
    connect(ui->qurry_2, &QLineEdit::textChanged, this, &Adm_user_manage::ShowUserInfo);
}

Adm_user_manage::~Adm_user_manage()
{
    delete ui;
}
void Set_Adm_Id(const QString& id)
{
    id_adm = id;
}
void UpdateInfo(const QVector<Employee>& employees,QTableWidget *employeeTable)
{
    for (int i = 0; i < employees.size(); ++i)
    {
        const Employee& employee = employees[i];
        // 在表格中显示员工信息
        employeeTable->setItem(i, 0, new QTableWidgetItem(employee.id));
        employeeTable->setItem(i, 1, new QTableWidgetItem(employee.name));
        employeeTable->setItem(i, 2, new QTableWidgetItem(employee.sex));
        employeeTable->setItem(i, 3, new QTableWidgetItem(employee.Dept));
        if(employee.Position==1)
        {
            employeeTable->setItem(i, 4, new QTableWidgetItem("普通员工"));
        }
        else
        {
            employeeTable->setItem(i, 4, new QTableWidgetItem("主管"));
        }
        employeeTable->setItem(i, 5, new QTableWidgetItem(employee.Address));
        employeeTable->setItem(i, 6, new QTableWidgetItem(employee.Date_birth));
        employeeTable->setItem(i, 7, new QTableWidgetItem(employee.Phone));
        employeeTable->setItem(i, 8, new QTableWidgetItem(employee.Email));
        employeeTable->setItem(i, 9, new QTableWidgetItem(employee.Password));
        if(employee.Status==0)
        {
            employeeTable->setItem(i, 10, new QTableWidgetItem("不存在"));
            for(int col= 0;col < 2;col++)
            {
                QTableWidgetItem *itemToColor = employeeTable->item(i, col);
                if (itemToColor)
                {
                    itemToColor->setBackground(Qt::red);
                }
            }

        }
        else
        {
            employeeTable->setItem(i, 10, new QTableWidgetItem("存在"));
        }
    }
    // 调整表格大小
    employeeTable->resizeColumnsToContents();
}
void Adm_user_manage::DisplayEmployeeData(QTableWidget *employeeTable)//直接在最初展示所有信息
{
    const QVector<Employee>& employees = ReadEmployee();
    employeeTable->setRowCount(employees.size());
    if (employees.isEmpty())
    {
        return;
    }
    UpdateInfo(employees,employeeTable);

}

void Adm_user_manage::on_btn_back_admin_clicked()//返回
{
    emit Show_Admin_Widget();
    this->close();
}

void Adm_user_manage::on_btn_add_clicked()//添加按钮
{
    AddEmployeeToFile(ui->tableWidget);

}
void AddEmployeeToFile(QTableWidget* employeeTable)//添加的函数
{
    int row = employeeTable->rowCount();// 获取表格当前的行数
    employeeTable->insertRow(row);
    for (int col = 0; col < employeeTable->columnCount(); col++) //设置列
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        //item->setFlags(item->flags() | Qt::ItemIsEditable); // 允许编辑
        employeeTable->setItem(row, col, item);
    }
    employeeTable->scrollToBottom();//滚动到底部
}

void Adm_user_manage::on_btn_save_clicked()//保存按钮
{
    int result = WriteEmployeeFromUiToFile(ui->tableWidget);
    if(result == 1)
    {
        QMessageBox::information(nullptr, "提示","信息已成功保存");
    }

    //保存之后要添加员工的工资信息
    QVector<Salary> sa_new_user = Per_Sal_New();//员工信息文件
    AddNewPerSalary(sa_new_user);
}

int WriteEmployeeFromUiToFile(QTableWidget* employeeTable)//将展示的信息写回文件
{
   QFile file("D:/5942c++/keshecpp/员工信息表.csv");
   if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
   {
       qDebug() << "文件打开失败\n";
       return 0;
   }
   QTextStream out(&file);
   QString tr = "工号,姓名,性别,部门,职位(1员工2主管),住址,出生日期,手机号,邮箱,密码,任职状态(1在0否)\n";
   out<<tr;

   int rowCount = employeeTable->rowCount();
   int columnCount = employeeTable->columnCount();

   for (int i = 0; i < rowCount; i++) // 遍历表格中的所有行和列
   {
       QStringList rowData;
       for (int j = 0; j < columnCount; j++)
       {
           QTableWidgetItem *item = employeeTable->item(i, j);
           if (item)
           {
               if(item->text()=="主管")
               {
                   out<<"2";
               }
               else if(item->text() == "普通员工")
               {
                   out<<"1";
               }
               else if(item->text() =="存在")
               {
                   out<<"1";
               }
               else if(item->text()=="不存在")
               {
                   out<<"0";
               }
               else
               {
                   out << item->text();
               }
           }
           else
           {
               out << " "; // 如果单元格为空，写入空字符串
           }

           if (j < columnCount - 1)
           {
               out << ","; // 在数据项之间添加逗号分隔符
           }
       }
       out << "\n"; // 每一行数据结束时添加换行符
   }
   file.close();
   return 1;
}

void Adm_user_manage::on_btn_delete_clicked()//删除员工
{
   int row = ui->tableWidget->currentRow();
   qDebug()<<row;
   if (row <= 0)
   {
       QMessageBox::information(this, "提示", "没有选中要删除的员工,请选中一行后执行删除操作");
       return;
   }
   Employee user = FindUserByidInEmp(id_adm);
   if(ui->tableWidget->item(row,3)->text()=="财务部"&&user.Position!=2)
   {
       QMessageBox::information(nullptr, "警告","您没有权限删除该部门员工");
       return;
   }
   if(ui->tableWidget->item(row,3)->text()=="财务部" && ui->tableWidget->item(row,4)->text()=="主管")
   {
       QMessageBox::information(nullptr, "警告","您没有权限删除该部门员工");
       return;
   }
   if(ui->tableWidget->item(row,10)->text()=="不存在")
   {
       QMessageBox::information(nullptr, "警告","改员工已不存在，无法再次删除");
       return;
   }
   QMessageBox msgBox;
   msgBox.setText("您确认删除此员工吗？");
   msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
   msgBox.setDefaultButton(QMessageBox::Cancel);
   int ret = msgBox.exec();
   if (ret == QMessageBox::Ok)
   {
       for(int col= 0;col < 2;col++)
       {
           QTableWidgetItem *itemToColor = ui->tableWidget->item(row, col);
           if (itemToColor)
           {
               itemToColor->setBackground(Qt::red);
           }
       }
       ui->tableWidget->setItem(row, 10, new QTableWidgetItem("不存在"));
       int result = WriteEmployeeFromUiToFile(ui->tableWidget);
       if(result == 1)
       {
           QMessageBox::information(nullptr, "提示","该员工已删除");
       }
   }
   else
   {
       return;
   }
}

void Adm_user_manage::on_btn_quit_clicked()
{
    qApp->quit();
}

void Adm_user_manage::on_comboBox_currentIndexChanged(int index)//排序时操作
{
    QVector<Employee> em = ReadEmployee();
    QVector<Employee> employ;
    switch(index)
    {
    case 0:
        break;
    case 1:
        employ = sort_name(em);
        UpdateInfo(employ,ui->tableWidget);
        break;
    case 2:
        employ = sort_id(em);
        UpdateInfo(employ,ui->tableWidget);
        break;
    case 3:
        employ = sort_time(em);
        UpdateInfo(employ,ui->tableWidget);
        break;
    default:
        break;
    }
}

void Adm_user_manage::ShowUserInfo()//查询时操作
{
    QString s1 = ui->qurry_1->text();
    QString s2 = ui->qurry_2->text();
    int index = ui->comboBox_2->currentIndex();
    switch(index)
    {
    case 0:
        break;
    case 1:
        if(ui->qurry_1->text().isEmpty())//姓名
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        else
        {
            QVector<Employee> per = inq_name(ui->qurry_1->text());
            ui->tableWidget->clear();
            ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
            UpdateInfo(per,ui->tableWidget);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 2:
        if(ui->qurry_1->text().isEmpty())//工号
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        else
        {
            QVector<Employee> per = inq_id(ui->qurry_1->text());
            ui->tableWidget->clear();
            ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
            UpdateInfo(per,ui->tableWidget);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 3:
        if(ui->qurry_1->text().isEmpty())//部门
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        else
        {
            QVector<Employee> per = inq_depart(ui->qurry_1->text());
            ui->tableWidget->clear();
            ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
            UpdateInfo(per,ui->tableWidget);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 4:
        if(ui->qurry_1->text().isEmpty())//职位
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        else
        {
            if(ui->qurry_1->text()=="主管")
            {
                 QVector<Employee> per = inq_postition(2);
                 ui->tableWidget->clear();
                 ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
                 UpdateInfo(per,ui->tableWidget);
                 ui->comboBox_2->setCurrentIndex(0);
            }
            else if(ui->qurry_1->text()=="普通员工")
            {
                 QVector<Employee> per = inq_postition(1);
                 ui->tableWidget->clear();
                 ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
                 UpdateInfo(per,ui->tableWidget);
                 ui->comboBox_2->setCurrentIndex(0);
            }
            else
            {
                 QVector<Employee> per = inq_postition(0);
                 ui->tableWidget->clear();
                 ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
                 UpdateInfo(per,ui->tableWidget);
                 ui->comboBox_2->setCurrentIndex(0);
            }
        }
        break;
    case 5:
        if(ui->qurry_1->text().isEmpty())//姓名模糊
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        else
        {
            QVector<Employee> per = inq_iname(ui->qurry_1->text());
            ui->tableWidget->clear();
            ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
            UpdateInfo(per,ui->tableWidget);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 6:
        if(ui->qurry_1->text().isEmpty())//工号模糊
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        else
        {
            QVector<Employee> per = inq_iid(ui->qurry_1->text());
            ui->tableWidget->clear();
            ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
            UpdateInfo(per,ui->tableWidget);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 7://职位加部门
        if(ui->qurry_1->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        if(ui->qurry_2->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_2->setFocus();
            return ;
        }
        if(ui->qurry_1->text()=="主管")
        {
             QVector<Employee> per = inq_position_dept(2,ui->qurry_2->text());
             ui->tableWidget->clear();
             ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
             UpdateInfo(per,ui->tableWidget);
             ui->comboBox_2->setCurrentIndex(0);
        }
        else if(ui->qurry_1->text()=="普通员工")
        {
             QVector<Employee> per = inq_position_dept(1,ui->qurry_2->text());
             ui->tableWidget->clear();
             ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
             UpdateInfo(per,ui->tableWidget);
             ui->comboBox_2->setCurrentIndex(0);
        }
        else//如果输入的不是普通员工或者主管，就只查部门
        {
             QVector<Employee> per = inq_depart(ui->qurry_2->text());
             ui->tableWidget->clear();
             ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
             UpdateInfo(per,ui->tableWidget);
             ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 8://姓名加职位
        if(ui->qurry_1->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        if(ui->qurry_2->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_2->setFocus();
            return ;
        }
        if(ui->qurry_2->text()=="主管")
        {
             QVector<Employee> per = inq_name_position(ui->qurry_1->text(),2);
             ui->tableWidget->clear();
             ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
             UpdateInfo(per,ui->tableWidget);
             ui->comboBox_2->setCurrentIndex(0);
        }
        else if(ui->qurry_2->text()=="普通员工")
        {
             QVector<Employee> per = inq_name_position(ui->qurry_1->text(),1);
             ui->tableWidget->clear();
             ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
             UpdateInfo(per,ui->tableWidget);
             ui->comboBox_2->setCurrentIndex(0);
        }
        else//如果输入的不是普通员工或者主管，就只查姓名
        {
             QVector<Employee> per = inq_name(ui->qurry_1->text());
             ui->tableWidget->clear();
             ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
             UpdateInfo(per,ui->tableWidget);
             ui->comboBox_2->setCurrentIndex(0);
        }

        break;
    case 9://姓名加部门
        if(ui->qurry_1->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        else if(ui->qurry_2->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_2->setFocus();
            return ;
        }
        else
        {
            QVector<Employee> per = inq_name_dept(ui->qurry_1->text(),ui->qurry_2->text());
            ui->tableWidget->clear();
            ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
            UpdateInfo(per,ui->tableWidget);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 10://手机号加邮箱模糊
        if(ui->qurry_1->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        else if(ui->qurry_2->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_2->setFocus();
            return ;
        }
        else
        {
            QVector<Employee> per = inq_phone_plus_email(ui->qurry_1->text(),ui->qurry_2->text());
            ui->tableWidget->clear();
            ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
            UpdateInfo(per,ui->tableWidget);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    case 11://姓名加地址模糊
        if(ui->qurry_1->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            return ;
        }
        else if(ui->qurry_2->text().isEmpty())
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_2->setFocus();
            return ;
        }
        else
        {
            QVector<Employee> per = inq_name_plus_address(ui->qurry_1->text(),ui->qurry_2->text());
            ui->tableWidget->clear();
            ui->tableWidget->setHorizontalHeaderLabels({"工号", "姓名", "性别","部门", "职位", "住址","出生日期","手机号","邮箱","密码","任职状态"});
            UpdateInfo(per,ui->tableWidget);
            ui->comboBox_2->setCurrentIndex(0);
        }
        break;
    default:
        break;
    }
}


void Adm_user_manage::on_btn_add_2_clicked()//批量添加
{
    if(ui->path_from->text().isEmpty())
    {
        QMessageBox::information(nullptr, "提示","请输入文件有效路径信息");
        ui->path_from->setFocus();
        return ;
    }
    QString path_from = ui->path_from->text().trimmed();
    if (!QFile::exists(path_from)) //判断文件存不存在
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的文件的路径出现错误，请重新输入"),QMessageBox::Yes);
        ui->path_from->clear();
        qDebug() << "文件不存在";
        return;
    }
    bool result = AddInfoToFile(path_from,"D:/5942c++/keshecpp/员工信息表.csv");
    if(result)
    {
        QVector<Salary> sa_NewUser = Per_Sal_New();
        AddNewPerSalary(sa_NewUser);
    }
    DisplayEmployeeData(ui->tableWidget);
}
QTableWidget* Adm_user_manage::GetTable()
{
    return ui->tableWidget;
}
