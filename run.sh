#!/bin/bash

count=1054560
# run this command: ./bin/enigma --rotor-one III --rotor-two II --rotor-three I --reflector B --ring-settings AAA > /dev/null
# but run it in parallel using GNU parallel
./bin/enigma --rotor-one III --rotor-two II --rotor-three I --reflector B --ring-settings AAA --input "HALLOWORLD"
