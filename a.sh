#!/bin/bash

current_time_in_seconds=$(date +%s)


#curl localhost:17576 -X POST --data "@example.json"  -H "Content-Type: application/json" > /dev/null
# launch 17576 curl requests in parallel but max 1000 at a time

start_time_in_seconds=$(date +%s)


for i in {1..17576}
do
    curl localhost:17576 -s -X POST --data "@example.json"  -H "Content-Type: application/json" > /dev/null 
    echo "Request $i sent"
done

current_time_in_seconds=$(date +%s)

echo "Time taken: $((current_time_in_seconds - start_time_in_seconds)) seconds"



