#ifndef ADDRECORDPRODUCT_WINDOW_H
#define ADDRECORDPRODUCT_WINDOW_H

#include <QMainWindow>

#include "databasemanager.h"

namespace Ui {
class AddRecordProduct_Window;
}

class AddRecordProduct_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddRecordProduct_Window(QWidget *parent = nullptr);
    ~AddRecordProduct_Window();

private:
    Ui::AddRecordProduct_Window *ui;

    DataBaseManager *dbManager;

    void accept();
};

#endif // ADDRECORDPRODUCT_WINDOW_H
