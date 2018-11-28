#include "otvet.h"
#include "ui_otvet.h"
#include "mainwindow.h"
#include "rezz.h"

#include <fstream>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QTimer>
#include <QDebug>


using namespace std;

rezz *rz;
QTimer *timer;
bool prov1;


string number_to_string_o(int x){
    if(!x) return "0";
    string s,s2;
    while(x){
        s.push_back(x%10 + '0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}
int num=0;


otvet::otvet(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::otvet){
    ui->setupUi(this);
    rz=new rezz();
    rz->mas=-1;

    key=new QShortcut(this);
    key->setKey(Qt::CTRL+Qt::Key_F10);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
    //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
    // Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)
    otvet::setFixedSize(788,592);

    connect(ui->start,SIGNAL(clicked(bool)),this,SLOT(show_1()));
    connect(ui->Next,SIGNAL(clicked(bool)),this,SLOT(show_1()));

    connect(ui->otvet1,SIGNAL(clicked(bool)),this,SLOT(check_o()));
    connect(ui->otvet2,SIGNAL(clicked(bool)),this,SLOT(check_o()));
    connect(ui->otvet3,SIGNAL(clicked(bool)),this,SLOT(check_o()));
    connect(ui->otvet4,SIGNAL(clicked(bool)),this,SLOT(check_o()));

    connect(key,SIGNAL(activated()),this,SLOT(on_pod_triggered()));

    schet=0; schet2=0; schet3=0;
    prov1=true;
}


otvet::~otvet(){
    delete ui;
}

void otvet::show_1(){
    int jey=0;
    QStringList list;
    QString s_new="";
    int sz=0;
    int cnt_1=1;
    if(sender()->objectName()=="start"){
        timer=new QTimer();
        timer->setInterval(1000);
        connect(timer,SIGNAL(timeout()),this,SLOT(timer_func()));
        if(prov1){
            timer->start();
            prov1=false;
        }
    }
    ui->label_2->setNum(posl);
    mass[0]=false;
    mass[1]=false;
    mass[2]=false;
    mass[3]=false;
    if(schet==schet2 && schet3==0)
        rz->mas++;
    schet=0;
    schet2=0;
    schet3=0;
    QString vopr=QString::fromStdString(number_to_string_o(num+1)+"-ый Вопрос /");
    ui->Vopros->setText(vopr);
    ui->start->close();
    ui->area->close();
    ui->textEdit->setStyleSheet("background-image: url(:/bg_image/images/White);font: 18pt \"Times New Roman\";");
    ui->otvet1->setStyleSheet("background-image: url(:/bg_image/images/White);font: 15pt \"Times New Roman\";");
    ui->otvet2->setStyleSheet("background-image: url(:/bg_image/images/White);font: 15pt \"Times New Roman\";");
    ui->otvet3->setStyleSheet("background-image: url(:/bg_image/images/White);font: 15pt \"Times New Roman\";");
    ui->otvet4->setStyleSheet("background-image: url(:/bg_image/images/White);font: 15pt \"Times New Roman\";");

    ui->otvet1->setDisabled(false); ui->otvet1->hide();
    ui->otvet2->setDisabled(false); ui->otvet2->hide();
    ui->otvet3->setDisabled(false); ui->otvet3->hide();
    ui->otvet4->setDisabled(false); ui->otvet4->hide();

    if(num==posl){
        test_time2=0;
        this->close();
        rz->show();
        rz->show_col(posl,m_path);
        num=0;
        ui->area->show();
        ui->start->show();
        num-=1;

    }

    string path ="./"+m_path.toStdString()+'/'+number_to_string_o(rand_f[num])+".txt";
    num++;

    ui->textEdit->clear();
    ui->otvet1->setText("");
    ui->otvet2->setText("");
    ui->otvet3->setText("");
    ui->otvet4->setText("");

    QFile fileo(path.c_str());
    fileo.open(QIODevice::ReadOnly);
    QString s="";
    int sc=0;
    s=fileo.readLine(256);
    s.chop(2);
    int chr=s.toInt();
    switch (chr) {
    case 4:
        ui->otvet4->show();
    case 3:
        ui->otvet3->show();
    case 2:
        ui->otvet2->show();
    case 1:
        ui->otvet1->show();
    }
    while(!fileo.atEnd()){
        s=fileo.readLine(1000);
        if(jey>0){
            list.clear();
            list<<s;
            s_new="";
            sz=(s.size()-3)/65;
            qDebug() << sz;
            cnt_1=1;
            while(sz!=0){
                //qDebug() << s.size();
                foreach (s, list) {
                    s_new+=s.left(65)+="\n\r";
                }
                s.remove(0,65);
                list.clear();
                list<<s;
                if(cnt_1==sz)
                    break;
                cnt_1+=1;
            }
            s_new+=s;
            s=s_new;
        }
        jey++;
        if(s.endsWith("$\r\n"))
            s.chop(3);
        sc++;
        if(ui->textEdit->toPlainText()=="" && s!=""){
            ui->textEdit->setText(s);
        }
        else if(ui->otvet1->text()==""){
            ui->otvet1->setText(s);
        }
        else if(ui->otvet2->text()==""){
            ui->otvet2->setText(s);
        }
        else if(ui->otvet3->text()==""){
            ui->otvet3->setText(s);
            if(s=="")
                ui->otvet3->setText("Empty");
        }
        else if(ui->otvet4->text()==""){
            ui->otvet4->setText(s);
            if(s=="")
                ui->otvet4->setText("Empty");
        }
        else {
            if(s=="1"){
                mass[0]=true;
                schet++;
            }
            if(s=="2"){
                mass[1]=true;
                schet++;
            }
            if(s=="3"){
                mass[2]=true;
                schet++;
            }
            if(s=="4"){
                mass[3]=true;
                schet++;
            }
        }
        s="";
    }
    fileo.close();
}


void otvet::check_o(){
    if(sender()->objectName()=="otvet1" && mass[0]==true){
        ui->otvet1->setStyleSheet("*{background-image: url(:/bg_image/images/White); background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));font: 15pt \"Times New Roman\";}");
        schet2++;
    }
    if(sender()->objectName()=="otvet1" && mass[0]==false){
        ui->otvet1->setDisabled(true);
        ui->otvet2->setDisabled(true);
        ui->otvet3->setDisabled(true);
        ui->otvet4->setDisabled(true);
        ui->otvet1->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.283582 rgba(255, 189, 189, 255), stop:0.547264 rgba(255, 153, 153, 255), stop:0.791045 rgba(255, 72, 72, 255), stop:1 rgba(220, 0, 0, 255));font: 15pt \"Times New Roman\";}");
        schet3++;
    }
    if(sender()->objectName()=="otvet2" && mass[1]==true){
        ui->otvet2->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));font: 15pt \"Times New Roman\";}");
        schet2++;
    }
    if(sender()->objectName()=="otvet2" && mass[1]==false){
        ui->otvet1->setDisabled(true);
        ui->otvet2->setDisabled(true);
        ui->otvet3->setDisabled(true);
        ui->otvet4->setDisabled(true);
        ui->otvet2->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.283582 rgba(255, 189, 189, 255), stop:0.547264 rgba(255, 153, 153, 255), stop:0.791045 rgba(255, 72, 72, 255), stop:1 rgba(220, 0, 0, 255));font: 15pt \"Times New Roman\";}");
        schet3++;
    }
    if(sender()->objectName()=="otvet3" && mass[2]==true){
        ui->otvet3->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));font: 15pt \"Times New Roman\";}");
        schet2++;
    }
    if(sender()->objectName()=="otvet3" && mass[2]==false){
        ui->otvet1->setDisabled(true);
        ui->otvet2->setDisabled(true);
        ui->otvet3->setDisabled(true);
        ui->otvet4->setDisabled(true);
        ui->otvet3->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.283582 rgba(255, 189, 189, 255), stop:0.547264 rgba(255, 153, 153, 255), stop:0.791045 rgba(255, 72, 72, 255), stop:1 rgba(220, 0, 0, 255));font: 15pt \"Times New Roman\";}");
        schet3++;
    }
    if(sender()->objectName()=="otvet4" && mass[3]==true){
        ui->otvet4->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));font: 15pt \"Times New Roman\";}");
        schet2++;
    }
    if(sender()->objectName()=="otvet4" && mass[3]==false){
        ui->otvet1->setDisabled(true);
        ui->otvet2->setDisabled(true);
        ui->otvet3->setDisabled(true);
        ui->otvet4->setDisabled(true);
        ui->otvet4->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.283582 rgba(255, 189, 189, 255), stop:0.547264 rgba(255, 153, 153, 255), stop:0.791045 rgba(255, 72, 72, 255), stop:1 rgba(220, 0, 0, 255));font: 15pt \"Times New Roman\";}");
        schet3++;
    }
}

