CPP=gcc

OBJECTS=
BINS=parser_Wiki
CPPFLAGS=-Wall -g3 -o9
DEST=bin

obj/%.o: src/%.c
	$(CPP) $(CPPFLAGS) -c  $< -o $@ $(linkLib) 

all: bin

bin: $(OBJECTS) $(BINS)

parser_Wiki:
	$(CPP) $(CPPFLAGS) -o $(DEST)/parser_wiki src/parserWiki.c $(OBJECTS) -lm
cleaner_wiki:
	javac src/cleanerWiki.java -d bin/
clean:
	rm -f $(OBJECTS) $(BINS)
	cd $(DEST); rm -f *.a $(BINS)
