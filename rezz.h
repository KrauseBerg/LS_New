#ifndef REZZ_H
#define REZZ_H

#include <QDialog>

namespace Ui {
class rezz;
}

class rezz : public QDialog
{
    Q_OBJECT

public:
    explicit rezz(QWidget *parent = 0);
    ~rezz();
    int mas;
    int five;
    int four;
    int three;
public slots:
    void show_col(int posl, QString path);

private:
    Ui::rezz *ui;
};

#endif // REZZ_H
