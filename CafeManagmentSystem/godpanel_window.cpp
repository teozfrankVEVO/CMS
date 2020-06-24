#include "godpanel_window.h"
#include "ui_godpanel_window.h"
#include "administratorwindow.h"
#include "supplierwindow.h"
#include "waiterpanel.h"

#include <QDebug>

GodPanel_window::GodPanel_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GodPanel_window)
{
    ui->setupUi(this);
    this->setWindowTitle("Панель бога");

    firstInit();
}

GodPanel_window::~GodPanel_window()
{
    delete ui;
}

void GodPanel_window::firstInit()
{
    connect(ui->btnSelectAdministratorMode, &QPushButton::clicked, this, &GodPanel_window::openAdministratorPanel);
    connect(ui->btnSelectSupplierMode, &QPushButton::clicked, this, &GodPanel_window::openSupplierPanel);
    connect(ui->btnSelectWaiterMode, &QPushButton::clicked, this, &GodPanel_window::openWaiterPanel);
}

void GodPanel_window::openAdministratorPanel()
{
    AdministratorWindow *admWin = new AdministratorWindow();
    admWin->setWindowTitle("Панель администратора");
    admWin->show();
    this->hide();
}

void GodPanel_window::openSupplierPanel()
{
    SupplierWindow *supWin = new SupplierWindow();
    supWin->setWindowTitle("Панель снабжения");
    supWin->show();
    this->hide();
}

void GodPanel_window::openWaiterPanel()
{
    WaiterPanel *waiterWin = new WaiterPanel();
    waiterWin->setWindowTitle("Панель официанта");
    waiterWin->show();
    this->hide();
}
