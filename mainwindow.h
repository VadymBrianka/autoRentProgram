#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlTableModel>
#include <QDateTime>
#include <QMessageBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QWidget>
#include "signinwindow.h"
#include "signupwindow.h"
#include "dbmanager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSqlTableModel;
class DBManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DBManager* dbManager,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_signInButton_clicked();

    void on_signUpButton_clicked();

public slots:
    void onDialogClosed();
private:
    Ui::MainWindow *ui;
    DBManager* dbManager;
    QSqlTableModel  *model;
};
#endif // MAINWINDOW_H
