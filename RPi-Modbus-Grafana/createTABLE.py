import mysql.connector

#CREATE MySQL DATABASE, CURSOR, TABLE
mydb = mysql.connector.connect(
  host="localhost",
  user="grafana",
  passwd="grafana",
  database = "grafana"
)
mycursor = mydb.cursor()
mycursor.execute("CREATE TABLE sensors (id INT AUTO_INCREMENT PRIMARY KEY, lux VARCHAR(255), time VARCHAR(255))")

        