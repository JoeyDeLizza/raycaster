OBJS= main.o Cell.o graphics.o

all: $(OBJS)
	g++ $(OBJS) -lSDL2
main.o: Cell.o
Cell.o: Cell.h
##map.o: map.h graphics.o Cell.o
graphics.o: graphics.h
run: all
	./a.out
clean:
	rm a.out *.o
