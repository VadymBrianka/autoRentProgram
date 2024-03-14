#ifndef PAYMENTWINDOW_H
#define PAYMENTWINDOW_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QClipboard>
#include <QMessageBox>
namespace Ui {
class PaymentWindow;
}

class PaymentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentWindow(QWidget *parent = nullptr);
    ~PaymentWindow();

private:
    Ui::PaymentWindow *ui;
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_openButton_clicked();
    void on_copyButton_clicked();
};

#endif // PAYMENTWINDOW_H
