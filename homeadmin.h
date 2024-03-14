#ifndef HOMEADMIN_H
#define HOMEADMIN_H

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
#include "carswindow.h"
#include "dealwindow.h"
#include "customerswindow.h"
#include "managerswindow.h"
#include "userwindow.h"

namespace Ui {
class HomeAdmin;
}

class HomeAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit HomeAdmin(int id, int role, QWidget *parent = nullptr);
    ~HomeAdmin();
public slots:
    void onDialogClosed();
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_managersButton_clicked();

    void on_dealButton_clicked();

    void on_customersButton_clicked();

    void on_carsButton_clicked();

    void on_exitButton_clicked();

    void on_editUserInformationButton_clicked();

private:
    Ui::HomeAdmin *ui;
    int currentUserId;
    int currentRole;
};

#endif // HOMEADMIN_H
