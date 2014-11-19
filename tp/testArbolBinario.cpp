#include "../aed2.h"
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
	ASSERT_EQ(arbol.Tamanho(), 0);
	ASSERT_EQ(arbol.Altura(), 0);
}

void test_arbol_bin()
{
	ArbolBinario<int> izq;
	ArbolBinario<int> der;
	ArbolBinario<int> arbol(izq, 42, der);
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Tamanho(), 1);
	ASSERT_EQ(arbol.Altura(), 1);
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

void test_swap_der()
{
	ArbolBinario<int> izqDer;
	ArbolBinario<int> derDer;
	ArbolBinario<int> der(izqDer, 19, derDer);;
	ArbolBinario<int> izq;
	ArbolBinario<int> arbol(izq, 42, der);
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Raiz(), 42);
	ASSERT_EQ(arbol.Der().EsNil(), false);
	ASSERT_EQ(arbol.Izq().EsNil(), true);
	//ASSERT_EQ(arbol.Der().Padre(), arbol);
	ASSERT_EQ(arbol.Der().Raiz(), 19);
	ASSERT_EQ(arbol.Der().Izq().EsNil(), true);
	ASSERT_EQ(arbol.Der().Der().EsNil(), true);

	// swap arbol con der
	ArbolBinario<int>::Swap(arbol, arbol.Der());
	ASSERT_EQ(der.EsNil(), false);
	ASSERT_EQ(der.Raiz(), 42);
	ASSERT_EQ(der.Der().EsNil(), false);
	ASSERT_EQ(der.Izq().EsNil(), true);
	//ASSERT_EQ(der.Der().Padre(), der);
	ASSERT_EQ(der.Der().Raiz(), 19);
	ASSERT_EQ(der.Der().Izq().EsNil(), true);
	ASSERT_EQ(der.Der().Der().EsNil(), true);
}

void test_borrar_hoja_izq()
{
	ArbolBinario<int> izqIzq;
	ArbolBinario<int> derIzq;
	ArbolBinario<int> izq(izqIzq, 19, derIzq);;
	ArbolBinario<int> der;
	ArbolBinario<int> arbol(izq, 42, der);
	ASSERT_EQ(arbol.Tamanho(), 2);
	ASSERT_EQ(arbol.Altura(), 2);

	arbol.BorrarHojaIzq();
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Raiz(), 42);
	ASSERT_EQ(arbol.Izq().EsNil(), true);
	ASSERT_EQ(arbol.Der().EsNil(), true);
	ASSERT_EQ(arbol.Tamanho(), 1);
	ASSERT_EQ(arbol.Altura(), 1);
}

void test_borrar_hoja_der()
{
	ArbolBinario<int> izqDer;
	ArbolBinario<int> derDer;
	ArbolBinario<int> der(izqDer, 19, derDer);;
	ArbolBinario<int> izq;
	ArbolBinario<int> arbol(izq, 42, der);
	ASSERT_EQ(arbol.Tamanho(), 2);
	ASSERT_EQ(arbol.Altura(), 2);

	arbol.BorrarHojaDer();
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Raiz(), 42);
	ASSERT_EQ(arbol.Izq().EsNil(), true);
	ASSERT_EQ(arbol.Der().EsNil(), true);
	ASSERT_EQ(arbol.Tamanho(), 1);
	ASSERT_EQ(arbol.Altura(), 1);
}

void test_agregar_hoja_izq()
{
	ArbolBinario<int> hojaIzq;
	ArbolBinario<int> hojaDer;
	ArbolBinario<int> hoja(hojaIzq, 19, hojaDer);
	ArbolBinario<int> izq;
	ArbolBinario<int> der;
	ArbolBinario<int> arbol(izq, 42, der);
	ASSERT_EQ(arbol.Tamanho(), 1);
	ASSERT_EQ(arbol.Altura(), 1);

	arbol.AgregarHojaIzq(hoja);
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Raiz(), 42);
	ASSERT_EQ(arbol.Izq().EsNil(), false);
	ASSERT_EQ(arbol.Der().EsNil(), true);
	//ASSERT_EQ(arbol.Izq().Padre(), arbol);
	ASSERT_EQ(arbol.Izq().Raiz(), 19);
	ASSERT_EQ(arbol.Izq().Izq().EsNil(), true);
	ASSERT_EQ(arbol.Izq().Der().EsNil(), true);
	ASSERT_EQ(arbol.Tamanho(), 2);
	ASSERT_EQ(arbol.Altura(), 2);
}

void test_agregar_hoja_der()
{
	ArbolBinario<int> hojaIzq;
	ArbolBinario<int> hojaDer;
	ArbolBinario<int> hoja(hojaIzq, 19, hojaDer);
	ArbolBinario<int> izq;
	ArbolBinario<int> der;
	ArbolBinario<int> arbol(izq, 42, der);
	ASSERT_EQ(arbol.Tamanho(), 1);
	ASSERT_EQ(arbol.Altura(), 1);

	arbol.AgregarHojaDer(hoja);
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Raiz(), 42);
	ASSERT_EQ(arbol.Izq().EsNil(), true);
	ASSERT_EQ(arbol.Der().EsNil(), false);
	//ASSERT_EQ(arbol.Der().Padre(), arbol);
	ASSERT_EQ(arbol.Der().Raiz(), 19);
	ASSERT_EQ(arbol.Der().Izq().EsNil(), true);
	ASSERT_EQ(arbol.Der().Der().EsNil(), true);
	ASSERT_EQ(arbol.Tamanho(), 2);
	ASSERT_EQ(arbol.Altura(), 2);
}

int main(int argc, char **argv)
{
	RUN_TEST(test_arbol_vacio_es_nil);
	RUN_TEST(test_arbol_bin);
	RUN_TEST(test_swap_izq);
	RUN_TEST(test_swap_der);
	//RUN_TEST(test_borrar_hoja_izq);
	//RUN_TEST(test_borrar_hoja_der);
	//RUN_TEST(test_agregar_hoja_izq);
	//RUN_TEST(test_agregar_hoja_der);
	return 0;
}