void otvet::on_pod_triggered()
{
    ui->otvet1->setDisabled(true);
    ui->otvet2->setDisabled(true);
    ui->otvet3->setDisabled(true);
    ui->otvet4->setDisabled(true);
    if(mass[0]==true){
        ui->otvet1->setStyleSheet("*{background-image: url(:/bg_image/images/White); background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));font: 15pt \"Times New Roman\";}");
        schet2++;
    }
    if(mass[1]==true){
        ui->otvet2->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));font: 15pt \"Times New Roman\";}");
        schet2++;
    }
    if(mass[2]==true){
        ui->otvet3->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));font: 15pt \"Times New Roman\";}");
        schet2++;
    }
    if(mass[3]==true){
        ui->otvet4->setStyleSheet("*{background-image: url(:/bg_image/images/White); background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));font: 15pt \"Times New Roman\";}");
        schet2++;
    }
}

void otvet::take_path(QString path, int kol){
    if(path[0]==' ')
        path.remove(0,1);
    m_path=path;
    posl=kol;
    string path1 ="./"+m_path.toStdString()+"/time.txt";
    QFile time(path1.c_str());
    time.open(QIODevice::ReadOnly);
    test_time=time.read(1).toInt();
    ui->time->setText(QString::number(test_time));
    test_time2=test_time*60;
    time.close();
}

void otvet::timer_func(){
    test_time2--;
    ui->time_2->setNum(test_time2);
    if(test_time2==0){
        this->close();
        rz->show();
        rz->show_col(posl,m_path);
        num=0;
        ui->area->show();
        ui->start->show();
        num-=1;
    }
}

