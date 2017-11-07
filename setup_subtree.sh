esp8266=$(git remote | grep "thanh_esp8266")
servo=$(git remote | grep "thanh_servo")
stm32=$(git remote | grep "thanh_stm32")
if  [ ! -z "$esp8266" ] ; then
	echo "Adding remote $esp8266 to subtree $esp8266 "
    git subtree add --prefix=$esp8266   $esp8266 master
    git fetch $esp8266 master
fi

if  [ ! -z "$servo" ] ; then
	echo "Adding remote $servo to subtree $servo "
    git subtree add --prefix=$servo   $servo master
    git fetch $servo master
fi

if  [ ! -z "$stm32" ] ; then
	echo "Adding remote $stm32 to subtree $stm32 "
    git subtree add --prefix=$stm32   $stm32 master
    git fetch $stm32 master
fi




