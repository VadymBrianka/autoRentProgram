#include "addcarwindow.h"
#include "ui_addcarwindow.h"

AddCarWindow::AddCarWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCarWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Add car");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
}

AddCarWindow::~AddCarWindow()
{
    delete ui;
}

bool AddCarWindow::checkFields()
{
    bool check = false;
    if(ui->modelLE->text().isEmpty() || ui->brandLE->text().isEmpty() || ui->yearLE->text().isEmpty() || ui->engineCapacityLE->text().isEmpty() || ui->vinLE->text().isEmpty() || ui->numberOfSeatsLE->text().isEmpty() || ui->trunkVolumeLE->text().isEmpty() ||
        ui->priceLE->text().isEmpty() || ui->priceOfRentingLE->text().isEmpty()){
        throw std::runtime_error("Error in inputing data about Car:( some fields are empty");
        check = false;
    }
    else check = true;
    return check;
}

void AddCarWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}

void AddCarWindow::on_confirmButton_clicked()
{
    QString VERIFICATED = "VERIFICATED", Not_Verificated ="Not_Verificated", ACTIVE ="ACTIVE", CLOSED ="CLOSED", MANAGER="MANAGER", ADMIN="ADMIN";
    SqliteDBManager* db= SqliteDBManager::getInstance();
    brand = ui->brandLE->text();
    model = ui->modelLE->text();
    year = ui->yearLE->text();
    vin = ui->vinLE->text();
    engineCapacity = ui->engineCapacityLE->text();
    numberOfSeats = ui->numberOfSeatsLE->text();
    trunkVolume = ui->trunkVolumeLE->text();
    price = ui->priceLE->text();
    priceOfRenting = ui->priceOfRentingLE->text();
    status = "available";
    try {
        if (checkFields()) {
            Car car;
            car.setBrand(brand.toStdString());
            car.setModel(model.toStdString());
            car.setYear(year.toInt());
            car.setVin(vin.toStdString());
            car.setEngineCapacity(engineCapacity.toInt());
            car.setNumberOfSeats(numberOfSeats.toInt());
            car.setTrunkVolume(trunkVolume.toInt());
            car.setPrice(price.toInt());
            car.setPriceOfRenting(priceOfRenting.toInt());
            car.setStatus(status.toStdString());
            try{

                QString queryStr = QString("SELECT COUNT(*) FROM Cars WHERE vin = '%1';")
                                       .arg(vin.toStdString().c_str());
                QSqlQuery query;
                query.prepare(queryStr);

                if(query.exec() && query.next()){
                    int customerCount = query.value(0).toInt();

                    if (customerCount > 0) {
                        QMessageBox::warning(this, "Unavailable vin","Car with this vin already exists", QMessageBox::Ok);
                    }
                    else{
                        if (db->insertIntoTableCars(car)) {
                            QMessageBox::information(this, "Success!","Congratulations! New car has been successfully added.", QMessageBox::Ok);
                            this->close();
                        }
                        else{
                            QMessageBox::warning(this, "Error3:(", "Ось і помилка!");
                        }
                    }
                }
                else{
                    QMessageBox::warning(this, "Error2:(", "Ось і помилка!");
                }
            }catch(const std::exception &e){
                QMessageBox::warning(this, "Error due to database operation :(", "Data couldn't be saved in the database!");
                qCritical() << "Exception in: " << e.what();
            }
        }
    }catch(const std::exception &ex){
        QMessageBox::warning(this, "Error due to input data :(", "Some fields are empty, please fill them all!!!");
        qWarning() << "Exception in inputing data: " << ex.what();
    }
}

