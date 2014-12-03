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

	Caracteristica tag_Camion = "Camion";
	RestriccionTP rest(tag_Camion);

	mapa.Conectar("A", "B", rest);

	Ciudad c(mapa);
}

void test_ciudad_entrar()
{
	Mapa mapa;
	mapa.Agregar("A");
	mapa.Agregar("B");
	mapa.Agregar("C");

	Caracteristica tag_Camion = "Camion";
	RestriccionTP rest(tag_Camion);

	mapa.Conectar("A", "B", rest);

	Ciudad c(mapa);

	ConjRapido tags;
	Caracteristica tag_Auto = "Auto";
	tags.Agregar(tag_Auto);

	int rur = c.ProximoRUR();
	c.Entrar(tags, "A");

	ASSERT_EQ(c.EstacionActual(rur), "A");
	const ConjRapido& tagsRobot = c.Tags(rur);
	ASSERT_EQ(&tagsRobot, &tags);
	ASSERT_EQ(c.CantInfracciones(rur), 0);
}

void test_ciudad_mover_sin_infraccion()
{
	Mapa mapa;
	mapa.Agregar("A");
	mapa.Agregar("B");
	mapa.Agregar("C");

	Caracteristica tag_Camion = "Camion";
	RestriccionTP rest(tag_Camion);

	mapa.Conectar("A", "B", rest);

	Ciudad c(mapa);

	ConjRapido tags;
	tags.Agregar(tag_Camion);

	int rur = c.ProximoRUR();
	c.Entrar(tags, "A");
	c.Mover(rur, "B");
	ASSERT_EQ(c.EstacionActual(rur), "B");
	ASSERT_EQ(c.CantInfracciones(rur), 1);
}

void test_ciudad_mover_con_infraccion()
{
	Mapa mapa;
	mapa.Agregar("A");
	mapa.Agregar("B");
	mapa.Agregar("C");

	Caracteristica tag_Camion = "Camion";
	RestriccionTP rest(tag_Camion);

	mapa.Conectar("A", "B", rest);

	Ciudad c(mapa);

	ConjRapido tags;
	Caracteristica tag_Auto = "Auto";
	tags.Agregar(tag_Auto);

	int rur = c.ProximoRUR();
	c.Entrar(tags, "A");
	c.Mover(rur, "B");
	ASSERT_EQ(c.EstacionActual(rur), "B");
	ASSERT_EQ(c.CantInfracciones(rur), 0);
}

void test_ciudad_iterador()
{
	Mapa mapa;
	mapa.Agregar("A");
	mapa.Agregar("B");
	mapa.Agregar("C");

	Caracteristica tag_Camion = "Camion";
	RestriccionTP rest1(tag_Camion);

	mapa.Conectar("A", "B", rest1);

	Caracteristica tag_Auto = "Auto";
	RestriccionTP rest2(tag_Auto);

	mapa.Conectar("B", "C", rest2);

	Ciudad c(mapa);

	ConjRapido tags1;
	tags1.Agregar(tag_Camion);
	int rur1 = c.ProximoRUR();
	c.Entrar(tags1, "A");

	ConjRapido tags2;
	tags2.Agregar(tag_Auto);
	int rur2 = c.ProximoRUR();
	c.Entrar(tags2, "B");

	itArreglo& it(c.Robots());
	int cant = 0;
	bool robot1Esta = false;
	bool robot2Esta = false;
	bool hayOtro = false;
	while (it.HaySiguiente()) {
		cant = cant + 1;
		if (it.Siguiente().posEstacion.Siguiente().rur == rur1) {
			ASSERT_EQ(it.Siguiente().estActual, "A");
			ASSERT_EQ(it.Siguiente().infracciones, 0);
			robot1Esta = true;
		} else if (it.Siguiente().posEstacion.Siguiente().rur == rur2) {
			ASSERT_EQ(it.Siguiente().estActual, "B");
			ASSERT_EQ(it.Siguiente().infracciones, 0);
			robot2Esta = true;
		} else {
			hayOtro = true;
		}
        it.Avanzar();
    }

    ASSERT_EQ(robot1Esta, true);
    ASSERT_EQ(robot2Esta, true);
    ASSERT_EQ(hayOtro, false);
	ASSERT_EQ(cant, 2);
	delete &it;
}

void test_ciudad_inspeccion()
{
	Mapa mapa;
	mapa.Agregar("A");
	mapa.Agregar("B");
	mapa.Agregar("C");

	Caracteristica tag_Camion = "Camion";
	RestriccionTP rest1(tag_Camion);

	mapa.Conectar("A", "B", rest1);

	Caracteristica tag_Auto = "Auto";
	RestriccionTP rest2(tag_Auto);

	mapa.Conectar("B", "C", rest2);

	Ciudad c(mapa);

	ConjRapido tags1;
	tags1.Agregar(tag_Camion);
	int rur1 = c.ProximoRUR();
	c.Entrar(tags1, "A");

	ConjRapido tags2;
	tags2.Agregar(tag_Auto);
	int rur2 = c.ProximoRUR();
	c.Entrar(tags2, "B");

	c.Mover(rur1, "B");
	c.Mover(rur1, "A");
	c.Mover(rur1, "B");
	c.Mover(rur1, "A");
	ASSERT_EQ(c.CantInfracciones(rur1), 4);

	c.Mover(rur2, "C");
	c.Mover(rur2, "B");
	c.Mover(rur2, "A");
	ASSERT_EQ(c.CantInfracciones(rur2), 2);

	c.Inspeccion("A");

	// chequeamos con el iterador de robots activos que rur1 no este mas en la ciudad
	itArreglo& it(c.Robots());
	int cant = 0;
	bool robot1Esta = false;
	bool robot2Esta = false;
	bool hayOtro = false;
	while (it.HaySiguiente()) {
		cant = cant + 1;
		if (it.Siguiente().posEstacion.Siguiente().rur == rur1) {
			robot1Esta = true;
		} else if (it.Siguiente().posEstacion.Siguiente().rur == rur2) {
			robot2Esta = true;
		} else {
			hayOtro = true;
		}
		it.Avanzar();
	}

	ASSERT_EQ(robot1Esta, false);
	ASSERT_EQ(robot2Esta, true);
	ASSERT_EQ(hayOtro, false);
	ASSERT_EQ(cant, 1);
	delete &it;
}

int main(int argc, char **argv)
{
	RUN_TEST(test_ciudad_vacia);
	RUN_TEST(test_ciudad_entrar);
	RUN_TEST(test_ciudad_mover_sin_infraccion);
	RUN_TEST(test_ciudad_mover_con_infraccion);
	RUN_TEST(test_ciudad_iterador);
	RUN_TEST(test_ciudad_inspeccion);
	return 0;
}
