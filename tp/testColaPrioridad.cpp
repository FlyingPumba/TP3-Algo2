#include "../mini_test.h"
#include "ColaPrioridad.h"
#include <iostream>


#include <string>

using namespace tp;

/**
* Imprime un elemento a un string, en vez de a una pantalla,
* a través del operador <<
*/
template <typename T>
std::string to_str(const T& t)
{
	std::stringstream ss;
	ss << t;

	return ss.str();
}

void test_cola_vacia_es_vacia()
{
	ColaPrioridad<int> cola;
	ASSERT_EQ(cola.EsVacia(), true);

}

void test_cola_encolar()
{
	ColaPrioridad<int> cola;
	ASSERT_EQ(cola.EsVacia(), true);
    int aux = 10;
    int aux2 = 42;
    int aux3 = 5;
    int aux4 = 60;
	cola.Encolar(aux);
	//ASSERT_EQ(cola.EsVacia(), false);
	ASSERT_EQ(cola.Proximo(), 10);
	cola.Encolar(aux2);
	ASSERT_EQ(cola.Proximo(), 42);
	cola.Encolar(aux3);
	ASSERT_EQ(cola.Proximo(), 42);
	cola.Encolar(aux4);
	ASSERT_EQ(cola.Proximo(), 60); 
}

void test_cola_desencolar()
{
	ColaPrioridad<int> cola;
	int aux = 10;
	int aux2 = 5;
	cola.Encolar(aux);

	ASSERT_EQ(cola.EsVacia(), false);
	ASSERT_EQ(cola.Proximo(), 10);
	cola.Encolar(aux2);
	cola.Desencolar();
	ASSERT_EQ(cola.Proximo(), 5);
	ASSERT_EQ(cola.EsVacia(), false);
	cola.Desencolar();

}

void test_cola_encolar_y_desencolar()
{
    ColaPrioridad<int> cola;
    int aux = 10;
    int aux2 = 42;
    cola.Encolar(aux);
    cola.Encolar(aux2);

    ASSERT_EQ(cola.EsVacia(), false);
    ASSERT_EQ(cola.Proximo(), 42);

    cola.Desencolar();

    ASSERT_EQ(cola.EsVacia(), false);
    ASSERT_EQ(cola.Proximo(), 10);

    cola.Desencolar();

    ASSERT_EQ(cola.EsVacia(), true);

}


void test_cola_encolar_y_desencolar_groso()
{
	ColaPrioridad<int> cola;
	ASSERT_EQ(cola.EsVacia(), true);

	int aux = 10;
	int aux2 = 42;
	int aux3 = 5;
	int aux4 = 60;
	int aux5 = 3;
	int aux6 = 1;

	cola.Encolar(aux);

	ASSERT_EQ(cola.EsVacia(), false);
	ASSERT_EQ(cola.Proximo(), 10);

	cola.Encolar(aux2);
	ASSERT_EQ(cola.Proximo(), 42);

	cola.Encolar(aux3);
	ASSERT_EQ(cola.Proximo(), 42);

	cola.Encolar(aux4);
	ASSERT_EQ(cola.Proximo(), 60);
	cola.Encolar(aux5);
	cola.Encolar(aux6);
	cola.Desencolar();
	ASSERT_EQ(cola.Proximo(), 42);

	cola.Desencolar();
	ASSERT_EQ(cola.Proximo(), 10);

	cola.Desencolar();
	ASSERT_EQ(cola.Proximo(), 5);

	cola.Desencolar();
	ASSERT_EQ(cola.EsVacia(), false);
}

void test_iterador_cola()
{
	ColaPrioridad<int> cola;
	ASSERT_EQ(cola.EsVacia(), true);

	int aux = 10;
	int aux2 = 42;
	//int aux3 = 5;
	//int aux4 = 60;

	ColaPrioridad<int>::const_Iterador it= cola.Encolar(aux);
	ColaPrioridad<int>::const_Iterador it1 = cola.Encolar(aux2);
	//cola.Desencolar();
	ASSERT_EQ(it.HaySiguiente(), true);
	ASSERT_EQ(it1.Siguiente(), 42);
	ASSERT_EQ(it.Siguiente(), 10);

}

int main(int argc, char **argv)
{
	RUN_TEST(test_cola_vacia_es_vacia);
	RUN_TEST(test_cola_encolar);
	RUN_TEST(test_cola_desencolar);
	RUN_TEST(test_cola_encolar_y_desencolar);
	RUN_TEST(test_cola_encolar_y_desencolar_groso);
	RUN_TEST(test_iterador_cola);

	return 0;
}
