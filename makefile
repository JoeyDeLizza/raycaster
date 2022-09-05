OBJS= tgaimage.o

all: $(OBJS)
	g++ main.cpp $(OBJS)

run:
	./a.out
