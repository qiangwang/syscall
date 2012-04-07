#!/bin/bash

grep -aP '^\d{1,3},\d+,[a-zA-Z_\-]+$' syscall.log > clean.log

awk -F[,] '{print $1}' clean.log  | sort -u
