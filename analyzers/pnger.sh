COUNTER=1
while [ $COUNTER -lt 41 ]; do
	root -l "pnger.C($COUNTER)" &
	let COUNTER=COUNTER+1
done
