#include "contact.h"
#include "ui_contact.h"
#include "mainwindow.h"

Contact::Contact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contact)
{
    ui->setupUi(this);

}

Contact::~Contact()
{
    delete ui;
}

void Contact::setInfo(QString name, QString streetAddress, QString city, QString state, QString zipCode, QString note)
{
    ui->nameLabel->setText(name);
    ui->streetAddressLabel->setText(streetAddress);
    ui->cityStateZipLabel->setText(city + ", " + state + " " + zipCode);
    ui->noteTextEdit->setText(note);
}

void Contact::setInfo(QString name, QString streetAddress, QString city, QString state, QString zipCode)
{
    ui->nameLabel->setText(name);
    ui->streetAddressLabel->setText(streetAddress);
    ui->cityStateZipLabel->setText(city + ", " + state + " " + zipCode);
    setWindowTitle(name);
}

void Contact::on_closeButton_clicked()
{
    accept();
}
