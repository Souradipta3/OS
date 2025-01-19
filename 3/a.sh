#!/bin/bash

echo "Enter a number:"
read num

is_prime=1

for ((i = 2; i * i <= num; i++)); do
    if ((num % i == 0)); then
        is_prime=0
        break
    fi
done

if ((num < 2)); then
    echo "$num is not a prime number."
elif ((is_prime == 1)); then
    echo "$num is a prime number."
else
    echo "$num is not a prime number."
fi