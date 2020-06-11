contactAPP: contact.o main.o
	g++ contact.o main.o -o contactAPP
contact.o: contact.cpp
	g++ contact.cpp -c -o contact.o
main.o: main.cpp
	g++ main.cpp -c -o main.o
