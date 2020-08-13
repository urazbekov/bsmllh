#uncrustify -c /usr/local/share/uncrustify/d.cfg -f main.cpp -o main.cpp
clear
if g++ -Wall -I/usr/local/include -c *.cpp;
g++ -L/usr/local/lib -o main.exe *.o -lgsl -lgslcblas -lm; then
./main.exe
fi
