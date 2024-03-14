#include "adddealwindow.h"
#include "ui_adddealwindow.h"

AddDealWindow::AddDealWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDealWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Add deal");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
    fillComboBoxes();
}

AddDealWindow::~AddDealWindow()
{
    delete ui;
}
void AddDealWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}

bool AddDealWindow::checkFields()
{
    bool check = false;

    if(ui->itinCB->currentIndex() != 1 || ui->vinCB->currentIndex() != 1 || ui->daysOfRentingLE->text().isEmpty()){
        throw std::runtime_error("Error in inputing data about Deal:( some fields are empty");
        check = false;
    }
    else check = true;
    return check;
}

void AddDealWindow::fillComboBoxes()
{
    SqliteDBManager* db = SqliteDBManager::getInstance();
    QMap<int, QList<QString>> carsMap = db->getAllIVins();
    QMap<int, QList<QString>> customerssMap = db->getAllItins();

    for (auto it = customerssMap.begin(); it != customerssMap.end(); ++it) {
        qDebug() << "Car ID:" << it.key() << " Customer name:" << it.value();
    }
    for (auto it = customerssMap.begin(); it != customerssMap.end(); ++it) {
        qDebug() << "Car ID:" << it.key() << " Customer name:" << it.value();
    }

    // Очищення вмісту ComboBox перед заповненням
    ui->vinCB->clear();
    // ui->vinCB->addItem("");
    ui->itinCB->clear();
    // ui->itinCB->addItem("");

    // Вставлення команд у ComboBox з використанням ID як додаткового даних
    for (auto it = carsMap.begin(); it != carsMap.end(); ++it) {
        QStringList itemList = carsMap.value(it.key());
        QString combinedItem = itemList.join(" ");
        ui->vinCB->addItem(combinedItem);
    }
    for (auto it = customerssMap.begin(); it != customerssMap.end(); ++it) {
        QStringList itemList = customerssMap.value(it.key());
        QString combinedItem = itemList.join(" ");
        ui->itinCB->addItem(combinedItem);
    }
}


void AddDealWindow::on_confirmButton_clicked()
{
    SqliteDBManager* db = SqliteDBManager::getInstance();
    /*itinOfCustomer = ui->itinLE->text();
    vinOfCar = ui->vinLE->text();*/
    daysOfRenting = ui->daysOfRentingLE->text();
    days = daysOfRenting.toInt();

    QString itinOfCustomerBefore = ui->itinCB->currentText();
    QStringList itinList = itinOfCustomerBefore.split(" ");
    itinOfCustomer = itinList.last();
    QString vinOfCarBefore = ui->vinCB->currentText();
    QStringList vinList = vinOfCarBefore.split(" ");
    vinOfCar = vinList.last();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    rentStartDate = currentDateTime.toString("yyyy.MM.dd");
    QDateTime currentDatePlusDays = currentDateTime.addDays(days);
    rentEndDate = currentDatePlusDays.toString("yyyy.MM.dd");
    status = "active";
    check = "unChecked";
    payment = "unpaid";

    try {
        //if (checkFields()) {
        if (1==1) {
            Deal deal;
            deal.setItin(itinOfCustomer.toStdString());
            deal.setVin(vinOfCar.toStdString());
            deal.setRentStartDate(rentStartDate.toStdString());
            deal.setRentEndDate(rentEndDate.toStdString());
            deal.setStatus(status.toStdString());
            deal.setCheck(check.toStdString());
            deal.setPayment(payment.toStdString());

            QSqlQuery query;
            QString queryStr;

            queryStr = QString("SELECT COUNT(*) FROM Customers WHERE itin = '%1';").arg(itinOfCustomer);
            query.prepare(queryStr);
            if (query.exec() && query.next()) {
                int customerCount = query.value(0).toInt();
                if (customerCount == 0) {
                    QMessageBox::warning(this, "Error", "There is no customer with this itin!", QMessageBox::Ok);
                    return;
                }
            }

            queryStr = QString("SELECT COUNT(*) FROM Customers WHERE itin = '%1' AND status != 'Active';").arg(itinOfCustomer);
            query.prepare(queryStr);
            if (query.exec() && query.next()) {
                int inactiveCustomerCount = query.value(0).toInt();
                if (inactiveCustomerCount > 0) {
                    QMessageBox::warning(this, "Error", "There is no active customer with this itin!", QMessageBox::Ok);
                    return;
                }
            }

            queryStr = QString("SELECT COUNT(*) FROM Cars WHERE vin = '%1' AND status = 'available';").arg(vinOfCar);
            query.prepare(queryStr);
            if (query.exec() && query.next()) {
                int carCount = query.value(0).toInt();
                if (carCount == 0) {
                    QMessageBox::warning(this, "Error", "There is no available car with this vin!", QMessageBox::Ok);
                    return;
                }
            }

            if (db->insertIntoTableDeals(deal)) {
                queryStr = QString("UPDATE Cars SET status = 'notAvailable' WHERE vin = '%1';").arg(vinOfCar);
                query.prepare(queryStr);
                if (query.exec()) {

                    queryStr = QString("SELECT priceOfRenting FROM Cars WHERE vin = '%1';").arg(vinOfCar);
                    query.prepare(queryStr);
                    if (query.exec() && query.next()) {
                        int rentValue = query.value(0).toInt() * days;
                        queryStr = QString("SELECT deal_id FROM Deals WHERE vin = '%1' AND status = 'active';").arg(vinOfCar);
                        query.prepare(queryStr);
                        if (query.exec() && query.next()) {
                            int id = query.value(0).toInt();
                            QString message = QString("Congratulations! Firstly you have to pay for renting: %1 uah, for all period of renting! Do not forget to mention the application number %2 in the comments!!!").arg(rentValue).arg(id);
                            QMessageBox::information(this, "Payment!", message, QMessageBox::Ok);
                        }
                    }

                    //QMessageBox::information(this, "Success!", "Congratulations! New deal has been successfully added.", QMessageBox::Ok);
                    PaymentWindow *paymentWindow = new PaymentWindow(this);
                    connect(paymentWindow, &PaymentWindow::closed, this, &AddDealWindow::onDialogClosed);
                    paymentWindow->setModal(true);
                    paymentWindow->show();
                    hide();
                    //this->close();
                } else {
                    QMessageBox::warning(this, "Error", "Failed to update Cars table", QMessageBox::Ok);
                }
            } else {
                QMessageBox::warning(this, "Error", "Failed to insert deal into Deals table", QMessageBox::Ok);
            }
        }
    } catch (const std::exception &ex) {
        QMessageBox::warning(this, "Error", "Some fields are empty, please fill them all!!!", QMessageBox::Ok);
        qWarning() << "Exception in inputting data: " << ex.what();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", "Data couldn't be saved in the database!", QMessageBox::Ok);
        qCritical() << "Exception in: " << e.what();
    }
}

void AddDealWindow::onDialogClosed()
{
    emit close();
    close();
}

