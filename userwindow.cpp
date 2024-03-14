#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(int id, int role, QWidget *parent)
    : QDialog(parent),
    currentUserId(id),
    currentRole(role),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("User menu");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
    SqliteDBManager* db= SqliteDBManager::getInstance();
    if(role == 1){
        QString queryStr = QString("SELECT * FROM Admins WHERE admin_id = '%1'")
                               .arg(id);
        QSqlQuery query;
        query.exec(queryStr);

        if(query.next()){
            QString login = query.value(1).toString();
            QString surName = query.value(5).toString();
            QString firstName = query.value(6).toString();
            QString middleName = query.value(7).toString();
            QString phoneNumber = query.value(8).toString();
            QString email = query.value(9).toString();
            ui->loginLE->setText(login);
            ui->surnameLE->setText(surName);
            ui->firstNameLE->setText(firstName);
            ui->middleNameLE->setText(middleName);
            ui->phoneNumberLE->setText(phoneNumber);
            ui->emailLE->setText(email);
        }
    }else{
        if(role == 2){
            QString queryStr = QString("SELECT * FROM Managers WHERE manager_id = '%1'")
                                   .arg(id);
            QSqlQuery query;
            query.exec(queryStr);

            if(query.next()){
                QString login = query.value(1).toString();
                QString surName = query.value(5).toString();
                QString firstName = query.value(6).toString();
                QString middleName = query.value(7).toString();
                QString phoneNumber = query.value(8).toString();
                QString email = query.value(9).toString();
                ui->loginLE->setText(login);
                ui->surnameLE->setText(surName);
                ui->firstNameLE->setText(firstName);
                ui->middleNameLE->setText(middleName);
                ui->phoneNumberLE->setText(phoneNumber);
                ui->emailLE->setText(email);
            }
        }
    }
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}
void UserWindow::onDialogClosed()
{
    emit closed();
    show();
}

void UserWindow::on_changePasswordButton_clicked()
{
    ForgotPasswordWindow *forgotPasswordWindow = new ForgotPasswordWindow();
    connect(forgotPasswordWindow, &ForgotPasswordWindow::closed, this, &UserWindow::onDialogClosed);
    forgotPasswordWindow->setModal(true);
    forgotPasswordWindow->show();
    hide();
}


void UserWindow::on_saveChangesButton_clicked()
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    if(currentRole == 1){
        loginL = ui->loginLE->text();
        surNameL = ui->surnameLE->text();
        firstNameL = ui->firstNameLE->text();
        middleNameL = ui->middleNameLE->text();
        phoneNumberL = ui->phoneNumberLE->text();
        emailL = ui->emailLE->text();
        try {
            if (checkFieldsUser()) {
                try{
                    QString queryStr = QString("SELECT COUNT(*) FROM Admins WHERE login = '%1' AND admin_id != %2")
                                           .arg(loginL.toStdString().c_str())
                                           .arg(currentUserId);
                    QSqlQuery query;
                    query.prepare(queryStr);

                    QString queryStr2 = QString("SELECT COUNT(*) FROM Managers WHERE login = '%1'")
                                            .arg(loginL.toStdString().c_str());
                    QSqlQuery query2;
                    query2.prepare(queryStr2);

                    if(query.exec() && query.next()){
                        int adminCount = query.value(0).toInt();

                        if (adminCount > 0) {
                            QMessageBox::warning(this, "Unavailable login","Admin with this login already exists", QMessageBox::Ok);
                        }
                        else{
                            if(query2.exec() && query2.next()){
                                int managerCount = query2.value(0).toInt();

                                if (managerCount > 0) {
                                    QMessageBox::warning(this, "Unavailable login","User with this login already exists", QMessageBox::Ok);
                                }
                                else{
                                    QString queryStr3 = QString("UPDATE Admins SET login = '%1', surname = '%2', firstName = '%3', middleName = '%4', phoneNumber = '%5', email = '%6' WHERE admin_id = '%7'")
                                                            .arg(loginL.toStdString().c_str())
                                                            .arg(surNameL.toStdString().c_str())
                                                            .arg(firstNameL.toStdString().c_str())
                                                            .arg(middleNameL.toStdString().c_str())
                                                            .arg(phoneNumberL.toStdString().c_str())
                                                            .arg(emailL.toStdString().c_str())
                                                            .arg(currentUserId);
                                    QSqlQuery query3;
                                    query3.prepare(queryStr3);
                                    if (query3.exec()) {
                                        QMessageBox::information(this, "Congratulations!", "Data updated successfully!", QMessageBox::Ok);
                                        this->close();
                                    }
                                }
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
    }else{
        if(currentRole == 2){
            loginL = ui->loginLE->text();
            surNameL = ui->surnameLE->text();
            firstNameL = ui->firstNameLE->text();
            middleNameL = ui->middleNameLE->text();
            phoneNumberL = ui->phoneNumberLE->text();
            emailL = ui->emailLE->text();
            try {
                if (checkFieldsUser()) {
                    try{
                        QString queryStr = QString("SELECT COUNT(*) FROM Managers WHERE login = '%1' AND manager_id != %2")
                                               .arg(loginL.toStdString().c_str())
                                               .arg(currentUserId);
                        QSqlQuery query;
                        query.prepare(queryStr);

                        QString queryStr2 = QString("SELECT COUNT(*) FROM Admins WHERE login = '%1'")
                                                .arg(loginL.toStdString().c_str());
                        QSqlQuery query2;
                        query2.prepare(queryStr2);

                        if(query.exec() && query.next()){
                            int adminCount = query.value(0).toInt();

                            if (adminCount > 0) {
                                QMessageBox::warning(this, "Unavailable login","Manager with this login already exists", QMessageBox::Ok);
                            }
                            else{
                                if(query2.exec() && query2.next()){
                                    int managerCount = query2.value(0).toInt();

                                    if (managerCount > 0) {
                                        QMessageBox::warning(this, "Unavailable login","User with this login already exists", QMessageBox::Ok);
                                    }
                                    else{
                                        QString queryStr3 = QString("UPDATE Managers SET login = '%1', surname = '%2', firstName = '%3', middleName = '%4', phoneNumber = '%5', email = '%6' WHERE manager_id = '%7'")
                                                                .arg(loginL.toStdString().c_str())
                                                                .arg(surNameL.toStdString().c_str())
                                                                .arg(firstNameL.toStdString().c_str())
                                                                .arg(middleNameL.toStdString().c_str())
                                                                .arg(phoneNumberL.toStdString().c_str())
                                                                .arg(emailL.toStdString().c_str())
                                                                .arg(currentUserId);
                                        QSqlQuery query3;
                                        query3.prepare(queryStr3);
                                        if (query3.exec()) {
                                            QMessageBox::information(this, "Congratulations!", "Data updated successfully!", QMessageBox::Ok);
                                            this->close();
                                        }
                                    }
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
    }
}

bool UserWindow::checkFieldsUser()
{
    bool check = false;
    if(ui->surnameLE->text().isEmpty() || ui->firstNameLE->text().isEmpty()|| ui->phoneNumberLE->text().isEmpty() ||
        ui->middleNameLE->text().isEmpty()|| ui->emailLE->text().isEmpty() ||ui->loginLE->text().isEmpty()){
        throw std::runtime_error("Error in inputing data about Admin:( some fields are empty");
        check = false;
    }
    else check = true;
    return check;
}
