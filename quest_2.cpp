#include "ui_quest_2.h"
#include "quest_2.h"
#include <quest.h>
#include <fstream>
#include <QDebug>
#include <redactor.h>
#include <QFile>
#include <QTextStream>

using namespace std;

QWidget *butt;
Redactor *rd;
int *mass[200];

string number_to_string_oqu(int x){
    if(!x) return "0";
    string s,s2;
    while(x){
        s.push_back(x%10 + '0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}

quest_2::quest_2(QWidget *parent) :
    QMainWindow(parent),perk(1),
    ui(new Ui::quest_2){
    ui->setupUi(this);
    connect(ui->add,SIGNAL(clicked(bool)),this,SLOT(add_button()));
    connect(ui->del,SIGNAL(clicked(bool)),this,SLOT(delete_button()));
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    quest_2::setFixedSize(788,592);
    ui->spinBox->hide(); ui->spinBox_2->hide();
    ui->pushButton->hide(); ui->pushButton_5->hide();
    ui->spinBox_3->hide(); ui->spinBox_4->hide();
}

quest_2::~quest_2()
{
    delete ui;
}

void quest_2::add_text_1(QString id){
    ui->label->setText(id);
}

void quest_2::add_bb(QString &ide){
    id=ide;
    string str="";
    QString s="";
    QString s1="";
    string ph="./"+id.toStdString()+'/'+"time.txt";
    QFile file(ph.c_str());
    QTextStream stream(&file);
    if(file.exists()){
        file.open(QIODevice::ReadOnly);
        while(!file.atEnd()){
            s1=file.read(1);
            if(s1!="$"){
                s+=s1;
            }
            else{
                ui->time->setText(s);
                s="";
            }
        }
        file.close();
    }
    else{
        file.open(QIODevice::WriteOnly);
        stream<<"5$";
        file.close();
    }
    ph="./"+id.toStdString()+'/'+"krit.txt";
    QFile file1(ph.c_str());
    QTextStream stream1(&file1);
    if(file1.exists()){
        file1.open(QIODevice::ReadOnly);
        while(!file1.atEnd()){
            s1=file1.read(1);
            if(s1!="$"){
                s+=s1;
            }
            else{
                if(ui->label_7->text()==""){
                    ui->label_7->setText(s);
                    s="";
                }
                else if(ui->label_8->text()==""){
                    ui->label_8->setText(s);
                    s="";
                }
                else if(ui->label_10->text()==""){
                    ui->label_10->setText(s);
                    s="";
                }
            }
        }
        file1.close();
    }
    else{
        file1.open(QIODevice::WriteOnly);
        stream1<<"$ $ $";
        file1.close();
    }
    for(int i=perk;i<140;i++){
        string ph="./"+ide.toStdString()+'/'+number_to_string_oqu(i)+".txt";
        QFile file2(ph.c_str());
        if(file2.exists()){
            add_button();
        }
        //file2.close();
    }
}

void quest_2::add_button(){
    butt=new QPushButton(QString::number(perk));
    butt->setObjectName(QString::number(perk));
    butt->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
    butt->setStyleSheet("background-image: url(:/bg_image/images/White);");
    mass[perk]=(int*)butt;
    ui->scrollArea->setWidgetResizable(true);
    ui->verticalLayout->addWidget(butt);
    string ph="./"+id.toStdString()+'/'+number_to_string_oqu(perk)+".txt";
    QFile file3(ph.c_str());
    if(!file3.exists()){
        file3.open(QIODevice::WriteOnly);
        file3.close();
    }
    connect(butt,SIGNAL(clicked(bool)),this,SLOT(show_red()));
    perk++;
}

void quest_2::delete_button(){
    if(perk>1){
        butt=(QPushButton*)mass[perk-1];
        butt->hide();
        string del="./"+id.toStdString()+'/'+number_to_string_oqu(perk-1)+".txt";
        QFile delet(del.c_str());
        delet.remove();
        perk--;
    }
}

void quest_2::show_red(){
    int perk1;
    rd=new Redactor();
    perk1=sender()->objectName().toInt();
    rd->initi(id,perk1);
    rd->add_text();
    rd->show();
}

void quest_2::on_change_clicked(){
    ui->pushButton->show();
    ui->spinBox->show();
}


void quest_2::on_pushButton_clicked(){
    time_per=ui->spinBox->text().toInt();
    ui->time->setText(QString::number(time_per));
    ui->pushButton->hide();
    ui->spinBox->hide();
    string ph="./"+id.toStdString()+'/'+"time.txt";
    QFile pile(ph.c_str());
    pile.open(QIODevice::WriteOnly);
    QTextStream stream1(&pile);
    stream1<<QString::number(time_per)<<"$";
    pile.close();
}

void quest_2::on_pushButton_4_clicked(){
    ui->spinBox_2->show();
    ui->spinBox_3->show();
    ui->spinBox_4->show();
    ui->pushButton_5->show();
    ui->spinBox_2->setValue(ui->label_7->text().toInt());
    ui->spinBox_3->setValue(ui->label_8->text().toInt());
    ui->spinBox_4->setValue(ui->label_10->text().toInt());
}

void quest_2::on_pushButton_5_clicked(){
    krit[0]=ui->spinBox_2->text().toInt();
    ui->label_7->setText(QString::number(krit[0]));
    krit[1]=ui->spinBox_3->text().toInt();
    ui->label_8->setText(QString::number(krit[1]));
    krit[2]=ui->spinBox_4->text().toInt();
    ui->label_10->setText(QString::number(krit[2]));
    ui->spinBox_2->hide();
    ui->spinBox_3->hide();
    ui->spinBox_4->hide();
    ui->pushButton_5->hide();
    string ph="./"+id.toStdString()+'/'+"krit.txt";
    QFile pile1(ph.c_str());
    pile1.open(QIODevice::WriteOnly);
    QTextStream stream2(&pile1);
    stream2<<QString::number(krit[0])<<"$"<<QString::number(krit[1])<<"$"<<QString::number(krit[2])<<"$";
    pile1.close();
}
