#include "signupwindow.h"
#include "ui_signupwindow.h"

SignUpWindow::SignUpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sign up");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
    ui->passwordLE->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordLE->setEchoMode(QLineEdit::Password);
    ui->secretPasswordLE->setEchoMode(QLineEdit::Password);
    ui->secretPasswordLE->hide();
    connect(ui->showPasswordCheckBox, &QCheckBox::stateChanged, this, &SignUpWindow::onShowPasswordChanged);
    connect(ui->roleCB, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SignUpWindow::onUserRoleChanged);
}

SignUpWindow::~SignUpWindow()
{
    delete ui;
}

void SignUpWindow::onUserRoleChanged(int index)
{
    const QString selectedRole = ui->roleCB->itemText(index);
    bool isAdmin = (selectedRole == "Manager");
    if(!isAdmin){
        ui->secretPasswordLE->show();
        ui->surnameLE->clear();
        ui->firstNameLE->clear();
        ui->phoneNumberLE->clear();
        ui->emailLE->clear();
        ui->middleNameLE->clear();
        ui->passwordLE->clear();
        ui->confirmPasswordLE->clear();
        ui->loginLE->clear();
        ui->secretQuestionLE->clear();
        ui->answerToSecretQuestionLE->clear();
        ui->secretPasswordLE->clear();
    }else{
        ui->secretPasswordLE->hide();
        ui->surnameLE->clear();
        ui->firstNameLE->clear();
        ui->phoneNumberLE->clear();
        ui->emailLE->clear();
        ui->middleNameLE->clear();
        ui->passwordLE->clear();
        ui->confirmPasswordLE->clear();
        ui->loginLE->clear();
        ui->secretQuestionLE->clear();
        ui->answerToSecretQuestionLE->clear();
        ui->secretPasswordLE->clear();
    }
}

void SignUpWindow::onShowPasswordChanged(int state)
{
    if (state == Qt::Checked) {
        ui->passwordLE->setEchoMode(QLineEdit::Normal);
        ui->confirmPasswordLE->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordLE->setEchoMode(QLineEdit::Password);
        ui->confirmPasswordLE->setEchoMode(QLineEdit::Password);
    }
}

void SignUpWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}

