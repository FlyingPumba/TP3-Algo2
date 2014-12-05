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
	Conj<Estacion> estaciones;
	estaciones.Agregar("Belgrano"); 
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

void test_ciudad_hiper_completo() {
	Conj<Estacion> estaciones;
	estaciones.Agregar("Sol"); 
	estaciones.Agregar("Mercurio"); 
	estaciones.Agregar("Venus");
	estaciones.Agregar("Tierra");
	estaciones.Agregar("Luna");
	estaciones.Agregar("Marte");
	estaciones.Agregar("Jupiter");
	estaciones.Agregar("Saturno");
	estaciones.Agregar("Urano");
	estaciones.Agregar("Neptuno");

	Driver sistemaSolar(estaciones);

	sistemaSolar.AgregarSenda("Marte", "Sol", "RecolectorDePlasma");
	sistemaSolar.AgregarSenda("Marte", "Mercurio", "RecolectorDePlasma");
	sistemaSolar.AgregarSenda("Mercurio", "Sol", "RecolectorDePlasma");

	sistemaSolar.AgregarSenda("Tierra", "Marte", "Escavadora | NaveDeCarga | ModuloHabitable | NaveDePasajeros");
	sistemaSolar.AgregarSenda("Tierra", "Luna", "ModuloHabitable & NaveDePasajeros");
	sistemaSolar.AgregarSenda("Marte", "Luna", "ModuloHabitable | NaveDePasajeros");

	sistemaSolar.AgregarSenda("Tierra", "Neptuno", "NaveReactorNuclear & !NaveDePasajeros");
	sistemaSolar.AgregarSenda("Tierra", "Saturno", "NaveReactorNuclear & !NaveDePasajeros");
	sistemaSolar.AgregarSenda("Tierra", "Urano", "NaveReactorNuclear & !NaveDePasajeros");
	sistemaSolar.AgregarSenda("Neptuno", "Urano", "NaveReactorNuclear & !NaveDePasajeros");
	sistemaSolar.AgregarSenda("Saturno", "Urano", "NaveReactorNuclear & !NaveDePasajeros");
	sistemaSolar.AgregarSenda("Saturno", "Neptuno", "NaveReactorNuclear & !NaveDePasajeros");
	sistemaSolar.AgregarSenda("Saturno", "Jupiter", "NaveReactorNuclear & !NaveDePasajeros");
	sistemaSolar.AgregarSenda("Urano", "Venus", "NaveReactorNuclear & !NaveDePasajeros");
	sistemaSolar.AgregarSenda("Neptuno", "Jupiter", "NaveReactorNuclear & !NaveDePasajeros");

	sistemaSolar.AgregarSenda("Marte", "Venus", "NaveDePasajeros");
	sistemaSolar.AgregarSenda("Venus", "Jupiter", "NaveRebelde");
	sistemaSolar.AgregarSenda("Tierra", "Venus", "NaveDeGuerra");
	sistemaSolar.AgregarSenda("Tierra", "Jupiter", "NaveDeGuerra");


	Conj<Caracteristica> r1, r2, r3, r4, r5, r6, r7, r8, r9;
	r1.Agregar("NaveDePasajeros"); 

	r2.Agregar("NaveDePasajeros"); 
	r2.Agregar("ModuloHabitable"); 

	r3.Agregar("Escavadora"); 

	r4.Agregar("NaveDeCarga");
	r4.Agregar("NaveDePasajeros");

	r5.Agregar("NaveRebelde");
	r5.Agregar("NaveDePasajeros");	

	r6.Agregar("NaveRebelde");
	r6.Agregar("NaveDePasajeros");
	r6.Agregar("ModuloHabitable");

	r7.Agregar("RecolectorDePlasma"); 

	r8.Agregar("NaveReactorNuclear");

	r9.Agregar("NaveRebelde");
	r9.Agregar("NaveDeGuerra");
	r9.Agregar("NaveReactorNuclear");

	sistemaSolar.Entrar(r1,"Tierra"); // RUR 0 
	sistemaSolar.Entrar(r2,"Luna"); // RUR 1 
	sistemaSolar.Entrar(r3,"Marte"); // RUR 2 
	sistemaSolar.Entrar(r4,"Marte"); // RUR 3

	ASSERT_EQ(sistemaSolar.IesimoRobotActivo(2),2);
	ASSERT_EQ(sistemaSolar.EstacionActualIesimoRobotActivo(2),"Marte");
	ASSERT_EQ(sistemaSolar.CantidadEstaciones(), 10);
	ASSERT_EQ(sistemaSolar.CaracteristicasIesimoRobotActivo(3) == r4, true);
	ASSERT_EQ(sistemaSolar.CantidadRobotsActivos(), 4);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(0), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(1), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(2), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(3), 0);
	ASSERT_EQ(sistemaSolar.CantidadDeSendasParaEstacion("Venus"), 4);
	ASSERT_EQ(sistemaSolar.CantidadDeSendasParaEstacion("Tierra"), 7);

	// r1 lleva pasajeros a la Luna, pero no es un modulo habitable
	sistemaSolar.Mover(0,"Luna"); // RUR 0: 1 infracciones 
	// r1 lleva pasajeros a Marte
	sistemaSolar.Mover(0,"Marte"); // RUR 0: 0 infracciones 
	// r1 vuelve a la Luna
	sistemaSolar.Mover(0,"Luna"); // RUR 0: 0 infracciones 
	// r1 vuelve a la Tierra
	sistemaSolar.Mover(0,"Tierra"); // RUR 0: 2 infracciones 

	// r2 va a la Tierra a buscar pasajeros
	sistemaSolar.Mover(1,"Tierra"); // RUR 1: 0 infracciones 
	// r2 va a Marte a colonizar
	sistemaSolar.Mover(1,"Marte"); // RUR 1: 0 infracciones

	// inspeccion en Marte !
	sistemaSolar.Inspeccion("Marte");
	// todo en orden por acá:
	ASSERT_EQ(sistemaSolar.CantidadRobotsActivos(), 4);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(0), 2);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(1), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(2), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(3), 0);

	// r3 se mueve a escavar en Venus
	sistemaSolar.Mover(2,"Venus"); // RUR 2: 1 infracciones 

	sistemaSolar.Entrar(r5,"Venus"); // RUR 4
	// r5 se mueve a jupiter
	sistemaSolar.Mover(4,"Jupiter"); // RUR 4: 0 infracciones 
	// r5 decide explorar Saturno y Urano en busca de material radioactivo
	sistemaSolar.Mover(4,"Saturno"); // RUR 4: 1 infracciones 
	sistemaSolar.Mover(4,"Urano"); // RUR 4: 2 infracciones 
	// r5 vuelve a Venus
	sistemaSolar.Mover(4,"Venus"); // RUR 4: 3 infracciones 

	// inspeccion en Venus !
	sistemaSolar.Inspeccion("Venus");
	// r5 es eliminado del sistema
	ASSERT_EQ(sistemaSolar.CantidadRobotsActivos(), 4);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(0), 2);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(1), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(2), 1);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(3), 0);

	// entras las naves restantes al sistema
	sistemaSolar.Entrar(r6,"Jupiter"); // RUR 5
	sistemaSolar.Entrar(r7,"Marte"); // RUR 6
	sistemaSolar.Entrar(r8,"Saturno"); // RUR 7
	sistemaSolar.Entrar(r9,"Jupiter"); // RUR 8

	// r8 recorre todos los planetas radioactivos
	sistemaSolar.Mover(7,"Urano"); // RUR 8: 0 infracciones 
	sistemaSolar.Mover(7,"Neptuno"); // RUR 8: 0 infracciones 
	sistemaSolar.Mover(7,"Urano"); // RUR 8: 0 infracciones 
	sistemaSolar.Mover(7,"Saturno"); // RUR 8: 0 infracciones 
	sistemaSolar.Mover(7,"Neptuno"); // RUR 8: 0 infracciones 
	sistemaSolar.Mover(7,"Saturno"); // RUR 8: 0 infracciones 

	// r9 se mueve a Saturno a buscar material radioactivo, escoltado por r6
	sistemaSolar.Mover(8,"Saturno"); // RUR 8: 1 infracciones 
	sistemaSolar.Mover(5,"Saturno"); // RUR 8: 1 infracciones 

	// encuentran a r8 y lo capturan, llevandolo a Neptuno y luego volviendo a Jupiter
	sistemaSolar.Mover(7,"Neptuno"); // RUR 7: 0 infracciones 
	sistemaSolar.Mover(8,"Neptuno"); // RUR 8: 2 infracciones 
	sistemaSolar.Mover(5,"Neptuno"); // RUR 5: 2 infracciones 
	sistemaSolar.Mover(7,"Jupiter"); // RUR 7: 1 infracciones 
	sistemaSolar.Mover(8,"Jupiter"); // RUR 8: 2 infracciones 
	sistemaSolar.Mover(5,"Jupiter"); // RUR 5: 2 infracciones 

	// patrulla de inspeccion en Jupiter !
	sistemaSolar.Inspeccion("Jupiter");
	sistemaSolar.Inspeccion("Jupiter");

	ASSERT_EQ(sistemaSolar.CantidadRobotsActivos(), 7);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(0), 2);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(1), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(2), 1);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(3), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(4), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(5), 0);
	ASSERT_EQ(sistemaSolar.CantInfraccionesIesimoRobotActivo(6), 0);

	ASSERT_EQ(sistemaSolar.ElMasInfractor(), 0);
	ASSERT_EQ(sistemaSolar.EstacionActualIesimoRobotActivo(0),"Tierra");
	ASSERT_EQ(sistemaSolar.EstacionActualIesimoRobotActivo(1),"Marte");
	ASSERT_EQ(sistemaSolar.EstacionActualIesimoRobotActivo(2),"Venus");
	ASSERT_EQ(sistemaSolar.EstacionActualIesimoRobotActivo(3),"Marte");
	ASSERT_EQ(sistemaSolar.EstacionActualIesimoRobotActivo(4),"Marte");
	ASSERT_EQ(sistemaSolar.EstacionActualIesimoRobotActivo(5),"Jupiter");
	ASSERT_EQ(sistemaSolar.EstacionActualIesimoRobotActivo(6),"Jupiter");
}

int main(int argc, char **argv)
{
	RUN_TEST(test_ciudad_simple);
	RUN_TEST(test_ciudad_completo);
	RUN_TEST(test_ciudad_hiper_completo);

/******************************************************************
 * TODO: escribir casos de test exhaustivos para todas            *
 * las funcionalidades del módulo.                                *
 * La interacción con el TAD Ciudad se debe hacer exclusivamente  *
 * a través de la interfaz del driver.                            *
 ******************************************************************/

 return 0;
}
