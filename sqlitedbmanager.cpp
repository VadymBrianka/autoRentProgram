#include "sqlitedbmanager.h"

#include <QObject>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>

SqliteDBManager* SqliteDBManager::instance = nullptr;

SqliteDBManager::SqliteDBManager(){

}

SqliteDBManager* SqliteDBManager::getInstance()
{
    if(instance == nullptr){
        instance = new SqliteDBManager();
    }
    return instance;
}

void SqliteDBManager::connectToDataBase()
{
    try{
        if (QFile(DATABASE_NAME).exists()) this->openDataBase();
        else this->restoreDataBase();
    }catch(const std::exception &ex){throw;}
}

QSqlDatabase SqliteDBManager::getDB()
{
    return db;
}


bool SqliteDBManager::restoreDataBase()
{
    try {
        if (this->openDataBase()) {
            if (!this->createTables()) {
                return false;
            } else {
                return true;
            }
        } else {
            throw std::runtime_error("Failed to restore database");
        }
    } catch(const std::exception &ex) {
        throw;
    }
}

bool SqliteDBManager::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);

    if (!db.isValid()) {
        qCritical() << "Недійсні параметри підключення до бази даних.";
        return false;
    }

    if (db.open()) {
        return true;
    } else {
        qCritical() << "Не вдалося відкрити базу даних:" << db.lastError().text();
            return false;
    }
}

void SqliteDBManager::closeDataBase()
{
    db.close();
}

bool SqliteDBManager::createTables()
{
    QSqlQuery query, query2, query3, query4, query5;
    bool success = true;

    if (!query.exec("CREATE TABLE " TABLE_MANAGERS "("
                    "manager_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_LOGIN " TEXT NOT NULL, "
                    TABLE_QUESTION " TEXT NOT NULL, "
                    TABLE_ANSWER " TEXT NOT NULL, "
                    TABLE_PASSWORD " TEXT NOT NULL, "
                    TABLE_SURNAME " TEXT NOT NULL,"
                    TABLE_FIRSTNAME " TEXT NOT NULL,"
                    TABLE_MIDDLENAME " TEXT NOT NULL,"
                    TABLE_PHONENUMBER " TEXT,"
                    TABLE_EMAIL " TEXT NOT NULL,"
                    TABLE_ROLE " TEXT NOT NULL,"
                    TABLE_STATUS " TEXT NOT NULL)"))
    {
        success = false;
    }

    if (!query2.exec("CREATE TABLE " TABLE_ADMINS "("
                    "admin_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_LOGIN " TEXT NOT NULL, "
                    TABLE_QUESTION " TEXT NOT NULL, "
                    TABLE_ANSWER " TEXT NOT NULL, "
                    TABLE_PASSWORD " TEXT NOT NULL, "
                    TABLE_SURNAME " TEXT NOT NULL,"
                    TABLE_FIRSTNAME " TEXT NOT NULL,"
                    TABLE_MIDDLENAME " TEXT NOT NULL,"
                    TABLE_PHONENUMBER " TEXT,"
                    TABLE_EMAIL " TEXT NOT NULL,"
                    TABLE_ROLE " TEXT NOT NULL,"
                    TABLE_STATUS " TEXT NOT NULL)"))
    {
        success = false;
    }

    if (!query3.exec("CREATE TABLE " TABLE_CUSTOMERS "("
                     "customer_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     TABLE_SURNAME " TEXT NOT NULL,"
                     TABLE_FIRSTNAME " TEXT NOT NULL,"
                     TABLE_MIDDLENAME " TEXT NOT NULL,"
                     TABLE_AGE " INT NOT NULL,"
                     TABLE_PHONENUMBER " TEXT NOT NULL,"
                     TABLE_EMAIL " TEXT NOT NULL,"
                     TABLE_YEARSOFEXPERIENCE " INT,"
                     TABLE_ITIN " TEXT NOT NULL,"
                     TABLE_ADDRESS " TEXT NOT NULL,"
                     TABLE_STATUS " TEXT NOT NULL)"))
    {
        success = false;
    }

    if (!query4.exec("CREATE TABLE " TABLE_CARS "("
                     "car_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     TABLE_BRAND " TEXT NOT NULL,"
                     TABLE_MODEL " TEXT NOT NULL,"
                     TABLE_YEAR " INT NOT NULL,"
                     TABLE_VIN " TEXT NOT NULL,"
                     TABLE_ENGINECAPACITY " FLOAT(2,1) NOT NULL,"
                     TABLE_NUMBEROFSEATS " INT NOT NULL,"
                     TABLE_TRUNKVOLUME " INT,"
                     TABLE_PRICE " INT NOT NULL,"
                     TABLE_PRICEOFRENTING " INT NOT NULL,"
                     TABLE_STATUS " TEXT NOT NULL)"))
    {
        success = false;
    }

    if (!query5.exec("CREATE TABLE " TABLE_DEALS "("
                     "deal_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     TABLE_ITIN " TEXT NOT NULL,"
                     TABLE_VIN " TEXT NOT NULL,"
                     TABLE_RENTSTARTDATE " DATE,"
                     TABLE_RENTENDDATE " DATE,"
                     TABLE_STATUS " TEXT NOT NULL,"
                     TABLE_CHECK " TEXT NOT NULL,"
                     TABLE_PAYMENT " TEXT NOT NULL,"
                     "FOREIGN KEY (" TABLE_ITIN ") REFERENCES " TABLE_CUSTOMERS "(" TABLE_ITIN ") ON DELETE CASCADE ON UPDATE CASCADE,"
                     "FOREIGN KEY (" TABLE_VIN ") REFERENCES " TABLE_CARS "(" TABLE_VIN ") ON DELETE CASCADE ON UPDATE CASCADE)"))
    {
        success = false;
    }
    if (!success)
    {
        throw std::runtime_error("Error in creating tables");
    }

    return success;
}

