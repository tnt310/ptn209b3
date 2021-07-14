from PyQt5 import QtCore, QtWidgets, QtSerialPort
from PyQt5.QtWidgets import QApplication,QMainWindow
from NEWUI.login import Ui_logingateway
from NEWUI.gateway import Ui_gateway
from NEWUI.device import Ui_device
from NEWUI.network import Ui_network
from NEWUI.telemetry import Ui_telemetry
from NEWUI.testtool import Ui_toolLogin

class Serial():
    def __init__(self, parent=None):
        super(Serial, self).__init__(parent)

class Network():
    def __init__(self, parent=None):
        super(Network, self).__init__(parent)

class Control():
    def __init__(self, parent=None):
        super(Control, self).__init__(parent)

class Device():
    def __init__(self, parent=None):
        super(Device, self).__init__(parent)

class TestTool():
    def __init__(self, parent=None):
        super(TestTool, self).__init__(parent)
