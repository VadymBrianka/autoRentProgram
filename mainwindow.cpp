#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include <QtSql/QSqlTableModel>
MainWindow::MainWindow(DBManager* dbManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbManager->connectToDataBase();
    this->setWindowTitle("Brianka");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_signInButton_clicked()
{
    this->hide();
    SignInWindow *signInWindow = new SignInWindow();
    connect(signInWindow, &SignInWindow::closed, this, &MainWindow::onDialogClosed);
    signInWindow->show();
}


void MainWindow::on_signUpButton_clicked()
{
    this->hide();
    SignUpWindow *signUpWindow = new SignUpWindow();
    connect(signUpWindow, &SignUpWindow::closed, this, &MainWindow::onDialogClosed);
    signUpWindow->show();
}

void MainWindow::onDialogClosed()
{
    show();
}
