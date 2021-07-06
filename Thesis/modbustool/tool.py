import os 
import sys
from PyQt5 import QtGui, QtWidgets
from PyQt5.QtWidgets import QMessageBox
from PyQt5.QtCore import pyqtSlot
from PyQt5.QtWidgets import QApplication,QFileDialog,QMainWindow,QMessageBox
from v0 import Ui_MainWindow
import threading
import paho.mqtt.client as mqttclient
import time
from PyQt5.QtWidgets import * 
from PyQt5.QtGui import * 
from PyQt5.QtCore import * 
import paho.mqtt.client as mqttclient
import time

stateR2 = False
stateR3 = False
stateR4 = False
temp_receive = ''
check_temp = False

def on_connect(client,userdata,flags,rc):
    print("Connected with code : " + str(rc))
    if rc == 0:
        client.subscribe("up/command"+apikey)

def on_message(client,userdata,msg):
    global temp_receive
    temp_receive = str(msg.payload.decode("utf-8"))

apikey = '60d9cb2955193093bbcd0027'
id = '{"device_id":"20",'
channel = '"channel_id":"02",'
code = '"command": "write",'
value = '"value": 220}'
power = id + channel + code + value


client=mqttclient.Client()
client.on_connect=on_connect
client.on_message=on_message


    # Enable Connect Button and Disable Others

class ASWA_MainWindow(QMainWindow,Ui_MainWindow):
    def __init__(self,parent=None):
        super(ASWA_MainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.setupUi(self)
        self.power.setStyleSheet("background-image:url(off.jpg);") #defaul off
        self.fan.setStyleSheet("background-image:url(off.jpg);") #defaul off
        self.connect.clicked.connect(self.connect_server)
        self.disconnect.clicked.connect(self.disconnect_server)
        self.power.clicked.connect(self.Power)
        self.fan.clicked.connect(self.Fan)
        self.Write_btn.clicked.connect(self.Write_Modbus)
        self.Read_btn.clicked.connect(self.Read_Modbus)
    ############################## function connect/disconnect
    def connect_server(self):
        broker = self.server.text()
        user = self.mqtt_user.text()
        password = self.mqtt_pwd.text()
        port = int(self.mqtt_port.text())
        client.username_pw_set(user,password)
        client.connect(broker,port,60)
        client.loop_start()
    def disconnect_server(self):
        client.loop_stop(self)
        client.disconnect()
        print("Disconnected")
    ############################## function click below
    def Power(self):
        global stateR2
        stateR2 = not stateR2
        if stateR2:
            self.power.setStyleSheet("background-image:url(on.jpg);")
            client.publish("down/command/"+apikey,power)
        else:
            self.power.setStyleSheet("background-image:url(off.jpg);")
            client.publish("down/command/"+apikey,power)
    def Fan(self):
        global stateR3
        stateR3 = not stateR3
        if stateR3:
            self.fan.setStyleSheet("background-image:url(on.jpg);")
            client.publish("down/command/"+apikey,power)
        else:
            self.fan.setStyleSheet("background-image:url(off.jpg);")
            client.publish("down/command/"+apikey,power)
    
    ############################### second thread below 
    def Read_Modbus(self):
        if self.Adress_R.text().strip() == '':
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Warning)
            msg.setText("Please fill ID")
            msg.setWindowTitle("Warning")
            msg.exec_() 
        elif self.Register_R.text().strip() == '':
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Warning)
            msg.setText("Please fill Register")
            msg.setWindowTitle("Warning")
            msg.exec_()
        elif self.Manual.isChecked() and self.Auto.isChecked():
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Warning)
            msg.setText("Please check just one check box: Manual or Auto")
            msg.setWindowTitle("Warning")
            msg.exec_()
        elif self.Register_R.text().strip() != '256' or self.Adress_R.text().strip() != '1':
            global check_temp
            check_temp = False
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Warning)
            msg.setText("Don't find Device")
            msg.setWindowTitle("Warning")
            msg.exec_()
        else:  
            check_temp = True

    def Write_Modbus(self):
        if self.Adress_W.text().strip() == '':
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Warning)
            msg.setText("Please fill ID")
            msg.setWindowTitle("Warning")
            msg.exec_() 
        elif self.Register_W.text().strip() == '':
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Warning)
            msg.setText("Please fill Register")
            msg.setWindowTitle("Warning")
            msg.exec_()
        elif self.Adress_W.text().strip() == '2' and self.Register_W.text().strip() == '01' and self.State.currentText().strip() == 'ON':
            client.publish("RLM","RLM1ON")
        elif self.Adress_W.text().strip() == '2' and self.Register_W.text().strip() == '01' and self.State.currentText().strip() == 'OFF':
            client.publish("RLM","RLM1OFF")
        elif self.Adress_W.text().strip() == '2' and self.Register_W.text().strip() == '00' and self.State.currentText().strip() == 'ON':
            client.publish("RLM","RLM0ON")
        elif self.Adress_W.text().strip() == '2' and self.Register_W.text().strip() == '00' and self.State.currentText().strip() == 'OFF':
            client.publish("RLM","RLM0OFF")
        else:
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Warning)
            msg.setText("Don't find Device")
            msg.setWindowTitle("Warning")
            msg.exec_()

if __name__ == '__main__':
    import sys
    if not QtWidgets.QApplication.instance():
        app = QApplication(sys.argv)
    else:
        app = QtWidgets.QApplication.instance()
    window  = ASWA_MainWindow()
    window.show()
    # t= threading.Thread(target=window.Update)
    # t.start()
    app.exec_()