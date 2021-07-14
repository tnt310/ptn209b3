from PyQt5 import QtCore, QtWidgets, QtSerialPort
from PyQt5.QtWidgets import QApplication, QDialog,QMainWindow
from NEWUI.login import Ui_logingateway
from NEWUI.gateway import Ui_gateway
from NEWUI.device import Ui_device
from NEWUI.network import Ui_network
from NEWUI.telemetry import Ui_telemetry
from NEWUI.testtool import Ui_toolLogin
from NEWUI.dialog import Ui_slavesetting
import paho.mqtt.client as mqttclient

class Serial(QtSerialPort.QSerialPort,Ui_logingateway):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.data = Ui_logingateway()
        self.serial = QtSerialPort.QSerialPort(self)
        self.openport()

    @QtCore.pyqtSlot()
    def openport(self):
        # self.serial.setPortName(self.data.comport.currentText())
        # self.serial.setBaudRate(self.data.baudrate.currentData())
        self.serial.setPortName('COM5')
        self.serial.setBaudRate(115200)
        if self.serial.open(QtCore.QIODevice.ReadWrite):
            print("OPEN")
        else:
            print("NOT OPEN")

    @QtCore.pyqtSlot()
    def send(self,string):
        print('SEND READY !!')
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
class Mqtt():
    def __init__(self, parent=None):
        super().__init__(parent)
        self.client= mqttclient.Client()
        self.client.on_connect=self.on_connect
        self.client.on_message=self.on_message
        self.ui = Ui_toolLogin()

    def connect_server(self):
        self.broker = self.ui.broker.text()
        self.user = self.ui.username.text()
        self.password = self.ui.password.text()
        self.port = int(self.ui.port.text())
        self.client.username_pw_set(self.user,self.password)
        self.client.connect(self.broker,self.port,60)
        self.client.loop_start()

    def disconnect_server(self):
        self.client.loop_stop(self)
        self.client.disconnect()
        print("Disconnected")

    def on_connect(self,client,userdata,flags,rc):
        print("Connected with code : " + str(rc))
        if rc == 0:
            self.client.subscribe("up/command")

    def on_message(self,client,userdata,msg):
        self.temp_receive = str(msg.payload.decode("utf-8"))
