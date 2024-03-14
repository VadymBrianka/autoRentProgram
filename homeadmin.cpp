#include "homeadmin.h"
#include "ui_homeadmin.h"

HomeAdmin::HomeAdmin(int id, int role, QWidget *parent) :
    QDialog(parent),
    currentUserId(id),
    currentRole(role),
    ui(new Ui::HomeAdmin)
{
    ui->setupUi(this);
    this->setWindowTitle("Home admin");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
}

HomeAdmin::~HomeAdmin()
{
    delete ui;
}

void HomeAdmin::onDialogClosed()
{
    show();
}

void HomeAdmin::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}

void HomeAdmin::on_managersButton_clicked()
{
    ManagersWindow *managersWindow = new ManagersWindow(this);
    connect(managersWindow, &ManagersWindow::closed, this, &HomeAdmin::onDialogClosed);
    managersWindow->setModal(true);
    managersWindow->show();
    hide();
    managersWindow->on_tabWidget_currentChanged(0);
    managersWindow->on_tabWidget_currentChanged(1);
}


void HomeAdmin::on_dealButton_clicked()
{
    DealWindow *dealWindow = new DealWindow(this);
    connect(dealWindow, &DealWindow::closed, this, &HomeAdmin::onDialogClosed);
    dealWindow->setModal(true);
    dealWindow->show();
    hide();
    dealWindow->on_tabWidget_currentChanged(1);
    dealWindow->on_tabWidget_currentChanged(0);
}


void HomeAdmin::on_customersButton_clicked()
{
    CustomersWindow *customersWindow = new CustomersWindow(this);
    connect(customersWindow, &CustomersWindow::closed, this, &HomeAdmin::onDialogClosed);
    customersWindow->setModal(true);
    customersWindow->show();
    hide();
    customersWindow->on_tabWidget_currentChanged(0);
    customersWindow->on_tabWidget_currentChanged(1);
}


void HomeAdmin::on_carsButton_clicked()
{
    this->hide();
    CarsWindow *carsWindow = new CarsWindow(this);
    connect(carsWindow, &CarsWindow::closed, this, &HomeAdmin::onDialogClosed);
    carsWindow->show();
    carsWindow->setList1(0);
    carsWindow->setList2(0);
}


void HomeAdmin::on_exitButton_clicked()
{
    close();
}


void HomeAdmin::on_editUserInformationButton_clicked()
{
    this->hide();
    UserWindow *userWindow = new UserWindow(currentUserId, 1, this);
    connect(userWindow, &UserWindow::closed, this, &HomeAdmin::onDialogClosed);
    userWindow->show();
}

