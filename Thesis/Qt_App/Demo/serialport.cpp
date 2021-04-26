#include "serialport.h"
#include <QMessageBox>
#include <QWidget>
#include <QtDebug>

SerialPort::SerialPort()
{
    serial = new QSerialPort(this);
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    openSerialPort();
}

void SerialPort::openSerialPort()
{
    serial->setPortName("COM5");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        showStatusMessage("Connected");
    } else {
        showStatusMessage("No connection");
    }
}

void SerialPort::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();

    showStatusMessage("Disconnected");
}

void SerialPort::readData()
{
   QByteArray data = serial->readAll();
   qDebug() << data;
}

void SerialPort::writeData(const QByteArray &data)
{
    serial->write(data);
}

void SerialPort::showStatusMessage(const QString &message)
{
    qDebug() << message;
}
