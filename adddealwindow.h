#ifndef ADDDEALWINDOW_H
#define ADDDEALWINDOW_H

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
#include <QDateTime>
#include <QString>
#include <QCoreApplication>
#include "sqlitedbmanager.h"
#include "paymentwindow.h"
namespace Ui {
class AddDealWindow;
}

class AddDealWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddDealWindow(QWidget *parent = nullptr);
    ~AddDealWindow();

private:
    Ui::AddDealWindow *ui;
    bool checkFields();
    QString itinOfCustomer, vinOfCar, rentStartDate, rentEndDate, daysOfRenting, status, check, payment;
    int days;
    void fillComboBoxes();
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_confirmButton_clicked();
public slots:
    void onDialogClosed();
};

#endif // ADDDEALWINDOW_H
