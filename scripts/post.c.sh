#!/bin/bash

/sbin/ifconfig > /tmp/ifconfig
/usr/bin/curl -F 'ifconfig=</tmp/ifconfig' 'http://randomfoo.net/status/blueball/update?c'
