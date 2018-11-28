#ifndef QUEST_H
#define QUEST_H

#include <QDialog>
#include <QString>

namespace Ui {
class quest;
}

class quest : public QDialog
{
    Q_OBJECT

public:
    explicit quest(QWidget *parent = 0);
    QString p_name;
    int font1, font2;
    QString str_color1, str_color2;
    QString str_col1,str_col2;
    QString name1, name2;
    int row, column;
    ~quest();
private slots:
    void add_but();
    void delet();
    void show_rd();
    void on_color1_clicked();

    void on_color2_clicked();

    void on_up1_clicked();

    void on_down1_clicked();

    void on_up2_clicked();

    void on_down2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_apply_clicked();

    void on_apply_2_clicked();

public slots:
    bool add_bb();

private:
    Ui::quest *ui;
    virtual void closeEvent (QCloseEvent *even);
};

#endif // QUEST_H
