#include "forgotpasswordwindow.h"
#include "ui_forgotpasswordwindow.h"
ForgotPasswordWindow::ForgotPasswordWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgotPasswordWindow)
{
    ui->setupUi(this);
    ui->checkSecretQuestion->hide();
    ui->newPassword->hide();
    ui->passwordLE->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordLE->setEchoMode(QLineEdit::Password);
    connect(ui->showPasswordCheckBox, &QCheckBox::stateChanged, this, &ForgotPasswordWindow::onShowPasswordChanged);
    this->setWindowTitle("Forgot password");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
}

ForgotPasswordWindow::~ForgotPasswordWindow()
{
    delete ui;
}

void ForgotPasswordWindow::on_resetPasswordButton_clicked()
{
    answer = ui->answerLE->text();
    QByteArray bytesAns = QCryptographicHash::hash(answer.toUtf8(), QCryptographicHash::Sha256);
    QString outAns = QString(bytesAns.toHex());

    QString queryStr = QString("SELECT login, password FROM Managers WHERE login = '%1' AND answer = '%2';")
                           .arg(login.toStdString().c_str())
                           .arg(outAns.toStdString().c_str());
    QSqlQuery query;
    query.exec(queryStr);

    QString queryStr2 = QString("SELECT login, password FROM Admins WHERE login = '%1' AND answer = '%2';")
                            .arg(login.toStdString().c_str())
                            .arg(outAns.toStdString().c_str());
    QSqlQuery query2;
    query2.exec(queryStr2);

    if(query.next()){
        QString queryId = QString("SELECT manager_id FROM Managers WHERE login = '%1' AND answer = '%2';")
                              .arg(login.toStdString().c_str())
                              .arg(outAns.toStdString().c_str());
        QSqlQuery id;
        id.exec(queryId);
        if(id.next()){
            QMessageBox::information(this, "Success", "Successful!!!");
            ui->checkSecretQuestion->hide();
            ui->newPassword->show();
            this->setWindowTitle("New password");
        }
    }
    else {
        if(query2.next()){
            QString queryId = QString("SELECT admin_id FROM Admins WHERE login = '%1' AND answer = '%2';")
                                  .arg(login.toStdString().c_str())
                                  .arg(outAns.toStdString().c_str());
            QSqlQuery id;
            id.exec(queryId);
            if(id.next()){
                QMessageBox::information(this, "Success", "Successful!!!");
                ui->checkSecretQuestion->hide();
                ui->newPassword->show();
                this->setWindowTitle("New password");
            }
        }else{
            QMessageBox::warning(this, "Error due to input data :(", "Invalid answear!");
        }
    }
}

void ForgotPasswordWindow::onDialogClosed()
{
    emit closed();
    close();
}

void ForgotPasswordWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}


void ForgotPasswordWindow::on_confirmLoginButton_clicked()
{
    login = ui->loginLE->text();
    QString queryStr = QString("SELECT question FROM Managers WHERE login = '%1';")
                           .arg(login.toStdString().c_str());
    QSqlQuery query;
    query.prepare(queryStr);
    QString queryStr2 = QString("SELECT question FROM Admins WHERE login = '%1';")
                            .arg(login.toStdString().c_str());
    QSqlQuery query2;
    query2.prepare(queryStr2);
    if (query.exec()) {
        if (query.next()) {
            QString question = query.value(0).toString();
            ui->questionLB->setText(question);
            ui->checkLogin->hide();
            ui->checkSecretQuestion->show();
        }else{
            if (query2.exec()) {
                if (query2.next()) {
                    QString question = query2.value(0).toString();
                    ui->questionLB->setText(question);
                    ui->checkLogin->hide();
                    ui->checkSecretQuestion->show();
                } else {
                    QMessageBox::warning(this, "Error","Login not found", QMessageBox::Ok);
                }
            }
        }
    }else{
        if (query2.exec()) {
            if (query2.next()) {
                QString question = query2.value(0).toString();
                ui->questionLB->setText(question);
                ui->checkLogin->hide();
                ui->checkSecretQuestion->show();
            } else {
                QMessageBox::warning(this, "Error","Login not found", QMessageBox::Ok);
            }
        }
    }
}

void ForgotPasswordWindow::onShowPasswordChanged(int state)
{
    if (state == Qt::Checked) {
        ui->passwordLE->setEchoMode(QLineEdit::Normal);
        ui->confirmPasswordLE->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordLE->setEchoMode(QLineEdit::Password);
        ui->confirmPasswordLE->setEchoMode(QLineEdit::Password);
    }
}

void ForgotPasswordWindow::on_setNewPasswordButton_clicked()
{
    password = ui->passwordLE->text();

    QByteArray bytesi = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString oute = QString(bytesi.toHex());

    QString queryStr = QString("UPDATE Managers SET password = '%1' WHERE login = '%2'")
                           .arg(oute.toStdString().c_str())
                           .arg(login.toStdString().c_str());
    QSqlQuery query;
    query.prepare(queryStr);
    QString queryStr2 = QString("UPDATE Admins SET password = '%1' WHERE login = '%2'")
                           .arg(oute.toStdString().c_str())
                           .arg(login.toStdString().c_str());
    QSqlQuery query2;
    query2.prepare(queryStr2);
    if(query.exec() && query.numRowsAffected() > 0){
        QMessageBox::about(this, "Password changed", login + ", your password was changed successfully!");
        this->close();
    }
    else {
        if(query2.exec() && query2.numRowsAffected() > 0){
            QMessageBox::about(this, "Password changed", login + ", your password was changed successfully!");
            this->close();
        }
        else {
            QMessageBox::warning(this, "Error", login + ", your password wasn't changed.");
        }
    }
}

