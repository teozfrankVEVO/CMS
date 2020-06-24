#ifndef GODPANEL_WINDOW_H
#define GODPANEL_WINDOW_H

#include <QMainWindow>

namespace Ui {
class GodPanel_window;
}

class GodPanel_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit GodPanel_window(QWidget *parent = nullptr);
    ~GodPanel_window();

private:
    Ui::GodPanel_window *ui;

    void firstInit();
    void openAdministratorPanel();
    void openSupplierPanel();
    void openWaiterPanel();
};

#endif // GODPANEL_WINDOW_H
