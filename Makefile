target:
	g++ -c main.cpp
	g++ -o producer main.o
	g++ -c consumer.cpp
	g++ -o consumer consumer.o
