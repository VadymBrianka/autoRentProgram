#include "paymentwindow.h"
#include "ui_paymentwindow.h"

PaymentWindow::PaymentWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PaymentWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Payment");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
}

PaymentWindow::~PaymentWindow()
{
    delete ui;
}

void PaymentWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}

void PaymentWindow::on_openButton_clicked()
{
    QUrl url("https://prt.mn/67QVp7L1Z4");
    if (!QDesktopServices::openUrl(url)) {
        qDebug() << "Could not open browser for URL:" << url.toString();
    }
}


void PaymentWindow::on_copyButton_clicked()
{
    QString linlText = ui->linkLB->text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(linlText);
    QMessageBox::information(this, "Copied successfully", "The text has been copied to the clipboard.");
}

