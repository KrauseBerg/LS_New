#ifndef OTVET_H
#define OTVET_H

#include <QDialog>
#include <cstring>
#include <QShortcut>

using namespace std;
namespace Ui {
class otvet;
}

class otvet : public QDialog
{
    Q_OBJECT

public:
    explicit otvet(QWidget *parent = 0);
    ~otvet();
    vector <int> rand_f;
    void take_path(QString path,int kol);
    int posl;
    int schet, schet2, schet3;
    bool mass[4];
    int test_time, test_time2;
private slots:
    void check_o();
    void on_pod_triggered();

public slots:
    void show_1();
    void timer_func();

private:
    Ui::otvet *ui;
    string otv;
    QShortcut *key;
    QString m_path;

};

#endif // OTVET_H
