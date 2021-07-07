from PyQt5 import QtCore, QtWidgets, QtSerialPort
from config import Ui_MainWindow

class Dialog(QtWidgets.QDialog):
    def __init__(self, parent=None):
        super(Dialog, self).__init__(parent)
        self.comport = QtWidgets.QComboBox()
        self.baudrate = QtWidgets.QComboBox()
        for info in QtSerialPort.QSerialPortInfo.availablePorts():
            self.portname_comboBox.addItem(info.portName())
        self.setFixedSize(self.sizeHint())
    def get_results(self):
        return self.comport.currentText(), self.baudrate.currentData()

class Connection(QtWidgets.QFrame):
    def __init__(self, parent=None):
        super(Connection, self).__init__(parent)
        
    def get_results(self):
        return self.comport.currentText(), self.baudrate.currentData()

class MainWindow(QtWidgets.QMainWindow,Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.setupUi(self)
        self.lcd_StartBtn = QtWidgets.QPushButton("Send",clicked=self.send)
        self.lcd_lineEdit = QtWidgets.QLineEdit()
        self.light_lineEdit = QtWidgets.QLineEdit(readOnly=True)
        self.connect = QtWidgets.QPushButton("Open",clicked=self.connectToPort )
        self.close = QtWidgets.QPushButton("Close", clicked=self.disconnectFromPort)
        self.configure_btn = QtWidgets.QPushButton("Configure",clicked=self.open_dialog)
        self.serial = QtSerialPort.QSerialPort(self,readyRead=self.receive)

    def connection(self):
        connection = Connection()
        if connection.exec_():
            comport, baudrate = connection.get_results()
            self.serial.setPortName(portname)
            self.serial.setBaudRate(baudrate)

    def open_dialog(self):
        dialog = Dialog()
        if dialog.exec_():
            portname, baudrate = dialog.get_results()
            self.serial.setPortName(portname)
            self.serial.setBaudRate(baudrate)
    def receive(self):
        while self.serial.canReadLine():
            text = self.serial.readLine().data().decode()
            text = text.rstrip('\r\n')
            self.light_lineEdit.setText(text)
            print(text)
    def send(self):
        self.serial.write(self.lcd_lineEdit.text().encode())
    def connectToPort(self):
        self.serial.open(QtCore.QIODevice.ReadWrite)
    def disconnectFromPort(self):
        self.serial.close()

if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())