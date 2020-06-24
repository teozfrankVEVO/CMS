#ifndef WAITERPANEL_H
#define WAITERPANEL_H

#include <QMainWindow>
#include <QSqlTableModel>

#include "databasemanager.h"

namespace Ui {
class WaiterPanel;
}

class WaiterPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit WaiterPanel(QWidget *parent = nullptr);
    ~WaiterPanel();

private:
    Ui::WaiterPanel *ui;

    DataBaseManager *dbManager;
    QSqlTableModel *sqlTable;

    void setupModel(const QString &tableName, const QStringList &headers);
    void createTableUI();
    void resetTableUI();
    void sellProduct();


};

#endif // WAITERPANEL_H
