#!/bin/bash

WORK_PATH=$(pwd)
SERVICE_NAME=udp_server
SERVICE=$WORK_PATH/bin/${SERVICE_NAME}
LOG=$WORK_PATH/log/server.log
CONF=$WORK_PATH/conf/server.conf


proc=$(basename $0)


function print_log()
{
	local msg="$1"
	local level="$2"
	local date=$(date +%Y_%m_%d_%H/%M/%S)
	echo "[$date]    [$msg]     [$level]" >> $LOG
}

function server_status()
{
	local ret= $(pidof ${SERVICE_NAME})
	if [ -z ${ret} ];then
		print_log "$SERVICE_NAME status is close ......." "Notice"
		return 1
	else
		print_log "$SERVICE_NAME status is running......" "Notice"
		return 0
	fi
}
function server_start()
{
	if server_status;then
		print_log "$(SERVICE_NAME) is already running ....." "Notice"
	else
		local ip=$(more $CONF | grep 'IP' | awk -F':' '{print $2}' | tr -d ' ')
		local port=$(more $CONF | grep 'PORT' | awk -F':' '{print $2}' | tr -d ' ')
     ./bin/$SERVICE_NAME  ${ip}   ${port}
	 print_log "$SERVICE_NAME running success......" "Notice"
	fi
}
function server_stop()
{
	if server_status; then
		kill -g `pidof $SERVICE_NAME`
		print_log "$SERVICE_NAME stop success......" "Notice"
	else
		print_log "$SERVICE_NAME already stoped......" "Notice"
	fi
}
function  server_restart()
{
	server_stop;
	server_start;
}
function usage()
{
if [ "$#" == "0" ];then
	echo "Usage $0 [start | restart | stop | status ]"
fi
}
case $1 in
	'start' )
    server_start
	;;
	'stop' )
	server_stop
	;;
	'restart' )
	server_restart
	;;
	'status' )
	server_status
	;;
	* )
     usage
	 ;;
 esac


