#include "../mini_test.h"
#include "Restriccion.h"

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

	Restriccion rest(tag_Camion);
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

	Restriccion r1(tag_Camion);
	Restriccion r2(tag_Auto);

	Restriccion restAnd = Restriccion::And(r1, r2);

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

	Restriccion r1(tag_Camion);
	Restriccion r2(tag_Auto);

	Restriccion restOr = Restriccion::Or(r1, r2);

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

	Restriccion r1(tag_Camion);

	Restriccion restNot = Restriccion::Not(r1);

	ASSERT_EQ(restNot.Verifica(tags), true);
	tags.Agregar(tag_Auto);
	ASSERT_EQ(restNot.Verifica(tags), true);
	tags.Agregar(tag_Bici);
	ASSERT_EQ(restNot.Verifica(tags), true);
	tags.Agregar(tag_Camion);
	ASSERT_EQ(restNot.Verifica(tags), false);
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

	Restriccion r1(tag_Camion);
	Restriccion r2(tag_Auto);
	Restriccion r3(tag_Bici);
	Restriccion r4(tag_Avion);
	Restriccion r5(tag_Lancha);

	// Restriccion:
	// (!Avion & !Lancha) & (Camion | Auto | Bici)
	Restriccion restNot1 = Restriccion::Not(r5);
	Restriccion restNot2 = Restriccion::Not(r4);
	Restriccion restAnd1 = Restriccion::And(restNot1, restNot2);

	Restriccion restOr1 = Restriccion::Or(r1, r2);
	Restriccion restOr2 = Restriccion::Or(r3, restOr1);

	Restriccion rest = Restriccion::And(restOr2, restAnd1);

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
