import os
import sys
from PyQt5 import QtGui, QtWidgets
from PyQt5 import QtCore, QtWidgets, QtSerialPort, uic
from PyQt5.uic import loadUi
from PyQt5.QtWidgets import QApplication,QMainWindow
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from UI.config import Ui_MainWindow
from UI.network import Network_frame
from UI.serial import Serial_frame
from UI.testtool import Testtool_frame
from UI.testtool_login import TesttoolLogin_frame
from mqttThread import  MqttThread


class ASWA_MainWindow(QMainWindow, Ui_MainWindow, Network_frame, Serial_frame,Testtool_frame,TesttoolLogin_frame):
    def __init__(self,parent=None):
        super(ASWA_MainWindow, self).__init__(parent)
        loadUi('UI/config.ui',self)
        self.connection.clicked.connect(self.serialspace)
        self.network.clicked.connect(self.networkspace)
        self.testtool.clicked.connect(self.testtoolworkspace)

    def serialspace(self):
        loadUi('UI/serial.ui',self)
        self.connection.clicked.connect(self.serialspace)
        self.network.clicked.connect(self.networkspace)
        self.testtool.clicked.connect(self.testtoolworkspace)

    def networkspace(self):
        loadUi('UI/network.ui',self)
        self.connection.clicked.connect(self.serialspace)
        self.network.clicked.connect(self.networkspace)
        self.testtool.clicked.connect(self.testtoolworkspace)

    def testtoolworkspace(self):
        loadUi('UI/testtool_login.ui',self)
        self.connection.clicked.connect(self.serialspace)
        self.network.clicked.connect(self.networkspace)
        self.testtool.clicked.connect(self.testtoolworkspace)
        self.connect.clicked.connect(MqttThread.connect_server)
        self.disconnect.clicked.connect(MqttThread.disconnect_server)


if __name__ == '__main__':
    import sys
    if not QtWidgets.QApplication.instance():
        app = QApplication(sys.argv)
    else:
        app = QtWidgets.QApplication.instance()
    window  = ASWA_MainWindow()
    window.show()
    sys.exit(app.exec_()) 