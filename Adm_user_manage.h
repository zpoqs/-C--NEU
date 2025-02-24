#ifndef ADM_USER_MANAGE_H
#define ADM_USER_MANAGE_H

#include <QWidget>
#include<QTableWidget>
namespace Ui {
class Adm_user_manage;
}

class Adm_user_manage : public QWidget
{
    Q_OBJECT

public:
    explicit Adm_user_manage(QWidget *parent = nullptr);
    ~Adm_user_manage();
    void DisplayEmployeeData(QTableWidget *employeeTable);//展示信息
    QTableWidget* GetTable();


private:
    Ui::Adm_user_manage *ui;
signals:
    void Show_Admin_Widget();
private slots:

    void on_btn_back_admin_clicked();
    void on_btn_add_clicked();
    void on_btn_save_clicked();
    void on_btn_delete_clicked();
    void on_btn_quit_clicked();
    void on_comboBox_currentIndexChanged(int index);
    //void on_comboBox_2_currentIndexChanged(int index);
    void ShowUserInfo();

    void on_btn_add_2_clicked();
};
int WriteEmployeeFromUiToFile(QTableWidget* employeeTable);//将展示的信息写回文件
void AddEmployeeToFile(QTableWidget* employeeTable);
void Set_Adm_Id(const QString& id);
#endif // ADM_USER_MANAGE_H
