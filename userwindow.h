#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>
#include "forgotpasswordwindow.h"
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
class UserWindow;
}

class UserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserWindow(int id, int role, QWidget *parent = nullptr);
    ~UserWindow();

private:
    Ui::UserWindow *ui;
    DBManager *db;
    QSqlTableModel  *model;
    int currentUserId;
    int currentRole;
    QString loginL, surNameL, firstNameL, middleNameL, phoneNumberL, emailL;
    bool checkFieldsUser();
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
public slots:
    void onDialogClosed();
private slots:
    void on_changePasswordButton_clicked();
    void on_saveChangesButton_clicked();
};

#endif // USERWINDOW_H
