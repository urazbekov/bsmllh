#!/bin/bash

a=3
b=9
number1=$((a+RANDOM%(b-a))).$((RANDOM%999))
number2=$((a+RANDOM%(b-a))).$((RANDOM%999))

for filename in *.in; do
  sed -e '3s/.*/ '$number1' '$number2' /' -i '' $filename
  echo "$filename" >> input.txt
  ./thecode.exe < input.txt > "$(basename "$filename" .in).out"
  rm input.txt
  rm cij.data
  rm f*
  echo $(head -n 1 spectr7) >> "$(basename "$filename" .in).sp"
  rm spe*
  cp WF.data "$(basename "$filename" .in).wf"
  rm WF.data
  rm *.out
done
