# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'network.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Network_frame(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1178, 735)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
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
        self.connection = QtWidgets.QPushButton(self.list)
        self.connection.setGeometry(QtCore.QRect(50, 170, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.connection.setFont(font)
        self.connection.setObjectName("connection")
        self.network = QtWidgets.QPushButton(self.list)
        self.network.setGeometry(QtCore.QRect(50, 240, 181, 51))
        font = QtGui.QFont()
        font.setFamily("Segoe UI")
        font.setPointSize(10)
        self.network.setFont(font)
        self.network.setObjectName("network")
        self.modbus = QtWidgets.QPushButton(self.list)
        self.modbus.setGeometry(QtCore.QRect(50, 310, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.modbus.setFont(font)
        self.modbus.setObjectName("modbus")
        self.devicelist = QtWidgets.QPushButton(self.list)
        self.devicelist.setGeometry(QtCore.QRect(50, 380, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.devicelist.setFont(font)
        self.devicelist.setObjectName("devicelist")
        self.testtool = QtWidgets.QPushButton(self.list)
        self.testtool.setGeometry(QtCore.QRect(50, 450, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.testtool.setFont(font)
        self.testtool.setObjectName("testtool")
        self.line = QtWidgets.QFrame(self.list)
        self.line.setGeometry(QtCore.QRect(310, 0, 20, 761))
        font = QtGui.QFont()
        font.setBold(False)
        font.setWeight(50)
        self.line.setFont(font)
        self.line.setFrameShape(QtWidgets.QFrame.VLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line.setObjectName("line")
        self.connection.raise_()
        self.modbus.raise_()
        self.devicelist.raise_()
        self.testtool.raise_()
        self.line.raise_()
        self.network.raise_()
        self.seial_workspace = QtWidgets.QFrame(self.scrollAreaWidgetContents)
        self.seial_workspace.setGeometry(QtCore.QRect(320, 0, 1001, 761))
        self.seial_workspace.setStyleSheet("background-color:rgb(255, 255, 255)")
        self.seial_workspace.setObjectName("seial_workspace")
        self.apikey = QtWidgets.QTextEdit(self.seial_workspace)
        self.apikey.setGeometry(QtCore.QRect(330, 450, 251, 41))
        self.apikey.setObjectName("apikey")
        self.label_14 = QtWidgets.QLabel(self.seial_workspace)
        self.label_14.setGeometry(QtCore.QRect(220, 180, 81, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_14.setFont(font)
        self.label_14.setObjectName("label_14")
        self.label_17 = QtWidgets.QLabel(self.seial_workspace)
        self.label_17.setGeometry(QtCore.QRect(220, 340, 91, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_17.setFont(font)
        self.label_17.setObjectName("label_17")
        self.label_16 = QtWidgets.QLabel(self.seial_workspace)
        self.label_16.setGeometry(QtCore.QRect(220, 290, 81, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_16.setFont(font)
        self.label_16.setObjectName("label_16")
        self.label_18 = QtWidgets.QLabel(self.seial_workspace)
        self.label_18.setGeometry(QtCore.QRect(220, 400, 71, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_18.setFont(font)
        self.label_18.setObjectName("label_18")
        self.update = QtWidgets.QPushButton(self.seial_workspace)
        self.update.setGeometry(QtCore.QRect(360, 550, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.update.setFont(font)
        self.update.setObjectName("update")
        self.ip = QtWidgets.QTextEdit(self.seial_workspace)
        self.ip.setGeometry(QtCore.QRect(330, 170, 251, 41))
        self.ip.setObjectName("ip")
        self.mqttport = QtWidgets.QTextEdit(self.seial_workspace)
        self.mqttport.setGeometry(QtCore.QRect(330, 390, 251, 41))
        self.mqttport.setObjectName("mqttport")
        self.label_19 = QtWidgets.QLabel(self.seial_workspace)
        self.label_19.setGeometry(QtCore.QRect(220, 450, 71, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_19.setFont(font)
        self.label_19.setObjectName("label_19")
        self.broker = QtWidgets.QTextEdit(self.seial_workspace)
        self.broker.setGeometry(QtCore.QRect(330, 330, 251, 41))
        self.broker.setObjectName("broker")
        self.netmask = QtWidgets.QTextEdit(self.seial_workspace)
        self.netmask.setGeometry(QtCore.QRect(330, 220, 251, 41))
        self.netmask.setObjectName("netmask")
        self.gateway = QtWidgets.QTextEdit(self.seial_workspace)
        self.gateway.setGeometry(QtCore.QRect(330, 280, 251, 41))
        self.gateway.setObjectName("gateway")
        self.label_15 = QtWidgets.QLabel(self.seial_workspace)
        self.label_15.setGeometry(QtCore.QRect(220, 230, 91, 31))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_15.setFont(font)
        self.label_15.setObjectName("label_15")
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.verticalLayout.addWidget(self.scrollArea)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1178, 26))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "TEST TOOL"))
        self.connection.setText(_translate("MainWindow", "CONNECTION"))
        self.network.setText(_translate("MainWindow", "NETWORK"))
        self.modbus.setText(_translate("MainWindow", "MODBUS"))
        self.devicelist.setText(_translate("MainWindow", "DEVICE LIST"))
        self.testtool.setText(_translate("MainWindow", "TESTTOOL"))
        self.apikey.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">60d9cb2955193093bbcd0027</span></p></body></html>"))
        self.label_14.setText(_translate("MainWindow", "IP"))
        self.label_17.setText(_translate("MainWindow", "BROKER"))
        self.label_16.setText(_translate("MainWindow", "GATEWAY"))
        self.label_18.setText(_translate("MainWindow", "PORT"))
        self.update.setText(_translate("MainWindow", "UPDATE"))
        self.ip.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">192.168.100.111</span></p></body></html>"))
        self.mqttport.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">1883</span></p></body></html>"))
        self.label_19.setText(_translate("MainWindow", "APIKEY"))
        self.broker.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">95.111.195.76</span></p></body></html>"))
        self.netmask.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">255.255.255.0</span></p></body></html>"))
        self.gateway.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">192.168.100.1</span></p></body></html>"))
        self.label_15.setText(_translate("MainWindow", "NETMASK"))


# if __name__ == "__main__":
#     import sys
#     app = QtWidgets.QApplication(sys.argv)
#     MainWindow = QtWidgets.QMainWindow()
#     ui = Ui_MainWindow()
#     ui.setupUi(MainWindow)
#     MainWindow.show()
#     sys.exit(app.exec_())