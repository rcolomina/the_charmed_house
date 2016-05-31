# Fuentes: 
# http://mrbook.org/blog/tutorials/make/
# http://arco.esi.uclm.es/~david.villa/pensar_en_C++/vol1/ch03s11s03.html
# http://stackoverflow.com/questions/16221805/why-isnt-make-detecting-changes-in-header-dependencies

CC=g++
CFLAGS=-g -Wall
LDFLAGS=-lpthread

#SOURCES := $(wildcard *.cpp | grep -v "test")
#SOURCES := $(echo $(ls *.cpp | grep -v test))
SOURCES :=$(shell ls *.cpp | grep -v "test" | xargs)


OBJECTS := $(SOURCES:.cpp=.o)    
DEPENDENCIES := $(OBJECTS:.o=.d)
EXECUTABLE=game

PATH_TINYXML := ./3rdParty/tinyxml
OBJ_TINYXML := ${PATH_TINYXML}/tinystr.o ${PATH_TINYXML}/tinyxmlerror.o ${PATH_TINYXML}/tinyxml.o ${PATH_TINYXML}/tinyxmlparser.o

INCS := -I${PATH_TINYXML}

#TESTCPP := $(wildcard ./test/*.cpp)
#TEST := $(TESTCPP:.cpp=)

TESTCPP := $(wildcard *test.cpp)

TEST := $(TESTCPP:.cpp=)

#OBJTEST := $(shell TESTCPP:_test.cpp=.o)
OBJTEST :=$(shell ls *.cpp | grep -v "test" | grep -v "main.cpp" | xargs)

#TESTO := $(TESTCPP:_test.cpp=.o)
#TESTO2 := $(TESTO:./test/=)

all: $(EXECUTABLE)
	@echo "Fin compilacion y linkado del programa"

$(EXECUTABLE): $(OBJECTS)
	@echo "================"
	@echo "Linking objects "
	@echo "================"	
	@echo "OBJECT LIST = " $(OBJECTS)
	@echo "EXECUTABLE NAME = " $(EXECUTABLE)
	$(CC) $(OBJECTS) $(OBJ_TINYXML) $(LDFLAGS) ${INCS} -o $@

%.o: %.cpp %.h
	@echo "Generando codigo objeto --> " $< 
	$(CC) $(CFLAGS) -c ${INCS} $< -o $@ 

%.o: %.cpp
	@echo "Generando codigo objeto --> " $<
	$(CC) $(CFLAGS) -c ${INCS} $< -o $@ 

clean:
	@echo "Borrado de objetos"
	rm -rf *.o *~ *.gch core $(EXECUTABLE)
	rm -f *_test

#test: $(TEST)
#	@echo $(TEST)
#	$(CC) $(CFLAGS) -c ${INCS} $< -o $@ 
#	@echo "Fin compilacion y linkado de test"

test: $(TEST)
	@echo "TESTCPP = " $(TESTCPP)
	@echo "LIST GENERATED: TEST = " $(TEST)
	@echo "Test built ended"

$(TEST):	$(TESTCPP) $(OBJTEST)
	$(CC) $@.cpp $(OBJTEST) $(OBJ_TINYXML) ${INCS} -I./ -o $@


#test%: 

#%.o: %.o
#	@echo "TEST="$(TEST)
#	$(CC) $(TEST) ${INCS} -I./ -o factory_test

#%_test: %_test.o
#	$(CC) $(OBJECTS) -c $(OBJ_TINYXML) $(LDFLAGS) ${INCS} -o $@

#%_test.o:  %_test.cpp
#	@echo "Generando test --> " $<
#	$(CC) $(CFLAGS) -c ${INCS} $< -o $@ 

