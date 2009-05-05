#!/bin/bash

# INSTALL MySQL 5
sudo port selfupdate
sudo port -d sync
sudo portindex
sudo port upgrade installed
sudo port clean mysql5
sudo port -v install mysql5 +server
sudo -u mysql mysql_install_db5
sudo -u mysql /opt/local/lib/mysql5/bin/mysqld_safe &

/opt/local/lib/mysql5/bin/mysql -u root < blueball.sql
