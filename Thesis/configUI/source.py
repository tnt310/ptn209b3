
from NEWUI.warning import Ui_warning
from PyQt5 import QtCore, QtWidgets, QtSerialPort
from PyQt5.QtWidgets import QApplication, QDialog,QMainWindow
from NEWUI.login import Ui_logingateway
from NEWUI.gateway import Ui_gateway
from NEWUI.device import Ui_device
from NEWUI.network import Ui_network
from NEWUI.telemetry import Ui_telemetry
from NEWUI.testtool import Ui_toolLogin
from NEWUI.dialog import Ui_slavesetting
from NEWUI.mqtt import Ui_demo
from NEWUI.server_warning import Ui_server_warning
import paho.mqtt.client as mqttclient

class Serial(QtSerialPort.QSerialPort,Ui_logingateway):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.serial = QtSerialPort.QSerialPort(self)

    @QtCore.pyqtSlot()
    def openport(self,portname,baudrate):
        self.serial.setPortName(portname)
        self.serial.setBaudRate(baudrate)
        return self.serial.open(QtCore.QIODevice.ReadWrite)

    @QtCore.pyqtSlot()
    def send(self,string):
        self.serial.write((str(string).encode()))

class Dialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_slavesetting()
        self.ui.setupUi(self)
        self.ui.save.clicked.connect(self.save)
    def save(self):
        # print(self.ui.devicetype.currentText())
        return self.ui.devicetype.currentText()
        # return self.ui.slaveAddress.text(),self.ui.function.currentText(),self.ui.devicechannel.text(),self.ui.datatype.currentText(),self.ui.devicetype.currentText(),self.ui.devicename.text(),self.ui.channeltitle.text(),self.ui.valuetype.currentText(),self.ui.scale.text()
    def is_valid(self):
        return True

class WarningDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.warning = Ui_warning()
        self.warning.setupUi(self)
class ServerWarning(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.warning = Ui_server_warning()
        self.warning.setupUi(self)
class Tool(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.tool = Ui_demo()
        self.tool.setupUi(self)
        self.tool.getlumen.clicked.connect(self.get_lumen)
    def get_lumen(self):
        self.tool.lumen.text()

class MqttClient():
    def __init__(self, parent=None):
        self.client= mqttclient.Client()
        self.client.on_connect=self.on_connect()
        self.client.on_message=self.on_message
    def connect_server(self,broker,username,password,port):
        self.client.username_pw_set(username,password)
        self.client.connect(broker,port,60)
        self.client.loop_start()
    def disconnect_server(self):
        self.client.loop_stop(self)
        self.client.disconnect()
        print("Disconnected")
    def on_connect(self,client,userdata,flags,rc):
        print("Connected with code : " + str(rc))
        if rc == 0:
            client.subscribe("up/command")

    def on_message(self,client,userdata,msg):
        temp_receive = str(msg.payload.decode("utf-8"))
