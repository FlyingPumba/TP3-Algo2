# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=testArbolBinario.cpp testMapa.cpp testDiccRapido.cpp

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=testArbolBinario testMapa testDiccRapido

arbol: testArbolBinario.o
	$(CC) testArbolBinario.cpp $(CFLAGS) -o testArbolBinario

mapa: testMapa.o
	$(CC) testMapa.cpp $(CFLAGS) -o testMapa

dicc: testDiccRapido.o
	$(CC) testDiccRapido.cpp $(CFLAGS) -o testDiccRapido

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

#.cpp.o:
#	$(CC) -I$(INCDIR) $(CFLAGS) $< -c -o $@
