#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include"Adm_user_manage.h"
#include"Admin_salary_manage.h"
#include"Adm_sala_satis.h"
#include"Adm_user_satis.h"
namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
signals:
    void back();
private slots:

    void on_btn_user_mag_clicked();

    void on_btn_back_login_clicked();
    void show_Adm_again();

    void on_btn_quit_clicked();

    void on_btn_sal_mag_clicked();

    void on_pushButton_clicked();

    void on_btn_sala_satis_clicked();

    void on_btn_user_sas_clicked();

private:
    Ui::Admin *ui;
    Adm_user_manage adm_user_mag;
    Admin_salary_manage adm_sal_mag;
    Adm_user_satis adm_user_satis;
    Adm_sala_satis adm_sal_satis;

signals:
    void Show_login_Widget();
};

#endif // ADMIN_H
