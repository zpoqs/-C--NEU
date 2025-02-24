#include "Adm_user_satis.h"
#include "ui_adm_user_satis.h"
#include"satatis.h"
#include"QDebug"
Adm_user_satis::Adm_user_satis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Adm_user_satis)
{
    ui->setupUi(this);
    ShowResult_StaUser();

}
void Adm_user_satis::ShowResult_StaUser()
{
    drawGenderPieChart("D:/5942c++/keshecpp/员工信息表.csv",this);
    QMap<QString, int> dept = countEmployeesByDepartment("D:/5942c++/keshecpp/员工信息表.csv") ;
    drawBarChart(dept, this);
    QVector<int> peo = extractAndSubtractFrom2024();

    createPieAgeChart(peo,this);
    std::unordered_map<int, int> peo_statu = countEmployeeStatuses("D:/5942c++/keshecpp/员工信息表.csv",1);
    createPieChart(peo_statu, this);

}

Adm_user_satis::~Adm_user_satis()
{
    delete ui;
}

void Adm_user_satis::on_btn_back_clicked()//返回
{
    emit Show_Admin_Widget();
    this->close();
}

void Adm_user_satis::on_pushButton_2_clicked()
{
    qApp->quit();
}
