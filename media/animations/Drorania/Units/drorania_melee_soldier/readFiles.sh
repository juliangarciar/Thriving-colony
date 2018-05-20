function readFiles() {
	cd $1
	for entry in "."/*
	do
	  	if [ -f "$entry" ];then
			before="\"$entry\","
			after=$(sed 's/\.\///g' <<< $before)
			echo $after
	  	fi
	done
}

readFiles $1
