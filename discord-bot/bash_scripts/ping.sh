#!/usr/bin/env bash
if ps -p `cat pid.txt` >> /dev/null ; then echo "Bot is running"; else echo "Bot is not running"; fi
