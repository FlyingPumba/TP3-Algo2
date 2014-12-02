#include "Driver.h"
#include "ArbolSintactico.h"

namespace aed2 {

Driver::Driver(const Conj<Estacion> &estacionesIniciales) : ciudad(NULL) {
    Conj<Estacion>::const_Iterador it = estacionesIniciales.CrearIt();
    while (it.HaySiguiente()) {
    	mapa.Agregar(it.Siguiente());
        it.Avanzar();
    }
    ciudad = new Ciudad(mapa);
}

Driver::~Driver() {
    delete ciudad;
}

Nat Driver::CantidadEstaciones() const
{
	int cant = 0;
	Conj<Estacion>::const_Iterador it = mapa.Estaciones();
    while (it.HaySiguiente()) {
    	cant = cant + 1;
        it.Avanzar();
    }
    return cant;
}

Estacion IesimaEstacion(Nat i) const
{
	Conj<Estacion>::const_Iterador it = mapa.Estaciones();
	int i = 0;
    while (j < i) {
    	j = j + 1;
        it.Avanzar();
    }
    return it.Siguiente();
}


Nat Driver::CantidadDeSendasParaEstacion(const Estacion &e) const
{
	Conj<Estacion>::const_Iterador it = mapa.Estaciones();
	int cant = 0;
    while (it.HaySiguiente()) {
    	if (mapa.Conectadas(e, it.Siguiente())) {
    		cant = cant + 1;
    	}

        it.Avanzar();
    }
    return cant;
}

Estacion Driver::IesimaEstacionDeSenda(const Estacion &e, Nat i) const
{
	Conj<Estacion>::const_Iterador it = mapa.Estaciones();
	int j = 0;
    while (j < i) {
    	if (mapa.Conectadas(e, it.Siguiente())) {
    		j = j + 1;
    	}
        it.Avanzar();
    }
    return it.Siguiente();
}

Restriccion Driver::IesimaRestriccionDeSenda(const Estacion &e1, Nat i) const
{
	Conj<Estacion>::const_Iterador it = mapa.Estaciones();
	int j = 0;
    while (j < i) {
    	if (mapa.Conectadas(e, it.Siguiente())) {
    		j = j + 1;
    	}
        it.Avanzar();
    }
    RestriccionTP& rest = mapa.Rest(it.Siguiente(), e);
    return "";
}

void Driver::AgregarSenda(const Estacion &e1, const Estacion &e2, Restriccion r)
{
    ArbolSintactico* expr = ArbolSintactico::LeerDeString(r);
    std::cout << expr->aString() << std::endl;

    delete expr;
}

Nat Driver::CantidadRobotsActivos() const
{
 // TODO
}

RUR Driver::IesimoRobotActivo(Nat i) const
{
 // TODO
}

Estacion Driver::EstacionActualIesimoRobotActivo(Nat i) const
{
 // TODO
}

Conj<Caracteristica> Driver::CaracteristicasIesimoRobotActivo(Nat i) const
{
 // TODO
}

Nat Driver::CantInfraccionesIesimoRobotActivo(Nat i) const
{
 // TODO
}

RUR Driver::ElMasInfractor() const
{
 // TODO
}

void Driver::Entrar(const Conj<Caracteristica> &cs, const Estacion &estacionInicial)
{
 // TODO
}

void Driver::Mover(RUR robot, const Estacion &destino)
{
 // TODO
}

void Driver::Inspeccion(const Estacion &e)
{
    // TODO
}

} // namespace aed2
