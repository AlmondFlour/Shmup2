set PATH=%PATH%;C:\MinGW\bin
::g++ -g -fopenmp -c main.cpp level.cpp animation.cpp -IC:\SFML-2.4.1\include
::g++ main.o level.o animation.o -o final -fopenmp  -LC:\SFML-2.4.1\lib -lsfml-graphics -lsfml-window -lsfml-system

cd C:\Code\Shump2

g++ -std=c++14  -g -fopenmp -c gameloop.cpp -IC:\SFML-2.4.1\include
g++ -std=c++14  -c animation.cpp -IC:\SFML-2.4.1\include
g++ -std=c++14 -c unit.cpp -IC:\SFML-2.4.1\include
g++ gameloop.o animation.o unit.o -o Shmup2 -fopenmp  -LC:\SFML-2.4.1\lib -lsfml-graphics -lsfml-window -lsfml-system

pause