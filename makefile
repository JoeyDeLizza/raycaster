OBJS=

all: $(OBJS)
	g++ main.cpp $(OBJS)

run:
	./a.out
clean:
	rm a.out *.o
