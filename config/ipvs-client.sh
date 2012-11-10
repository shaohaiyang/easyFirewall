#!/bin/bash
#
# hidden 	This shell script takes care of starting and stopping
#		the ipvs-hidden subsystem (hiddend).
#
# chkconfig: 2345 78 12
# description:	ipvs-hidden
# processname: hiddend
prog="hidden"
start(){
	echo 0 >/proc/sys/net/ipv4/ip_forward
	/sbin/ifconfig lo:0 192.168.1.50 broadcast 192.168.1.50 netmask 255.255.255.255 up
	# installing route for VIP 192.168.1.110 on device lo:0
	/sbin/route add -host 192.168.1.50 dev lo:0
	# listing routing info for VIP 192.168.1.50
	/bin/netstat -rn
	# hiding interface lo:0, will not arp
	echo "1">/proc/sys/net/ipv4/conf/lo/arp_ignore
	echo "2">/proc/sys/net/ipv4/conf/lo/arp_announce
	echo "1">/proc/sys/net/ipv4/conf/all/arp_ignore
	echo "2">/proc/sys/net/ipv4/conf/all/arp_announce
}
stop(){
	echo 1 >/proc/sys/net/ipv4/ip_forward
	/sbin/ifconfig lo:0 192.168.1.50 broadcast 192.168.1.50 netmask 255.255.255.255 down
	/sbin/route del -host 192.168.1.50 dev lo:0
	echo "0">/proc/sys/net/ipv4/conf/lo/arp_ignore
	echo "0">/proc/sys/net/ipv4/conf/lo/arp_announce
	echo "0">/proc/sys/net/ipv4/conf/all/arp_ignore
	echo "0">/proc/sys/net/ipv4/conf/all/arp_announce
}
 
restart(){
	stop
        start
	}

condrestart(){
	[ -e /var/lock/subsys/hiddend ] && restart || :
	}

# See how we were called.
case "$1" in
	start)
		start ;;
	stop)
		stop ;;
	restart)
		restart ;;
	*)
		echo $"Usage: $0 {start|stop|restart}"
esac
exit $?

