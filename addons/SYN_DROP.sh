#!/bin/sh
#######################################################
# The Scripts written by geminis(shaohaiyang@gmail.com)
#######################################################
## define some vars 
MAX_TOTAL_SYN_RECV="1000"
MAX_PER_IP_SYN_RECV="20"
MARK="SYN_RECV"
PORT="80"
LOGFILE="/var/log/netstat_$MARK-$PORT"
LOGFILE_IP="/var/log/netstat_connect_ip.log"
DROP_IP_LOG="/var/log/netstat_syn_drop_ip.log"

## iptables default rules: accept normailly packages and drop baleful SYN* packages 
#iptables -F -t filter
iptables -A INPUT -p TCP ! --syn -m state --state NEW -j DROP
iptables -A INPUT -p ALL -m state --state INVALID -j DROP
iptables -A INPUT -p ALL -m state --state ESTABLISHED,RELATED -j ACCEPT

## initialize
if [ -z $MARK ];then
	MARK="LISTEN"
fi

if [ -z $PORT ];then
	SPORT="tcp"
else
	SPORT=":$PORT"
fi

## save the results of command netstat to specifal file
netstat -atun|grep $MARK|grep $SPORT 2>&1 >/dev/null >$LOGFILE

REPEAT_CONNECT_IP=`less $LOGFILE|awk '{print $5}'|cut -f1 -d ':'|sort|uniq -d |tee > $LOGFILE_IP`


for i in `less $LOGFILE_IP`;do
	REPEAT_CONNECT_NUM=`grep $i $LOGFILE|wc -l`
	## count repeat connections ,if the accout is large than default number,then drop packages
	if [ $REPEAT_CONNECT_NUM -gt $MAX_PER_IP_SYN_RECV ];then
		echo "$i####$REPEAT_CONNECT_NUM" >> $DROP_IP_LOG
		/sbin/iptables -A SYN_DROP -p ALL -s $i -j DROP
	fi
done

ALL_CONNECT=`uniq -u $LOGFILE|wc -l`
#echo $ALL_CONNECT
## count repeat connections ,if the accout is large than default number,then drop packages
if [ $ALL_CONNECT -gt $MAX_TOTAL_SYN_RECV ];then
	echo $ALL_CONNECT
	exit
fi
