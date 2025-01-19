#!/bin/bash

echo "Enter three numbers:"
read a
read b
read c

if ((a >= b && a >= c)); then
    echo "The largest number is $a"
elif ((b >= a && b >= c)); then
    echo "The largest number is $b"
else
    echo "The largest number is $c"
fi