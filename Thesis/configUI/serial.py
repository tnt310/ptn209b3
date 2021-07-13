from PyQt5 import QtCore, QtWidgets, QtSerialPort
from PyQt5.QtWidgets import QApplication,QMainWindow
from NEWUI.login import Ui_logingateway

class Serial(Ui_logingateway):
    def __init__(self, parent=None):
        super(Serial, self).__init__(parent)
        login = Ui_logingateway()
        login.setupUi(self)
        for info in QtSerialPort.QSerialPortInfo.availablePorts():
            login.comport.addItem(info.portName())
        login.refresh.clicked.connect(self.refresh)

    def refresh(self):
        refresh = Ui_logingateway()
        refresh.setupUi(self)
        for info in QtSerialPort.QSerialPortInfo.availablePorts():
            refresh.comport.addItem(info.portName())
        refresh.refresh.clicked.connect(self.refresh)


# if __name__ == '__main__':
#     import sys
#     app = QtWidgets.QApplication(sys.argv)
#     w = Serial()
#     w.show()
#     sys.exit(app.exec_())