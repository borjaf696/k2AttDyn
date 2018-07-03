CPP=gcc

OBJECTS= bin/MemoryManager.o bin/basic.o bin/bitrankw32int.o bin/kTree.o bin/kTreeMulti.o bin/mymalloc.o bin/Buffer.o bin/AttK2T.o bin/AttList.o bin/schema.o bin/operations.o
BINS=query query_gen
#CPPFLAGS=-Wall -g3 
CPPFLAGS=-Wall -g -DNDEBUG 
DEST=bin/

bin/%.o: src/%.c
	$(CPP) $(CPPFLAGS) -c $< -o $@

all: binaries

binaries: $(OBJECTS) $(BINS)

query_gen:
	gcc $(CPPFLAGS) -o $(DEST)/query_gen src/queryGen.c $(OBJECTS) -lm

query:
	gcc $(CPPFLAGS) -o $(DEST)/query src/query.c $(OBJECTS) -lm

clean:
	rm -f $(OBJECTS) $(BINS)
	cd $(DEST); rm -f *.a $(BINS)
