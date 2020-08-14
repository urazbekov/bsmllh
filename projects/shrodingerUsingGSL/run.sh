#!/bin/bash
if g++ -Wall -I/usr/local/include -c *.cpp; then
  if g++ -L/usr/local/lib -o main.exe *.o -lgsl -lgslcblas -lm; then
  echo "Jaraisyn :)"
  ./main.exe
  else
    echo echo "Birdenki durys bolmai qaldy... Asyqpai jaqsylap qara :)";
  fi
else
  echo "Birdenki durys bolmai qaldy... Asyqpai jaqsylap qara :)";
fi
