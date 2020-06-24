#ifndef ADMINISTRATORWINDOW_H
#define ADMINISTRATORWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "databasemanager.h"


namespace Ui {
class AdministratorWindow;
}

class AdministratorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorWindow(QWidget *parent = nullptr);
    ~AdministratorWindow();

private:
    Ui::AdministratorWindow *ui;

    DataBaseManager *dbManager;
    QSqlTableModel *sqlTable;

    void setupModel(const QString &tableName, const QStringList &headers);
    void createTableUI();
    void resetTableUI();
    void showAddRecordWindow();
    void deleteWorkerRecord();
};

#endif // ADMINISTRATORWINDOW_H
