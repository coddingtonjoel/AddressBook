#ifndef INFOINPUT_H
#define INFOINPUT_H

#include <QDialog>

namespace Ui {
class InfoInput;
}

class InfoInput : public QDialog
{
    Q_OBJECT

public:
    explicit InfoInput(QWidget *parent = nullptr);
    ~InfoInput();

    QString getFirstName() const;

    QString getLastName() const;

    QString getCity() const;

    QString getState() const;

    QString getStreetAddress() const;

    QString getZipCode() const;

    QString getNote() const;

    void setInfo(QString firstName, QString lastName, QString streetAddress, QString city, QString state, QString zipCode, QString note);

private slots:

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::InfoInput *ui;
    QString firstName;
    QString lastName;
    QString city;
    QString state;
    QString streetAddress;
    QString zipCode;
    QString note;
};

#endif // INFOINPUT_H
