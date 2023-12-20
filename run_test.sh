#!/bin/bash

printf "Plaintext HALLO Expected Cyphertext MTNCZ: Cybhertext: "
./bin/enigma --enigma M3 \
    --rotor-one 3 \
    --rotor-two 2   \
    --rotor-three 1 \
    --ring-positions AAA \
    --rotor-positions AAA \
    --reflector B   \
    --plaintext HALLO

printf "Plaintext HALLO Expected Cyphertext FVWYT: Cybhertext: "

./bin/enigma --enigma M3 \
    --rotor-one 2 \
    --rotor-two 1 \
    --rotor-three 3 \
    --ring-positions HAS \
    --rotor-positions OIJ \
    --reflector C \
    --plaintext HALLO

printf "reverse: Cybhertext FVWYT Expected Plaintext HALLO: Plaintext: "
./bin/enigma --enigma M3 \
    --rotor-one 2 \
    --rotor-two 1 \
    --rotor-three 3 \
    --ring-positions HAS \
    --rotor-positions OIJ \
    --reflector C \
    --plaintext HALLO
