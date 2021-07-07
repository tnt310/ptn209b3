import os 
import sys
from PyQt5.uic import loadUi
from PyQt5 import QtGui, QtWidgets
from PyQt5.QtWidgets import QMessageBox
from PyQt5.QtCore import pyqtSlot
from PyQt5.QtWidgets import QApplication,QFileDialog,QMainWindow,QMessageBox
# from testtool_login import TesttoolLogin_frame
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from testtool_login import *
import paho.mqtt.client as mqttclient

def on_connect(client,userdata,flags,rc):
    print("Connected with code : " + str(rc))
    if rc == 0:
        client.subscribe("up/command")


def on_message(client,userdata,msg):
    global temp_receive
    temp_receive = str(msg.payload.decode("utf-8"))

client = mqttclient.Client()
client.on_connect=on_connect
client.on_message=on_message

class MqttThread(QMainWindow,TesttoolLogin_frame):
    def __init__(self):
        super(MqttThread, self).__init__(parent)

    def connect_server(self):
        broker = TesttoolLogin_frame.server.text()
        user = TesttoolLogin_frame.mqtt_user.text()
        password = TesttoolLogin_frame.mqtt_pwd.text()
        port = int(TesttoolLogin_frame.mqtt_port.text())
        client.username_pw_set(user,password)
        client.connect(broker,self.port,60)
        client.loop_start()

    def disconnect_server(self):
        client.loop_stop(self)
        client.disconnect()
