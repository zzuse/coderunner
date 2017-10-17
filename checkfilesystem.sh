#!/bin/bash
moudel_code[112]="/dev/disk1"
echo "-------------------check filesystem---------------------------"
i=112
maxvalue=90
while [ $i -lt 113 ]; do
i_warning_size=$(df |grep ${moudel_code[$i]} |awk '{print $5}' | sed 's/%//g')

case $i in
 101)  file_code="/"
		;;
 102)  file_code="/dev"
		;;
esac

if [ $i -lt 103 ];then
		if [[ $i_warning_size -gt $maxvalue ]] ; then
					now_date=`date '+%Y%m%d_%H:%M:%S'`
					msg="X86告警[BILLING-五星]：$now_date:143主机_"$file_code"_文件系统空间已达到:"$i_warning_size"%"
					echo $msg
					#sendSMS $msg
		fi
else
		if [[ $i_warning_size -gt $maxvalue ]] ; then
			now_date=`date '+%Y%m%d_%H:%M:%S'`
			msg="five star warning：$now_date:localhost_${moudel_code[$i]}_filesystem:"$i_warning_size"%"
			echo $msg
			#sendSMS $msg
		fi
fi
		i=` expr $i + 1 `
done

