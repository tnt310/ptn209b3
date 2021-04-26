#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSerialPortInfo"
#include "QSerialPort"
#include <QPlainTextEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort *port;

private slots:
    void on_OPENBUTTON_clicked();

    void on_CLOSEBUTTON_clicked();

    void on_UPDATE_clicked();

    void on_bt_refresh_clicked();

//    void data_received();

    void on_SETIP_clicked();

    void on_SETGATEWAY_clicked();

    void on_SETNETMASK_clicked();

    void on_SETMQTT_clicked();

    void on_UPDATE_ID_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
