#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void zap(QString name1,QString name2, QString str_col1, QString str_col2);
    ~MainWindow();
    int kol;
    QString name_1, name_2, str_col_1,str_col_2;

private slots:
    void showSetting();
    void showOtvet();
public slots:
    void fil_f();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
