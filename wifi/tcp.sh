#!/usr/bin/expect
spawn /etc/init.d/wifi_tcp &
expect "*password*" {send "1\n"}
expect eof
 

