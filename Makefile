# Docs:
# http://mrbook.org/blog/tutorials/make/
# http://arco.esi.uclm.es/~david.Villa/pensar_en_C++/vol1/ch03s11s03.html
# http://stackoverflow.com/questions/16221805/why-isnt-make-detecting-changes-in-header-dependencies

CC=g++
CFLAGS=-g -Wall -std=c++11
LDFLAGS=-lpthread

# Directories
SRC_DIR := src
LIB_DIR := lib
PATH_TINYXML := ./3rdParty/tinyxml

# Include paths - add src/ and lib/ to include search paths
INCS := -I. -I${SRC_DIR} -I${LIB_DIR} -I${PATH_TINYXML}

# Executable name
EXECUTABLE := main

# TinyXML objects
OBJ_TINYXML := ${PATH_TINYXML}/tinystr.o ${PATH_TINYXML}/tinyxmlerror.o ${PATH_TINYXML}/tinyxml.o ${PATH_TINYXML}/tinyxmlparser.o

# Find all .cpp source files recursively (excluding tests)
SOURCES := $(shell find ${SRC_DIR} ${LIB_DIR} -name '*.cpp' ! -name '*_test.cpp')
OBJECTS := $(SOURCES:.cpp=.o)

# Find all test files
TESTCPP := $(shell find ${SRC_DIR}/tests -name '*_test.cpp' 2>/dev/null)
TEST := $(TESTCPP:.cpp=)

# Objects for tests (everything except main.cpp and test files)
SOURCETEST := $(shell find ${SRC_DIR} ${LIB_DIR} -name '*.cpp' ! -name '*_test.cpp' ! -name 'main.cpp')
OBJECTSTEST := $(SOURCETEST:.cpp=.o)

.PHONY: all clean cleanall test

all: $(EXECUTABLE)
	@echo "End of compilation and program link"

$(EXECUTABLE): $(OBJECTS) $(OBJ_TINYXML)
	@echo "================"
	@echo "Linking objects "
	@echo "================"
	@echo "OBJECTS LIST = " $(OBJECTS)
	@echo "OBJECTS TINYXML = " $(OBJ_TINYXML)
	@echo "EXECUTABLE NAME = " $(EXECUTABLE)
	$(CC) $(OBJECTS) $(OBJ_TINYXML) $(LDFLAGS) -o $@

$(OBJ_TINYXML):
	cd 3rdParty/tinyxml && make

# Pattern rule for .cpp with matching .h
%.o: %.cpp %.h
	@echo "Generating object code --> " $<
	$(CC) $(CFLAGS) -c ${INCS} $< -o $@

# Pattern rule for .cpp without .h
%.o: %.cpp
	@echo "Generating object code --> " $<
	$(CC) $(CFLAGS) -c ${INCS} $< -o $@

clean:
	@echo "Cleaning objects and executables"
	find ${SRC_DIR} ${LIB_DIR} -name '*.o' -delete 2>/dev/null || true
	find ${SRC_DIR} ${LIB_DIR} -name '*.gch' -delete 2>/dev/null || true
	rm -f core $(EXECUTABLE) log.out
	find ${SRC_DIR}/tests -type f ! -name '*.*' -delete 2>/dev/null || true

cleanall:
	@echo "Cleaning objects and executables and 3rd parties"
	find ${SRC_DIR} ${LIB_DIR} -name '*.o' -delete 2>/dev/null || true
	find ${SRC_DIR} ${LIB_DIR} -name '*.gch' -delete 2>/dev/null || true
	rm -f *.o *.gch core $(EXECUTABLE) log.out
	find ${SRC_DIR}/tests -type f ! -name '*.*' -delete 2>/dev/null || true
	cd 3rdParty/tinyxml && make clean

test: $(OBJECTSTEST) $(TESTCPP) $(TEST)
	@echo "============="
	@echo "TESTCPP = " $(TESTCPP)
	@echo "LIST GENERATED: TEST = " $(TEST)
	@echo "Test built ended"

$(TEST): $(OBJECTSTEST) $(TESTCPP)
	@echo "Building Test: $@"
	$(CC) $(CFLAGS) $@.cpp $(OBJECTSTEST) $(OBJ_TINYXML) ${INCS} $(LDFLAGS) -o $@

# Individual test targets for convenience
factory_test: ${SRC_DIR}/tests/factory_test.cpp $(OBJECTSTEST) $(OBJ_TINYXML)
	$(CC) $(CFLAGS) $< $(OBJECTSTEST) $(OBJ_TINYXML) ${INCS} $(LDFLAGS) -o ${SRC_DIR}/tests/factory_test

distance_test: ${SRC_DIR}/tests/distance_test.cpp ${LIB_DIR}/distance/distance.o
	$(CC) $(CFLAGS) $< ${LIB_DIR}/distance/distance.o ${INCS} -o ${SRC_DIR}/tests/distance_test

logger_test: ${SRC_DIR}/tests/logger_test.cpp ${LIB_DIR}/logger/logger.o
	$(CC) $(CFLAGS) $< ${LIB_DIR}/logger/logger.o ${INCS} $(LDFLAGS) -o ${SRC_DIR}/tests/logger_test

colormod_test: ${SRC_DIR}/tests/colormod_test.cpp ${LIB_DIR}/colormod/colormod.o
	$(CC) $(CFLAGS) $< ${LIB_DIR}/colormod/colormod.o ${INCS} -o ${SRC_DIR}/tests/colormod_test

property_test: ${SRC_DIR}/tests/property_test.cpp ${LIB_DIR}/property/property.o
	$(CC) $(CFLAGS) $< ${LIB_DIR}/property/property.o ${INCS} -o ${SRC_DIR}/tests/property_test

invocador_test: ${SRC_DIR}/tests/invocador_test.cpp $(OBJECTSTEST) $(OBJ_TINYXML)
	$(CC) $(CFLAGS) $< $(OBJECTSTEST) $(OBJ_TINYXML) ${INCS} $(LDFLAGS) -o ${SRC_DIR}/tests/invocador_test

game_test: ${SRC_DIR}/tests/game_test.cpp $(OBJECTSTEST) $(OBJ_TINYXML)
	$(CC) $(CFLAGS) $< $(OBJECTSTEST) $(OBJ_TINYXML) ${INCS} $(LDFLAGS) -o ${SRC_DIR}/tests/game_test
