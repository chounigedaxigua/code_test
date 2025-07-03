#!/bin/sh

### BEGIN INIT INFO
# Provides:     test
# Required-Start:  $remote_fs $syslog
# Required-Stop:   $remote_fs $syslog
# Default-Start:   2 3 4 5
# Default-Stop:   0 1 6
# Short-Description: start test
# Description:    start test
### END INIT INFO

while :
do
    stillRunning=`ps -ef|grep wifi_tcp|grep -v "grep" | wc -l`
    echo $stillRunning
    if [ $stillRunning -eq 1 ];  
    then
	logger -i "runing..."
	echo "running..."
        sleep 10
    else
	logger -i "start monitor"
        /etc/init.d/wifi_tcp &
	echo "start"
    fi
    sleep 10
 done

 exit 0

