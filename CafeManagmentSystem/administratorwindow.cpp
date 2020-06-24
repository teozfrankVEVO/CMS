#include "administratorwindow.h"
#include "ui_administratorwindow.h"
#include "addrecordworker_window.h"


#include <QSettings>

AdministratorWindow::AdministratorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorWindow)
{
    ui->setupUi(this);

    QSettings *settings = new QSettings("MainSettings.ini", QSettings::IniFormat);
    dbManager = new DataBaseManager(settings->value("DBFilePath").toString());
    if(dbManager->connect())
    {
        resetTableUI();
    }

    connect(ui->btnUpdate, &QPushButton::clicked, this, &AdministratorWindow::resetTableUI);
    connect(ui->btnAddRecord, &QPushButton::clicked, this, &AdministratorWindow::showAddRecordWindow);
    connect(ui->btnDelRecord, &QPushButton::clicked, this, &AdministratorWindow::deleteWorkerRecord);
}

AdministratorWindow::~AdministratorWindow()
{
    delete ui;
}

void AdministratorWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    sqlTable = new QSqlTableModel();
    sqlTable->setTable(tableName);

    for(int i = 0, j = 0; i < sqlTable->columnCount(); i++, j++)
    {
        sqlTable->setHeaderData(i, Qt::Horizontal, headers[j]);
    }

    sqlTable->setSort(0, Qt::AscendingOrder);
}

void AdministratorWindow::createTableUI()
{
    ui->tableView->setModel(sqlTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    sqlTable->select();
}

void AdministratorWindow::resetTableUI()
{
    setupModel(TABLE_WORKERS, QStringList() << trUtf8("Number")
               << trUtf8("FullName")
               << trUtf8("Position")
               << trUtf8("Login")
               << trUtf8("Password"));
    createTableUI();
}

void AdministratorWindow::showAddRecordWindow()
{
    AddRecordWorker_window *addRecordWin = new AddRecordWorker_window();
    addRecordWin->setWindowTitle("Добавление записи о работнике");
    addRecordWin->show();
}

void AdministratorWindow::deleteWorkerRecord()
{
    QString Number = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toString();
    dbManager->deleteWorkerRecord(Number);

    resetTableUI();
}
