#include "../mini_test.h"
#include "DiccRapido.h"

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

void test_dicc_vacio()
{
	DiccRapido<int> dicc;
	ASSERT_EQ(dicc.Definido("A"), false);
	ASSERT_EQ(dicc.Definido("B"), false);
	ASSERT_EQ(dicc.Definido("C"), false);
}

void test_dicc_con_elementos_simples()
{
	DiccRapido<int> dicc;
	dicc.DefinirRapido("A", 1);
	dicc.DefinirRapido("B", 2);
	dicc.DefinirRapido("C", 3);

	ASSERT_EQ(dicc.Definido("A"), true);
	ASSERT_EQ(dicc.Definido("B"), true);
	ASSERT_EQ(dicc.Definido("C"), true);

	ASSERT_EQ(dicc.Significado("A"), 1);
	ASSERT_EQ(dicc.Significado("B"), 2);
	ASSERT_EQ(dicc.Significado("C"), 3);
}

void test_dicc_con_elementos_complejos()
{
	DiccRapido<int> dicc;
	dicc.DefinirRapido("A", 1);
	dicc.DefinirRapido("Abe", 2);
	dicc.DefinirRapido("Abeja", 3);

	ASSERT_EQ(dicc.Definido("A"), true);
	ASSERT_EQ(dicc.Definido("Ab"), false);
	ASSERT_EQ(dicc.Definido("Abe"), true);
	ASSERT_EQ(dicc.Definido("Abej"), false);
	ASSERT_EQ(dicc.Definido("Abeja"), true);

	ASSERT_EQ(dicc.Significado("A"), 1);
	ASSERT_EQ(dicc.Significado("Abe"), 2);
	ASSERT_EQ(dicc.Significado("Abeja"), 3);
}

void test_dicc_iterador()
{
	DiccRapido<int> dicc;
	dicc.DefinirRapido("A", 1);
	dicc.DefinirRapido("B", 2);
	dicc.DefinirRapido("C", 3);

	DiccRapido<int>::const_Iterador it = dicc.CrearIt();
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
	RUN_TEST(test_dicc_vacio);
	RUN_TEST(test_dicc_con_elementos_simples);
	RUN_TEST(test_dicc_con_elementos_complejos);
	RUN_TEST(test_dicc_iterador);
	return 0;
}
