#include "../mini_test.h"
#include "ConjRapido.h"

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

void test_conj_vacio()
{
	ConjRapido conj;
	ASSERT_EQ(conj.EsVacio(), true);
	ASSERT_EQ(conj.Cardinal(), 0);
}

void test_conj_con_elementos()
{
	ConjRapido conj;
	conj.AgregarRapido("A");
	conj.AgregarRapido("B");
	conj.AgregarRapido("C");

	ASSERT_EQ(conj.EsVacio(), false);
	ASSERT_EQ(conj.Cardinal(), 3);

	ASSERT_EQ(conj.Pertenece("A"), true);
	ASSERT_EQ(conj.Pertenece("B"), true);
	ASSERT_EQ(conj.Pertenece("C"), true);

	ASSERT_EQ(conj.Pertenece("D"), false);
	ASSERT_EQ(conj.Pertenece("E"), false);
}

void test_conj_iterador()
{
	ConjRapido conj;
	conj.AgregarRapido("A");
	conj.AgregarRapido("B");
	conj.AgregarRapido("C");

	ConjRapido::const_Iterador it = conj.CrearIt();
	ASSERT_EQ(it.HaySiguiente(), true);
	it.Avanzar();
	ASSERT_EQ(it.HaySiguiente(), true);
	it.Avanzar();
	ASSERT_EQ(it.HaySiguiente(), true);
	it.Avanzar();
	ASSERT_EQ(it.HaySiguiente(), false);
}

int main(int argc, char **argv)
{
	RUN_TEST(test_conj_vacio);
	RUN_TEST(test_conj_con_elementos);
	RUN_TEST(test_conj_iterador);
	return 0;
}
