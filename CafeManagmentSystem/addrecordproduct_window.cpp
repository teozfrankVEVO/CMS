#include "addrecordproduct_window.h"
#include "ui_addrecordproduct_window.h"

#include <QSettings>
#include <QMessageBox>

AddRecordProduct_Window::AddRecordProduct_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddRecordProduct_Window)
{
    ui->setupUi(this);

    connect(ui->btnAccept, &QPushButton::clicked, this, &AddRecordProduct_Window::accept);

    QSettings *settings = new QSettings("MainSettings.ini", QSettings::IniFormat);
    dbManager = new DataBaseManager(settings->value("DBFilePath").toString());
}

AddRecordProduct_Window::~AddRecordProduct_Window()
{
    delete ui;
}

void AddRecordProduct_Window::accept()
{
    QVariantList newRecord;

    newRecord.append(ui->leNumber->text());
    newRecord.append(ui->leName->text());
    newRecord.append(ui->leCount->text());
    newRecord.append(ui->lePrice->text());

    if(dbManager->insertProductRecord(newRecord))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Запись добавлена");
        msgBox.setText("<b>Данные о новом товаре успешно добавлены.\nОбновите список, чтобы увидеть изменение.</b>");
        msgBox.exec();

        this->close();
    }
}


