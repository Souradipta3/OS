#!/bin/bash

echo "Enter a number:"
read num

reverse=0
original=$num

while [ $num -ne 0 ]; do
    digit=$((num % 10))
    reverse=$((reverse * 10 + digit))
    num=$((num / 10))
done

echo "The reverse of $original is $reverse"