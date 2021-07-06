import os 
import sys
from PyQt5 import QtGui, QtWidgets
from PyQt5.QtCore import pyqtSlot
from PyQt5.QtWidgets import QApplication,QFileDialog,QMainWindow,QMessageBox
from v0 import Ui_MainWindow
import threading
import paho.mqtt.client as mqttclient
import time



class ASWA_MainWindow(QMainWindow,Ui_MainWindow):
    def __init__(self,parent=None):
        super(ASWA_MainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.setupUi(self)
        # self.Temp.setText('qwe')
        # self.Temp.setText(str(i))
    def Update(self):
        i=0
        while(1):
            def on_connect(client,userdata,flags,rc):
                if rc==0:
                    print("Client is connected")
                    global connected
                    connected=True
                else:
                    print("Client is not connected")
            def on_message(client,userdata,message):
                print('haha')
                self.Temp.setText(str(message.payload.decode("utf-8")))
            connected = False
            Messagereceived = False
            broker_address = 'm14.cloudmqtt.com'
            port = 	19613
            user = 'yktdxpqb'
            password = 'VKCG6yboYrYd'

            client = mqttclient.Client("MQTT")
            client.on_message = on_message
            client.username_pw_set(user,password=password)
            client.on_connect = on_connect
            client.connect(broker_address,port=port)
            client.loop_start()
            client.subscribe("An")
            while connected!= True:
                time.sleep(0.2)
            while Messagereceived!=True:
                time.sleep(0.2)

            client.loop_stop()
if __name__ == '__main__':
    import sys
    if not QtWidgets.QApplication.instance():
        app = QApplication(sys.argv)
    else:
        app = QtWidgets.QApplication.instance()
    window  = ASWA_MainWindow()
    window.show()
    t= threading.Thread(target=window.Update)
    t.start()
    app.exec_()