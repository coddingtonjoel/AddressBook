#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QModelIndex>
#include "infoinput.h"
#include "contact.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Address Book");

    //set App Icon
    QPixmap icon("://resources/icon.png");
    QIcon appIcon(icon);
    setWindowIcon(appIcon);

    //model
    addressBook = new QStandardItemModel(this);
    //QStandardItem* root = addressBook->invisibleRootItem();
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
    QString streetAddress = addressBook->data(parent.child(0,0), Qt::DisplayRole).toString();
    QString city = addressBook->data(parent.child(1,0), Qt::DisplayRole).toString();
    QString state = addressBook->data(parent.child(2,0), Qt::DisplayRole).toString();
    QString zipCode = addressBook->data(parent.child(3,0), Qt::DisplayRole).toString();
    QString note = addressBook->data(parent.child(4,0), Qt::DisplayRole).toString();

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
        QMessageBox::warning(this, "Error", "Please select a contact before editing.", QMessageBox::Ok, QMessageBox::Ok);
    }
    else {
        InfoInput* w = new InfoInput(this);

        QModelIndex parent = ui->listView->currentIndex();
        QString firstName = addressBook->data(parent.child(5,0), Qt::DisplayRole).toString();
        QString lastName = addressBook->data(parent.child(6,0), Qt::DisplayRole).toString();
        QString streetAddress = addressBook->data(parent.child(0,0), Qt::DisplayRole).toString();
        QString city = addressBook->data(parent.child(1,0), Qt::DisplayRole).toString();
        QString state = addressBook->data(parent.child(2,0), Qt::DisplayRole).toString();
        QString zipCode = addressBook->data(parent.child(3,0), Qt::DisplayRole).toString();
        QString note = addressBook->data(parent.child(4,0), Qt::DisplayRole).toString();

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

            addressBook->setData(parent, newName, Qt::DisplayRole);
            addressBook->setData(parent.child(0,0), newAddress, Qt::DisplayRole);
            addressBook->setData(parent.child(1,0), newCity, Qt::DisplayRole);
            addressBook->setData(parent.child(2,0), newState, Qt::DisplayRole);
            addressBook->setData(parent.child(3,0), newZipCode, Qt::DisplayRole);
            addressBook->setData(parent.child(4,0), newNote, Qt::DisplayRole);


        }
    }
}

