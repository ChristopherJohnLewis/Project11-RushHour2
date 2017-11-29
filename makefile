
all: rushhour

rushhour: rushhour.o Timer.o
	g++ -pg  -o rushhour rushhour.o Timer.o

Timer.o: Timer.cpp
	g++ -pg -c Timer.cpp

clean:
	rm -f rushhour; rm -f rushhour.o
	
rushhour.o: rushhour.cpp 
	g++ -pg -c rushhour.cpp