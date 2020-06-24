#include "waiterpanel.h"
#include "ui_waiterpanel.h"

#include <QSettings>
#include <QDebug>

WaiterPanel::WaiterPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WaiterPanel)
{
    ui->setupUi(this);

    QSettings *settings = new QSettings("MainSettings.ini", QSettings::IniFormat);
    dbManager = new DataBaseManager(settings->value("DBFilePath").toString());
    if(dbManager->connect())
    {
        resetTableUI();
    }

    connect(ui->btnSell, &QPushButton::clicked, this, &WaiterPanel::sellProduct);
}

WaiterPanel::~WaiterPanel()
{
    delete ui;
}

void WaiterPanel::setupModel(const QString &tableName, const QStringList &headers)
{
    sqlTable = new QSqlTableModel();
    sqlTable->setTable(tableName);

    for(int i = 0, j = 0; i < sqlTable->columnCount(); i++, j++)
    {
        sqlTable->setHeaderData(i, Qt::Horizontal, headers[j]);
    }

    sqlTable->setSort(0, Qt::AscendingOrder);
}

void WaiterPanel::createTableUI()
{
    ui->tableView->setModel(sqlTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    sqlTable->select();
}

void WaiterPanel::resetTableUI()
{
    setupModel(TABLE_PRODUCTS, QStringList() << trUtf8("Number")
               << trUtf8("Name")
               << trUtf8("Count")
               << trUtf8("Price"));
    createTableUI();
}

void WaiterPanel::sellProduct()
{
    int count = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 2)).toInt();
    if(count - ui->spinBox->value() > 0)
    {
        QString Number = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toString();
        int newCount = count - ui->spinBox->value();
        dbManager->changeProductCount(Number, newCount);
        resetTableUI();
    }
    else
    {
        qDebug() << "Не хватает";
    }
}
