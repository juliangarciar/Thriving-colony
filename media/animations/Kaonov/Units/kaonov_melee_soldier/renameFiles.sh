for entry in "$1"/*
do
  if [ -f "$entry" ];then
	renamed=$(sed 's/repose/idle/g' <<< $entry)
	mv $entry $renamed
    	echo "$entry -> $renamed"
  fi
done
