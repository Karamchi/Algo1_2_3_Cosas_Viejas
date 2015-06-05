CC=g++

CFLAGS=-g -Wall

LDFLAGS=

INCDIR=

SOURCES=t.cpp aux/matriz.cpp aux/Parabrisas.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=tp

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) -I$(INCDIR) $(CFLAGS) $< -c -o $@
