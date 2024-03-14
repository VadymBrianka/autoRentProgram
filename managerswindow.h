#ifndef MANAGERSWINDOW_H
#define MANAGERSWINDOW_H

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
#include<QStandardItem>
#include<QTabWidget>
#include "sqlitedbmanager.h"

namespace Ui {
class ManagersWindow;
}

class ManagersWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ManagersWindow(QWidget *parent = nullptr);
    ~ManagersWindow();
    void setList1();
    void setList2();
private:
    Ui::ManagersWindow *ui;
    void setupModel1(const QString &tableName, const QStringList &headers);
    void setupModel2(const QString &tableName, const QStringList &headers);
    void createUI1();
    void createUI2();
    DBManager *db;
    QSqlTableModel  *model1;
    QSqlTableModel  *model2;
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
public slots:
    void on_tabWidget_currentChanged(int index);
};

#endif // MANAGERSWINDOW_H
