#include "Driver.cpp"
#include "mini_test.h"
#include "aed2/Lista.h"
#include "aed2/Conj.h"
#include "aed2/Dicc.h"

#include <string>
#include <iostream>

using namespace aed2;

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

/**
* Esta función se puede utilizar para comparar dos colecciones
* iterables que representen conjuntos, es decir, que no tengan 
* elementos repetidos.
*/
template<typename T, typename S>
bool Comparar(const T& t, const S& s)
{
	typename T::const_Iterador it1 = t.CrearIt();
	typename S::const_Iterador it2 = s.CrearIt();

// me fijo si tienen el mismo tamanho

	Nat len1 = 0;
	while( it1.HaySiguiente() ) {
		len1++;
		it1.Avanzar();
	}

	Nat len2 = 0;
	while( it2.HaySiguiente() ) {
		len2++;
		it2.Avanzar();
	}

	if ( len1 != len2 )
		return false;

	it1 = t.CrearIt();
	it2 = s.CrearIt();

// me fijo que tengan los mismos elementos

	while( it1.HaySiguiente() )
	{
		bool esta = false;
		it2 = s.CrearIt();

		while( it2.HaySiguiente() ) {
			if ( it1.Siguiente() == it2.Siguiente() ) {
				esta = true;
				break;
			}
			it2.Avanzar();
		}

		if ( !esta ) {
			return false;
		}

		it1.Avanzar();
	}

	return true;
}


// ---------------------------------------------------------------------

/**
* Ejemplo de caso de test, con llamadas a las rutinas de aserción 
* definidas en mini_test.h
*/
void test_ciudad_simple()
{
	Conj<Estacion> estaciones;
	estaciones.Agregar("Belgrano");
	estaciones.Agregar("Retiro");
	estaciones.Agregar("Martinez");

	Driver caba(estaciones);

	caba.AgregarSenda("Belgrano", "Retiro", "(trenDePasajeros | trenDeCarga) & !trenDeLaAlegria");
	caba.AgregarSenda("Martinez", "Retiro", "trenDeLaAlegria");
	caba.AgregarSenda("Martinez", "Belgrano", "trenDePasajeros");

	Conj<Caracteristica> r1, r2, r3;
	r1.Agregar("trenDePasajeros");
	r2.Agregar("trenDeCarga");
	r3.Agregar("trenDeLaAlegria");

	caba.Entrar(r1,"Belgrano"); // RUR 0
	caba.Entrar(r2,"Retiro");   // RUR 1
	caba.Entrar(r3,"Martinez"); // RUR 2

	ASSERT_EQ(caba.CantidadEstaciones(), 3);
	ASSERT_EQ(caba.CantidadRobotsActivos(), 3);
	ASSERT_EQ(caba.CantidadDeSendasParaEstacion("Belgrano"), 2);

	caba.Mover(0,"Retiro");    // RUR 0: 0 infracciones
	caba.Mover(0,"Martinez");  // RUR 0: 1 infracciones

	caba.Mover(1,"Belgrano");  // RUR 1: 0 infracciones
	caba.Mover(1,"Martinez");  // RUR 1: 1 infracciones

	caba.Mover(2,"Belgrano");  // RUR 2: 1 infracciones
	caba.Mover(2,"Retiro");    // RUR 2: 2 infracciones

	Dicc<RUR,Nat> infraccionesRobots;

	// Chequeo infracciones iterando los robots
	for (Nat i = 0;  i< caba.CantidadRobotsActivos(); ++i)
		infraccionesRobots.Definir(caba.IesimoRobotActivo(i),caba.CantInfraccionesIesimoRobotActivo(i));

	ASSERT_EQ(infraccionesRobots.Significado(0), 1);
	ASSERT_EQ(infraccionesRobots.Significado(1), 1);
	ASSERT_EQ(infraccionesRobots.Significado(2), 2);

	ASSERT_EQ(caba.ElMasInfractor(),2);

	// Vuela un robot
	caba.Inspeccion("Retiro");
	ASSERT_EQ(caba.CantidadRobotsActivos(),2);
}

