# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=testArbolBinario.cpp testMapa.cpp testDiccRapido.cpp testConjRapido.cpp testCiudad.cpp testRestriccion.cpp testColaPrioridad.cpp

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=testArbolBinario testMapa testDiccRapido testConjRapido testCiudad testRestriccion testColaPrioridad

arbol: testArbolBinario.o
	$(CC) testArbolBinario.cpp $(CFLAGS) -o testArbolBinario

mapa: testMapa.o
	$(CC) testMapa.cpp $(CFLAGS) -o testMapa

dicc: testDiccRapido.o
	$(CC) testDiccRapido.cpp $(CFLAGS) -o testDiccRapido

conj: testConjRapido.o
	$(CC) testConjRapido.cpp $(CFLAGS) -o testConjRapido

ciudad: testCiudad.o
	$(CC) testCiudad.cpp $(CFLAGS) -o testCiudad

rest: testRestriccion.o
	$(CC) testRestriccion.cpp $(CFLAGS) -o testRestriccion

cola: testColaPrioridad.o
	$(CC) testColaPrioridad.cpp $(CFLAGS) -o testColaPrioridad

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
