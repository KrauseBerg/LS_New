#include "ui_quest.h"
#include "quest.h"
//#include "w_setting.h"
#include <QDir>
#include <QColor>
#include <QColorDialog>
#include <cstring>
#include <QVBoxLayout>
#include <QDynamicPropertyChangeEvent>
#include <fstream>
#include <QDebug>
#include <QSignalMapper>
#include "quest_2.h"
#include "mainwindow.h"

using namespace std;


quest_2 *que_2;
QWidget *but;

int i=1;
int *mas[200];

quest::quest(QWidget *parent) :
    QDialog(parent), font1(30),
    str_color1("rgb(255, 255, 127)"),font2(45),
    str_color2("rgb(255, 255, 255)"), row(0), column(0),
    str_col1("color: rgb(255, 255, 127); font: 30pt;"),
    str_col2("color: rgb(255, 255, 255); font: 45pt;"),
    name1("Безопасность Жизнедеятельности"),name2("Тест"),
    ui(new Ui::quest)
{
    ui->setupUi(this);

    // ws=new w_setting();
    connect(ui->add,SIGNAL(clicked(bool)),this,SLOT(add_but()));
    connect(ui->del,SIGNAL(clicked(bool)),this,SLOT(delet()));

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)
    quest::setFixedSize(788,592);
    ui->red->hide();
    ui->red_2->hide();
    ui->apply->hide();
    ui->apply_2->hide();
    QFile color_up("color.txt");
    if(color_up.exists()){
        color_up.open(QIODevice::ReadOnly);
        name1=color_up.readLine(512);
        name1.chop(2);
        name2=color_up.readLine(512);
        name2.chop(2);
        str_col1=color_up.readLine(512);
        str_col1.chop(2);
        str_col2=color_up.readLine(512);
        color_up.close();
    }
    ui->name1->setText(name1);
    ui->red->setText(name1);
    ui->name2->setText(name2);
    ui->red_2->setText(name2);
    ui->name1->setStyleSheet(str_col1);
    ui->name2->setStyleSheet(str_col2);
}

quest::~quest()
{
    delete ui->scrollAreaWidgetContents;
    delete ui;
}

bool quest::add_bb(){
    int ch=0;
    fstream kat("katalog.txt");
    if(kat.peek()!=EOF){
        string str="";
        while((ch = kat.get()) != EOF){
            if(char(ch)!='$')
                str=str+char(ch);
            else{
                QString s=QString::fromStdString(str);
                but=new QPushButton(s);
                but->setObjectName(s);
                but->setStyleSheet("background-image: url(:/bg_image/images/White); font: 16pt;");
                but->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
                mas[i]=(int*)but;i++;
                ui->scrollArea->setWidgetResizable(true);
                if(ui->gridLayout->isEmpty()==true){
                    ui->gridLayout->addWidget(but);
                }
                str="";
                connect(but,SIGNAL(clicked(bool)),this,SLOT(show_rd()));
            }
        }
    }
    return true;
}

void quest::add_but(){
    if(ui->inputpapka->text()!=""){
        fstream file("katalog.txt");
        string new_str;
        getline(file,new_str);
        string stroka=ui->inputpapka->text().toStdString();
        stroka+='$';
        int jop=new_str.find(stroka);
        if(jop!=-1 && new_str[jop-1]==' '){
            ui->inputpapka->setText("Тема уже существует!");
        }
        else{
            but=new QPushButton(ui->inputpapka->text());
            but->setObjectName(ui->inputpapka->text());
            but->setStyleSheet("background-image: url(:/bg_image/images/White); font: 16pt;");
            but->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
            mas[i]=(int*)but; i++;
            ui->scrollArea->setWidgetResizable(true);
            ui->gridLayout->addWidget(but);

            QDir().mkpath(ui->inputpapka->text());
            ofstream p("katalog.txt",ios_base::app);
            p<<" "<<ui->inputpapka->text().toStdString().c_str()<<"$";
            p.close();
            ui->inputpapka->clear();
        }
        file.close();
    }
    else{

    }
    connect(but,SIGNAL(clicked(bool)),this,SLOT(show_rd()));


}

