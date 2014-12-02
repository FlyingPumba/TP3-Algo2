#include "../mini_test.h"
#include "RestriccionTP.h"

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

void test_restriccion_simple()
{
	ConjRapido tags;
	Caracteristica tag_Camion = "Camion";
	Caracteristica tag_Auto = "Auto";

	RestriccionTP rest(tag_Camion);
	ASSERT_EQ(rest.Verifica(tags), false);

	tags.Agregar(tag_Auto);
	ASSERT_EQ(rest.Verifica(tags), false);

	tags.Agregar(tag_Camion);
	ASSERT_EQ(rest.Verifica(tags), true);
}

void test_restriccion_and()
{
	ConjRapido tags;
	Caracteristica tag_Camion = "Camion";
	Caracteristica tag_Auto = "Auto";
	Caracteristica tag_Bici = "Bici";

	RestriccionTP r1(tag_Camion);
	RestriccionTP r2(tag_Auto);

	RestriccionTP restAnd = RestriccionTP::And(r1, r2);

	ASSERT_EQ(restAnd.Verifica(tags), false);
	tags.Agregar(tag_Auto);
	ASSERT_EQ(restAnd.Verifica(tags), false);
	tags.Agregar(tag_Bici);
	ASSERT_EQ(restAnd.Verifica(tags), false);
	tags.Agregar(tag_Camion);
	ASSERT_EQ(restAnd.Verifica(tags), true);
}

void test_restriccion_or()
{
	ConjRapido tags1;
	ConjRapido tags2;
	Caracteristica tag_Camion = "Camion";
	Caracteristica tag_Auto = "Auto";
	Caracteristica tag_Bici = "Bici";

	RestriccionTP r1(tag_Camion);
	RestriccionTP r2(tag_Auto);

	RestriccionTP restOr = RestriccionTP::Or(r1, r2);

	ASSERT_EQ(restOr.Verifica(tags1), false);
	tags1.Agregar(tag_Bici);
	ASSERT_EQ(restOr.Verifica(tags1), false);
	tags1.Agregar(tag_Auto);
	ASSERT_EQ(restOr.Verifica(tags1), true);
	tags2.Agregar(tag_Camion);
	ASSERT_EQ(restOr.Verifica(tags2), true);
}

void test_restriccion_not()
{
	ConjRapido tags;
	Caracteristica tag_Camion = "Camion";
	Caracteristica tag_Auto = "Auto";
	Caracteristica tag_Bici = "Bici";

	RestriccionTP r1(tag_Camion);

	RestriccionTP restNot = RestriccionTP::Not(r1);

	ASSERT_EQ(restNot.Verifica(tags), true);
	tags.Agregar(tag_Auto);
	ASSERT_EQ(restNot.Verifica(tags), true);
	tags.Agregar(tag_Bici);
	ASSERT_EQ(restNot.Verifica(tags), true);
	tags.Agregar(tag_Camion);
	ASSERT_EQ(restNot.Verifica(tags), false);

	std::cout << restNot;
}

void test_restriccion_compleja()
{
	ConjRapido tags1;
	ConjRapido tags2;
	Caracteristica tag_Camion = "Camion";
	Caracteristica tag_Auto = "Auto";
	Caracteristica tag_Bici = "Bici";
	Caracteristica tag_Avion = "Avion";
	Caracteristica tag_Lancha = "Lancha";

	RestriccionTP r1(tag_Camion);
	RestriccionTP r2(tag_Auto);
	RestriccionTP r3(tag_Bici);
	RestriccionTP r4(tag_Avion);
	RestriccionTP r5(tag_Lancha);

	// Restriccion:
	// (!Avion & !Lancha) & (Camion | Auto | Bici)
	RestriccionTP restNot1 = RestriccionTP::Not(r5);
	RestriccionTP restNot2 = RestriccionTP::Not(r4);
	RestriccionTP restAnd1 = RestriccionTP::And(restNot1, restNot2);

	RestriccionTP restOr1 = RestriccionTP::Or(r1, r2);
	RestriccionTP restOr2 = RestriccionTP::Or(r3, restOr1);

	RestriccionTP rest = RestriccionTP::And(restOr2, restAnd1);

	ConjRapido tags;
	ASSERT_EQ(rest.Verifica(tags), false);
	tags.Agregar(tag_Auto);
	ASSERT_EQ(rest.Verifica(tags), true);
	tags.Agregar(tag_Camion);
	ASSERT_EQ(rest.Verifica(tags), true);
	tags.Agregar(tag_Avion);
	ASSERT_EQ(rest.Verifica(tags), false);
}

int main(int argc, char **argv)
{
	RUN_TEST(test_restriccion_simple);
	RUN_TEST(test_restriccion_and);
	RUN_TEST(test_restriccion_or);
	RUN_TEST(test_restriccion_not);
	RUN_TEST(test_restriccion_compleja);
	return 0;
}
