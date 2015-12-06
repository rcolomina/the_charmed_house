# Fuentes: 
# http://mrbook.org/blog/tutorials/make/
# http://arco.esi.uclm.es/~david.villa/pensar_en_C++/vol1/ch03s11s03.html
# http://stackoverflow.com/questions/16221805/why-isnt-make-detecting-changes-in-header-dependencies

CC=g++
CFLAGS=-g -Wall
LDFLAGS=-lpthread
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
DEPENDENCIES := $(OBJECTS:.o=.d)
EXECUTABLE=miprograma

all: $(SOURCES) $(EXECUTABLE)
	@echo "Fin compilacion y linkado del programa"

$(EXECUTABLE): $(OBJECTS) 
	@echo "Linkando los objetos " 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.cpp %.h
	@echo "Generando codigo objeto --> " $< 
	$(CC) $(CFLAGS) -c $< -o $@ 

%.o: %.cpp
	@echo "Generando codigo objeto --> " $<
	$(CC) $(CFLAGS) -c $< -o $@ 


clean:
	@echo "Borrado de objetos"
	rm -rf *.o *~ *.gch core
	rm $(EXECUTABLE)