QMap<int, QList<QString>> SqliteDBManager::getAllItins()
{
    QMap<int, QList<QString>> itinsMap;
    QSqlQuery query("SELECT customer_id, surname, firstName, middleName, itin FROM Customers WHERE status = 'Active'");

    if (query.exec()) {
        while (query.next()) {
            int customerId = query.value("customer_id").toInt();
            QString customerSurname = query.value("surname").toString();
            QString customerFirstName = query.value("firstName").toString();
            QString customerMiddleName = query.value("middleName").toString();
            QString customerItin = query.value("itin").toString();
            if (itinsMap.contains(customerId)) {
                itinsMap[customerId].append(customerSurname);
                itinsMap[customerId].append(customerFirstName);
                itinsMap[customerId].append(customerMiddleName);
                itinsMap[customerId].append(customerItin);
            } else {
                QList<QString> values;
                values.append(customerSurname);
                values.append(customerFirstName);
                values.append(customerMiddleName);
                values.append(customerItin);
                itinsMap.insert(customerId, values);
            }
        }
    } else {
        qDebug() << "Error retrieving customers from the database:" << query.lastError().text();
    }

    return itinsMap;
}

QMap<int, QList<QString>> SqliteDBManager::getAllIVins()
{
   QMap<int, QList<QString>> itinsMap;
    QSqlQuery query("SELECT car_id, brand, model, year, vin FROM Cars WHERE status = 'available'");

    if (query.exec()) {
        while (query.next()) {
            int carId = query.value("car_id").toInt();
            QString carBrand = query.value("brand").toString();
            QString carModel = query.value("model").toString();
            int carYear = query.value("year").toInt();
            QString carYearString = QString::number(carYear);
            QString carVin = query.value("vin").toString();
            if (itinsMap.contains(carId)) {
                itinsMap[carId].append(carBrand);
                itinsMap[carId].append(carModel);
                itinsMap[carId].append(carYearString);
                itinsMap[carId].append(carVin);
            } else {
                QList<QString> values;
                values.append(carBrand);
                values.append(carModel);
                values.append(carYearString);
                values.append(carVin);
                itinsMap.insert(carId, values);
            }
        }
    } else {
        qDebug() << "Error retrieving cars from the database:" << query.lastError().text();
    }

    return itinsMap;
}


