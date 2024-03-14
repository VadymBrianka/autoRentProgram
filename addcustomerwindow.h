#ifndef ADDCUSTOMERWINDOW_H
#define ADDCUSTOMERWINDOW_H

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
#include "sqlitedbmanager.h"

namespace Ui {
class AddCustomerWindow;
}

class AddCustomerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomerWindow(QWidget *parent = nullptr);
    ~AddCustomerWindow();

private:
    Ui::AddCustomerWindow *ui;
    bool checkFields();
    QString surname, firstName, middleName, phoneNumber, email, age, address, yearsOfExperience, ITIN, status;
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_confirmButton_clicked();
};

#endif // ADDCUSTOMERWINDOW_H
