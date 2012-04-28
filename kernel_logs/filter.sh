#!/bin/bash

grep -aPv "^(265|119|240)," $1 > "$1-filter.log"
