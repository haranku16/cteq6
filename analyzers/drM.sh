COUNTER=0
while [ $COUNTER -lt 41 ]; do
	root -b "drM.C($COUNTER)" &
	let COUNTER=COUNTER+1
done
