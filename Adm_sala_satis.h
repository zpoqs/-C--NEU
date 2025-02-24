#ifndef ADM_SALA_SATIS_H
#define ADM_SALA_SATIS_H

#include <QWidget>

namespace Ui {
class Adm_sala_satis;
}

class Adm_sala_satis : public QWidget
{
    Q_OBJECT

public:
    explicit Adm_sala_satis(QWidget *parent = nullptr);
    ~Adm_sala_satis();
    void DisplayResult_Statis();
signals:
    void Show_Admin_Widget();

private slots:
    void on_btn_back_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Adm_sala_satis *ui;
};

#endif // ADM_SALA_SATIS_H
