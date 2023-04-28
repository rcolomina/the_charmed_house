# Docs:
# http://mrbook.org/blog/tutorials/make/
# http://arco.esi.uclm.es/~david.villa/pensar_en_C++/vol1/ch03s11s03.html
# http://stackoverflow.com/questions/16221805/why-isnt-make-detecting-changes-in-header-dependencies

CC=g++
CFLAGS=-g -Wall -std=c++11
LDFLAGS=-lpthread
PATH_TINYXML := ./3rdParty/tinyxml
OBJ_TINYXML := ${PATH_TINYXML}/tinystr.o ${PATH_TINYXML}/tinyxmlerror.o ${PATH_TINYXML}/tinyxml.o ${PATH_TINYXML}/tinyxmlparser.o
INCS := -I${PATH_TINYXML}
EXECUTABLE=main
SRC_FOLDER=src


# Sources and objects to compile main program
SOURCES :=$(shell ls ${SRC_FOLDER}/*.cpp | grep -v "test" | xargs)
OBJECTS := $(SOURCES:.cpp=.o)    

# Sources and objets to compile test classes
TESTCPP := $(wildcard ${SRC_FOLDER}/*test.cpp)
TEST := $(TESTCPP:.cpp=)
SOURCETEST :=$(shell ls ${SRC_FOLDER}/*.cpp | grep -v "test" | grep -v "main.cpp" | xargs)
OBJECTSTEST := $(SOURCETEST:.cpp=.o)    


all: $(EXECUTABLE)
	@echo "End of compilation and program link"

$(EXECUTABLE): $(OBJECTS) $(OBJ_TINYXML)
	@echo "================"
	@echo "Linking objects "
	@echo "================"	
	@echo "OBJECTS LIST = " $(OBJECTS)
	@echo "OBJECTS TINYXML = " $(OBJ_TINYXML)
	@echo "EXECUTABLE NAME = " $(EXECUTABLE)
	$(CC) $(OBJECTS) $(OBJ_TINYXML) $(LDFLAGS) ${INCS} -o $@

$(OBJ_TINYXML):
	cd 3rdParty/tinyxml && make

%.o: %.cpp %.h
	@echo "Generating object code --> " $< 
	$(CC) $(CFLAGS) -c ${INCS} $< -o $@ 

%.o: %.cpp
	@echo "Generating object code --> " $<
	$(CC) $(CFLAGS) -c ${INCS} $< -o $@ 

clean:
	@echo "Cleaning objects and executables"
	rm -f src/*.o src/*.gch core $(EXECUTABLE) src/*_test log.out

cleanall:
	@echo "Cleaning objects and executables and 3rd parties"
	rm -f *.o *.gch core $(EXECUTABLE) *_test log.out
	cd 3rdParty/tinyxml && make clean

test: $(OBJECTSTEST) $(TESTCPP) $(TEST)
	@echo "============="	
	@echo "TESTCPP = " $(TESTCPP)
	@echo "LIST GENERATED: TEST = " $(TEST)
	@echo "Test built ended"

$(TEST): $(OBJECTSTEST) $(TESTCPP) 
	@echo "Building Test "
	$(CC) $(CFLAGS) $@.cpp $(OBJECTSTEST) $(OBJ_TINYXML) ${INCS} -I./ -o $@


factory: factory_test.cpp factory.o objeto.o
	$(CC) $(CFLAGS) $@_test.cpp factory.o objeto.o $(OBJ_TINYXML) ${INCS} -I./ -o $@_test
	@echo "Test built ended"

distance: distance_test.cpp distance.o
	$(CC) $(CFLAGS) $@_test.cpp distance.o -o $@_test
	@echo "Test built ended"

invocador: invocador_test.cpp invocador.o objecto.o
	$(CC) $(CFLAGS) $@.cpp abstract_creator.o activador.o colormod.o conceal.o distance.o entidad.o escenario.o event.o eventsqueue.o factory.o game.o ICommand.o ievent.o inventario.o invocador.o item_creator.o jugador.o logger.o manager.o objeto.o operaciones.o parametros.o property.o $(OBJ_TINYXML) ${INCS} -I./ -o $@_test
	@echo "Test built ended"


#g++ -g -Wall -std=c++11 invocador_test.cpp abstract_creator.o activador.o colormod.o conceal.o distance.o entidad.o escenario.o event.o eventsqueue.o factory.o game.o ICommand.o ievent.o inventario.o invocador.o item_creator.o jugador.o logger.o manager.o objeto.o operaciones.o parametros.o property.o     ./3rdParty/tinyxml/tinystr.o ./3rdParty/tinyxml/tinyxmlerror.o ./3rdParty/tinyxml/tinyxml.o ./3rdParty/tinyxml/tinyxmlparser.o -I./3rdParty/tinyxml -I./ -o invocador_test
