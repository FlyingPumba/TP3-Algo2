# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall

# flags de linkeo
LDFLAGS=

# Agrear acá los directorios a incluir en la compilación
#INCDIR=../../../../../Modulos-CPP

# Agregar acá los archivos .cpp a compilar
SOURCES=test.cpp # Driver.cpp ArbolSintactico.cpp

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=test

#all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

all: test.o
	$(CC) test.cpp $(CFLAGS) -o test

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@
