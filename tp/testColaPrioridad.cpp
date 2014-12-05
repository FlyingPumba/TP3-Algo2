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
	mt::assert_eq(cola.EsVacia(), true, "");

}

void test_cola_encolar()
{
	ColaPrioridad<int> cola;
	mt::assert_eq(cola.EsVacia(), true, "");
    int aux = 10;
    int aux2 = 42;
    int aux3 = 5;
    int aux4 = 60;
	cola.Encolar(aux);
	//mt::assert_eq(cola.EsVacia(), false, "");
	mt::assert_eq(cola.Proximo(), 10, "");
	cola.Encolar(aux2);
	mt::assert_eq(cola.Proximo(), 42, "");
	cola.Encolar(aux3);
	mt::assert_eq(cola.Proximo(), 42, "");
	cola.Encolar(aux4);
	mt::assert_eq(cola.Proximo(), 60, "");
}

void test_cola_encolar1_desencolar1()
{
	ColaPrioridad<int> cola;

	int aux = 10;
	cola.Encolar(aux);
	mt::assert_eq(cola.EsVacia(), false, "");
	mt::assert_eq(cola.Proximo(), 10, "");

	cola.Desencolar();

	mt::assert_eq(cola.EsVacia(), true, "");

	cola.Encolar(aux);

	mt::assert_eq(cola.EsVacia(), false, "");
	mt::assert_eq(cola.Proximo(), 10, "");

	cola.Desencolar();

	mt::assert_eq(cola.EsVacia(), true, "");
}

void test_cola_desencolar()
{
	ColaPrioridad<int> cola;
	int aux = 10;
	int aux2 = 5;
	cola.Encolar(aux);

	mt::assert_eq(cola.EsVacia(), false, "");
	mt::assert_eq(cola.Proximo(), 10, "");
	cola.Encolar(aux2);
	cola.Desencolar();
	mt::assert_eq(cola.Proximo(), 5, "");
	mt::assert_eq(cola.EsVacia(), false, "");
	cola.Desencolar();

}

void test_cola_encolar_y_desencolar()
{
    ColaPrioridad<int> cola;
    int aux = 10;
    int aux2 = 42;
    cola.Encolar(aux);
    cola.Encolar(aux2);

    mt::assert_eq(cola.EsVacia(), false, "");
    mt::assert_eq(cola.Proximo(), 42, "");

    cola.Desencolar();

    mt::assert_eq(cola.EsVacia(), false, "");
    mt::assert_eq(cola.Proximo(), 10, "");

    cola.Desencolar();

    mt::assert_eq(cola.EsVacia(), true, "");

}


void test_cola_encolar_y_desencolar_groso()
{
	ColaPrioridad<int> cola;
	mt::assert_eq(cola.EsVacia(), true, "");

	int aux = 10;
	int aux2 = 42;
	int aux3 = 5;
	int aux4 = 60;
	int aux5 = 3;
	int aux6 = 1;

	cola.Encolar(aux);

	mt::assert_eq(cola.EsVacia(), false, "");
	mt::assert_eq(cola.Proximo(), 10, "");

	cola.Encolar(aux2);
	mt::assert_eq(cola.Proximo(), 42, "");

	cola.Encolar(aux3);
	mt::assert_eq(cola.Proximo(), 42, "");

	cola.Encolar(aux4);
	mt::assert_eq(cola.Proximo(), 60, "");
	cola.Encolar(aux5);
	cola.Encolar(aux6);
	cola.Desencolar();
	mt::assert_eq(cola.Proximo(), 42, "");

	cola.Desencolar();
	mt::assert_eq(cola.Proximo(), 10, "");

	cola.Desencolar();
	mt::assert_eq(cola.Proximo(), 5, "");

	cola.Desencolar();
	mt::assert_eq(cola.EsVacia(), false, "");
}

void test_iterador_cola()
{
	ColaPrioridad<int> cola;
	mt::assert_eq(cola.EsVacia(), true, "");

	int aux = 10;
	int aux2 = 42;
	int aux3 = 5;
	int aux4 = 60;

	ColaPrioridad<int>::Iterador* it = cola.Encolar(aux);
	ColaPrioridad<int>::Iterador* it1 = cola.Encolar(aux2);
	ColaPrioridad<int>::Iterador* it2 = cola.Encolar(aux3);
	ColaPrioridad<int>::Iterador* it3 = cola.Encolar(aux4);

	mt::assert_eq(it->HaySiguiente(), true, "");

	mt::assert_eq(it->Siguiente(), 10, "");
	mt::assert_eq(it1->Siguiente(), 42, "");
	mt::assert_eq(it2->Siguiente(), 5, "");
	mt::assert_eq(it3->Siguiente(), 60, "");

	mt::assert_eq(cola.Proximo(), 60, "");

	it->BorrarSiguiente();

	mt::assert_eq(cola.Proximo(), 60, "testlinea180");

	it2->BorrarSiguiente();

	mt::assert_eq(cola.Proximo(), 60, "testlinea184");

	it3->BorrarSiguiente();

	mt::assert_eq(cola.Proximo(), 42, "testlinea188");

	it1->BorrarSiguiente();

	mt::assert_eq(cola.EsVacia(),true,"testlinea192");
}

int main(int argc, char **argv)
{
	RUN_TEST(test_cola_encolar1_desencolar1);
	RUN_TEST(test_cola_vacia_es_vacia);
	RUN_TEST(test_cola_encolar);
	RUN_TEST(test_cola_desencolar);
	RUN_TEST(test_cola_encolar_y_desencolar);
	RUN_TEST(test_cola_encolar_y_desencolar_groso);
	RUN_TEST(test_iterador_cola);

	return 0;
}
