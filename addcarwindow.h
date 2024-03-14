#ifndef ADDCARWINDOW_H
#define ADDCARWINDOW_H
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
class AddCarWindow;
}

class AddCarWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddCarWindow(QWidget *parent = nullptr);
    ~AddCarWindow();

private:
    Ui::AddCarWindow *ui;
    bool checkFields();
    QString brand, model, year, vin, engineCapacity, numberOfSeats, trunkVolume, price, priceOfRenting, status;
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_confirmButton_clicked();
};

#endif // ADDCARWINDOW_H
