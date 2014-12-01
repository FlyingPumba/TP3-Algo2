#include "../mini_test.h"
#include "Ciudad.h"

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

void test_ciudad_vacia()
{
	Mapa mapa;
	mapa.Agregar("A");
	mapa.Agregar("B");
	mapa.Agregar("C");
	//mapa.Conectar("A", "B", "auto | camion");

	Ciudad c(mapa);
}

void test_ciudad_entrar()
{
	// TODO
}

int main(int argc, char **argv)
{
	RUN_TEST(test_ciudad_vacia);
	return 0;
}
