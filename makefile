CC=gcc
AR=ar
OBJECTS_MAIN=main.o
OBJECTS_LIB=graph.o algo.o
FLAGS= -Wall -g

all: libgraph.a graph	
graph: $(OBJECTS_MAIN) libgraph.a 
	$(CC) $(FLAGS) -o graph $(OBJECTS_MAIN) libgraph.a
libgraph.a: $(OBJECTS_LIB)
	$(AR) -rcs libgraph.a $(OBJECTS_LIB)	
graph.o: graph.c lib.h 
	$(CC) $(FLAGS) -c graph.c
algo.o: algo.c lib.h
	$(CC) $(FLAGS) -c algo.c
main.o: main.c lib.h  
	$(CC) $(FLAGS) -c main.c 


.PHONY: clean all

clean:
	rm -f *.o *.a graph