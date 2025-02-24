#ifndef ADM_USER_SATIS_H
#define ADM_USER_SATIS_H

#include <QWidget>

namespace Ui {
class Adm_user_satis;
}

class Adm_user_satis : public QWidget
{
    Q_OBJECT

public:
    explicit Adm_user_satis(QWidget *parent = nullptr);
    ~Adm_user_satis();
    void ShowResult_StaUser();
signals:
    void Show_Admin_Widget();

private slots:
    void on_btn_back_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::Adm_user_satis *ui;
};

#endif // ADM_USER_SATIS_H
