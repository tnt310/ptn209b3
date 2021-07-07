#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>

class SerialPort : public QObject
{
    Q_OBJECT;

public:
    SerialPort();
    void openSerialPort();
    void closeSerialPort();
    void readData();
    void writeData(const QByteArray &data);
    void showStatusMessage(const QString &message);


private:

    QSerialPort *serial;
    QString m_com;
    QString m_baudRate;
    QString m_dataBits;
    QString m_stopBits;
    QString m_parity;
    QString m_flowControl;
};

#endif // SERIALPORT_H