void SignUpWindow::on_signUpButton_clicked()
{
    QString verificated = "VERIFICATED", not_Verificated ="Not_Verificated", active ="ACTIVE", closed ="CLOSED", manager="MANAGER", admin="ADMIN";
    SqliteDBManager* db= SqliteDBManager::getInstance();
    const bool selectedRole = onUserRoleChanged1();
    bool isAdmin = (selectedRole == false);
    if(!isAdmin){
        login = ui->loginLE->text();
        password = ui->passwordLE->text();
        question = ui->secretQuestionLE->text();
        answer = ui->answerToSecretQuestionLE->text();
        surname = ui->surnameLE->text();
        firstName = ui->firstNameLE->text();
        middleName = ui->middleNameLE->text();
        phoneNumber = ui->phoneNumberLE->text();
        email = ui->emailLE->text();
        confirmPassword = ui->confirmPasswordLE->text();
        role =manager;
        status =not_Verificated;

        QByteArray bytesi = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
        QString oute = QString(bytesi.toHex());

        QByteArray bytesAns = QCryptographicHash::hash(answer.toUtf8(), QCryptographicHash::Sha256);
        QString outAns = QString(bytesAns.toHex());
        try {
            if (checkFieldsUser()) {
                Manager manager;
                manager.setLogin(login.toStdString());
                manager.setPassword(oute.toStdString());
                manager.setSecretQuestion(question.toStdString());
                manager.setAnswerToSecretQuestion(outAns.toStdString());
                manager.setSurname(surname.toStdString());
                manager.setFirstName(firstName.toStdString());
                manager.setMiddleName(middleName.toStdString());
                manager.setPhoneNumber(phoneNumber.toStdString());
                manager.setEmail(email.toStdString());
                manager.setRole(role.toStdString());
                manager.setStatus(status.toStdString());
                if(ui->passwordLE->text()!=ui->confirmPasswordLE->text()){
                    QMessageBox::warning(this, "Error!", "Passwords do not match.", QMessageBox::Ok);
                }else{
                    try{

                        QString queryStr = QString("SELECT COUNT(*) FROM Managers WHERE login = '%1'")
                                               .arg(login.toStdString().c_str());
                        QSqlQuery query;
                        query.prepare(queryStr);

                        QString queryStr2 = QString("SELECT COUNT(*) FROM Admins WHERE login = '%1'")
                                               .arg(login.toStdString().c_str());
                        QSqlQuery query2;
                        query2.prepare(queryStr2);

                        if(query.exec() && query.next()){
                            int managerCount = query.value(0).toInt();

                            if (managerCount > 0) {
                                QMessageBox::warning(this, "Unavailable login","Manager with this login already exists", QMessageBox::Ok);
                            }
                            else{
                                if(query2.exec() && query2.next()){
                                    int adminCount = query2.value(0).toInt();

                                    if (adminCount > 0) {
                                        QMessageBox::warning(this, "Unavailable login","User with this login already exists", QMessageBox::Ok);
                                    }
                                    else{
                                        if (db->insertIntoTableManagers(manager)) {
                                            QMessageBox::information(this, "Sign up!", "Congratulations! You have successfully registered.", QMessageBox::Ok);
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
            }

        }catch(const std::exception &ex){
            QMessageBox::warning(this, "Error due to input data :(", "Some fields are empty, please fill them all!!!");
            qWarning() << "Exception in inputing data: " << ex.what();
        }
    }else{
        login = ui->loginLE->text();
        password = ui->passwordLE->text();
        question = ui->secretQuestionLE->text();
        answer = ui->answerToSecretQuestionLE->text();
        surname = ui->surnameLE->text();
        firstName = ui->firstNameLE->text();
        middleName = ui->middleNameLE->text();
        phoneNumber = ui->phoneNumberLE->text();
        email = ui->emailLE->text();
        confirmPassword = ui->confirmPasswordLE->text();
        role =admin;
        status =active;
        secretPassword = ui->secretPasswordLE->text();

        QByteArray bytesi = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
        QString oute = QString(bytesi.toHex());

        QByteArray bytesAns = QCryptographicHash::hash(answer.toUtf8(), QCryptographicHash::Sha256);
        QString outAns = QString(bytesAns.toHex());

        QByteArray bytespas = QCryptographicHash::hash(secretPassword.toUtf8(), QCryptographicHash::Sha256);
        QString outPas = QString(bytespas.toHex());
        try {
            if (checkFieldsAdmin()) {
                Admin admin;
                admin.setLogin(login.toStdString());
                admin.setPassword(oute.toStdString());
                admin.setSecretQuestion(question.toStdString());
                admin.setAnswerToSecretQuestion(outAns.toStdString());
                admin.setSurname(surname.toStdString());
                admin.setFirstName(firstName.toStdString());
                admin.setMiddleName(middleName.toStdString());
                admin.setPhoneNumber(phoneNumber.toStdString());
                admin.setEmail(email.toStdString());
                admin.setRole(role.toStdString());
                admin.setStatus(status.toStdString());
                if(ui->passwordLE->text()!=ui->confirmPasswordLE->text()){
                    QMessageBox::warning(this, "Error!", "Passwords do not match.", QMessageBox::Ok);
                }else{
                    try{

                        QString queryStr = QString("SELECT COUNT(*) FROM Admins WHERE login = '%1'")
                                               .arg(login.toStdString().c_str());
                        QSqlQuery query;
                        query.prepare(queryStr);

                        QString queryStr2 = QString("SELECT COUNT(*) FROM Managers WHERE login = '%1'")
                                               .arg(login.toStdString().c_str());
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
                                        if(outPas == secretPassword1){
                                            if (db->insertIntoTableAdmins(admin)) {
                                                QMessageBox::information(this, "Sign up!", "Congratulations! You have successfully registered.", QMessageBox::Ok);
                                                this->close();
                                            }
                                        }else{
                                            QMessageBox::warning(this, "Error", "Secret password from your director is incorect!");
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
            }

        }catch(const std::exception &ex){
            QMessageBox::warning(this, "Error due to input data :(", "Some fields are empty, please fill them all!!!");
            qWarning() << "Exception in inputing data: " << ex.what();
        }
    }
}
bool SignUpWindow::onUserRoleChanged1()
{
    const QString selectedRole = ui->roleCB->currentText();
    return (selectedRole == "Manager");
}

bool SignUpWindow::checkFieldsUser()
{
    bool check = false;
    if(ui->surnameLE->text().isEmpty() || ui->firstNameLE->text().isEmpty() ||ui->passwordLE->text().isEmpty() ||
        ui->confirmPasswordLE->text().isEmpty() || ui->emailLE->text().isEmpty() || ui->passwordLE->text().isEmpty() ||
        ui->confirmPasswordLE->text().isEmpty() || ui->loginLE->text().isEmpty() || ui->secretQuestionLE->text().isEmpty() ||
        ui->answerToSecretQuestionLE->text().isEmpty() || ui->phoneNumberLE->text().isEmpty() || ui->middleNameLE->text().isEmpty()){
        throw std::runtime_error("Error in inputing data about Manager:( some fields are empty");
        check = false;
    }
    else check = true;
    return check;
}

bool SignUpWindow::checkFieldsAdmin()
{
     bool check = false;
    if(ui->secretPasswordLE->text().isEmpty() || ui->surnameLE->text().isEmpty() || ui->firstNameLE->text().isEmpty()|| ui->phoneNumberLE->text().isEmpty() ||
         ui->middleNameLE->text().isEmpty() ||ui->passwordLE->text().isEmpty() ||
        ui->confirmPasswordLE->text().isEmpty() || ui->emailLE->text().isEmpty() ||
        ui->loginLE->text().isEmpty() || ui->secretQuestionLE->text().isEmpty() ||
        ui->answerToSecretQuestionLE->text().isEmpty()){
        throw std::runtime_error("Error in inputing data about Admin:( some fields are empty");
        check = false;
     }
    else check = true;
    return check;
}

