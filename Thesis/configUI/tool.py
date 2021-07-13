from PyQt5 import QtCore, QtWidgets, QtSerialPort
from PyQt5.QtWidgets import QApplication,QMainWindow
from NEWUI.login import Ui_logingateway
from NEWUI.gateway import Ui_gateway
from NEWUI.device import Ui_device
from NEWUI.network import Ui_network
from NEWUI.telemetry import Ui_telemetry
from NEWUI.testtool import Ui_toolLogin
class Gateway(QMainWindow):
    def __init__(self,parent=None):
        super(Gateway, self).__init__(parent)
        login = Ui_logingateway()
        login.setupUi(self)
        for info in QtSerialPort.QSerialPortInfo.availablePorts():
            login.comport.addItem(info.portName())
        login.refresh.clicked.connect(self.refresh)
        login.open.clicked.connect(self.open)

    def refresh(self):
        refresh = Ui_logingateway()
        refresh.setupUi(self)
        for info in QtSerialPort.QSerialPortInfo.availablePorts():
            refresh.comport.addItem(info.portName())
        refresh.refresh.clicked.connect(self.refresh)
        refresh.open.clicked.connect(self.open)

    def open(self):
        gateway = Ui_gateway()
        gateway.setupUi(self)
        gateway.gatewaysetting.clicked.connect(self.gateway_setting)
        gateway.devicesetting.clicked.connect(self.device_setting)
        gateway.networksetting.clicked.connect(self.network_setting)
        gateway.telemetrycontrol.clicked.connect(self.telemetry_control)
        gateway.testtool.clicked.connect(self.test_tool)

    def gateway_setting(self):
        gateway = Ui_gateway()
        gateway.setupUi(self)
        gateway.gatewaysetting.clicked.connect(self.gateway_setting)
        gateway.devicesetting.clicked.connect(self.device_setting)
        gateway.networksetting.clicked.connect(self.network_setting)
        gateway.telemetrycontrol.clicked.connect(self.telemetry_control)
        gateway.testtool.clicked.connect(self.test_tool)

    def device_setting(self):
        device = Ui_device()
        device.setupUi(self)
        device.gatewaysetting.clicked.connect(self.gateway_setting)
        device.devicesetting.clicked.connect(self.device_setting)
        device.networksetting.clicked.connect(self.network_setting)
        device.telemetrycontrol.clicked.connect(self.telemetry_control)
        device.testtool.clicked.connect(self.test_tool)

    def network_setting(self):
        network = Ui_network()
        network.setupUi(self)
        network.gatewaysetting.clicked.connect(self.gateway_setting)
        network.devicesetting.clicked.connect(self.device_setting)
        network.networksetting.clicked.connect(self.network_setting)
        network.telemetrycontrol.clicked.connect(self.telemetry_control)
        network.testtool.clicked.connect(self.test_tool)

    def telemetry_control(self):
        control = Ui_telemetry()
        control.setupUi(self)
        control.gatewaysetting.clicked.connect(self.gateway_setting)
        control.devicesetting.clicked.connect(self.device_setting)
        control.networksetting.clicked.connect(self.network_setting)
        control.telemetrycontrol.clicked.connect(self.telemetry_control)
        control.testtool.clicked.connect(self.test_tool)

    def test_tool(self):
        test = Ui_toolLogin()
        test.setupUi(self)
        test.gatewaysetting.clicked.connect(self.gateway_setting)
        test.devicesetting.clicked.connect(self.device_setting)
        test.networksetting.clicked.connect(self.network_setting)
        test.telemetrycontrol.clicked.connect(self.telemetry_control)
        test.testtool.clicked.connect(self.test_tool)


if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = Gateway()
    w.show()
    sys.exit(app.exec_())