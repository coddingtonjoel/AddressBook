#ifndef CONTACT_H
#define CONTACT_H

#include <QDialog>
#include <QStandardItemModel>
#include <QModelIndex>

namespace Ui {
class Contact;
}

class Contact : public QDialog
{
    Q_OBJECT

public:
    explicit Contact(QWidget *parent = nullptr);
    ~Contact();
    void setInfo(QString name, QString streetAddress, QString city, QString state, QString zipCode, QString note);
    void setInfo(QString name, QString streetAddress, QString city, QString state, QString zipCode);

private slots:
    void on_closeButton_clicked();

private:
    Ui::Contact *ui;
};

#endif // CONTACT_H
