#ifndef HOMEMANAGER_H
#define HOMEMANAGER_H

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
#include "userwindow.h"
namespace Ui {
class HomeManager;
}

class HomeManager : public QDialog
{
    Q_OBJECT

public:
    explicit HomeManager(int id, int role, QWidget *parent = nullptr);
    ~HomeManager();

private slots:
    void on_exitButton_clicked();

    void on_carsButton_clicked();

    void on_customersButton_clicked();

    void on_dealButton_clicked();

    void on_editUserInformationButton_clicked();

public slots:
    void onDialogClosed();
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::HomeManager *ui;
    int currentUserId;
    int currentRole;
};

#endif // HOMEMANAGER_H
