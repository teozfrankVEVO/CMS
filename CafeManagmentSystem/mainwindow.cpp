#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "godpanel_window.h"
#include "databasemanager.h"
#include "administratorwindow.h"
#include "supplierwindow.h"
#include "waiterpanel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    firstInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::firstInit()
{
    QSettings *settings = new QSettings("MainSettings.ini", QSettings::IniFormat);
    if(settings->contains("DBFilePath"))
    {
        DBPath = settings->value("DBFilePath").toString();
        if(DBPath.isEmpty() != true)
        {
            DB_isSelected = true;
            ui->labStatusDB->setText("БД подключена");
        }
    }


    connect(ui->btnEnter, &QPushButton::clicked, this, &MainWindow::auth);
    connect(ui->actionSelectDB, &QAction::triggered, this, &MainWindow::selectDB);
}

void MainWindow::auth()
{
    if(DB_isSelected)
    {
        DataBaseManager *dbManager = new DataBaseManager(DBPath);
        if(dbManager->connect())
        {
            QString login = ui->leLogin->text();
            QString password = ui->lePassword->text();

            Positions pos = dbManager->getAuth(login, password);

            if(pos == Positions::GOD)
            {
                GodPanel_window *godPanel = new GodPanel_window();
                godPanel->show();
                this->hide();
            }

            else if(pos == Positions::NONE)
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Ошибка аутентификации");
                msgBox.setText("<b>Неверный логин или пароль.</b>");
                msgBox.exec();
            }

            else if(pos == Positions::ADMINISTRATOR)
            {
                AdministratorWindow *admWin = new AdministratorWindow();
                admWin->setWindowTitle("Панель администратора");
                admWin->show();
                this->hide();
            }

            else if(pos == Positions::WAITER)
            {
                WaiterPanel *waiterWin = new WaiterPanel();
                waiterWin->setWindowTitle("Панель официанта");
                waiterWin->show();
                this->hide();
            }

            else if(pos == Positions::SUPPLIER)
            {
                SupplierWindow *supplWin = new SupplierWindow();
                supplWin->setWindowTitle("Панель снабжения");
                supplWin->show();
                this->hide();
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка подключения к БД");
            msgBox.setText("<b>Не удалось подключиться к БД.</b>");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка доступа к БД");
        msgBox.setText("<b>База данных не выбрана.</b>");
        msgBox.exec();
        selectDB();
    }
}

void MainWindow::selectDB()
{
    DBPath = QFileDialog::getOpenFileName(this, tr("Выбрать файл БД"), "", tr("AccessDB (*.mdb)"));
    if(DBPath.isEmpty() != true)
    {
        DB_isSelected = true;
        ui->labStatusDB->setText("БД подключена");

        QSettings *settings = new QSettings("MainSettings.ini", QSettings::IniFormat);

        settings->setValue("DBFilePath", DBPath);
        settings->sync();
    }
}
