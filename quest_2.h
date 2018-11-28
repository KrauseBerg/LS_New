#ifndef QUEST_2_H
#define QUEST_2_H

#include <QMainWindow>


namespace Ui {
class quest_2;
}

class quest_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit quest_2(QWidget *parent = 0);
    void add_bb(QString &id);
    int perk;
    QString id;
    int time_per;
    int krit[3];
    ~quest_2();

private:
    Ui::quest_2 *ui;
public slots:
    void add_button();
    void delete_button();
    void add_text_1(QString id);
    void show_red();
private slots:
    void on_change_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};

#endif // QUEST_2_H
