#ifndef ADDRECORDWORKER_WINDOW_H
#define ADDRECORDWORKER_WINDOW_H

#include <QMainWindow>
#include "databasemanager.h"

namespace Ui {
class AddRecordWorker_window;
}

class AddRecordWorker_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddRecordWorker_window(QWidget *parent = nullptr);
    ~AddRecordWorker_window();

private:
    Ui::AddRecordWorker_window *ui;

    DataBaseManager *dbManager;

    void accept();
};

#endif // ADDRECORDWORKER_WINDOW_H
