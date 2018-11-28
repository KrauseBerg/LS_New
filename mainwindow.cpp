#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "w_setting.h"
#include "otvet.h"
#include <fstream>
#include <QFile>
#include <ctime>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>

w_setting *set;
otvet *otv;

QWidget *thems;


string number_to_string_mw(int x){
    if(!x) return "0";
    string s,s2;
    while(x){
        s.push_back(x%10 + '0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), kol(0),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    set=new w_setting();
    otv=new otvet();
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)
    ui->mainToolBar->setMovable(false);
    int i,j;
    int ch=0;i=0;j=0;
    fstream kat("katalog.txt");QString s_new;QStringList list;
    if(kat.peek()!=EOF){
        string str="";
        while((ch = kat.get()) != EOF)
        {
            if(char(ch)!='$')
                str=str+char(ch);

            else{
                QString s=QString::fromStdString(str);
                QString s1=s;
                if(s.size()>45){
                    list.clear();
                    list<<s;
                    s_new="";
                    foreach (s, list) {
                        s_new+=s.left(45)+="\n\r";
                    }
                    s.remove(0,45);
                    s_new+=s;
                    s=s_new;
                }
                thems=new QPushButton(s);
                thems->setObjectName(s1);
                thems->setStyleSheet("background-image: url(:/bg_image/images/White);color: rgb(0, 0, 0);font: 15pt \"Times New Roman\";");
                thems->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
                ui->scrollArea->setWidgetResizable(true);
                ui->gridLayout->addWidget(thems,i,j);
                connect(thems,SIGNAL(clicked()),this,SLOT(showOtvet()));
                str="";
                if(j==0)
                    j++;
                else{
                    i++;
                    j--;
                }
            }
        }
    }
    MainWindow::setFixedSize(942,726);
    connect(ui->setting,SIGNAL(triggered(bool)),this,SLOT(showSetting()));
    QFile col("color.txt");
    col.open(QIODevice::ReadOnly);
    if(col.exists()){
        name_1=col.readLine(512);
        name_1.chop(2);
        ui->name1->setText(name_1);
        name_2=col.readLine(512);
        name_2.chop(2);
        ui->name2->setText(name_2);
        str_col_1=col.readLine(512);
        str_col_1.chop(2);
        ui->name1->setStyleSheet(str_col_1);
        str_col_2=col.readLine(512);
        ui->name2->setStyleSheet(str_col_2);
    }
    col.close();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showSetting(){
    set->show();
    this->close();
}

void MainWindow::showOtvet(){
    fil_f();
    otv->take_path(sender()->objectName(),kol);
    otv->show();
}

void MainWindow::fil_f(){
    kol=0;
    QString path=sender()->objectName();
    if(path[0]==' ')
        path.remove(0,1);

    otv->rand_f.clear();
    for(int i=1;i<140;i++){

        string ph="./"+path.toStdString()+'/'+number_to_string_mw(i)+".txt";
        QFile f(ph.c_str());
        if(f.exists()){
            kol++;
        }
    }
    for(int i=1;i<=kol;i++){
        otv->rand_f.push_back(i);
    }

    srand(time(0));
    random_shuffle(otv->rand_f.begin(),otv->rand_f.end());
}
void MainWindow::zap(QString name1, QString name2, QString str_col1, QString str_col2){
    QStringList list; QString s_new;
    int ch=0;
    fstream kat("katalog.txt");
    if(kat.peek()!=EOF){
        string str="";
        while((ch = kat.get()) != EOF){
            if(char(ch)!='$')
                str=str+char(ch);

            else{
                QString s=QString::fromStdString(str); QString s1=s;
                if(s.size()>45){
                    list.clear();
                    list<<s;
                    s_new="";
                    foreach (s, list) {
                        s_new+=s.left(45)+="\n\r";
                    }
                    s.remove(0,45);
                    s_new+=s;
                    s=s_new;
                }
                thems=new QPushButton(s);
                thems->setObjectName(s1);
                thems->setStyleSheet("background-image: url(:/bg_image/images/White);color: rgb(0, 0, 0);font: 15pt \"Times New Roman\";");
                thems->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
                ui->scrollArea->setWidgetResizable(true);
                str="";
                connect(thems,SIGNAL(clicked()),this,SLOT(showOtvet()));
            }
        }
    }
    ui->name1->setText(name1);
    ui->name1->setStyleSheet(str_col1);
    ui->name2->setText(name2);
    ui->name2->setStyleSheet(str_col2);
}
