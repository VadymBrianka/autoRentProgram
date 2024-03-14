#ifndef CUSTOMERSWINDOW_H
#define CUSTOMERSWINDOW_H

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
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include "sqlitedbmanager.h"
#include "addcustomerwindow.h"
namespace Ui {
class CustomersWindow;
}

class CustomersWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CustomersWindow(QWidget *parent = nullptr);
    ~CustomersWindow();
    void setList1(int sortField);
    void setList2(int sortField);
private:
    Ui::CustomersWindow *ui;
    void setupModel1(const QString &tableName, const QStringList &headers, int sortField);
    void setupModel2(const QString &tableName, const QStringList &headers, int sortField);
    void createUI1();
    void createUI2();
    DBManager *db;
    QSqlTableModel  *model1;
    QSqlTableModel  *model2;
    QSortFilterProxyModel *proxyModel1;
    QSortFilterProxyModel *proxyModel2;
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_addCustomerButton_clicked();
    void onSearchTextChanged(const QString &text);
    void onCBChanged(int index);
    void onCBChangedd(int index);
public slots:
    void onDialogClosed();
    void on_tabWidget_currentChanged(int index);
};

#endif // CUSTOMERSWINDOW_H
