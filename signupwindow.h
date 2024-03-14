#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

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
#include <QComboBox>
#include <QtGlobal>
#include <QCryptographicHash>
#include <QVariantList>
#include "customer.h"
#include "sqlitedbmanager.h"
namespace Ui {
class SignUpWindow;
}

class SignUpWindow : public QDialog
{
    Q_OBJECT
signals:
    void closed();
public:
    explicit SignUpWindow(QWidget *parent = nullptr);
    ~SignUpWindow();
private slots:
    void onUserRoleChanged(int index);
    void onShowPasswordChanged(int state);
    void on_signUpButton_clicked();
    bool onUserRoleChanged1();

private:
    Ui::SignUpWindow *ui;
    bool checkFieldsUser();
    bool checkFieldsAdmin();
    QString secretPassword1 = "b9c950640e1b3740e98acb93e669c65766f6670dd1609ba91ff41052ba48c6f3";
    QString login, password, question, answer, surname, firstName, middleName, phoneNumber, email, confirmPassword, secretPassword, role, status;
    DBManager *db;
    QSqlTableModel  *model;
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // SIGNUPWINDOW_H
