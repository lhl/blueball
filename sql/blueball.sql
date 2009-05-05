-- DATABASE
create database blueball;
use blueball;

-- USERS
GRANT ALL PRIVILEGES ON blueball.* TO 'blueball'@'localhost' IDENTIFIED BY 'blueball';
-- GRANT ALL PRIVILEGES ON blueball.* TO 'blueball'@'IP' IDENTIFIED BY PASSWORD 'blueball';
-- GRANT ALL PRIVILEGES ON blueball.* TO 'blueball'@'IP' IDENTIFIED BY PASSWORD 'blueball';

DROP TABLE IF EXISTS devices;
CREATE TABLE devices (
  id CHAR(20) NOT NULL, 
  name VARCHAR(255) default '',
  service VARCHAR(255) default '',
  major VARCHAR(255) default '',
  minor VARCHAR(255) default '',
  lastseen INT(11) default NULL,
  a_seen INT(11) default NULL,
  b_seen INT(11) default NULL,
  c_seen INT(11) default NULL,
  total_count INT(11) default 1,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS history;
CREATE TABLE history (
  id CHAR(20) NOT NULL, 
  name VARCHAR(255) default '',
  type INT(11) default NULL,
  scantime INT(11),
  sensor VARCHAR(255)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
