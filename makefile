OBJS= main.o coord.o lineseg.o Cell.o graphics.o core.o vec2.o geometry.o

all: $(OBJS)
	g++ -g $(OBJS) -lSDL2
main.o: main.cpp map.h

lineseg.o: lineseg.h

coord.o: coord.h lineseg.h

Cell.o: Cell.h

geometry.o : geometry.h point.h

map.o : map.h Cell.h
##map.o: map.h graphics.o Cell.o
graphics.o: graphics.h point.h
vec2.o: vec2.h
core.o: core.h lineseg.h
run: all
	./a.out
debug: 
	g++ -ggdb main.cpp core.cpp graphics.cpp geometry.cpp vec2.cpp Cell.cpp -lSDL2
clean:
	rm a.out *.o
