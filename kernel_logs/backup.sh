#!/bin/bash

date=$(date +%Y-%m-%d@%H:%M:%S)

mv syscall.log syscall/syscall_${date}.log
mv clean.log clean/clean_${date}.log
