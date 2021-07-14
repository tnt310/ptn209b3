from PyQt5 import QtCore, QtWidgets, QtSerialPort
from PyQt5.QtWidgets import QApplication,QMainWindow
from NEWUI.login import Ui_logingateway
from NEWUI.gateway import Ui_gateway
from NEWUI.device import Ui_device
from NEWUI.network import Ui_network
from NEWUI.telemetry import Ui_telemetry
from NEWUI.testtool import Ui_toolLogin
from NEWUI.dialog import Ui_slavesetting
from source import Dialog, Serial
class Gateway(QMainWindow):
    def __init__(self,parent=None):
        super(Gateway, self).__init__(parent)
        self.login = Ui_logingateway()
        self.login.setupUi(self)
        for info in QtSerialPort.QSerialPortInfo.availablePorts():
            self.login.comport.addItem(info.portName())
        self.login.refresh.clicked.connect(self.refresh)
        self.login.open.clicked.connect(self.open)

    def refresh(self):
        self.fresh = Ui_logingateway()
        self.fresh.setupUi(self)
        for info in QtSerialPort.QSerialPortInfo.availablePorts():
            self.fresh.comport.addItem(info.portName())
        self.fresh.refresh.clicked.connect(self.refresh)
        self.fresh.open.clicked.connect(self.open)

    def open(self):
        self.gateway = Ui_gateway()
        self.serial = Serial()
        if self.serial:
            self.gateway_setting()
        else:
            print("NOT OPEN")

    def gateway_setting(self):
        self.gateway.setupUi(self)
        self.gateway.gatewaysetting.clicked.connect(self.gateway_setting)
        self.gateway.devicesetting.clicked.connect(self.device_setting)
        self.gateway.networksetting.clicked.connect(self.network_setting)
        self.gateway.telemetrycontrol.clicked.connect(self.telemetry_control)
        self.gateway.testtool.clicked.connect(self.test_tool)
        self.gateway.updateport.clicked.connect(self.update_rs485)
        self.gateway.updatemqtt.clicked.connect(self.update_mqtt)
        self.gateway.updatetimeout.clicked.connect(self.update_timeout)
        self.gateway.updateapikey.clicked.connect(self.update_apikey)

    def update_rs485(self):
        global baud, databit, stopbit, parity
        baud = self.gateway.baudrate.currentData()
        # if self.gateway.databit.currentData() == 8:
        #     databit = '0'
        # if self.gateway.stopbit.currentData() == 1:
        #     stopbit = '0'
        # if self.gateway.parity.currentText() == "NONE":
        #     parity = '0'
        print(self.gateway.databit.currentData())
        # string = str(baud)+ databit + stopbit+ parity
        # self.serial.send(string)
    def update_mqtt(self):
        str = 'configmqtt'+' '+self.gateway.broker.text()+' '+ self.gateway.username.text()+' '+ self.gateway.password.text()+' '+ self.gateway.mqttport.text()+'\r'
        self.serial.send(str)
    def update_timeout(self):
        temp = self.gateway.timeout.currentText().split()
        str = 'configtimeout'+' '+ temp[0]+'\r'
        self.serial.send(str)
    def update_apikey(self):
        str = 'configapikey'+' '+ self.gateway.apikey.text()+'\r'
        self.serial.send(str)

    def device_setting(self):
        self.device = Ui_device()
        self.device.setupUi(self)
        self.device.gatewaysetting.clicked.connect(self.gateway_setting)
        self.device.devicesetting.clicked.connect(self.device_setting)
        self.device.networksetting.clicked.connect(self.network_setting)
        self.device.telemetrycontrol.clicked.connect(self.telemetry_control)
        self.device.testtool.clicked.connect(self.test_tool)
        self.device.add.clicked.connect(self.addDevice)

    def addDevice(self):
        self.dialog = Dialog()
        if self.dialog.exec_():
            self.type = dialog.save()
            print(self.type)

    def network_setting(self):
        self.network = Ui_network()
        self.network.setupUi(self)
        self.network.gatewaysetting.clicked.connect(self.gateway_setting)
        self.network.devicesetting.clicked.connect(self.device_setting)
        self.network.networksetting.clicked.connect(self.network_setting)
        self.network.telemetrycontrol.clicked.connect(self.telemetry_control)
        self.network.testtool.clicked.connect(self.test_tool)
        self.network.update.clicked.connect(self.update_network)
    def update_network(self):
        str = 'confignetwork'+' '+self.network.ip.text()+' '+ self.network.netmask.text()+' '+ self.network.gateway.text()+'\r'
        self.serial.send(str)

    def telemetry_control(self):
        self.control = Ui_telemetry()
        self.control.setupUi(self)
        self.control.gatewaysetting.clicked.connect(self.gateway_setting)
        self.control.devicesetting.clicked.connect(self.device_setting)
        self.control.networksetting.clicked.connect(self.network_setting)
        self.control.telemetrycontrol.clicked.connect(self.telemetry_control)
        self.control.testtool.clicked.connect(self.test_tool)
        self.control.provision.clicked.connect(self.send_provision)
        self.control.telemetryon.clicked.connect(self.set_telemetry)
        self.control.telemetryoff.clicked.connect(self.off_telemetry)
    def send_provision(self):
        str = 'sendprovision\r'
        self.serial.send(str)
    def set_telemetry(self):
        str = 'configtelemetry 1\r'
        self.serial.send(str)
    def off_telemetry(self):
        str = 'configtelemetry 0\r'
        self.serial.send(str)

    def test_tool(self):
        self.test = Ui_toolLogin()
        self.test.setupUi(self)
        self.test.gatewaysetting.clicked.connect(self.gateway_setting)
        self.test.devicesetting.clicked.connect(self.device_setting)
        self.test.networksetting.clicked.connect(self.network_setting)
        self.test.telemetrycontrol.clicked.connect(self.telemetry_control)
        self.test.testtool.clicked.connect(self.test_tool)




if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = Gateway()
    w.show()
    sys.exit(app.exec_())