test:main.o 
	g++ -o test main.o -std=c++11
String:String.o main.o
	g++ -o String String.o main.o -std=c++11
String.o:String.cpp
	g++ -c String.cpp -std=c++11
main.o:main.cpp Vector.h
	g++ -c main.cpp -std=c++11
clean:
	rm -rf *.o
