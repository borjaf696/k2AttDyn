CC = g++ -std=c++11

# Directories for includes and common classes
IDIR =-I../include/
CDIR=../include/
CDIR2=../include/plib/
CDIR3=../include/sequences/
LDIR=-L/usr/lib64/

#Compiler options
CFLAGS= -c -m64 -O3 -Wall $(IDIR)
LDFLAGS=$(LDIR)

#Sourcers and common classes
SOURCES=main.cpp
CSOURCES=$(CDIR3)dnaSeq.h $(CDIR2)tools.cpp $(CDIR2)k2TreeDyn.cpp $(CDIR2)AttributeV2.cpp $(CDIR2)SchemasV2.cpp  $(CDIR2)buildTree.cpp
#Para poner mas ficheros .cpp que se tienen que ejecutar CSOURCES=$(CDIR) *.cpp

#Objects
OBJECTS=$(SOURCES:.cpp=.o)
COBJECTS=$(CSOURCES:.cpp=.o)
#Igual si hay mas .cpp

#Executable
EXECUTABLE=main

all: $(SOURCES) $(CSOURCES) $(CUSOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(COBJECTS) $(CUOBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o: $(SOURCES) $(CSOURCES)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(CDIR2)*.o
	rm main
