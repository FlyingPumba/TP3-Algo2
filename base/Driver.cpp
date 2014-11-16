#include "Driver.h"
#include "ArbolSintactico.h"

namespace aed2 {

Driver::Driver(const Conj<Estacion> &estacionesIniciales) {
    // TODO
}

Driver::~Driver() {
    // TODO
}

Nat Driver::CantidadEstaciones() const
{
 // TODO
}

Nat Driver::CantidadDeSendasParaEstacion(const Estacion &e) const
{
 // TODO
}

const Estacion& Driver::IesimaEstacionDeSenda(const Estacion &e, Nat i) const
{
 // TODO
}

const Restriccion& Driver::IesimaRestriccionDeSenda(const Estacion &e1, Nat i) const
{
 // TODO
}

void Driver::AgregarSenda(const Estacion &e1, const Estacion &e2, Restriccion r)
{
    // TODO
    // Ejemplo uso ArbolSintactico:
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

const Estacion& Driver::EstacionActualIesimoRobotActivo(Nat i) const
{
 // TODO
}

const Conj<Caracteristica>& Driver::CaracteristicasIesimoRobotActivo(Nat i) const
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

