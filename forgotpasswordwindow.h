#ifndef FORGOTPASSWORDWINDOW_H
#define FORGOTPASSWORDWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
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
#include "dbmanager.h"
#include "sqlitedbmanager.h"
namespace Ui {
class ForgotPasswordWindow;
}

class ForgotPasswordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPasswordWindow(QWidget *parent = nullptr);
    ~ForgotPasswordWindow();
signals:
    void closed();
private slots:
    void on_resetPasswordButton_clicked();
    void on_confirmLoginButton_clicked();
    void onShowPasswordChanged(int state);
    void on_setNewPasswordButton_clicked();

public slots:
    void onDialogClosed();
private:
    Ui::ForgotPasswordWindow *ui;
    QString login, answer, password;
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // FORGOTPASSWORDWINDOW_H
