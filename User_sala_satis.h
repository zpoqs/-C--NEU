#ifndef USER_SALA_SATIS_H
#define USER_SALA_SATIS_H

#include <QWidget>

namespace Ui {
class User_sala_satis;
}

class User_sala_satis : public QWidget
{
    Q_OBJECT

public:
    explicit User_sala_satis(QWidget *parent = nullptr);
    ~User_sala_satis();

private:
    Ui::User_sala_satis *ui;
};

#endif // USER_SALA_SATIS_H
