#include "homemanager.h"
#include "ui_homemanager.h"

HomeManager::HomeManager(int id, int role, QWidget *parent) :
    QDialog(parent),
    currentUserId(id),
    currentRole(role),
    ui(new Ui::HomeManager)
{
    ui->setupUi(this);
    this->setWindowTitle("Home manager");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
}

HomeManager::~HomeManager()
{
    delete ui;
}


void HomeManager::onDialogClosed()
{
    show();
}

void HomeManager::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}


void HomeManager::on_exitButton_clicked()
{
    close();
}


void HomeManager::on_carsButton_clicked()
{
    this->hide();
    CarsWindow *carsWindow = new CarsWindow(this);
    connect(carsWindow, &CarsWindow::closed, this, &HomeManager::onDialogClosed);
    carsWindow->show();
    carsWindow->setList1(0);
    carsWindow->setList2(0);
}


void HomeManager::on_customersButton_clicked()
{
    CustomersWindow *customersWindow = new CustomersWindow(this);
    connect(customersWindow, &CustomersWindow::closed, this, &HomeManager::onDialogClosed);
    customersWindow->setModal(true);
    customersWindow->show();
    hide();
    customersWindow->on_tabWidget_currentChanged(0);
    customersWindow->on_tabWidget_currentChanged(1);
}


void HomeManager::on_dealButton_clicked()
{
    DealWindow *dealWindow = new DealWindow(this);
    connect(dealWindow, &DealWindow::closed, this, &HomeManager::onDialogClosed);
    dealWindow->setModal(true);
    dealWindow->show();
    hide();
    dealWindow->on_tabWidget_currentChanged(1);
    dealWindow->on_tabWidget_currentChanged(0);
}


void HomeManager::on_editUserInformationButton_clicked()
{
    this->hide();
    UserWindow *userWindow = new UserWindow(currentUserId, 2, this);
    connect(userWindow, &UserWindow::closed, this, &HomeManager::onDialogClosed);
    userWindow->show();
}

