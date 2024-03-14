#ifndef DEALWINDOW_H
#define DEALWINDOW_H

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
#include "adddealwindow.h"
#include "sqlitedbmanager.h"
namespace Ui {
class DealWindow;
}

class DealWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DealWindow(QWidget *parent = nullptr);
    ~DealWindow();
    void setList1(int sortField);
    void setList2(int sortField);
private:
    Ui::DealWindow *ui;
    void setupModel1(const QString &tableName, const QStringList &headers, int sortField);
    void setupModel2(const QString &tableName, const QStringList &headers, int sortField);
    void createUI1();
    void createUI2();
    DBManager *db;
    QSqlTableModel  *model1;
    QSqlTableModel  *model2;
    QString  rentStartDate, rentEndDate, status;
    QSortFilterProxyModel *proxyModel1;
    QSortFilterProxyModel *proxyModel2;
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_addDealButton_clicked();
    void onSearchTextChanged(const QString &text);
    void onCBChanged(int index);
    void onCBChangedd(int index);
    void on_paymentButton_clicked();

public slots:
    void onDialogClosed();
    void on_tabWidget_currentChanged(int index);
};

#endif // DEALWINDOW_H
