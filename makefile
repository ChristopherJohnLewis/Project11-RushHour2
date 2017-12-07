
all: rushhour

rushhour: rushhour.o
	g++ -pg  -o rushhour rushhour.o

clean:
	rm -f rushhour; rm -f rushhour.o
	
rushhour.o: rushhour.cpp 
	g++ -pg -c rushhour.cpp