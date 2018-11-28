#ifndef W_SETTING_H
#define W_SETTING_H

#include <QDialog>

namespace Ui {
class w_setting;
}

class w_setting : public QDialog
{
    Q_OBJECT

public:
    explicit w_setting(QWidget *parent = 0);
    bool bl;
    ~w_setting();

private slots:
    void showQue();
    void pass();
    void takeP();


private:
    Ui::w_setting *ui;
    QString password;
    virtual void closeEvent (QCloseEvent *event);
};

#endif // W_SETTING_H
