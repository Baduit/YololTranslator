#!/usr/bin/env bash
if ps -p `cat pid.txt` >> /dev/null ; then echo "API is running"; else echo "API is not running"; fi