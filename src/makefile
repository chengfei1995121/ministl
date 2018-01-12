String:String.o main.o
	g++ -o String String.o main.o -std=c++11
String.o:String.cpp
	g++ -c String.cpp -std=c++11
main.o:main.cpp 
	g++ -c main.cpp -std=c++11
clean:
	rm -rf *.o
