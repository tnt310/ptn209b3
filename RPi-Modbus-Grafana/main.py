from pymodbus.client.sync import ModbusSerialClient as ModbusClient
from pymodbus.register_read_message import ReadHoldingRegistersResponse
import RPi.GPIO as GPIO
import mysql.connector
import time
import datetime

#DECLARE MySQL DATABASE, CURSOR, TABLE
mydb = mysql.connector.connect(
  host="localhost",
  user="grafana",
  passwd="grafana",
  database="grafana"
)
#DECLARE GPIO FOR LED WARNING
GPIO.setmode(GPIO.BCM)   
GPIO.setup(24, GPIO.OUT)
#CREATE CURSOR TO ACCESS TO DATABASE
mycursor = mydb.cursor()
try :
    while True :
        rtu= ModbusClient(method = "rtu", port="/dev/ttyUSB0", stopbits = 1, bytesize = 8, parity = 'N', baudrate=4800,timeout=0.3)
        connection = rtu.connect()
        if(connection):
            GPIO.output(24, GPIO.LOW)
            a = rtu.read_holding_registers(0x0006,1,unit= 0x01)
            result=((a.registers)[0])
            date = str(datetime.datetime.fromtimestamp(int(time.time())).strftime('%Y-%m-%d %H:%M:%S'))
            sql = "INSERT INTO sensors (lumen, time) VALUES (%s, %s)"
            val = (result, date)
            mycursor.execute(sql, val)
            mydb.commit()
            time.sleep(5)
        else :
            GPIO.output(24, GPIO.HIGH)
            print ("Modbus device connection status: ", connection)
except KeyboardInterrupt:
    pass


