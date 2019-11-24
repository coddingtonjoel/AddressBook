#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "infoinput.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;
    QModelIndex parentIndex;
    QStandardItemModel* addressBook;

};
#endif // MAINWINDOW_H
