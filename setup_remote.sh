esp8266=$(git remote | grep "thanh_esp8266")
servo=$(git remote | grep "thanh_servo")
stm32=$(git remote | grep "thanh_stm32")
if  [ ! -z "$esp8266" ] ; then
	echo "remote $esp8266 is existed"
else
    git remote add thanh_esp8266 https://github.com/quangthanh010290/esp8266.git
fi

if  [ ! -z "$servo" ] ; then
	echo "remote $servo is existed"
else
    git remote add thanh_servo https://github.com/quangthanh010290/ArduinoServo.git
fi

if  [ ! -z "$stm32" ] ; then
	echo "remote $stm32 is existed"
else
    git remote add thanh_stm32 https://github.com/quangthanh010290/STM32_Arduino.git
fi




