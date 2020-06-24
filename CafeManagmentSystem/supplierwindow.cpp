#include "supplierwindow.h"
#include "ui_supplierwindow.h"
#include "addrecordproduct_window.h"

#include <QSettings>

SupplierWindow::SupplierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SupplierWindow)
{
    ui->setupUi(this);

    QSettings *settings = new QSettings("MainSettings.ini", QSettings::IniFormat);
    dbManager = new DataBaseManager(settings->value("DBFilePath").toString());
    if(dbManager->connect())
    {
        resetTableUI();
    }

    connect(ui->btnUpdate, &QPushButton::clicked, this, &SupplierWindow::resetTableUI);
    connect(ui->btnAddProduct, &QPushButton::clicked, this, &SupplierWindow::showAddRecordWindow);
    connect(ui->btnDeleteProduct, &QPushButton::clicked, this, &SupplierWindow::deleteWorkerRecord);
}

SupplierWindow::~SupplierWindow()
{
    delete ui;
}

void SupplierWindow::showAddRecordWindow()
{
    AddRecordProduct_Window *addRecordWin = new AddRecordProduct_Window();
    addRecordWin->setWindowTitle("Добавление записи о товаре");
    addRecordWin->show();
}

void SupplierWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    sqlTable = new QSqlTableModel();
    sqlTable->setTable(tableName);

    for(int i = 0, j = 0; i < sqlTable->columnCount(); i++, j++)
    {
        sqlTable->setHeaderData(i, Qt::Horizontal, headers[j]);
    }

    sqlTable->setSort(0, Qt::AscendingOrder);
}

void SupplierWindow::createTableUI()
{
    ui->tableView->setModel(sqlTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    sqlTable->select();
}

void SupplierWindow::resetTableUI()
{
    setupModel(TABLE_PRODUCTS, QStringList() << trUtf8("Number")
               << trUtf8("Name")
               << trUtf8("Count")
               << trUtf8("Price"));
    createTableUI();
}

void SupplierWindow::deleteWorkerRecord()
{
    QString Number = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toString();
    dbManager->deleteProductRecord(Number);

    resetTableUI();
}




