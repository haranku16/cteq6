COUNTER=1
while [ $COUNTER -lt 21 ]; do
	root -l "plots.C(0,$COUNTER)" &
	#root -l "plots.C(1,$COUNTER)" &
	#root -l "plots.C(2,$COUNTER)" &
	let COUNTER=COUNTER+1
done
