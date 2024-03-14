#include "addcustomerwindow.h"
#include "ui_addcustomerwindow.h"

AddCustomerWindow::AddCustomerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomerWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Add customer");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
}

AddCustomerWindow::~AddCustomerWindow()
{
    delete ui;
}

void AddCustomerWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}




void AddCustomerWindow::on_confirmButton_clicked()
{
    QString VERIFICATED = "VERIFICATED", Not_Verificated ="Not_Verificated", ACTIVE ="ACTIVE", CLOSED ="CLOSED", MANAGER="MANAGER", ADMIN="ADMIN";
    SqliteDBManager* db= SqliteDBManager::getInstance();
        surname = ui->surnameLE->text();
        firstName = ui->firstNameLE->text();
        phoneNumber = ui->phoneNumberLE->text();
        email = ui->emailLE->text();
        middleName = ui->middleNameLE->text();
        age = ui->ageLE->text();
        address = ui->addressLE->text();
        ITIN = ui->ITINLE->text();
        yearsOfExperience = ui->yearsOfExperienceLE->text();
        status = "Active";
        try {
            if (checkFields()) {
                Customer customer;
                customer.setSurname(surname.toStdString());
                customer.setFirstName(firstName.toStdString());
                customer.setPhoneNumber(phoneNumber.toStdString());
                customer.setEmail(email.toStdString());
                customer.setMiddleName(middleName.toStdString());
                customer.setAge(age.toInt());
                customer.setYearsOfExperience(yearsOfExperience.toInt());
                customer.setAddress(address.toStdString());
                customer.setITIN(ITIN.toStdString());
                customer.setStatus(status.toStdString());
                    try{

                        QString queryStr = QString("SELECT COUNT(*) FROM Customers WHERE (surname = '%1' AND firstName = '%2') AND (middleName = '%3' AND itin = '%4');")
                                               .arg(surname.toStdString().c_str())
                                               .arg(firstName.toStdString().c_str())
                                               .arg(middleName.toStdString().c_str())
                                               .arg(ITIN.toStdString().c_str());
                        QSqlQuery query;
                        query.prepare(queryStr);

                        if(query.exec() && query.next()){
                            int customerCount = query.value(0).toInt();

                            if (customerCount > 0) {
                                QMessageBox::warning(this, "Unavailable login","Customer with this data already exists", QMessageBox::Ok);
                            }
                            else{
                                if(age.toInt() >= 18){
                                        if (db->insertIntoTableCustomers(customer)) {
                                            QMessageBox::information(this, "Success!","Congratulations! New customer has been successfully added.", QMessageBox::Ok);
                                            this->close();
                                        }
                                }else{
                                        QMessageBox::warning(this, "Error","Customer too young!", QMessageBox::Ok);
                                }
                            }
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

bool AddCustomerWindow::checkFields()
{
    bool check = false;
    if(ui->surnameLE->text().isEmpty() || ui->firstNameLE->text().isEmpty() || ui->middleNameLE->text().isEmpty() || ui->ageLE->text().isEmpty() || ui->addressLE->text().isEmpty() || ui->ITINLE->text().isEmpty() || ui->emailLE->text().isEmpty() ||
        ui->phoneNumberLE->text().isEmpty() || ui->yearsOfExperienceLE->text().isEmpty()){
        throw std::runtime_error("Error in inputing data about Customer:( some fields are empty");
        check = false;
    }
    else check = true;
    return check;
}
