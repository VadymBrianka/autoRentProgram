#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H
#include <QDialog>
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
#include <QCryptographicHash>
#include "forgotpasswordwindow.h"
#include "homemanager.h"
#include "homeadmin.h"
#include "sqlitedbmanager.h"
namespace Ui {
class SignInWindow;
}

class SignInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignInWindow(QWidget *parent = nullptr);
    ~SignInWindow();

signals:
    void closed();
public slots:
    void onDialog1Closed();
    void onDialog2Closed();
private slots:
    void on_forgotPasswordButton_clicked();
    void onShowPasswordChanged(int state);
    void on_signInButton_clicked();
private:
    Ui::SignInWindow *ui;
    bool checkFields();
    QString login, password;
    DBManager *db;
    QSqlTableModel  *model;
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // SIGNINWINDOW_H
