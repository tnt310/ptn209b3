#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)  // Constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port = new QSerialPort(this);
}

MainWindow::~MainWindow() // Deconstructor
{
    delete ui;
}
void MainWindow::on_OPENBUTTON_clicked() // Open Serial
{
    port->setPortName(ui->COM->currentText());
   // qint32 temp = ui->BAUD->currentText().toUInt();
    port->setBaudRate(ui->BAUD->currentText().toUInt());
    //port->setDataBits(QSerialPort::dataBits(ui->DATABIT->currentText().toUtf8()));
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    if (port->open(QIODevice::ReadWrite)) {
        ui->testing->append("Port Open");
    }else {
        ui->testing->append("Device not open");
    }
}

void MainWindow::on_CLOSEBUTTON_clicked() // Close Serial
{
    ui->testing->clear();
    port->close();
    ui->testing->append("Port Close");
}

void MainWindow::on_bt_refresh_clicked() // Scan Port Serial
{
    ui->testing->clear();
    ui->COM->clear();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
    ui->COM->addItem(serialPortInfo.portName());
    }
}
void MainWindow::on_SETIP_clicked() // Set IP
{
    QString ip = "setip "+ ui->IP->toPlainText() +"\r";
    //QString ip = ui->IP->toPlainText() +"\n";
    port->write(ip.toStdString().c_str());
}
void MainWindow::on_SETNETMASK_clicked() // SET NETMASK
{
    QString net = "setnetmask "+ ui->NETMASK->toPlainText() +"\r";
    port->write(net.toStdString().c_str());
}
void MainWindow::on_SETGATEWAY_clicked() //Set GATEWAY
{
    QString gw = "setgateway "+ ui->GATEWAY->toPlainText() +"\r";
    port->write(gw.toStdString().c_str());
}
void MainWindow::on_SETMQTT_clicked()   // Set MQTT SERVER
{
    QString mqtt = "setmqttip "+ ui->MQTT->toPlainText() +"\r";
    port->write(mqtt.toStdString().c_str());
}

void MainWindow::on_UPDATE_clicked() // Save NETWORK
{
    QString save = "save\r";
    QByteArray update = save.toUtf8();
    port->write(update, update.length());
}

void MainWindow::on_UPDATE_ID_clicked()
{
    QString channel = ui->CHANNEL->currentText();
    QString id = ui->ID_DEVICE->toPlainText();
    QString func = ui->FUNC->currentText();
    QString reg_addr = ui->REG_ADDR->toPlainText();
    QString update = "setchannel "+ channel + " " + id + " " + func + " " + reg_addr + "\r";
    port->write(update.toStdString().c_str());
}
