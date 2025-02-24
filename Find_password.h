#ifndef FIND_PASSWORD_H
#define FIND_PASSWORD_H

#include <QWidget>

namespace Ui {
class Find_Password;
}

class Find_Password : public QWidget
{
    Q_OBJECT

public:
    explicit Find_Password(QWidget *parent = nullptr);
    ~Find_Password();

private slots:
    void on_btn_back_log_clicked();

    void on_pushButton_clicked();

    void on_quit_clicked();

private:
    Ui::Find_Password *ui;
signals:
    void Show_login_Widget();
};

#endif // FIND_PASSWORD_H
