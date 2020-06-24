#include "addrecordworker_window.h"
#include "ui_addrecordworker_window.h"

#include <QSettings>
#include <QMessageBox>

AddRecordWorker_window::AddRecordWorker_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddRecordWorker_window)
{
    ui->setupUi(this);

    connect(ui->btnAccept, &QPushButton::clicked, this, &AddRecordWorker_window::accept);

    QSettings *settings = new QSettings("MainSettings.ini", QSettings::IniFormat);
    dbManager = new DataBaseManager(settings->value("DBFilePath").toString());
}

AddRecordWorker_window::~AddRecordWorker_window()
{
    delete ui;
}

void AddRecordWorker_window::accept()
{
    QVariantList newRecord;

    newRecord.append(ui->leNumber->text().toInt());
    newRecord.append(ui->leFullName->text());

    if(ui->cbPosition->currentIndex() == 0)
    {
        newRecord.append("Администратор");
    }
    else if(ui->cbPosition->currentIndex() == 1)
    {
        newRecord.append("Снабженец");
    }
    else if(ui->cbPosition->currentIndex() == 2)
    {
        newRecord.append("Официант");
    }

    newRecord.append(ui->leLogin->text());
    newRecord.append(ui->lePassword->text());

    if(dbManager->insertWorkerRecord(newRecord))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Запись добавлена");
        msgBox.setText("<b>Данные о новом работнике успешно добавлены.\nОбновите список, чтобы увидеть изменение.</b>");
        msgBox.exec();

        this->close();
    }
}
