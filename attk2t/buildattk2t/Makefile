CPP=gcc

OBJECTS=obj/basic.o obj/bitrankw32int.o obj/BMap.o obj/zorden.o obj/kTree.o obj/readValues.o obj/dict.o obj/k2t.o
BINS=build_tree
CPPFLAGS=-Wall -g3 -o9
DEST=bin

obj/%.o: src/%.c
	$(CPP) $(CPPFLAGS) -c  $< -o $@ $(linkLib) 

all: bin

bin: $(OBJECTS) $(BINS)

build_tree:
	$(CPP) $(CPPFLAGS) -o $(DEST)/build_tree src/buildTree.c $(OBJECTS) -lm

clean:
	rm -f $(OBJECTS) $(BINS)
	cd $(DEST); rm -f *.a $(BINS)

