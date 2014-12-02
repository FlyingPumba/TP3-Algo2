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
	String clave1 = "A";
	String clave2 = "B";
	String clave3 = "C";
	ASSERT_EQ(dicc.Definido(clave1), false);
	ASSERT_EQ(dicc.Definido(clave2), false);
	ASSERT_EQ(dicc.Definido(clave3), false);
}

void test_dicc_con_elementos_simples()
{
	DiccRapido<int> dicc;
	String clave1 = "A";
	String clave2 = "B";
	String clave3 = "C";
	int sig1 = 1;
	int sig2 = 2;
	int sig3 = 3;
	dicc.Definir(clave1, sig1);
	dicc.Definir(clave2, sig2);
	dicc.Definir(clave3, sig3);

	ASSERT_EQ(dicc.Definido(clave1), true);
	ASSERT_EQ(dicc.Definido(clave2), true);
	ASSERT_EQ(dicc.Definido(clave3), true);

	ASSERT_EQ(dicc.Significado(clave1), sig1);
	ASSERT_EQ(dicc.Significado(clave2), sig2);
	ASSERT_EQ(dicc.Significado(clave3), sig3);
}

void test_dicc_con_elementos_complejos()
{
	DiccRapido<int> dicc;
	String clave1 = "A";
	String clave2 = "Abe";
	String clave3 = "Abeja";
	int sig1 = 1;
	int sig2 = 2;
	int sig3 = 3;
	dicc.Definir(clave1, sig1);
	dicc.Definir(clave2, sig2);
	dicc.Definir(clave3, sig3);

	String clave4 = "Ab";
	String clave5 = "Abej";
	ASSERT_EQ(dicc.Definido(clave1), true);
	ASSERT_EQ(dicc.Definido(clave2), true);
	ASSERT_EQ(dicc.Definido(clave3), true);
	ASSERT_EQ(dicc.Definido(clave4), false);
	ASSERT_EQ(dicc.Definido(clave5), false);

	ASSERT_EQ(dicc.Significado(clave1), sig1);
	ASSERT_EQ(dicc.Significado(clave2), sig2);
	ASSERT_EQ(dicc.Significado(clave3), sig3);
}

void test_dicc_con_elementos_complejos2()
{
	DiccRapido<int> dicc;
	String clave1 = "Camion";
	String clave2 = "Auto";
	String clave4 = "Avion";
	int sig1 = 1;
	int sig2 = 2;
	int sig4 = 4;
	dicc.Definir(clave1, sig1);
	dicc.Definir(clave2, sig2);
	dicc.Definir(clave4, sig4);

	ASSERT_EQ(dicc.Definido(clave1), true);
	ASSERT_EQ(dicc.Definido(clave2), true);
	ASSERT_EQ(dicc.Definido(clave4), true);

	ASSERT_EQ(dicc.Significado(clave1), sig1);
	ASSERT_EQ(dicc.Significado(clave2), sig2);
	ASSERT_EQ(dicc.Significado(clave4), sig4);
}

void test_dicc_iterador()
{
	DiccRapido<int> dicc;
	String clave1 = "A";
	String clave2 = "B";
	String clave3 = "C";
	int sig1 = 1;
	int sig2 = 2;
	int sig3 = 3;
	dicc.Definir(clave1, sig1);
	dicc.Definir(clave2, sig2);
	dicc.Definir(clave3, sig3);

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
	RUN_TEST(test_dicc_con_elementos_complejos2);
	RUN_TEST(test_dicc_iterador);
	return 0;
}
