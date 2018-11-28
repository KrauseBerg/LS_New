#include "rezz.h"
#include "ui_rezz.h"
#include "otvet.h"
#include <fstream>
#include <QDebug>
#include <QFile>

string number_to_string_n(int x){
    if(!x) return "0";
    string s,s2;
    while(x){
        s.push_back(x%10 + '0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}

rezz::rezz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rezz)
{
    ui->setupUi(this);
    //tv=new otvet();
    rezz::setFixedSize(706,407);
    connect(ui->cl,SIGNAL(clicked(bool)),this,SLOT(close()));
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)
}

rezz::~rezz()
{
    delete ui;
}

void rezz::show_col(int posl, QString path){
    bool prov[3];
    QString s1="";
    QString s="";
    prov[0]=false;
    prov[1]=false;
    prov[2]=false;
    string ph="./"+path.toStdString()+'/'+"krit.txt";
    qDebug() << QString::fromStdString(ph);
    QFile pile1(ph.c_str());
    pile1.open(QIODevice::ReadOnly);
    if(pile1.exists()){
        int ch=0;
       while(!pile1.atEnd()){
            s1=pile1.read(1);
            if(s1!="$"){
                s+=s1;
            }
            else{
                if(prov[0]==false){
                    five=s.toInt();
                    prov[0]=true;
                }
                else if(prov[1]==false){
                    four=s.toInt();
                    prov[1]=true;
                }
                else if(prov[2]==false){
                    three=s.toInt();
                    prov[2]=true;
                }
                s="";
            }
        }
    }
    pile1.close();

    QString cor=QString::number(mas);

    ui->cor->setText(cor);

    if(mas>=five){
        ui->cor->setStyleSheet("color: rgb(0, 255, 0);");
        ui->ozenka->setStyleSheet("color: rgb(0, 255, 0);font: 72pt \"Times New Roman\" ;");
        ui->ozenka->setText("5");

    }

    else if(mas<five && mas>=four){
        ui->cor->setStyleSheet("color: rgb(255, 255, 0);");
        ui->ozenka->setStyleSheet("color: rgb(255, 255, 0);font: 72pt \"Times New Roman\" ;");
        ui->ozenka->setText("4");
    }
    else if(mas<four && mas>=three){
        ui->cor->setStyleSheet("color: rgb(255, 85, 0);");
        ui->ozenka->setStyleSheet("color: rgb(255, 85, 0);font: 72pt \"Times New Roman\" ;");
        ui->ozenka->setText("3");
    }
    else {
        ui->cor->setStyleSheet("color: rgb(255, 0, 0);");
        ui->ozenka->setStyleSheet("color: rgb(255, 0, 0);font: 72pt \"Times New Roman\" ;");
        ui->ozenka->setText("2");
    }
    string str1='/'+number_to_string_n(posl);
    ui->label_3->setText(QString::fromStdString(str1));

    mas=-1;

}



