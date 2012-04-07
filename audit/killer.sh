#!/bin/bash

pids=$(ps aux | grep "$1" | awk '{print $2}')
for pid in $pids
do
    echo "kill $pid."
    kill -9 $pid
done
