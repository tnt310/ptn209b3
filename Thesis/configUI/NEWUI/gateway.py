# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'gateway.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_gateway(object):
    def setupUi(self, gateway):
        gateway.setObjectName("gateway")
        gateway.resize(1178, 735)
        self.centralwidget = QtWidgets.QWidget(gateway)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.scrollArea = QtWidgets.QScrollArea(self.centralwidget)
        self.scrollArea.setStyleSheet("background-color:rgb(255, 248, 254)\n"
"")
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents = QtWidgets.QWidget()
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 1154, 660))
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.list = QtWidgets.QFrame(self.scrollAreaWidgetContents)
        self.list.setGeometry(QtCore.QRect(0, 0, 321, 761))
        self.list.setStyleSheet("background-color:rgb(255, 223, 183)")
        self.list.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.list.setFrameShadow(QtWidgets.QFrame.Raised)
        self.list.setObjectName("list")
        self.networksetting = QtWidgets.QPushButton(self.list)
        self.networksetting.setGeometry(QtCore.QRect(50, 300, 181, 51))
        font = QtGui.QFont()
        font.setFamily("Segoe UI")
        font.setPointSize(10)
        self.networksetting.setFont(font)
        self.networksetting.setObjectName("networksetting")
        self.gatewaysetting = QtWidgets.QPushButton(self.list)
        self.gatewaysetting.setGeometry(QtCore.QRect(50, 140, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.gatewaysetting.setFont(font)
        self.gatewaysetting.setObjectName("gatewaysetting")
        self.devicesetting = QtWidgets.QPushButton(self.list)
        self.devicesetting.setGeometry(QtCore.QRect(50, 220, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.devicesetting.setFont(font)
        self.devicesetting.setObjectName("devicesetting")
        self.historical = QtWidgets.QPushButton(self.list)
        self.historical.setGeometry(QtCore.QRect(50, 450, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.historical.setFont(font)
        self.historical.setObjectName("historical")
        self.line = QtWidgets.QFrame(self.list)
        self.line.setGeometry(QtCore.QRect(310, 0, 20, 761))
        font = QtGui.QFont()
        font.setBold(False)
        font.setWeight(50)
        self.line.setFont(font)
        self.line.setFrameShape(QtWidgets.QFrame.VLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line.setObjectName("line")
        self.testtool = QtWidgets.QPushButton(self.list)
        self.testtool.setGeometry(QtCore.QRect(50, 530, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.testtool.setFont(font)
        self.testtool.setObjectName("testtool")
        self.telemetrycontrol = QtWidgets.QPushButton(self.list)
        self.telemetrycontrol.setGeometry(QtCore.QRect(50, 380, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.telemetrycontrol.setFont(font)
        self.telemetrycontrol.setObjectName("telemetrycontrol")
        self.gatewaysetting.raise_()
        self.devicesetting.raise_()
        self.historical.raise_()
        self.line.raise_()
        self.networksetting.raise_()
        self.testtool.raise_()
        self.telemetrycontrol.raise_()
        self.seial_workspace = QtWidgets.QFrame(self.scrollAreaWidgetContents)
        self.seial_workspace.setGeometry(QtCore.QRect(320, 0, 1001, 761))
        self.seial_workspace.setStyleSheet("background-color:rgb(255, 255, 255)")
        self.seial_workspace.setObjectName("seial_workspace")
        self.groupBox = QtWidgets.QGroupBox(self.seial_workspace)
        self.groupBox.setGeometry(QtCore.QRect(30, 0, 371, 451))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.groupBox.setFont(font)
        self.groupBox.setObjectName("groupBox")
        self.port = QtWidgets.QComboBox(self.groupBox)
        self.port.setGeometry(QtCore.QRect(140, 50, 221, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.port.setFont(font)
        self.port.setObjectName("port")
        self.port.addItem("")
        self.port.addItem("")
        self.label_18 = QtWidgets.QLabel(self.groupBox)
        self.label_18.setGeometry(QtCore.QRect(40, 60, 71, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_18.setFont(font)
        self.label_18.setObjectName("label_18")
        self.baudrate = QtWidgets.QComboBox(self.groupBox)
        self.baudrate.setGeometry(QtCore.QRect(140, 120, 221, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.baudrate.setFont(font)
        self.baudrate.setObjectName("baudrate")
        self.baudrate.addItem("")
        self.baudrate.addItem("")
        self.baudrate.addItem("")
        self.baudrate.addItem("")
        self.baudrate.addItem("")
        self.label_19 = QtWidgets.QLabel(self.groupBox)
        self.label_19.setGeometry(QtCore.QRect(30, 140, 81, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_19.setFont(font)
        self.label_19.setObjectName("label_19")
        self.label_20 = QtWidgets.QLabel(self.groupBox)
        self.label_20.setGeometry(QtCore.QRect(30, 210, 81, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_20.setFont(font)
        self.label_20.setObjectName("label_20")
        self.databit = QtWidgets.QComboBox(self.groupBox)
        self.databit.setGeometry(QtCore.QRect(140, 190, 221, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.databit.setFont(font)
        self.databit.setObjectName("databit")
        self.databit.addItem("")
        self.databit.addItem("")
        self.label_21 = QtWidgets.QLabel(self.groupBox)
        self.label_21.setGeometry(QtCore.QRect(30, 280, 81, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_21.setFont(font)
        self.label_21.setObjectName("label_21")
        self.stopbit = QtWidgets.QComboBox(self.groupBox)
        self.stopbit.setGeometry(QtCore.QRect(140, 260, 221, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.stopbit.setFont(font)
        self.stopbit.setObjectName("stopbit")
        self.stopbit.addItem("")
        self.stopbit.addItem("")
        self.label_22 = QtWidgets.QLabel(self.groupBox)
        self.label_22.setGeometry(QtCore.QRect(30, 350, 81, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_22.setFont(font)
        self.label_22.setObjectName("label_22")
        self.parity = QtWidgets.QComboBox(self.groupBox)
        self.parity.setGeometry(QtCore.QRect(140, 330, 221, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.parity.setFont(font)
        self.parity.setObjectName("parity")
        self.parity.addItem("")
        self.parity.addItem("")
        self.updateport = QtWidgets.QPushButton(self.groupBox)
        self.updateport.setGeometry(QtCore.QRect(170, 400, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.updateport.setFont(font)
        self.updateport.setObjectName("updateport")
        self.groupBox_2 = QtWidgets.QGroupBox(self.seial_workspace)
        self.groupBox_2.setGeometry(QtCore.QRect(440, 0, 371, 451))
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setUnderline(False)
        self.groupBox_2.setFont(font)
        self.groupBox_2.setObjectName("groupBox_2")
        self.label_23 = QtWidgets.QLabel(self.groupBox_2)
        self.label_23.setGeometry(QtCore.QRect(10, 70, 91, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_23.setFont(font)
        self.label_23.setObjectName("label_23")
        self.label_24 = QtWidgets.QLabel(self.groupBox_2)
        self.label_24.setGeometry(QtCore.QRect(10, 200, 91, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_24.setFont(font)
        self.label_24.setObjectName("label_24")
        self.label_25 = QtWidgets.QLabel(self.groupBox_2)
        self.label_25.setGeometry(QtCore.QRect(10, 270, 91, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_25.setFont(font)
        self.label_25.setObjectName("label_25")
        self.label_26 = QtWidgets.QLabel(self.groupBox_2)
        self.label_26.setGeometry(QtCore.QRect(30, 340, 81, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_26.setFont(font)
        self.label_26.setObjectName("label_26")
        self.updatemqtt = QtWidgets.QPushButton(self.groupBox_2)
        self.updatemqtt.setGeometry(QtCore.QRect(160, 390, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.updatemqtt.setFont(font)
        self.updatemqtt.setObjectName("updatemqtt")
        self.broker = QtWidgets.QLineEdit(self.groupBox_2)
        self.broker.setGeometry(QtCore.QRect(110, 60, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.broker.setFont(font)
        self.broker.setObjectName("broker")
        self.username = QtWidgets.QLineEdit(self.groupBox_2)
        self.username.setGeometry(QtCore.QRect(110, 190, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.username.setFont(font)
        self.username.setObjectName("username")
        self.password = QtWidgets.QLineEdit(self.groupBox_2)
        self.password.setGeometry(QtCore.QRect(110, 260, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.password.setFont(font)
        self.password.setObjectName("password")
        self.port_2 = QtWidgets.QLineEdit(self.groupBox_2)
        self.port_2.setGeometry(QtCore.QRect(110, 330, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.port_2.setFont(font)
        self.port_2.setObjectName("port_2")
        self.username_2 = QtWidgets.QLineEdit(self.groupBox_2)
        self.username_2.setGeometry(QtCore.QRect(110, 130, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.username_2.setFont(font)
        self.username_2.setObjectName("username_2")
        self.label_27 = QtWidgets.QLabel(self.groupBox_2)
        self.label_27.setGeometry(QtCore.QRect(20, 140, 41, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_27.setFont(font)
        self.label_27.setObjectName("label_27")
        self.groupBox_3 = QtWidgets.QGroupBox(self.seial_workspace)
        self.groupBox_3.setGeometry(QtCore.QRect(30, 450, 371, 181))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.groupBox_3.setFont(font)
        self.groupBox_3.setObjectName("groupBox_3")
        self.timeout = QtWidgets.QComboBox(self.groupBox_3)
        self.timeout.setGeometry(QtCore.QRect(140, 50, 221, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.timeout.setFont(font)
        self.timeout.setObjectName("timeout")
        self.timeout.addItem("")
        self.timeout.addItem("")
        self.timeout.addItem("")
        self.timeout.addItem("")
        self.timeout.addItem("")
        self.timeout.addItem("")
        self.timeout.addItem("")
        self.label_28 = QtWidgets.QLabel(self.groupBox_3)
        self.label_28.setGeometry(QtCore.QRect(30, 60, 81, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_28.setFont(font)
        self.label_28.setObjectName("label_28")
        self.updatetimeout = QtWidgets.QPushButton(self.groupBox_3)
        self.updatetimeout.setGeometry(QtCore.QRect(180, 120, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.updatetimeout.setFont(font)
        self.updatetimeout.setObjectName("updatetimeout")
        self.groupBox_4 = QtWidgets.QGroupBox(self.seial_workspace)
        self.groupBox_4.setGeometry(QtCore.QRect(440, 450, 371, 181))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.groupBox_4.setFont(font)
        self.groupBox_4.setObjectName("groupBox_4")
        self.label_29 = QtWidgets.QLabel(self.groupBox_4)
        self.label_29.setGeometry(QtCore.QRect(30, 60, 81, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_29.setFont(font)
        self.label_29.setObjectName("label_29")
        self.apikey_2 = QtWidgets.QLineEdit(self.groupBox_4)
        self.apikey_2.setGeometry(QtCore.QRect(100, 50, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.apikey_2.setFont(font)
        self.apikey_2.setObjectName("apikey_2")
        self.updateapikey = QtWidgets.QPushButton(self.groupBox_4)
        self.updateapikey.setGeometry(QtCore.QRect(160, 110, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.updateapikey.setFont(font)
        self.updateapikey.setObjectName("updateapikey")
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.verticalLayout.addWidget(self.scrollArea)
        gateway.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(gateway)
        self.statusbar.setObjectName("statusbar")
        gateway.setStatusBar(self.statusbar)
        self.menubar = QtWidgets.QMenuBar(gateway)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1178, 26))
        self.menubar.setObjectName("menubar")
        gateway.setMenuBar(self.menubar)

        self.retranslateUi(gateway)
        QtCore.QMetaObject.connectSlotsByName(gateway)

    def retranslateUi(self, gateway):
        _translate = QtCore.QCoreApplication.translate
        gateway.setWindowTitle(_translate("gateway", "TEST TOOL"))
        self.networksetting.setText(_translate("gateway", "NETWORK SETTING"))
        self.gatewaysetting.setText(_translate("gateway", "GATEWAY SETTING"))
        self.devicesetting.setText(_translate("gateway", "DEVICE SETTING"))
        self.historical.setText(_translate("gateway", "HISTORICAL RECORD"))
        self.testtool.setText(_translate("gateway", "TESTTOOL"))
        self.telemetrycontrol.setText(_translate("gateway", "TELEMETRY CONTROL"))
        self.groupBox.setTitle(_translate("gateway", "Port setting"))
        self.port.setItemText(0, _translate("gateway", "PORT 1"))
        self.port.setItemText(1, _translate("gateway", "PORT 2"))
        self.label_18.setText(_translate("gateway", "PORT"))
        self.baudrate.setItemText(0, _translate("gateway", "4800"))
        self.baudrate.setItemText(1, _translate("gateway", "9600"))
        self.baudrate.setItemText(2, _translate("gateway", "19200"))
        self.baudrate.setItemText(3, _translate("gateway", "38400"))
        self.baudrate.setItemText(4, _translate("gateway", "115200"))
        self.label_19.setText(_translate("gateway", "BAUDRATE"))
        self.label_20.setText(_translate("gateway", "DATABITS"))
        self.databit.setItemText(0, _translate("gateway", "8"))
        self.databit.setItemText(1, _translate("gateway", "7"))
        self.label_21.setText(_translate("gateway", "STOPBIT"))
        self.stopbit.setItemText(0, _translate("gateway", "1"))
        self.stopbit.setItemText(1, _translate("gateway", "2"))
        self.label_22.setText(_translate("gateway", "PARITY"))
        self.parity.setItemText(0, _translate("gateway", "NONE"))
        self.parity.setItemText(1, _translate("gateway", "1"))
        self.updateport.setText(_translate("gateway", "UPDATE"))
        self.groupBox_2.setTitle(_translate("gateway", "Mqtt setting"))
        self.label_23.setText(_translate("gateway", "BROKER"))
        self.label_24.setText(_translate("gateway", "USERNAME"))
        self.label_25.setText(_translate("gateway", "PASSWORD"))
        self.label_26.setText(_translate("gateway", "PORT"))
        self.updatemqtt.setText(_translate("gateway", "UPDATE"))
        self.broker.setText(_translate("gateway", "3.226.137.205"))
        self.username.setText(_translate("gateway", "NULL"))
        self.password.setText(_translate("gateway", "NULL"))
        self.port_2.setText(_translate("gateway", "1883"))
        self.username_2.setText(_translate("gateway", "NULL"))
        self.label_27.setText(_translate("gateway", "ID"))
        self.groupBox_3.setTitle(_translate("gateway", "Timeout setting"))
        self.timeout.setItemText(0, _translate("gateway", "30 second"))
        self.timeout.setItemText(1, _translate("gateway", "1 minute"))
        self.timeout.setItemText(2, _translate("gateway", "3 minutes"))
        self.timeout.setItemText(3, _translate("gateway", "5 minutes"))
        self.timeout.setItemText(4, _translate("gateway", "10 minutes"))
        self.timeout.setItemText(5, _translate("gateway", "30 minutes"))
        self.timeout.setItemText(6, _translate("gateway", "60 minutes"))
        self.label_28.setText(_translate("gateway", "TIMEOUT"))
        self.updatetimeout.setText(_translate("gateway", "UPDATE"))
        self.groupBox_4.setTitle(_translate("gateway", "API key setting"))
        self.label_29.setText(_translate("gateway", "APIKEY"))
        self.apikey_2.setText(_translate("gateway", "60cda6bc55193093bbcd001f"))
        self.updateapikey.setText(_translate("gateway", "UPDATE"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    gateway = QtWidgets.QMainWindow()
    ui = Ui_gateway()
    ui.setupUi(gateway)
    gateway.show()
    sys.exit(app.exec_())
