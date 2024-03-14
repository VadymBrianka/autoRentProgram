#include "signinwindow.h"
#include "ui_signinwindow.h"

SignInWindow::SignInWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
    this->setWindowTitle("Sign in");
    ui->passwordLE->setEchoMode(QLineEdit::Password);
    connect(ui->showPasswordCheckBox, &QCheckBox::stateChanged, this, &SignInWindow::onShowPasswordChanged);
}

SignInWindow::~SignInWindow()
{
    delete ui;
}

void SignInWindow::on_forgotPasswordButton_clicked()
{
    ForgotPasswordWindow *forgotPasswordWindow = new ForgotPasswordWindow();
    connect(forgotPasswordWindow, &ForgotPasswordWindow::closed, this, &SignInWindow::onDialog2Closed);
    forgotPasswordWindow->setModal(true);
    forgotPasswordWindow->show();
    hide();
    ui->passwordLE->clear();
}

void SignInWindow::onShowPasswordChanged(int state)
{
    if (state == Qt::Checked) {
        ui->passwordLE->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordLE->setEchoMode(QLineEdit::Password);
    }
}

void SignInWindow::onDialog1Closed()
{
    emit closed();
}

void SignInWindow::onDialog2Closed()
{
    show();
}

void SignInWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}


void SignInWindow::on_signInButton_clicked()
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    login = ui->loginLE->text();
    password = ui->passwordLE->text();
    QByteArray bytesi = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString oute = QString(bytesi.toHex());

    if (checkFields()) {
        // Manager manager;
        // Admin admin;
        // manager.setLogin(login.toStdString());
        // manager.setPassword(oute.toStdString());
        // admin.setLogin(login.toStdString());
        // admin.setPassword(oute.toStdString());
        QString queryStr = QString("SELECT login, password FROM Managers WHERE login = '%1' AND password = '%2';")
                               .arg(login.toStdString().c_str())
                               .arg(oute.toStdString().c_str());
        QSqlQuery query;
        query.exec(queryStr);

        QString queryStr2 = QString("SELECT login, password FROM Admins WHERE login = '%1' AND password = '%2';")
                               .arg(login.toStdString().c_str())
                               .arg(oute.toStdString().c_str());
        QSqlQuery query2;
        query2.exec(queryStr2);

        if(query.next()){
            int currentManagerId;
            QString queryId = QString("SELECT manager_id FROM Managers WHERE login = '%1' AND password = '%2';")
                                  .arg(login.toStdString().c_str())
                                  .arg(oute.toStdString().c_str());
            QSqlQuery id;
            id.exec(queryId);
            if(id.next()){currentManagerId = id.value(0).toInt();
                QString queryStatus = QString("SELECT status FROM Managers WHERE login = '%1';")
                                      .arg(login.toStdString().c_str());
                QSqlQuery status;
                status.exec(queryStatus);
                if (status.next()) {
                    QString statusValue = status.value(0).toString();
                    if (statusValue == "VERIFICATED") {
                        HomeManager *homeWindow = new HomeManager(currentManagerId, 2);
                        connect(homeWindow, &HomeManager::closed, this, &SignInWindow::onDialog1Closed);
                        homeWindow->setModal(true);
                        homeWindow->show();
                        hide();
                    } else {
                        QMessageBox::warning(this, "Error:(", "Your account is not activated!");
                    }
                } else {
                    QMessageBox::warning(this, "Error:(", "Failed to retrieve status!");
                }
            }
        }
        else {
            if(query2.next()){
                int currentAdminId;
                QString queryId = QString("SELECT admin_id FROM Admins WHERE login = '%1' AND password = '%2';")
                                      .arg(login.toStdString().c_str())
                                      .arg(oute.toStdString().c_str());
                QSqlQuery id;
                id.exec(queryId);
                if(id.next()){currentAdminId = id.value(0).toInt();
                    HomeAdmin *homeAdminWindow = new HomeAdmin(currentAdminId, 1);
                    connect(homeAdminWindow, &HomeAdmin::closed, this, &SignInWindow::onDialog1Closed);
                    homeAdminWindow->setModal(true);
                    homeAdminWindow->show();
                    hide();
                }
            }else{
                QMessageBox::warning(this, "Error due to input data :(", "Invalid login or password!");
            }
        }
    }
    else{
        QMessageBox::warning(this, "Error due to input data :(", "Some fields are empty, please fill them all!!!");
    }
}

bool SignInWindow::checkFields()
{
    bool check = false;
    if(ui->loginLE->text().isEmpty() || ui->passwordLE->text().isEmpty()){
        check = false;
    }
    else check = true;
    return check;
}

