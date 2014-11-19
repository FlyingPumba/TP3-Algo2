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

int main(int argc, char **argv)
{
	RUN_TEST(test_mapa_vacio);
	return 0;
}
