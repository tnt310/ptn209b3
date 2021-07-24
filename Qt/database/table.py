DROP DATABASE IF EXISTS `db_mysql_python`;
CREATE DATABASE `db_mysql_python`
  DEFAULT CHARACTER SET utf8   #https://dev.mysql.com/doc/refman/5.7/en/charset-applications.html
  DEFAULT COLLATE utf8_general_ci;

USE `db_mysql_python`;

CREATE TABLE `tbl_users` (
  `userID`  int(11) UNSIGNED NOT NULL auto_increment,
  `email` varchar(255)  NOT NULL,
  `password` varchar(255) NOT NULL,
   
  PRIMARY KEY (`userID`)
) ENGINE=InnoDB;