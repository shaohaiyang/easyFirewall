#!/bin/bash
#---------------mini-rc.lvs_dr-director------------------------
#set ip_forward OFF for vs-dr director (1 on, 0 off)
cat   /proc/sys/net/ipv4/ip_forward
echo 0 >/proc/sys/net/ipv4/ip_forward

#director is not gw for realservers: leave icmp redirects on
echo 'setting icmp redirects (1 on, 0 off) '
echo 1 >/proc/sys/net/ipv4/conf/all/send_redirects
cat    /proc/sys/net/ipv4/conf/all/send_redirects
echo 1 >/proc/sys/net/ipv4/conf/default/send_redirects
cat    /proc/sys/net/ipv4/conf/default/send_redirects
echo 1 >/proc/sys/net/ipv4/conf/eth0/send_redirects
cat    /proc/sys/net/ipv4/conf/eth0/send_redirects

#add ethernet device and routing for VIP 192.168.1.50
#if use backup director ,pay any attention about bellow
/sbin/ifconfig eth0:0 192.168.1.50 broadcast 192.168.1.50 netmask 255.255.255.255 up
/sbin/route add -host 192.168.1.50 dev eth0:0

#listing ifconfig info for VIP 192.168.1.50
/sbin/ifconfig eth0:0
/bin/ping -c 1 192.168.1.50
#listing routing info for VIP 192.168.1.50
/bin/netstat -rn

#setup_ipvsadm_table
#clear ipvsadm table
/sbin/ipvsadm -C

#installing LVS services with ipvsadm
#add telnet to VIP with round robin scheduling
/sbin/ipvsadm -A -t 192.168.1.50:80 -s rr

#forward telnet to realserver using direct routing with weight 1
/sbin/ipvsadm -a -t 192.168.1.50:80 -r 192.168.1.250 -g -w 1
#forward telnet to realserver using direct routing with weight 1
/sbin/ipvsadm -a -t 192.168.1.50:80 -r 192.168.1.2 -g -w 1

#displaying ipvsadm settings
/sbin/ipvsadm
#not installing a default gw for LVS_TYPE vs-dr
#---------------mini-rc.lvs_dr-director------------------------
