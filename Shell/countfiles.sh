i_retval=0
s_getline_buf="/usr/local/bin;50\r\n"
declare -i s_warning_maxvalue
s_path_buf=`echo $s_getline_buf | awk -F ';' '{print $1}'`
s_warning_maxvalue=$(echo -e $s_getline_buf | awk -F ';' '{print $2}'| tr -d '\r')
echo $s_warning_maxvalue
s_remark_flag=`echo $s_getline_buf|cut -c1-1`
if [ "$s_remark_flag" != "#" ];then
	i_retval=$(ls $s_path_buf|grep -v "process.lock"|wc -l)
	echo "check" $i_retval
	echo "barrier" $s_warning_maxvalue
	if [[ $i_retval -gt $s_warning_maxvalue ]] ; then
	#if (( $i_retval > $s_warning_maxvalue )) ; then
		now_date=`date '+%Y%m%d_%H:%M:%S'`
		msg="X86 five star：$now_date: $s_path_buf have $i_retval file!"
		echo $msg
		#sendSMS $msg
	fi
fi
