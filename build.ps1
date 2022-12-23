cd projectfiles


g++ -c *.cpp
g++ -o out/main.exe *.o
rm *.o
rm *.gch
./out/main.exe


cd ..