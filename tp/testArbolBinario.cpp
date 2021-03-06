#include "../mini_test.h"
#include "ArbolBinario.h"

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
	ASSERT_EQ(arbol.Izq().Padre(), &arbol);
	ASSERT_EQ(arbol.Izq().Raiz(), 19);
	ASSERT_EQ(arbol.Izq().Izq().EsNil(), true);
	ASSERT_EQ(arbol.Izq().Der().EsNil(), true);

	// swap arbol con izq
	ArbolBinario<int>::Swap(arbol, arbol.Izq());
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Raiz(), 19);
	ASSERT_EQ(arbol.Izq().EsNil(), false);
	ASSERT_EQ(arbol.Der().EsNil(), true);
	ASSERT_EQ(arbol.Izq().Padre(), &arbol);
	ASSERT_EQ(arbol.Izq().Raiz(), 42);
	ASSERT_EQ(arbol.Izq().Izq().EsNil(), true);
	ASSERT_EQ(arbol.Izq().Der().EsNil(), true);
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
	ASSERT_EQ(arbol.Der().Padre(), &arbol);
	ASSERT_EQ(arbol.Der().Raiz(), 19);
	ASSERT_EQ(arbol.Der().Izq().EsNil(), true);
	ASSERT_EQ(arbol.Der().Der().EsNil(), true);

	// swap arbol con der
	ArbolBinario<int>::Swap(arbol, arbol.Der());
	ASSERT_EQ(arbol.EsNil(), false);
	ASSERT_EQ(arbol.Raiz(), 19);
	ASSERT_EQ(arbol.Der().EsNil(), false);
	ASSERT_EQ(arbol.Izq().EsNil(), true);
	ASSERT_EQ(arbol.Der().Padre(), &arbol);
	ASSERT_EQ(arbol.Der().Raiz(), 42);
	ASSERT_EQ(arbol.Der().Izq().EsNil(), true);
	ASSERT_EQ(arbol.Der().Der().EsNil(), true);
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

	ArbolBinario<int> nil;
	arbol.BorrarHojaIzq(nil);
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
	ArbolBinario<int> der(izqDer, 19, derDer);
	ArbolBinario<int> izq;
	ArbolBinario<int> arbol(izq, 42, der);
	ASSERT_EQ(arbol.Tamanho(), 2);
	ASSERT_EQ(arbol.Altura(), 2);

	ArbolBinario<int> nil;
	arbol.BorrarHojaDer(nil);
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

void test_nuevo_swap_altura_2()
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
	ASSERT_EQ(&(arbol.Izq()), &izq);
	ASSERT_EQ(arbol.Izq().Padre(), &arbol);
	ASSERT_EQ(arbol.Izq().Raiz(), 19);
	ASSERT_EQ(arbol.Izq().Izq().EsNil(), true);
	ASSERT_EQ(arbol.Izq().Der().EsNil(), true);

	// swap arbol con izq
	ArbolBinario<int>::Swap(arbol, arbol.Izq());
	ASSERT_EQ(izq.EsNil(), false);
	ASSERT_EQ(izq.Raiz(), 19);
	ASSERT_EQ(izq.Izq().EsNil(), false);
	ASSERT_EQ(izq.Der().EsNil(), true);
	ASSERT_EQ(&(izq.Izq()), &arbol);
	ASSERT_EQ(izq.Izq().Padre(), &izq);
	ASSERT_EQ(izq.Izq().Raiz(), 42);
	ASSERT_EQ(izq.Izq().Izq().EsNil(), true);
	ASSERT_EQ(izq.Izq().Der().EsNil(), true);
}

void test_nuevo_swap_altura_3()
{
	ArbolBinario<int> izqDer;
	ArbolBinario<int> derDer;
	ArbolBinario<int> der(izqDer, 23, derDer);
	ArbolBinario<int> izqIzq;
	ArbolBinario<int> izq(izqIzq, 19, der);
	ArbolBinario<int> arbolDer;
	ArbolBinario<int> arbol(izq, 42, arbolDer);

	ArbolBinario<int>::Swap(arbol.Izq(), arbol.Izq().Der());
	ASSERT_EQ(der.EsNil(), false);
	ASSERT_EQ(der.Raiz(), 23);
	ASSERT_EQ(der.Der().EsNil(), false);
	ASSERT_EQ(der.Izq().EsNil(), true);
	ASSERT_EQ(der.Der().Raiz(), 19);
	ASSERT_EQ(der.Der().Izq().EsNil(), true);
	ASSERT_EQ(der.Der().Der().EsNil(), true);

	ASSERT_EQ(&(der.Der()), &izq);
	ASSERT_EQ(izq.Padre(), &der);

	ASSERT_EQ(der.Padre(), &arbol);
	ASSERT_EQ(&(arbol.Izq()), &der);

}

int main(int argc, char **argv)
{
	RUN_TEST(test_arbol_vacio_es_nil);
	RUN_TEST(test_arbol_bin);
	//RUN_TEST(test_swap_izq);
	//RUN_TEST(test_swap_der);
	RUN_TEST(test_borrar_hoja_izq);
	RUN_TEST(test_borrar_hoja_der);
	RUN_TEST(test_agregar_hoja_izq);
	RUN_TEST(test_agregar_hoja_der);
	RUN_TEST(test_nuevo_swap_altura_2);
	RUN_TEST(test_nuevo_swap_altura_3);

	return 0;
}
