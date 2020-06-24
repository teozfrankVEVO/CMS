#ifndef SUPPLIERWINDOW_H
#define SUPPLIERWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "databasemanager.h"

namespace Ui {
class SupplierWindow;
}

class SupplierWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SupplierWindow(QWidget *parent = nullptr);
    ~SupplierWindow();

private:
    Ui::SupplierWindow *ui;

    DataBaseManager *dbManager;
    QSqlTableModel *sqlTable;

    void setupModel(const QString &tableName, const QStringList &headers);
    void createTableUI();
    void resetTableUI();
    void showAddRecordWindow();
    void deleteWorkerRecord();
};

#endif // SUPPLIERWINDOW_H