void test_ciudad_completo() {
	Conj<Estacion> estaciones; estaciones.Agregar("Belgrano"); 
	estaciones.Agregar("Retiro");
	estaciones.Agregar("Martinez");
	estaciones.Agregar("Relejos");
	estaciones.Agregar("Laboca");

	Driver caba(estaciones);

	caba.AgregarSenda("Belgrano", "Retiro", "(trenDePasajeros | trenDeCarga) & !trenDeLaAlegria");
	caba.AgregarSenda("Martinez", "Retiro", "trenDeLaAlegria");
	caba.AgregarSenda("Martinez", "Belgrano", "trenDePasajeros");
	caba.AgregarSenda("Relejos", "Belgrano","trenDeCarga & !trenDePasajeros" );
	caba.AgregarSenda("Retiro", "Laboca", "trenDeAutos | trenDePasajeros");
	caba.AgregarSenda("Laboca", "Martinez","trenDeAutos & !trenDeLaAlegria");

	Conj<Caracteristica> r1, r2, r3, r4;
	r1.Agregar("trenDePasajeros"); 
	r2.Agregar("trenDeCarga"); 
	r3.Agregar("trenDeLaAlegria"); 
	r4.Agregar("trenDeAutos");

	caba.Entrar(r1,"Belgrano"); // RUR 0 
	caba.Entrar(r2,"Retiro"); // RUR 1 
	caba.Entrar(r3,"Martinez"); // RUR 2 
	caba.Entrar(r4,"Laboca"); // RUR 3

	ASSERT_EQ(caba.IesimoRobotActivo(2),2);
	ASSERT_EQ(caba.EstacionActualIesimoRobotActivo(2),"Martinez");
	ASSERT_EQ(caba.CantidadEstaciones(), 5);
	ASSERT_EQ(caba.CaracteristicasIesimoRobotActivo(1) == r2, true);
	ASSERT_EQ(caba.CantidadRobotsActivos(), 4);
	//ASSERT_EQ(caba.IesimaRestriccionDeSenda("Relejos",0),"trenDeCarga & !trenDePasajeros" ); //revisar 
	ASSERT_EQ(caba.CantInfraccionesIesimoRobotActivo(3), 0);
	ASSERT_EQ(caba.CantidadDeSendasParaEstacion("Belgrano"), 3);
	ASSERT_EQ(caba.IesimaEstacion(4), "Laboca");
	ASSERT_EQ(caba.IesimaEstacionDeSenda("Relejos", 0), "Belgrano"); //revisar

	caba.Mover(0,"Relejos"); // RUR 0: 1 infracciones 
	caba.Mover(0,"Belgrano"); // RUR 0: 2 infracciones 
	caba.Mover(0,"Retiro"); // RUR 0: 2 infracciones 
	caba.Mover(0,"Martinez"); // RUR 0: 3 infracciones

	caba.Mover(1,"Belgrano"); // RUR 1: 0 infracciones 
	caba.Mover(1,"Martinez"); // RUR 1: 1 infracciones

	caba.Mover(2,"Belgrano"); // RUR 2: 1 infracciones 
	caba.Mover(2,"Retiro"); // RUR 2: 2 infracciones 
	caba.Mover(2,"Belgrano"); // RUR 2: 3 infracciones

	caba.Mover(3,"Martinez"); // RUR 3: 0 infracciones 
	caba.Mover(3,"Belgrano"); // RUR 3: 1 infracciones 
	caba.Mover(3,"Retiro"); // RUR 3: 2 infracciones

	Dicc<RUR,Nat> infraccionesRobots;

	// Chequeo infracciones iterando los robots 
	for (Nat i = 0; i< caba.CantidadRobotsActivos(); ++i) 
		infraccionesRobots.Definir(caba.IesimoRobotActivo(i),caba.CantInfraccionesIesimoRobotActivo(i));

	ASSERT_EQ(infraccionesRobots.Significado(0), 3);
	ASSERT_EQ(infraccionesRobots.Significado(1), 1);
	ASSERT_EQ(infraccionesRobots.Significado(2), 3);
	ASSERT_EQ(infraccionesRobots.Significado(3), 2);

	ASSERT_EQ(caba.ElMasInfractor(),0);

	// Sacamos un robot 
	caba.Inspeccion("Martinez");
	// inspeccionamos una estacion que no tiene mas robots
	caba.Inspeccion("Martinez");

	ASSERT_EQ(caba.ElMasInfractor(),2);
	ASSERT_EQ(caba.CantidadRobotsActivos(), 2);
	ASSERT_EQ(caba.IesimoRobotActivo(0),2);
	ASSERT_EQ(caba.EstacionActualIesimoRobotActivo(0),"Belgrano");
	ASSERT_EQ(caba.CantInfraccionesIesimoRobotActivo(0), 3);

}

int main(int argc, char **argv)
{
	RUN_TEST(test_ciudad_simple);
	RUN_TEST(test_ciudad_completo);

/******************************************************************
 * TODO: escribir casos de test exhaustivos para todas            *
 * las funcionalidades del módulo.                                *
 * La interacción con el TAD Ciudad se debe hacer exclusivamente  *
 * a través de la interfaz del driver.                            *
 ******************************************************************/

 return 0;
}
