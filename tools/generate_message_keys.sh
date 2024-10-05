#!/bin/bash

START_LETTER="A"

for i in {1..26}; do
	STARTLETTER_REPEATED_SIX_TIMES=$(echo "$START_LETTER$START_LETTER$START_LETTER$START_LETTER$START_LETTER$START_LETTER")
	./build/enigma --rotor-one 2 --rotor-two 2 --rotor-three 1 -e M3 -ro XMV -rp ABL -rf A -pt $STARTLETTER_REPEATED_SIX_TIMES
	START_LETTER=$(echo "$START_LETTER" | tr "A-Z" "B-ZA")
done
