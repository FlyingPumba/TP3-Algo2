#include "mini_test.h"
#include "aed2.h"
#include "ArbolBinario.h"

#include <string>
#include <iostream>

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

void test_arbol_vacio_es_nil()
{
	ArbolBinario<int> arbol;
	ASSERT_EQ(arbol.EsNil(), true);
}

void test_arbol_bin()
{
	ArbolBinario<int> izq;
	ArbolBinario<int> der;
	ArbolBinario<int> arbol(izq, 42, der);
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Raiz(), 42);
	ASSERT_EQ(arbol.Izq().EsNil(), true);
	ASSERT_EQ(arbol.Der().EsNil(), true);
}

void test_swap_izq()
{
	ArbolBinario<int> izqIzq;
	ArbolBinario<int> derIzq;
	ArbolBinario<int> izq(izqIzq, 19, derIzq);;
	ArbolBinario<int> der;
	ArbolBinario<int> arbol(izq, 42, der);
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Raiz(), 42);
	ASSERT_EQ(arbol.Izq().EsNil(), false);
	ASSERT_EQ(arbol.Der().EsNil(), true);
	//ASSERT_EQ(arbol.Izq().Padre(), arbol);
	ASSERT_EQ(arbol.Izq().Raiz(), 19);
	ASSERT_EQ(arbol.Izq().Izq().EsNil(), true);
	ASSERT_EQ(arbol.Izq().Der().EsNil(), true);

	// swap arbol con izq
	ArbolBinario<int>::Swap(arbol, arbol.Izq());
	ASSERT_EQ(izq.EsNil(), false);
	ASSERT_EQ(izq.Raiz(), 42);
	ASSERT_EQ(izq.Izq().EsNil(), false);
	ASSERT_EQ(izq.Der().EsNil(), true);
	//ASSERT_EQ(izq.Izq().Padre(), izq);
	ASSERT_EQ(izq.Izq().Raiz(), 19);
	ASSERT_EQ(izq.Izq().Izq().EsNil(), true);
	ASSERT_EQ(izq.Izq().Der().EsNil(), true);
}

int main(int argc, char **argv)
{
	RUN_TEST(test_arbol_vacio_es_nil);
	RUN_TEST(test_arbol_bin);
	RUN_TEST(test_swap_izq);
	return 0;
}
