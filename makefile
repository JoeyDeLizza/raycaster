OBJS= main.o Cell.o graphics.o core.o

all: $(OBJS)
	g++ -g $(OBJS) -lSDL2
main.o: main.cpp map.h lineseg.h


Cell.o: Cell.h

map.o : map.h Cell.h
##map.o: map.h graphics.o Cell.o
graphics.o: graphics.h
core.o: core.h
run: all
	./a.out
debug: 
	g++ -g main.cpp core.cpp graphics.cpp Cell.cpp -lSDL2
clean:
	rm a.out *.o
