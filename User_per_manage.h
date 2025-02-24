#ifndef USER_PER_MANAGE_H
#define USER_PER_MANAGE_H

#include <QWidget>

namespace Ui {
class User_per_manage;
}

class User_per_manage : public QWidget
{
    Q_OBJECT

public:
    explicit User_per_manage(QWidget *parent = nullptr);
    ~User_per_manage();
    void Show_info();

signals:
    void Show_User_Widget();

private slots:
    void on_btn_back_clicked();

    void on_btn_save_password_clicked();



    void on_btn_save_phone_clicked();

    void on_btn_quit_clicked();

private:
    Ui::User_per_manage *ui;
};
void SetIdFromUserToMag(QString& id);
#endif // USER_PER_MANAGE_H
