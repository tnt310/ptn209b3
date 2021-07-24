import sqlite3
class Database:
    def __init__(self,db):
        self.conn = sqlite3.connect(db)
        self.cur = self.conn.cursor()
        # self.cur.execute("CREATE TABLE IF NOT EXISTS book (id INTEGER PRIMARY KEY, title TEXT, "
        #             "author TEXT, year INTEGER, isbn INTEGER)")
        self.cur.execute("CREATE TABLE IF NOT EXISTS device (id INTEGER PRIMARY KEY,\
                        port TEXT, slave INTEGER,func INTEGER,channel INTEGER, datatype TEXT,\
                        devicetype TEXT,devicename TEXT,channeltitle TEXT,\
                        valuetype TEXT,scale INTEGER)")
        self.conn.commit()

    # def insert(self,title, author, year, isbn):
    #     #the NULL parameter is for the auto-incremented id
    #     self.cur.execute("INSERT INTO book VALUES(NULL,?,?,?,?)", (title,author,year,isbn))
    #     self.conn.commit()
    def insert(self,port,slave,func,channel,datatype,devicetype,devicename,title,valuetype,scale):
        #the NULL parameter is for the auto-incremented id
        self.cur.execute("INSERT INTO device \
                          VALUES (NULL,?, ?,?,?,?,?,?,?,?,?)",\
                         (port,slave,func,channel,datatype,devicetype,devicename,\
                         title,valuetype,scale))
        self.conn.commit()
    def view(self):
        self.cur.execute("SELECT * FROM device")
        rows = self.cur.fetchall()
        print(rows)
        return rows
    def showDatabase(self):
        self.cur.execute("SELECT id, slave, func, channel, datatype,\
                        devicetype, devicename, channeltitle, \
                        valuetype, scale FROM device")
        result = self.cur.fetchall()
        for x in result:
            print(x)

    def search(self,title="", author="", year="", isbn=""):
        # self.cur.execute("SELECT * FROM book WHERE title = ? OR author = ? OR year = ? "
        #             "OR isbn = ?", (title, author, year, isbn))
        self.cur.execute("SELECT * FROM book WHERE title = ?", (title,))
        rows = self.cur.fetchall()
        print(rows[0][0])
        #conn.close()
        return rows

    def delete(self,id):
        self.cur.execute("DELETE FROM device WHERE id = ?", (id,))
        self.conn.commit()
        #conn.close()

    def update(self,id, title, author, year, isbn):
        self.cur.execute("UPDATE book SET title = ?, author = ?, year = ?, isbn = ? WHERE id = ?", (title, author, year, isbn, id))
        self.conn.commit()

    def refresh(self):
        self.cur.execute("SELECT DISTINCT devicetype FROM device")
        rows = self.cur.fetchall()
        return rows

    #destructor-->now we close the connection to our database here
    def __del__(self):
        self.conn.close()