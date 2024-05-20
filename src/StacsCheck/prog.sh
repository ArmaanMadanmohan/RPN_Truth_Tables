
tmpfile=`mktemp`
errfile=`mktemp`

./ttable `cat` > $tmpfile 2> $errfile

if [ $? == 0 ]; 
	then cat $tmpfile ; 
	else echo Non-zero return value; 
	fi
rm $tmpfile $errfile


