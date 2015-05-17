CC= g++
#CFLAGS = -g -Wall -std=gnu++0x
CFLAGS = -g -Wall
TARGET = miprograma
MAIN = main

all: $(TARGET)

$(TARGET) : main.o manager.o escenario.o jugador.o inventario.o objeto.o operaciones.o invocador.o
	$(CC) -g objeto.o inventario.o jugador.o escenario.o manager.o operaciones.o invocador.o main.o -lpthread -o $(TARGET)

main.o : main.cpp manager.o
	$(CC) $(CFLAGS) -c main.cpp

objeto.o : objeto.cpp objeto.h
	$(CC) $(CFLAGS) -c objeto.cpp

inventario.o : inventario.cpp inventario.h objeto.o
	$(CC) $(CFLAGS) -c inventario.cpp

jugador.o : jugador.cpp jugador.h inventario.o escenario.o objeto.o
	$(CC) $(CFLAGS) -c jugador.cpp

escenario.o : escenario.cpp escenario.h objeto.o
	$(CC) $(CFLAGS) -c escenario.cpp

parametros.o : parametros.cpp parametros.h
	$(CC) $(CFLAGS) -c parametros.cpp

manager.o : manager.cpp manager.h invocador.o parametros.o
	$(CC) $(CFLAGS) -c manager.cpp

operaciones.o : operaciones.cpp operaciones.h parametros.o escenario.o
	$(CC) $(CFLAGS) -c operaciones.cpp

invocador.o : invocador.cpp invocador.h operaciones.o
	$(CC) $(CFLAGS) -c invocador.cpp


clean:
	rm -rf *.o *~ *.gch core
	rm $(TARGET)



