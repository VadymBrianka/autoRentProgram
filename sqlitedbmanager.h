#ifndef SQLITEDBMANAGER_H
#define SQLITEDBMANAGER_H

#include <QtSql/QSqlTableModel>
#include <QVariantList>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <dbmanager.h>

#define DATABASE_HOSTNAME   "localname"
#define DATABASE_NAME       "Brianka.sqlite"

#define TABLE_MANAGERS "Managers"
#define TABLE_ADMINS "Admins"
#define TABLE_CUSTOMERS "Customers"
#define TABLE_CARS "Cars"
#define TABLE_DEALS "Deals"
#define TABLE_SURNAME "surname"
#define TABLE_FIRSTNAME "firstName"
#define TABLE_MIDDLENAME "middleName"
#define TABLE_PHONENUMBER "phoneNumber"
#define TABLE_EMAIL "email"
#define TABLE_LOGIN "login"
#define TABLE_PASSWORD "password"
#define TABLE_QUESTION "question"
#define TABLE_ANSWER "answer"
#define TABLE_ROLE "role"
#define TABLE_AGE "age"
#define TABLE_YEARSOFEXPERIENCE "yearsOfExperience"
#define TABLE_STATUS "status"
#define TABLE_ADDRESS "address"
#define TABLE_ITIN "itin"
#define TABLE_BRAND "brand"
#define TABLE_MODEL "model"
#define TABLE_YEAR "year"
#define TABLE_VIN "vin"
#define TABLE_ENGINECAPACITY "engineCapacity"
#define TABLE_NUMBEROFSEATS "numberOfSeats"
#define TABLE_PRICE "price"
#define TABLE_PRICEOFRENTING "priceOfRenting"
#define TABLE_TRUNKVOLUME "trunkVolume"
#define TABLE_RENTSTARTDATE "rentStartDate"
#define TABLE_RENTENDDATE "rentEndDate"
#define TABLE_CHECK "checkColumn"
#define TABLE_PAYMENT "payment"
class SqliteDBManager : public DBManager {

public:
    static SqliteDBManager* getInstance();

    void connectToDataBase();
    QSqlDatabase getDB();
    bool insertIntoTableManagers(Manager& manager);
    bool insertIntoTableAdmins(Admin& admin);
    bool insertIntoTableCustomers(Customer& customer);
    bool insertIntoTableCars(Car& car);
    bool insertIntoTableDeals(Deal& deal);
    QMap<int, QList<QString>> getAllItins();
    QMap<int, QList<QString>> getAllIVins();
private:
    QSqlDatabase db;

    static SqliteDBManager* instance;
    SqliteDBManager();
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();

};

#endif // SQLITEDBMANAGER_H
