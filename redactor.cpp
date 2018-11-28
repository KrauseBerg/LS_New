#include "redactor.h"
#include "mainwindow.h"
#include "ui_redactor.h"
#include "quest.h"
#include <QDebug>
#include <QFile>

#include "quest_2.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <QMessageBox>
#include <QTextStream>

using namespace std;

string number_to_string(int x){
    if(!x) return "0";
    string s,s2;
    while(x){
        s.push_back(x%10 + '0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}

Redactor::Redactor(QWidget *parent) :
    QDialog(parent),
    i_f(1), id2(0), id3(0),
    ui(new Ui::Redactor){
    ui->setupUi(this);
    if(ui->rb_1->isChecked())
        bl_mas[0]=true;
    else bl_mas[0]=false;
    if(ui->rb_2->isChecked())
        bl_mas[1]=true;
    else bl_mas[1]=false;
    if(ui->rb_3->isChecked())
        bl_mas[2]=true;
    else bl_mas[2]=false;
    if(ui->rb_4->isChecked())
        bl_mas[3]=true;
    else bl_mas[3]=false;
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)

    connect(ui->Gotovo,SIGNAL(clicked(bool)),this,SLOT(zapis()));
    connect(ui->apply_2,SIGNAL(clicked(bool)),this,SLOT(show_but()));

    ui->Gotovo->setDisabled(true);
    ui->Otvet1->hide();
    ui->Otvet2->hide();
    ui->Otvet3->hide();
    ui->Otvet4->hide();
    ui->Otvet_1->hide();
    ui->Otvet_2->hide();
    ui->Otvet_3->hide();
    ui->Otvet_4->hide();
    ui->rb_1->hide();
    ui->rb_2->hide();
    ui->rb_3->hide();
    ui->rb_4->hide();
    connect(ui->rb_1,SIGNAL(clicked(bool)),this,SLOT(undis_1()));
    connect(ui->rb_2,SIGNAL(clicked(bool)),this,SLOT(undis_2()));
    connect(ui->rb_3,SIGNAL(clicked(bool)),this,SLOT(undis_3()));
    connect(ui->rb_4,SIGNAL(clicked(bool)),this,SLOT(undis_4()));
    connect(ui->apply,SIGNAL(clicked(bool)),this,SLOT(show_otvet()));


    Redactor::setFixedSize(788,592);
}

Redactor::~Redactor(){
    delete ui;
}

void Redactor::undis_1(){
    if(bl_mas[0]==false){
        bl_mas[0]=true;
        id2++;
    }
    else {
        bl_mas[0]=false;
        id2--;
    }
    if(id2==ui->spinBox_2->text().toInt())
        ui->Gotovo->setDisabled(false);
    else ui->Gotovo->setDisabled(true);
}

void Redactor::undis_2(){
    if(bl_mas[1]==false){
        bl_mas[1]=true;
        id2++;
    }
    else {
        bl_mas[1]=false;
        id2--;
    }
    if(id2==ui->spinBox_2->text().toInt())
        ui->Gotovo->setDisabled(false);
    else ui->Gotovo->setDisabled(true);
}

void Redactor::undis_3(){
    if(bl_mas[2]==false){
        bl_mas[2]=true;
        id2++;
    }
    else {
        bl_mas[2]=false;
        id2--;
    }
    if(id2==ui->spinBox_2->text().toInt())
        ui->Gotovo->setDisabled(false);
    else ui->Gotovo->setDisabled(true);
}

void Redactor::undis_4(){
    if(bl_mas[3]==false){
        bl_mas[3]=true;
        id2++;
    }
    else {
        bl_mas[3]=false;
        id2--;
    }
    if(id2==ui->spinBox_2->text().toInt())
        ui->Gotovo->setDisabled(false);
    else ui->Gotovo->setDisabled(true);
}

void Redactor::zapis(){
    string s ="./"+id.toStdString()+'/'+number_to_string(perk)+".txt";
    QFile file(s.c_str());
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    QString str=ui->spinBox->text();
    stream<<str<<"\r\n";

    str=ui->Vopros_1->text();
    stream<<str<<"$"<<"\r\n";

    str=ui->Otvet_1->text();
    stream<<str<<"$"<<"\r\n";

    str=ui->Otvet_2->text();
    stream<<str<<"$"<<"\r\n";

    str=ui->Otvet_3->text();
    stream<<str<<"$"<<"\r\n";

    str=ui->Otvet_4->text();
    stream<<str<<"$"<<"\r\n";

    i_f++;
    ui->Vopros_1->clear();
    ui->Otvet_1->clear();
    ui->Otvet_2->clear();
    ui->Otvet_3->clear();
    ui->Otvet_4->clear();


    if(ui->rb_1->isChecked()==true){
        stream<<"1$"<<"\r\n";
    }
    if(ui->rb_2->isChecked()==true){
        stream<<"2$"<<"\r\n";
    }
    if(ui->rb_3->isChecked()==true){
        stream<<"3$"<<"\r\n";
    }
    if(ui->rb_4->isChecked()==true){
        stream<<"4$"<<"\r\n";
    }
    file.close();
    this->close();
}

void Redactor::add_text(){

    ui->Vopros_1->clear();
    ui->Otvet_1->clear();
    ui->Otvet_2->clear();
    ui->Otvet_3->clear();
    ui->Otvet_4->clear();

    ui->Gotovo->setDisabled(true);
//    ui->rb_1->setChecked(false);
//    ui->rb_2->setChecked(false);
//    ui->rb_3->setChecked(false);
//    ui->rb_4->setChecked(false);

    ui->label_3->setText(QString::number(perk));

    string ss ="./"+id.toStdString()+'/'+number_to_string(perk)+".txt";
    QFile file1(ss.c_str());
    file1.open(QIODevice::ReadOnly);
    QString s="";
    QString s1="";
    s1=file1.readLine(256);
    s1.chop(2);
    int ch=s1.toInt();
    ui->spinBox->setValue(ch);
    switch (ch) {
    case 4:
        ui->Otvet4->show();
        ui->Otvet_4->show();
        ui->rb_4->show();
    case 3:
        ui->Otvet3->show();
        ui->Otvet_3->show();
        ui->rb_3->show();
        if(ui->spinBox->text().toInt()!=4){
            ui->Otvet4->hide();
            ui->Otvet_4->hide();
            if(ui->rb_4->isHidden()==false)
                ui->rb_4->hide();
        }
    case 2:
        ui->Otvet2->show();
        ui->Otvet_2->show();
        ui->rb_2->show();
        if(ui->spinBox->text().toInt()!=3 && ui->spinBox->text().toInt()!=4){
            ui->Otvet4->hide(); ui->Otvet3->hide();
            ui->Otvet_4->hide(); ui->Otvet_3->hide();
            if(ui->rb_4->isHidden()==false)
                ui->rb_4->hide();
            if(ui->rb_3->isHidden()==false)
                ui->rb_3->hide();}

    case 1:
        ui->Otvet1->show();
        ui->Otvet_1->show();
        ui->rb_1->show();
        if(ui->spinBox->text().toInt()==1){
            ui->Otvet4->hide(); ui->Otvet3->hide(); ui->Otvet2->hide();
            ui->Otvet_4->hide(); ui->Otvet_3->hide(); ui->Otvet_2->hide();
            if(ui->rb_4->isHidden()==false)
                ui->rb_4->hide();
            if(ui->rb_3->isHidden()==false)
                ui->rb_3->hide();
            if(ui->rb_2->isHidden()==false)
                ui->rb_2->hide();}

    }
    while(!file1.atEnd()){
        s=file1.readLine(256);
        //        if(s1!="$"){
        //            s+=s1;
        //        }
        //        else{
        if(s.endsWith("$\r\n"))
            s.chop(3);
        if(ui->Vopros_1->text()==""){
            ui->Vopros_1->setText(s);
        }
        else if(ui->Otvet_1->text()==""){
            ui->Otvet_1->setText(s);
        }
        else if(ui->Otvet_2->text()==""){
            ui->Otvet_2->setText(s);
        }
        else if(ui->Otvet_3->text()==""){
            ui->Otvet_3->setText(s);
        }
        else if(ui->Otvet_4->text()==""){
            ui->Otvet_4->setText(s);
        }
        else{
            if(s=="1"){
                ui->rb_1->setChecked(true);
                bl_mas[0]=true;
                ui->Gotovo->setDisabled(false);
                id3++;
            }
            if(s=="2"){
                ui->rb_2->setChecked(true);
                bl_mas[1]=true;
                ui->Gotovo->setDisabled(false);
                id3++;
            }
            if(s=="3"){
                ui->rb_3->setChecked(true);
                bl_mas[2]=true;
                ui->Gotovo->setDisabled(false);
                id3++;
            }
            if(s=="4"){
                ui->rb_4->setChecked(true);
                bl_mas[3]=true;
                ui->Gotovo->setDisabled(false);
                id3++;
            }
        }
        s="";
    }
    file1.close();
    ui->spinBox_2->setValue(id3);
    id2=id3;
}


void Redactor::closeEvent(QCloseEvent *event){
    ui->rb_1->setChecked(false);
    ui->rb_2->setChecked(false);
    ui->rb_3->setChecked(false);
    ui->rb_4->setChecked(false);
}

void Redactor::initi(QString ide, int per){
    id=ide;
    perk=per;
}

void Redactor::show_otvet(){
    switch (ui->spinBox->text().toInt()) {
    case 4:
        ui->Otvet4->show();
        ui->Otvet_4->show();
    case 3:
        ui->Otvet3->show();
        ui->Otvet_3->show();
        if(ui->spinBox->text().toInt()!=4){
            ui->Otvet4->hide();
            ui->Otvet_4->hide();
            if(ui->rb_4->isHidden()==false){
                ui->rb_4->hide();
                if(ui->rb_4->isChecked())
                    id2--;
                ui->rb_4->setChecked(false);
                bl_mas[3]=false;
            }
        }
    case 2:
        ui->Otvet2->show();
        ui->Otvet_2->show();
        if(ui->spinBox->text().toInt()!=3 && ui->spinBox->text().toInt()!=4){
            ui->Otvet4->hide(); ui->Otvet3->hide();
            ui->Otvet_4->hide(); ui->Otvet_3->hide();
            if(ui->rb_4->isHidden()==false){
                ui->rb_4->hide();
                if(ui->rb_4->isChecked())
                    id2--;
                ui->rb_4->setChecked(false);
                bl_mas[3]=false;
            }
            if(ui->rb_3->isHidden()==false){
                ui->rb_3->hide();
                if(ui->rb_3->isChecked())
                    id2--;
                ui->rb_3->setChecked(false);
                bl_mas[2]=false;
            }
        }

    case 1:
        ui->Otvet1->show();
        ui->Otvet_1->show();
        if(ui->spinBox->text().toInt()==1){
            ui->Otvet4->hide(); ui->Otvet3->hide(); ui->Otvet2->hide();
            ui->Otvet_4->hide(); ui->Otvet_3->hide(); ui->Otvet_2->hide();
            if(ui->rb_4->isHidden()==false){
                ui->rb_4->hide();
                if(ui->rb_4->isChecked())
                    id2--;
                ui->rb_4->setChecked(false);
                bl_mas[3]=false;
            }
            if(ui->rb_3->isHidden()==false){
                ui->rb_3->hide();
                if(ui->rb_3->isChecked())
                    id2--;
                ui->rb_3->setChecked(false);
                bl_mas[2]=false;
            }
            if(ui->rb_2->isHidden()==false){
                ui->rb_2->hide();
                if(ui->rb_2->isChecked())
                    id2--;
                ui->rb_2->setChecked(false);
                bl_mas[1]=false;
            }
        }

    }
}
void Redactor::show_but(){
    switch (ui->spinBox->text().toInt()) {
    case 4:{
        ui->rb_4->show();
        if(ui->rb_4->isChecked())
            bl_mas[3]=true;
    }
    case 3:{
        ui->rb_3->show();
        if(ui->rb_3->isChecked())
            bl_mas[2]=true;
    }
    case 2:{
        ui->rb_2->show();
        if(ui->rb_2->isChecked())
            bl_mas[1]=true;
    }
    case 1:{
        ui->rb_1->show();
        if(ui->rb_1->isChecked())
            bl_mas[0]=true;
    }
    }
    if(ui->spinBox_2->text().toInt()==id2)
        ui->Gotovo->setDisabled(false);
    else ui->Gotovo->setDisabled(true);
}
