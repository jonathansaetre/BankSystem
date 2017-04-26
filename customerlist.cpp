#include "customerlist.h"
#include "ui_customerlist.h"
#include "customerdetails.h"
#include<QFile>
#include<QFileInfo>
#include <QSqlDatabase>
#include<QSqlQueryModel>
#include<QSqlQuery>

#include <QTextStream>
//#include <QMessageBox>
#include <QDebug>

CustomerList::CustomerList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerList)
{
    ui->setupUi(this);


     /* if(!BankSyst.open())
          ui->Status->setText("Failed to connect to Data Base");
      else
           ui->Status->setText("Connected to Data Base");
      */
    openDB();
      QFileInfo Checkfile("BankingSystem.sqlite");

      if(Checkfile.isFile()){
          if(BankSyst.open()){
              ui->Status->setText("Connected to data base file");
          }else{
               ui->Status->setText("Data base files doesn t exist");
          }
      }

}

CustomerList::~CustomerList()
{
    delete ui;
}

void CustomerList::on_buttonBack_clicked()
{
    this->close();
    emit showPrev();
}


void CustomerList::on_buttonNewCustomer_clicked()
{
    hide();
    CustomerDetails *CusDetai = new CustomerDetails();
    QObject::connect(CusDetai, SIGNAL(showPrev()), SLOT(show()));
    CusDetai->show();
}


void CustomerList::on_loadcust_clicked()
{
//openDB();
    QSqlQueryModel * Model=new QSqlQueryModel();
    if(BankSyst.open()){ ui->Status->setText("Data Base open");}
        QSqlQuery*  qry= new QSqlQuery(BankSyst);
        qry->prepare("SELECT * FROM customer");
        qry->exec();
        Model->setQuery(*qry);
        ui->CustList->setModel(Model);
        closeDB();
        ui->CustList->setModel(Model);
       // qDebug()<<(Model->rowCount());
}
