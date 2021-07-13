import os
import sys
from PyQt5 import QtGui, QtWidgets
from PyQt5 import QtCore, QtWidgets, QtSerialPort, uic
from PyQt5.uic import loadUi
from PyQt5.QtWidgets import QApplication,QMainWindow
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from NEWUI.login import Ui_logingateway


class Gateway_MainWindow(QMainWindow):
    def __init__(self,parent=None):
        super(Gateway_MainWindow, self).__init__(parent)
        self.login = Ui_logingateway()
        self.login.setupUi(self)
        self.login.refresh.clicked.connect(self.refresh)

    def refresh(self):
        

if __name__ == '__main__':
    import sys
    if not QtWidgets.QApplication.instance():
        app = QApplication(sys.argv)
    else:
        app = QtWidgets.QApplication.instance()
    window  = Gateway_MainWindow()
    window.show()
    sys.exit(app.exec_()) 