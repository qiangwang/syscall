#!/bin/bash

src=$1
proc=$2

grep "comm=\"$proc\"" $src > "$proc.log"
awk '{print $4}' "$proc.log" | awk -F'=' '{print $2}' > "$proc-call.log"
