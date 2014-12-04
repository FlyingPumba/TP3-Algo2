#include "Driver.h"
#include <iostream>
#include <string>
#include <sstream>

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

    Estacion Driver::IesimaEstacion(Nat i) const
    {
        Conj<Estacion>::const_Iterador it = mapa.Estaciones();
        int j = 0;
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
            if (mapa.Conectadas(e1, it.Siguiente())) {
                j = j + 1;
            }
            it.Avanzar();
        }
        RestriccionTP& rest = mapa.Rest(it.Siguiente(), e1);

        std::stringstream ss;
        ss << rest;

        return ss.str();
    }

    void Driver::AgregarSenda(const Estacion &e1, const Estacion &e2, Restriccion r)
    {
        ArbolSintactico* expr = ArbolSintactico::LeerDeString(r);
        //std::cout << expr->aString() << std::endl;

        RestriccionTP& rest = ParsearArbolSintactico(expr);
        mapa.Conectar(e1, e2, rest);

        if (ciudad != NULL) {
            delete ciudad;
        }
        ciudad = new Ciudad(mapa);
        //delete expr;
    }

    Nat Driver::CantidadRobotsActivos() const
    {
        int cant = 0;
        itArreglo& it(ciudad->Robots());
        while (it.HaySiguiente()) {
            cant = cant + 1;
            it.Avanzar();
        }
        delete &it;
        return cant;
    }

    RUR Driver::IesimoRobotActivo(Nat i) const
    {
        itArreglo& it(ciudad->Robots());
        int j = 0;
        while (j < i) {
            j = j + 1;
            it.Avanzar();
        }
        RUR r = it.Siguiente().posEstacion.Siguiente().rur;
        delete &it;
        return r;
    }

    Estacion Driver::EstacionActualIesimoRobotActivo(Nat i) const
    {
        itArreglo& it(ciudad->Robots());
        int j = 0;
        while (j < i) {
            j = j + 1;
            it.Avanzar();
        }
        Estacion est = (it.Siguiente()).estActual;
        delete &it;
        return est;
    }

    Conj<Caracteristica> Driver::CaracteristicasIesimoRobotActivo(Nat i) const
    {
        itArreglo& it(ciudad->Robots());
        int j = 0;
        while (j < i) {
            j = j + 1;
            it.Avanzar();
        }
        Conj<Caracteristica> conj;
        ConjRapido::const_Iterador itTags = (it.Siguiente()).tags.CrearIt();
        while (itTags.HaySiguiente()) {
            conj.AgregarRapido(itTags.Siguiente());
            itTags.Avanzar();
        }
        delete &it;
        return conj;
    }

    Nat Driver::CantInfraccionesIesimoRobotActivo(Nat i) const
    {
        itArreglo& it(ciudad->Robots());
        int j = 0;
        while (j < i) {
            j = j + 1;
            it.Avanzar();
        }
        Nat inf = (it.Siguiente()).infracciones;
        delete &it;
        return inf;
    }

    RUR Driver::ElMasInfractor() const
    {
        itArreglo& it(ciudad->Robots());
        RUR r = it.Siguiente().posEstacion.Siguiente().rur;
        Nat inf = it.Siguiente().infracciones;

        while (it.HaySiguiente()) {
            if (it.Siguiente().infracciones > inf) {
                r = it.Siguiente().posEstacion.Siguiente().rur;
                inf = it.Siguiente().infracciones;
            }
            it.Avanzar();
        }
        delete &it;
        return r;
    }

    void Driver::Entrar(const Conj<Caracteristica> &cs, const Estacion &estacionInicial)
    {
        ConjRapido* tags = new ConjRapido();
        Conj<Caracteristica>::const_Iterador it = cs.CrearIt();

        while (it.HaySiguiente()) {
            tags->Agregar(it.Siguiente());
            it.Avanzar();
        }
        ciudad->Entrar(*tags, estacionInicial);
    }

    void Driver::Mover(RUR robot, const Estacion &destino)
    {
        ciudad->Mover(robot, destino);
    }

    void Driver::Inspeccion(const Estacion &e)
    {
        ciudad->Inspeccion(e);
    }

    RestriccionTP& Driver::ParsearArbolSintactico(ArbolSintactico* expr) {
        RestriccionTP* rest;
        if (expr->raiz == "&") {
            rest = RestriccionTP::And(ParsearArbolSintactico(expr->izq), ParsearArbolSintactico(expr->der));
        } else if (expr->raiz == "|") {
            rest = RestriccionTP::Or(ParsearArbolSintactico(expr->izq), ParsearArbolSintactico(expr->der));
        } else if (expr->raiz == "!") {
            rest = RestriccionTP::Not(ParsearArbolSintactico(expr->izq));
        } else {
            //String* copia = new String(expr->raiz);
            rest = new RestriccionTP(expr->raiz);
        }
        return *rest;
    }

} // namespace aed2
