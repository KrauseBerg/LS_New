#include "w_setting.h"
#include "ui_w_setting.h"
#include "redactor.h"
#include "quest.h"

#include <fstream>
#include <qdebug.h>
#include <QCloseEvent>

quest* que;
bool chen=true;

using namespace std;
w_setting::w_setting(QWidget *parent) :
    QDialog(parent),
    bl(false),
    ui(new Ui::w_setting){
    ui->setupUi(this);
    if(chen==true){
        que=new quest();
        chen=false;
    }

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)
    connect(ui->commandLinkButton,SIGNAL(clicked(bool)),this,SLOT(showQue()));
    connect(ui->cp,SIGNAL(clicked(bool)),this,SLOT(pass()));
    w_setting::setFixedSize(224,147);
}

w_setting::~w_setting(){

    delete ui;
}

void w_setting::showQue(){
    QString text=ui->lineEdit_1->text();
    fstream pa("pass.txt");
    string p;
    pa>>p;
    password=QString::fromStdString(p);
    qDebug()<<password;
    pa.close();
    if(text==password){
        que->show();
        if(bl==false){
            bl=que->add_bb();
            bl=true;
        }
        this->close();
        this->ui->lineEdit_1->setText("");

    }
    ui->lineEdit_1->clear();
}

void w_setting::pass(){
    w_setting::setFixedSize(224,350);
    ui->old->clear();
    ui->new_2->clear();

    ui->commandLinkButton->setDisabled(true);
    ui->lineEdit_1->setDisabled(true);

    connect(ui->commandLinkButton_2,SIGNAL(clicked(bool)),this,SLOT(takeP()));

}

void w_setting::takeP(){

    QString old;
    old=ui->old->text();
    QString newp;
    newp=ui->new_2->text();
    if(old==password && newp!=password){
        password=newp;

        ofstream pas("pass.txt",ios::out|ios::trunc);
        string np=newp.toStdString();
        // qDebug()<<newp;
        pas<<np;
        pas.close();
    }
    else{

    }

    ui->commandLinkButton->setDisabled(false);
    ui->lineEdit_1->setDisabled(false);
    w_setting::setFixedSize(224,147);
}


void w_setting::closeEvent(QCloseEvent *event){
    w_setting::setFixedSize(224,147);
    ui->commandLinkButton->setDisabled(false);
    ui->lineEdit_1->setDisabled(false);
    ui->lineEdit_1->clear();
    ui->old->clear();
    ui->new_2->clear();
}
