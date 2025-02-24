#include "Admin.h"
#include "ui_admin.h"
#include"io_base.h"
#include"Adm_user_manage.h"
#include<QString>
#include"Filebackup.h"
#include"satatis.h"
Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{

    ui->setupUi(this);
    connect(&adm_user_mag,SIGNAL(Show_Admin_Widget()),this,SLOT(show_Adm_again()));
    connect(&adm_sal_mag,SIGNAL(Show_Admin_Widget()),this,SLOT(show_Adm_again()));
    connect(&adm_user_satis,SIGNAL(Show_Admin_Widget()),this,SLOT(show_Adm_again()));
    connect(&adm_sal_satis,SIGNAL(Show_Admin_Widget()),this,SLOT(show_Adm_again()));
    ui->help->setText("1.员工信息录入可选择批量录入和单个录入。\n"
                      "2.工资信息查询时请输入要查询的年份\n"
                      "3.请在月末之时录入员工考勤信息，\n"
                      "系统将自动帮您计算员工的工资。\n"
                      "4.如果员工已离职，将在显示他\n"
                      "信息时将其标红。\n"
                      "5.本系统仅支持更改基本工资信息和\n"
                      "岗位工资信息，在您确认更改后将自动\n"
                      "为您计算新的工资信息。\n"
                      "6.若您添加修改员工后请点击保存按钮\n"
                      "否则将不会记录您的更改\n"
                      "7.每次在您登录之时，系统将自动进行文件\n"
                      "备份，若您在修改后发现错误，请点击\n"
                      "恢复文件按钮\n"
                      "8.感谢您的使用。");
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_btn_user_mag_clicked()
{
    adm_user_mag.show();
    QTableWidget* table = adm_user_mag.GetTable();
    adm_user_mag.DisplayEmployeeData(table);
    this->hide();
}

void Admin::on_btn_back_login_clicked()
{
    emit Show_login_Widget();
    this->close();
}
void Admin::show_Adm_again()
{
    this->show();
}



void Admin::on_btn_quit_clicked()
{
    qApp->quit();
}

void Admin::on_btn_sal_mag_clicked()
{
    adm_sal_mag.show();
    QTableWidget* table_now = adm_sal_mag.GetNowTable();
    table_now->blockSignals(true);//非常重要，否则一直出现消息框
    adm_sal_mag.DisplaySalaryNowData(table_now);
    table_now->blockSignals(false);

    this->hide();
}

void Admin::on_pushButton_clicked()
{
    RestoreEmployee();
    RestoreSalary();
    RestoreSal_Posi();
    RestoreAttendce();
}

void Admin::on_btn_sala_satis_clicked()
{
    adm_sal_satis.show();
    adm_sal_satis.DisplayResult_Statis();
    this->hide();
}

void Admin::on_btn_user_sas_clicked()
{
    adm_user_satis.show();
    adm_user_satis.ShowResult_StaUser();
    this->hide();
}
