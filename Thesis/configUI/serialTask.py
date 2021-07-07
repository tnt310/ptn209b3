from PyQt5 import QtCore, QtWidgets, QtSerialPort
from UI.config import Ui_MainWindow

class SerialThread(QtWidgets.QDialog):
    def __init__(self, parent=None):
        super(Dialog, self).__init__(parent)
        self.portname_comboBox = QtWidgets.QComboBox()
        self.baudrate_comboBox = QtWidgets.QComboBox()

        for info in QtSerialPort.QSerialPortInfo.availablePorts():
            self.portname_comboBox.addItem(info.portName())

        for baudrate in QtSerialPort.QSerialPortInfo.standardBaudRates():
            self.baudrate_comboBox.addItem(str(baudrate), baudrate)

        buttonBox = QtWidgets.QDialogButtonBox()
        buttonBox.setOrientation(QtCore.Qt.Horizontal)
        buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        buttonBox.accepted.connect(self.accept)
        buttonBox.rejected.connect(self.reject)

        lay = QtWidgets.QFormLayout(self)
        lay.addRow("Port Name:", self.portname_comboBox)
        lay.addRow("BaudRate:", self.baudrate_comboBox)
        lay.addRow(buttonBox)
        self.setFixedSize(self.sizeHint())

    def get_results(self):
        return self.portname_comboBox.currentText(), self.baudrate_comboBox.currentData()