bool SqliteDBManager::insertIntoTableManagers(Manager& manager)
{
    QSqlQuery query;
    qInfo() << TABLE_MANAGERS<<" table\n";
    query.prepare("INSERT INTO " TABLE_MANAGERS " ("
                  TABLE_LOGIN ", "
                  TABLE_QUESTION ", "
                  TABLE_ANSWER ", "
                  TABLE_PASSWORD ", "
                  TABLE_SURNAME ", "
                  TABLE_FIRSTNAME ", "
                  TABLE_MIDDLENAME ", "
                  TABLE_PHONENUMBER ", "
                  TABLE_EMAIL ","
                  TABLE_ROLE ","
                  TABLE_STATUS ")"
                  "VALUES(:login, :question, :answer, :password, :surname, :firstName, :middleName, :phoneNumber, :email, :role, :status)");
    query.bindValue(":login", QString::fromStdString(manager.getLogin()));
    query.bindValue(":password", QString::fromStdString(manager.getPassword()));
    query.bindValue(":question", QString::fromStdString(manager.getSecretQuestion()));
    query.bindValue(":answer", QString::fromStdString(manager.getAnswerToSecretQuestion()));
    query.bindValue(":surname", QString::fromStdString(manager.getSurname()));
    query.bindValue(":firstName", QString::fromStdString(manager.getFirstName()));
    query.bindValue(":middleName", QString::fromStdString(manager.getMiddleName()));
    query.bindValue(":phoneNumber", QString::fromStdString(manager.getPhoneNumber()));
    query.bindValue(":email", QString::fromStdString(manager.getEmail()));
    query.bindValue(":role", QString::fromStdString(manager.getRole()));
    query.bindValue(":status", QString::fromStdString(manager.getStatus()));

    if (!query.exec()) {
        throw std::runtime_error("Error inserting into Managers` table");
        return false;
    } else
        return true;
}

bool SqliteDBManager::insertIntoTableAdmins(Admin& admin)
{
    QSqlQuery query;
    qInfo() << TABLE_ADMINS<<" table\n";
    query.prepare("INSERT INTO " TABLE_ADMINS " ("
                  TABLE_LOGIN ", "
                  TABLE_QUESTION ", "
                  TABLE_ANSWER ", "
                  TABLE_PASSWORD ", "
                  TABLE_SURNAME ", "
                  TABLE_FIRSTNAME ", "
                  TABLE_MIDDLENAME ", "
                  TABLE_PHONENUMBER ", "
                  TABLE_EMAIL ","
                  TABLE_ROLE ","
                  TABLE_STATUS ")"
                  "VALUES(:login, :question, :answer, :password, :surname, :firstName, :middleName, :phoneNumber, :email, :role, :status)");
    query.bindValue(":login", QString::fromStdString(admin.getLogin()));
    query.bindValue(":password", QString::fromStdString(admin.getPassword()));
    query.bindValue(":question", QString::fromStdString(admin.getSecretQuestion()));
    query.bindValue(":answer", QString::fromStdString(admin.getAnswerToSecretQuestion()));
    query.bindValue(":surname", QString::fromStdString(admin.getSurname()));
    query.bindValue(":firstName", QString::fromStdString(admin.getFirstName()));
    query.bindValue(":middleName", QString::fromStdString(admin.getMiddleName()));
    query.bindValue(":phoneNumber", QString::fromStdString(admin.getPhoneNumber()));
    query.bindValue(":email", QString::fromStdString(admin.getEmail()));
    query.bindValue(":role", QString::fromStdString(admin.getRole()));
    query.bindValue(":status", QString::fromStdString(admin.getStatus()));

    if (!query.exec()) {
        throw std::runtime_error("Error inserting into Admins` table");
        return false;
    } else
        return true;
}

