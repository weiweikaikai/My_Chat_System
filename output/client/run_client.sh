#!/bin/bash
WORK_PATH=$(pwd)
CLIENT_NAME=udp_client
CLIENT=$WORK_PATH/bin/${CLINET_NAME}
LOG=$WORK_PATH/log/client.log
CONF=$WORK_PATH/conf/client.conf



function print_log()
{
	local msg="$1"
	local level="$2"
	local date=$(date +%Y_%m_%d_%H/%M/%S)
	echo "[$date]    [$msg]     [$level]" >> $LOG
}


ip=$(more $CONF | grep 'IP' | awk -F':' '{print $2}' | tr -d ' ')
port=$(more $CONF | grep 'PORT' | awk -F':' '{print $2}' | tr -d ' ')

./bin/$CLIENT_NAME $ip $port
