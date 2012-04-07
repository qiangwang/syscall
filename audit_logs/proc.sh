#!/bin/bash

awk '{print $25}' $1| sort -u
