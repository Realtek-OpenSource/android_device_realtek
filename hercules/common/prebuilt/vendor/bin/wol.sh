#!/system/bin/sh
HAS_WOL=`cat /sys/kernel/suspend/wakeup|grep "* lan"`
ENABLE="$1"
# echo "$HAS_WOL"
if [ "$HAS_WOL" ];then
	logwrapper echo "wol enabled"
	if [ $ENABLE == "0" ]; then
		logwrapper echo "disable wol now"
		echo lan > /sys/kernel/suspend/wakeup
		echo 0 > /proc/net/eth0/r8169/wol_enable
	fi
else
	logwrapper echo "wol disabled"
	if [ $ENABLE == "1" ]; then
		logwrapper echo "enable wol now"
		echo lan > /sys/kernel/suspend/wakeup
		echo 1 > /proc/net/eth0/r8169/wol_enable
	fi
fi
