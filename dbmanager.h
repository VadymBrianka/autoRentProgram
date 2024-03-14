#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QVariantList>
#include <QtSql/QSqlTableModel>
#include "manager.h"
//#include "user.h"
#include "admin.h"
#include "customer.h"
#include "car.h"
#include "deal.h"
class DBManager
{
public:
    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;
    virtual bool insertIntoTableManagers(Manager& manager) = 0;
    virtual bool insertIntoTableAdmins(Admin& admin) = 0;
    virtual bool insertIntoTableCustomers(Customer& customer) = 0;
    virtual bool insertIntoTableCars(Car& car) = 0;
    virtual bool insertIntoTableDeals(Deal& deal) = 0;
};

#endif // DBMANAGER_H
