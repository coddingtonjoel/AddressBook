#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QModelIndex>
#include "infoinput.h"
#include "contact.h"
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Address Book");

    //set app icon from resources
    QPixmap icon("://resources/icon.png");
    QIcon appIcon(icon);
    setWindowIcon(appIcon);

    //model creation
    addressBook = new QStandardItemModel(this);
    parentIndex = QModelIndex();

    ui->listView->setModel(addressBook);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    InfoInput* w = new InfoInput(this);

    int ret = w->exec();

    if (ret == QDialog::Accepted) {
        QString name = w->getFirstName() + " " + w->getLastName();

        QStandardItem* fullName = new QStandardItem(name);
        QStandardItem* streetAddress = new QStandardItem(w->getStreetAddress());
        QStandardItem* city = new QStandardItem(w->getCity());
        QStandardItem* state = new QStandardItem(w->getState());
        QStandardItem* zipCode = new QStandardItem(w->getZipCode());
        QStandardItem* note = new QStandardItem(w->getNote());
        QStandardItem* firstName = new QStandardItem(w->getFirstName());
        QStandardItem* lastName = new QStandardItem(w->getLastName());

        addressBook->appendRow(fullName);
        fullName->appendRow(streetAddress);
        fullName->appendRow(city);
        fullName->appendRow(state);
        fullName->appendRow(zipCode);
        fullName->appendRow(note);
        fullName->appendRow(firstName);
        fullName->appendRow(lastName);
    }
}

void MainWindow::on_deleteButton_clicked()
{
    if (!ui->listView->currentIndex().isValid()) {
        QApplication::beep();
        QMessageBox::warning(this, "Error", "Please select a contact to delete.", QMessageBox::Ok, QMessageBox::Ok);
    }
    else {
        QModelIndex parent = ui->listView->currentIndex();
        QString name = addressBook->data(parent, Qt::DisplayRole).toString();
        int ret = QMessageBox::warning(this, "Delete Contact", "Are you sure you want to delete " + name + " from your Address Book?",
                                       QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel);

        if (ret == QMessageBox::Yes) {
            QModelIndex parent = ui->listView->rootIndex();
            int row = ui->listView->currentIndex().row();
            addressBook->removeRow(row, parent);
        }
    }
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{


    QModelIndex parent = index;
    QString name = addressBook->data(parent, Qt::DisplayRole).toString();
    QString streetAddress = addressBook->data(addressBook->index(0,0,parent), Qt::DisplayRole).toString();
    QString city = addressBook->data(addressBook->index(1,0, parent), Qt::DisplayRole).toString();
    QString state = addressBook->data(addressBook->index(2,0, parent), Qt::DisplayRole).toString();
    QString zipCode = addressBook->data(addressBook->index(3,0, parent), Qt::DisplayRole).toString();
    QString note = addressBook->data(addressBook->index(4,0, parent), Qt::DisplayRole).toString();

    Contact* contact = new Contact(this);

    if (!note.isEmpty())
        contact->setInfo(name, streetAddress, city, state, zipCode, note);
    else
        contact->setInfo(name, streetAddress, city, state, zipCode, note);
    contact->exec();
}

void MainWindow::on_editButton_clicked()
{
    if (!ui->listView->currentIndex().isValid()) {
        QApplication::beep();
        QMessageBox::warning(this, "Error", "Please select a contact before editing.", QMessageBox::Ok, QMessageBox::Ok);
    }
    else {
        InfoInput* w = new InfoInput(this);

        //set parent as the selected index
        QModelIndex parent = ui->listView->currentIndex();

        //capture the data from model into local variables
        QString firstName = addressBook->data(addressBook->index(5,0, parent), Qt::DisplayRole).toString();
        QString lastName = addressBook->data(addressBook->index(6,0, parent), Qt::DisplayRole).toString();
        QString streetAddress = addressBook->data(addressBook->index(0,0,parent), Qt::DisplayRole).toString();
        QString city = addressBook->data(addressBook->index(1,0, parent), Qt::DisplayRole).toString();
        QString state = addressBook->data(addressBook->index(2,0, parent), Qt::DisplayRole).toString();
        QString zipCode = addressBook->data(addressBook->index(3,0, parent), Qt::DisplayRole).toString();
        QString note = addressBook->data(addressBook->index(4,0, parent), Qt::DisplayRole).toString();

        //use InfoInput::setInfo() with local variables
        w->setInfo(firstName, lastName, streetAddress, city, state, zipCode, note);

        int ret = w->exec();

        if (ret == QDialog::Accepted) {
            QString name = w->getFirstName() + " " + w->getLastName();

            //need NEW info not reusing the same as collected from data before overwrite
            QString newName = w->getFirstName() + " " + w->getLastName();
            QString newAddress = w->getStreetAddress();
            QString newCity = w->getCity();
            QString newState = w->getState();
            QString newZipCode = w->getZipCode();
            QString newNote = w->getNote();

            //rewriting information
            addressBook->setData(parent, newName, Qt::DisplayRole);
            addressBook->setData(addressBook->index(0,0, parent), newAddress, Qt::DisplayRole);
            addressBook->setData(addressBook->index(1,0, parent), newCity, Qt::DisplayRole);
            addressBook->setData(addressBook->index(2,0, parent), newState, Qt::DisplayRole);
            addressBook->setData(addressBook->index(3,0, parent), newZipCode, Qt::DisplayRole);
            addressBook->setData(addressBook->index(4,0, parent), newNote, Qt::DisplayRole);
        }
    }
}

void MainWindow::on_actionNew_Address_triggered()
{
    on_addButton_clicked();
}

void MainWindow::on_actionQuit_AddressBook_triggered()
{
    QApplication::quit();
}

void MainWindow::on_viewButton_clicked()
{
    if (!ui->listView->currentIndex().isValid()) {
        QApplication::beep();
        QMessageBox::warning(this, "Error", "Please select or add a contact before viewing.", QMessageBox::Ok, QMessageBox::Ok);
    }
    else {
        QModelIndex index = ui->listView->currentIndex();
        on_listView_doubleClicked(index);
    }
}

void MainWindow::on_actionView_Contact_triggered()
{
    on_viewButton_clicked();
}

void MainWindow::on_actionDelete_Contact_triggered()
{
    on_deleteButton_clicked();
}

void MainWindow::on_actionEdit_Contact_triggered()
{
    on_editButton_clicked();
}

