#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QVariantList>

#define TABLE_WORKERS "Workers"
#define TABLE_WORKERS_NUMBER "Number"
#define TABLE_WORKERS_FULLNAME "FullName"
#define TABLE_WORKERS_POSITION "Position"
#define TABLE_WORKERS_LOGIN "Login"
#define TABLE_WORKERS_PASSWORD "Password"

#define TABLE_PRODUCTS "Products"
#define TABLE_PRODUCTS_NUMBER "Number"
#define TABLE_PRODUCTS_NAME "Name"
#define TABLE_PRODUCTS_COUNT "Count"
#define TABLE_PRODUCTS_PRICE "Price"

enum Positions {WAITER, ADMINISTRATOR, SUPPLIER, GOD, NONE};

class DataBaseManager
{
public:
    DataBaseManager(QString DBPath);
    bool connect();

    Positions getAuth(QString login, QString password);
    bool insertWorkerRecord(const QVariantList &newRecord);
    bool deleteWorkerRecord(QString Number);
    bool insertProductRecord(const QVariantList &newRecord);
    bool deleteProductRecord(QString Number);
    void changeProductCount(QString Number, int newCount);

private:
    QSqlDatabase db;
    QString fullPath;

};



#endif // DATABASEMANAGER_H
