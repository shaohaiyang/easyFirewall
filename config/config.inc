#################################################
IPT="/sbin/iptables"
HOST_CONF="/etc/init.d/functions"
HOST2_CONF="/etc/sysconfig/network"
DHCP_CONF="/etc/sysconfig/dhcpd"
DHCP_CONF2="/etc/dhcpd.conf"
DHCP_CONF3="/etc/sysconfig/dhcrelay"
THTTP_CONF="/etc/thttpd_config"
SSHD_CONF="/etc/ssh/sshd_config"
SQUID_CONF="/etc/squid/squid.conf"
VPN_CONF="/etc/openvpn/server.conf"
VPN_CLIENT_CONF="/etc/openvpn/client.ovpn"
PPP_CONF="/etc/ppp/ifcfg-ppp0"
PPP_PAP_CONF="/etc/ppp/pap-secrets"
PPTP_CONF="/etc/pptpd.conf"
PPTP_OPT_CONF="/etc/ppp/options.pptpd"
PPTP_CHAP_CONF="/etc/ppp/chap-secrets"
FIREWALL_PID="/var/run/firewall.pid"
POLICY_PID="/var/run/policy.pid"
ROUTE_TO="/config/.config/route_to"
ROUTE_FROM="/config/.config/route_from"

LOOP_IF=lo
BROADCAST_SRC="0.0.0.0"
BROADCAST_DEST="255.255.255.255"

# Protocols Configuration
# Private Ports
PRIVPORTS="0:1023"
UNPRIVPORTS="1024:65535"

# openvpn (tap+ or tun+) interface
VPN_IF=ppp+

# PPP interface
PPP_IF=ppp0

# Don't Change!
FTP_DATA_PORT="20"
FTP_PORT="21"
WHOIS_PORT="43"
NTP_PORT="123"
DNS_PORT="53"
SMB_PORT="135 139 445"

#################################################
DOMAIN=54geke.com
HOSTNAME=PLFirewall

# PPP function with adsl connection
PPP_ENABLE="NO"
PPP_USER="xs751238"
PPP_PASS="mixnijs"
PPP_DEV="eth0"
PPP_TIMEOUT="30"

# Enable OPENVPN or PPTP or NO
VPN_ENABLE="NO"

OPENVPN_PORT=1194
VPN_NET="10.10.8.1|255.255.255.0"
VPN_ROUTER="eth0|192.168.1.0#255.255.255.0"

PPTP_PORT="1723"
PPTP_DEV="eth0"
PPTP_RANGE="192.168.1.31-40"

# You can change
PING_HOST="0.0.0.0/0"

# FW_TYPE: firewall types as :
# 0 -> single host
# 1 -> gateway with NAT
# 2 -> gateway with DMZ
FW_TYPE=0

# Syn-flood protection:
ANTI_DDOS="YES"
SYN_ANTI_DDOS="22@TCP@connlimit#5 53@TCP@connlimit#30 53@UDP@limit#100/s#150 #8080@TCP@recent#60#8"

# Extern DNS-Servers
EXT_DNS_QUERY=ALL
EXT_DNS="202.101.172.35 202.101.172.46 202.96.96.68 "

# Squid Port
SQUID_RUN=NO
SQUID_PROXY_AUTH=NO
SQUID_PORT=3128
SQUID_RAMDISK=YES
SQUID_QUOTA=100
SQUID_BAD="sex"
SQUID_EMAIL="postmaster@audividi.com"

# Trans-proxy REDIRECT_ENABLE: YES NO
REDIRECT_ENABLE=NO
#REDIRECT_PORTS="eth1#eth0|192.168.1.9|!192.168.3.0/24"
REDIRECT_PORTS="eth1#eth0"

# DHCPD configuration
DHCP_RUN=NO
DHCP_DEV="eth1"
DHCP_SET="eth1#43200#51|250@geminis|192.168.1.30|00:18:8b:c3:e3:c3"

# FORWARD_RULE Format: ALL LIMIT eth1|eth0
# Limit Time Format: &00:00|18:00|Mon,Tue
#FORWARD_RULE="ALL&00:00|17:30|Mon,Tue,Wed,Thu,Fri,Sat,Sun"
#FORWARD_RULE="eth1|eth0&00:00|17:30|Mon,Tue,Wed,Thu eth1|eth3"
FORWARD_RULE="ALL"

# IP router
IPROUTER=0

#############################################
#LAN_IF="eth1|office|static|192.168.1.1|255.255.255.0|192.168.1.1#1500 eth2|wireless|static|192.168.2.1|255.255.255.0|192.168.2.1#1500 eth3|dmz|static|192.168.3.1|255.255.255.0|192.168.3.1#1500"
EXT_IF="eth1|eth1-WAN|static|192.168.0.1|255.255.255.0|192.168.0.1#1500 eth0:1|eth0:1-WAN|static|124.160.126.242|255.255.255.240|124.160.126.241#1500 *eth0|eth0-WAN|static|115.236.19.66|255.255.255.240|115.236.19.65#1500"

# Private Network
RESERVED_NET="192.168.0.0/16 10.0.0.0/8 172.16.0.0/12 224.0.0.0/4 240.0.0.0/5 127.0.0.0/8 0.0.0.0/8 169.254.0.0/16 192.0.2.0/24"
PREVENT_NET=""

# Drop some url which contain bad words or bad protocols
DROP_URL=""
GOOD_URL=""

# Format    port[#address] ex. 80 |192.168.1.6 21|192.168.0.0/24 137:139|192.168.0.0/24
#SRV_IN_PORTS="53 80|192.168.0.0/24 63306|192.168.0.0/24 3306|192.168.0.0/24 3307|192.168.0.0/24 10051|192.168.0.0/24 10051|122.227.58.118/26 10051|60.12.147.161/24 10051|60.191.223.34/25"
SRV_IN_PORTS="53 80 10051|122.227.58.118/26 10051|60.12.147.161/24 10051|60.191.223.34/25"
SRV_OUT_PORTS=""

# White List and Black List
WHITE_LIST="s#192.168.0.0/24"
BLACK_LIST=""

# TOS Setting
TOS_SET="All|53,80|16"

# TOS Mark
TOS_MARK=""

# FORWARD PORTS Format: protocol # in-interface#out-interface # allowed ports#allowed dest-address # allowed src-address
FORWARD_PORTS=""

# FORWARD Services to LAN
FORWARD_SERVICES=""
