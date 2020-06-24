#include "databasemanager.h"

#include <QSqlQuery>
#include <QVariant>

#include <QDebug>
#include <QSqlError>

DataBaseManager::DataBaseManager(QString DBPath)
{
    this->fullPath = DBPath;
}

bool DataBaseManager::connect()
{
    QString dataBaseName = "Driver={Microsoft Access Driver (*.mdb)};;DBQ=" + fullPath;
        db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("localhost");
        db.setDatabaseName(dataBaseName);
        db.setUserName("root");
        if(db.open())
        {
            return true;
        }
        else
        {
            return false;
        }
}

Positions DataBaseManager::getAuth(QString login, QString password)
{
    QSqlQuery query;
    QString textQuery = "SELECT " TABLE_WORKERS_POSITION " FROM " TABLE_WORKERS " WHERE Login = '" + login + "' AND Password = '" + password +"'";

    query.exec(textQuery);

    while(query.next())
    {
        if(query.value(0).toString() == "GOD")
        {
            return Positions::GOD;
        }

        else if(query.value(0).toString() == "Администратор")
        {
            return Positions::ADMINISTRATOR;
        }

        else if(query.value(0).toString() == "Официант")
        {
            return Positions::WAITER;
        }

        else if(query.value(0).toString() == "Снабженец")
        {
            return Positions::SUPPLIER;
        }
    }

    return Positions::NONE;
}

bool DataBaseManager::insertWorkerRecord(const QVariantList &newRecord)
{
    QSqlQuery query;

//    query.prepare("INSERT INTO " TABLE_WORKERS " ( " TABLE_WORKERS_NUMBER ", "
//                  TABLE_WORKERS_FULLNAME ", " TABLE_WORKERS_POSITION ", "
//                  TABLE_WORKERS_LOGIN ", " TABLE_WORKERS_PASSWORD ") "
//                  "VALUES (:Number, :FullName, :Position, :Login, :Password )");

    query.prepare("INSERT INTO Workers VALUES (:Number, :FullName, :Position, :Login, :Password)");

    query.bindValue(":Number", newRecord[0].toInt());
    query.bindValue(":FullName", newRecord[1].toString());
    query.bindValue(":Position", newRecord[2].toString());
    query.bindValue(":Login", newRecord[3].toString());
    query.bindValue(":Password", newRecord[4].toString());

    if(!query.exec())
    {
        qDebug() << "Error insert";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

bool DataBaseManager::deleteWorkerRecord(QString Number)
{
    QSqlQuery query;

    query.prepare("DELETE FROM " TABLE_WORKERS " WHERE Number= " + Number);
    if(!query.exec())
    {
        qDebug() << "Error delete";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

bool DataBaseManager::deleteProductRecord(QString Number)
{
    QSqlQuery query;

    query.prepare("DELETE FROM " TABLE_PRODUCTS " WHERE Number= " + Number);
    if(!query.exec())
    {
        qDebug() << "Error delete";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

bool DataBaseManager::insertProductRecord(const QVariantList &newRecord)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Products VALUES (:Number, :Name, :Count, :Price)");

    query.bindValue(":Number", newRecord[0].toInt());
    query.bindValue(":Name", newRecord[1].toString());
    query.bindValue(":Count", newRecord[2].toInt());
    query.bindValue(":Price", newRecord[3].toDouble());

    if(!query.exec())
    {
        qDebug() << "Error insert";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

void DataBaseManager::changeProductCount(QString Number, int newCount)
{
    QSqlQuery query;

    query.prepare("UPDATE " TABLE_PRODUCTS " SET Count = :Count WHERE NUMBER = :Number");
    query.bindValue(":Count", newCount);
    query.bindValue(":Number", Number.toInt());

    query.exec();
}