void quest::delet(){
    if(ui->deletepapka->text()!=""){
        fstream kat("katalog.txt");
        string text;
        getline(kat,text);
        string str=' '+ui->deletepapka->text().toStdString();
        string str1=str+'$';
        int pos=text.find(str1);
        if ( pos == (int) std::string::npos ){
            ui->deletepapka->setText("Нет такой темы!");
        }
        else{
            text.erase(pos,str1.size());
            kat.close();
            kat.open("katalog.txt",ios::out);
            kat<<text;
            kat.close();
            i=1;
            while(true){
                but=(QPushButton*)mas[i];
                text=but->objectName().toStdString();
                if(text[0]!=' '){
                    str1=' ';
                    str1+=but->objectName().toStdString();
                }
                else str1=but->objectName().toStdString();
                qDebug()<<QString::fromStdString(str);
                qDebug()<< QString::fromStdString(str1);
                if(str1==str){
                    but->hide();
                    QDir().rmpath(ui->deletepapka->text());
                    ui->deletepapka-> clear();
                    i--;
                    break;
                }
                else{
                    i++;
                }
            }
        }
    }
}
void quest::show_rd(){
    que_2=new quest_2();
    QString id;
    id=sender()->objectName();
    if(id[0]==' ')
        id.remove(0,1);
    que_2->show();
    que_2->add_text_1(id);
    que_2->add_bb(id);
}

void quest::closeEvent(QCloseEvent *event){
    MainWindow *mw=new MainWindow();
    mw->zap(ui->name1->text(),ui->name2->text(),str_col1,str_col2);
    mw->show();
    QFile color("color.txt");
    QTextStream color_ss(&color);
    color.open(QIODevice::WriteOnly);
    color_ss<<ui->name1->text()<<"\r\n"<<ui->name2->text()<<"\r\n";
    color_ss<<str_col1<<"\r\n"<<str_col2;
    color.close();
}



void quest::on_color1_clicked(){
    QColorDialog *dialog=new QColorDialog();
    QColor color=dialog->getColor();
    QVariant variant=color;
    str_color1=variant.toString();
    str_col1="color: "+str_color1+"; font: "+QString::number(font2)+"pt;";
    ui->name1->setStyleSheet(str_col1);
}

void quest::on_color2_clicked(){
    QColorDialog *dialog=new QColorDialog();
    QColor color=dialog->getColor();
    QVariant variant=color;
    str_color2=variant.toString();
    str_col2="color: "+str_color2+"; font: "+QString::number(font2)+"pt;";
    ui->name2->setStyleSheet(str_col2);
}

void quest::on_up1_clicked(){
    font1+=2;
    str_col1="font: "+QString::number(font1)+"pt; color: "+str_color1+";";
    ui->name1->setStyleSheet(str_col1);
}

void quest::on_down1_clicked(){
    font1-=2;
    str_col1="color: "+str_color1+"; font: "+QString::number(font1)+"pt;";
    ui->name1->setStyleSheet(str_col1);
}

void quest::on_up2_clicked(){
    font2+=2;
    str_col2="color: "+str_color2+"; font :"+QString::number(font2)+"pt;";
    ui->name2->setStyleSheet(str_col2);
}

void quest::on_down2_clicked(){
    font2-=2;
    str_col2="color: "+str_color2+"; font: "+QString::number(font2)+"pt;";
    ui->name2->setStyleSheet(str_col2);
}


void quest::on_pushButton_clicked(){
    ui->red->show();
    ui->apply->show();
}

void quest::on_pushButton_2_clicked(){
    ui->red_2->show();
    ui->apply_2->show();
}

void quest::on_apply_clicked(){
    ui->name1->setText(ui->red->text());
    ui->red->hide();
    ui->apply->hide();
}

void quest::on_apply_2_clicked(){
    ui->name2->setText(ui->red_2->text());
    ui->red_2->hide();
    ui->apply_2->hide();
}
