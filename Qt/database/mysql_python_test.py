import pymysql.cursors
 
# Connect to the database
connection = pymysql.connect(host='localhost',
                             user='root',
                             password='',
                             db='db_mysql_python',
                             charset='utf8mb4',
                             cursorclass=pymysql.cursors.DictCursor)
 
try:
    with connection.cursor() as cursor:
        # Create a new record
        sql = "INSERT INTO `tbl_users` (`email`, `password`) VALUES (%s, %s)"
        cursor.execute(sql, ('webmaster@example.com', 'very-secret'))
 
    # connection is not autocommit by default. So you must commit to save
    # your changes.
    connection.commit()
 
    with connection.cursor() as cursor:
        # Read a single record
        sql = "SELECT `id`, `password` FROM `tbl_users` WHERE `email`=%s"
        cursor.execute(sql, ('webmaster@example.com'))
        result = cursor.fetchone()
        print(result)
finally:
    connection.close()