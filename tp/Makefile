# Compilador que será utilizado
CC=clang++

# flags de compilación
CFLAGS=-g

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=testArbolBinario.cpp testMapa.cpp

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=testArbolBinario testMapa

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) -I$(INCDIR) $(CFLAGS) $< -c -o $@
