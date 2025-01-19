#!/bin/bash

echo "Enter the first number:"
read a
echo "Enter the second number:"
read b

a=$((a + b))
b=$((a - b))
a=$((a - b))

echo "After swapping:"
echo "First number: $a"
echo "Second number: $b"