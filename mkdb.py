#!/usr/bin/python

import sqlite3

conn = sqlite3.connect('blueball.db')
c = conn.cursor()

# Create Tables
c.execute('''create table devices
(id TEXT PRIMARY KEY, 
 name TEXT DEFAULT '',
 service TEXT DEFAULT '',
 major TEXT DEFAULT '',
 minor TEXT DEFAULT '',
 lastseen INTEGER,
 a_seen INTEGER,
 b_seen INTEGER,
 total_count INTEGER DEFAULT 0)''')

c.execute('''create table history
(id TEXT, 
 name TEXT,
 type INTEGER,
 scantime INTEGER,
 sensor TEXT)''')

conn.commit()

c.close()
