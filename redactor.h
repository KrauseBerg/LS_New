#ifndef REDACTOR_H
#define REDACTOR_H

#include <QDialog>

namespace Ui {
class Redactor;
}

class Redactor : public QDialog
{
    Q_OBJECT

public:
    explicit Redactor(QWidget *parent = 0);
    ~Redactor();
    QStringList list;
    int schet=1;
    int i_f;
    int id2;
    int id3;
    bool bl_mas[4];
    QString id;
    int perk;
    void initi(QString ide, int per);


private slots:
    void zapis();
    void undis_1();
    void undis_2();
    void undis_3();
    void undis_4();
    void show_otvet();
    void show_but();
public slots:
    void add_text();

private:
    Ui::Redactor *ui;
    virtual void closeEvent (QCloseEvent *event);
};

#endif // REDACTOR_H