bool SqliteDBManager::insertIntoTableCustomers(Customer &customer)
{
    QSqlQuery query;
    qInfo() << TABLE_CUSTOMERS<<" table\n";
    query.prepare("INSERT INTO " TABLE_CUSTOMERS " ("
                  TABLE_SURNAME ", "
                  TABLE_FIRSTNAME ", "
                  TABLE_MIDDLENAME ", "
                  TABLE_AGE ","
                  TABLE_PHONENUMBER ", "
                  TABLE_EMAIL ","
                  TABLE_YEARSOFEXPERIENCE ","
                  TABLE_ADDRESS ","
                  TABLE_ITIN ","
                  TABLE_STATUS ")"
                  "VALUES(:surname, :firstName, :middleName, :age, :phoneNumber, :email, :yearsOfExperience, :address, :itin, :status)");
    query.bindValue(":surname", QString::fromStdString(customer.getSurname()));
    query.bindValue(":firstName", QString::fromStdString(customer.getFirstName()));
    query.bindValue(":middleName", QString::fromStdString(customer.getMiddleName()));
    query.bindValue(":age", customer.getAge());
    query.bindValue(":phoneNumber", QString::fromStdString(customer.getPhoneNumber()));
    query.bindValue(":email", QString::fromStdString(customer.getEmail()));
    query.bindValue(":yearsOfExperience", customer.getYearsOfExperience());
    query.bindValue(":address", QString::fromStdString(customer.getAddress()));
    query.bindValue(":itin", QString::fromStdString(customer.getITIN()));
    query.bindValue(":status", QString::fromStdString(customer.getStatus()));
    if (!query.exec()) {
        throw std::runtime_error("Error inserting into Customers` table");
        return false;
    } else
        return true;
}

bool SqliteDBManager::insertIntoTableCars(Car &car)
{
    QSqlQuery query;
    qInfo() << TABLE_CARS<<" table\n";
    query.prepare("INSERT INTO " TABLE_CARS " ("
                  TABLE_BRAND ", "
                  TABLE_MODEL ", "
                  TABLE_YEAR ", "
                  TABLE_VIN ","
                  TABLE_ENGINECAPACITY ", "
                  TABLE_NUMBEROFSEATS ","
                  TABLE_TRUNKVOLUME ","
                  TABLE_PRICE ","
                  TABLE_PRICEOFRENTING ","
                  TABLE_STATUS ")"
                  "VALUES(:brand, :model, :year, :vin, :engineCapacity, :numberOfSeats, :trunkVolume, :price, :priceOfRenting, :status)");
    query.bindValue(":brand", QString::fromStdString(car.getBrand()));
    query.bindValue(":model", QString::fromStdString(car.getModel()));
    query.bindValue(":year", car.getYear());
    query.bindValue(":vin", QString::fromStdString(car.getVin()));
    query.bindValue(":engineCapacity", car.getEngineCapacity());
    query.bindValue(":numberOfSeats", car.getNumberOfSeats());
    query.bindValue(":trunkVolume", car.getTrunkVolume());
    query.bindValue(":price",car.getPrice());
    query.bindValue(":priceOfRenting",car.getPriceOfRenting());
    query.bindValue(":status",QString::fromStdString(car.getStatus()));
    if (!query.exec()) {
        throw std::runtime_error("Error inserting into Cars` table");
        return false;
    } else
        return true;
}

bool SqliteDBManager::insertIntoTableDeals(Deal &deal)
{
    QSqlQuery query;
    qInfo() << TABLE_DEALS<<" table\n";
    query.prepare("INSERT INTO " TABLE_DEALS " ("
                  TABLE_ITIN ", "
                  TABLE_VIN ", "
                  TABLE_RENTSTARTDATE ", "
                  TABLE_RENTENDDATE ","
                  TABLE_STATUS ","
                  TABLE_CHECK ","
                  TABLE_PAYMENT ")"
                  "VALUES(:itin, :vin, :rentStartDate, :rentEndDate, :status, :checkColumn, :payment)");
    query.bindValue(":itin", QString::fromStdString(deal.getItin()));
    query.bindValue(":vin", QString::fromStdString(deal.getVin()));
    query.bindValue(":rentStartDate", QDate::fromString(QString::fromStdString(deal.getRentStartDate()), "yyyy.MM.dd"));
    query.bindValue(":rentEndDate", QDate::fromString(QString::fromStdString(deal.getRentEndDate()), "yyyy.MM.dd"));
    query.bindValue(":status", QString::fromStdString(deal.getStatus()));
    query.bindValue(":checkColumn", QString::fromStdString(deal.getCheck()));
    query.bindValue(":payment", QString::fromStdString(deal.getPayment()));
    if (!query.exec()) {
        throw std::runtime_error("Error inserting into Deals` table");
        return false;
    } else
        return true;
}

