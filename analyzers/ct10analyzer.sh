#!/bin/bash
COUNTER=0
while [ $COUNTER -lt 53 ]; do
	root -b "a4.C($COUNTER)" &
	let COUNTER=COUNTER+1
done
