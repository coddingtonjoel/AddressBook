#include "infoinput.h"
#include "ui_infoinput.h"
#include <QMessageBox>

InfoInput::InfoInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoInput)
{
    ui->setupUi(this);
    setWindowTitle("Contact Information");
}

InfoInput::~InfoInput()
{
    delete ui;
}
void InfoInput::on_okButton_clicked()
{
    bool ok = !ui->firstNameLineEdit->text().isEmpty() && !ui->lastNameLineEdit->text().isEmpty()
            && !ui->streetAddressLineEdit->text().isEmpty() && !ui->cityLineEdit->text().isEmpty()
            && !ui->zipCodeLineEdit->text().isEmpty();


    if (ok && ui->stateComboBox->currentText() != "--Enter State--") {
        accept();
        firstName = ui->firstNameLineEdit->text();
        lastName = ui->lastNameLineEdit->text();
        streetAddress = ui->streetAddressLineEdit->text();
        city = ui->cityLineEdit->text();
        state = ui->stateComboBox->currentText();
        zipCode = ui->zipCodeLineEdit->text();
        note = ui->notesTextEdit->toPlainText();
    }
    else
        QMessageBox::warning(this, "Error", "Fields not completed.", QMessageBox::Ok, QMessageBox::Ok);
}

void InfoInput::on_cancelButton_clicked()
{
    reject();
}

QString InfoInput::getNote() const
{
    return note;
}

void InfoInput::setInfo(QString firstName, QString lastName, QString streetAddress, QString city, QString state, QString zipCode, QString note)
{
    ui->firstNameLineEdit->setText(firstName);
    ui->lastNameLineEdit->setText(lastName);
    ui->cityLineEdit->setText(city);
    ui->streetAddressLineEdit->setText(streetAddress);
    ui->stateComboBox->setItemText(0, state);
    ui->zipCodeLineEdit->setText(zipCode);
    ui->notesTextEdit->setText(note);
}

QString InfoInput::getZipCode() const
{
    return zipCode;
}

QString InfoInput::getStreetAddress() const
{
    return streetAddress;
}

QString InfoInput::getState() const
{
    return state;
}

QString InfoInput::getCity() const
{
    return city;
}

QString InfoInput::getLastName() const
{
    return lastName;
}

QString InfoInput::getFirstName() const
{
    return firstName;
}
