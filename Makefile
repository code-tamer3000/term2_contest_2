.PHONY: all clean install uninstall

CC=g++
CFLAGS=-c 
LDFLAGS=
SOURCES= task_2_1IGraph.cpp graph_implementation/ListGraph.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= task_2_1s
PREFIX = 

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)	
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf main *.o
install:
	install $(EXECUTABLE) $(PREFIX)
uninstall:
	rm -rf $(PREFIX)
	