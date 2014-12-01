#include "../mini_test.h"
#include "Mapa.h"

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

void test_mapa_vacio()
{
	Mapa mapa;
	Conj<Estacion>::const_Iterador ests = mapa.Estaciones();
	ASSERT_EQ(ests.HaySiguiente(), false);
}

void test_mapa_con_estaciones()
{
	Mapa mapa;
	mapa.Agregar("A");
	mapa.Agregar("B");
	mapa.Agregar("C");
	Conj<Estacion>::const_Iterador ests = mapa.Estaciones();
	ASSERT_EQ(ests.HaySiguiente(), true);
	ests.Avanzar();
	ASSERT_EQ(ests.HaySiguiente(), true);
	ests.Avanzar();
	ASSERT_EQ(ests.HaySiguiente(), true);
	ests.Avanzar();
	ASSERT_EQ(ests.HaySiguiente(), false);
	ASSERT_EQ(mapa.Conectadas("A", "B"), false);
	ASSERT_EQ(mapa.Conectadas("B", "A"), false);
	ASSERT_EQ(mapa.Conectadas("C", "B"), false);
	ASSERT_EQ(mapa.Conectadas("B", "C"), false);
	ASSERT_EQ(mapa.Conectadas("A", "C"), false);
	ASSERT_EQ(mapa.Conectadas("C", "A"), false);
}

void test_mapa_con_estaciones_conectadas()
{
	Mapa mapa;
	mapa.Agregar("A");
	mapa.Agregar("B");
	mapa.Agregar("C");

	Caracteristica tag_Camion = "Camion";
	RestriccionTP rest(tag_Camion);

	mapa.Conectar("A", "B", rest);
	ASSERT_EQ(mapa.Conectadas("A", "B"), true);
	ASSERT_EQ(mapa.Conectadas("B", "A"), true);
	ASSERT_EQ(mapa.Conectadas("C", "B"), false);
	ASSERT_EQ(mapa.Conectadas("B", "C"), false);
	ASSERT_EQ(mapa.Conectadas("A", "C"), false);
	ASSERT_EQ(mapa.Conectadas("C", "A"), false);
	ASSERT_EQ(mapa.Rest("A", "B") == rest, true);
	ASSERT_EQ(mapa.Rest("B", "A") == rest, true);
}

int main(int argc, char **argv)
{
	RUN_TEST(test_mapa_vacio);
	RUN_TEST(test_mapa_con_estaciones);
	RUN_TEST(test_mapa_con_estaciones_conectadas);
	return 0;
}
