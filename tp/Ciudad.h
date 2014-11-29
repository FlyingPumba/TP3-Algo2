#ifndef CIUDAD_H_INCLUDED
#define CIUDAD_H_INCLUDED

#include "../aed2.h"
#include "DiccRapido.h"
#include "ConjRapido.h"
#include "Mapa.h"
//#include "ColaPrioridad.h"

namespace tp {

    class Ciudad {
        public:

            /**
             * Genera una ciudad nueva
             */
            Ciudad(const Mapa& mapa);

            /**
             * Agrega un robot a la ciudad. La estacion actual del robot es la estacion pasada por parametro.
             * Requiere: est in estaciones(c)
             */
            void Entrar(const ConjRapido& tags, const Estacion est);

            /**
             * Mueve el robot dado de su estacion actual a la estacion de destino.
             * Sí el robot comete una infraccion, la cantidad de sus infracciones aumenta en 1.
             * Requiere: est in estaciones(c)
             */
            void Mover(const RUR rur, const Estacion est);

            /**
             * Saca de circulacion el robot con mayor cantidad de infracciones en la estacion dada, desempatando por RUR.
             * Requiere: est in estaciones(c)
             */
            void Inspeccion(const Estacion est);

            /**
             * Destructor.
             */
            ~Ciudad();

            /**
             * Devuelve el proximo RUR a ser asignado.
             */
            const RUR ProximoRUR() const;

            /**
             * Devuelve el mapa de la ciudad.
             */
            const class Mapa& Mapa() const;

            /**
             * Devuelve un iterador a los robots de la ciudad.
             */
            //const itCiudad Robots() const;

            /**
             * Devuelve la estacion actual del robot.
             * Requiere: r in robots(c)
             */
            Estacion EstacionActual(const RUR r) const;

            /**
             * Devuelve los tags actual del robot.
             * Requiere: r in robots(c)
             */
            const ConjRapido Tags(const RUR r) const;

            /**
             * Devuelve la cantidad de infracciones del robot.
             * Requiere: r in robots(c)
             */
            const Nat CantInfracciones(const RUR r) const;

            /**
             * Devuelve las estaciones que componen la ciudad.
             */
            const Conj<Estacion>::const_Iterador Estaciones() const;

            /**
             * Devuelve la cantidad de veces que se realizo una inspeccion en la estacion est.
             * Requiere: est in estaciones(c)
             */
            const Nat CantInspecciones(const Estacion est) const;

            /**
             * Devuelve la cantidad de veces que se realizo una inspeccion en la estacion est.
             * Requiere: est in estaciones(c)
             */
            const Nat CantInfraccionesXTag(const Caracteristica est) const;

            /**
             * Devuelve el conjunto de tags historicos de la ciudad.
             */
            const Conj<Caracteristica> TagsHistoricos() const;

            /**
             * Devuelve el conjunto de tags historicos de la ciudad.
             */
            const Caracteristica TagMasInvolucrado() const;

        private:
            struct Ests {
                Estacion estA;
                Estacion estB;

                bool operator == (const Ests& otro) const {
                    return (estA == otro.estA && estB == otro.estB);
                }
            };

            struct NodoPrioridad {
                Nat infracciones;
                RUR rur;
            };

            struct DatoTag {
                Caracteristica elTag;
                Nat inf;
            };

            struct DatoRobot {
                Estacion estActual;
                ConjRapido tags;
                Nat infracciones;
                //ColaPrior::itColaPrior posEstacion;
                DiccRapido< DiccRapido<bool> > sendasInfrac;
                bool esta;
            };

            struct DatoEstacion {
                DiccRapido<Restriccion> sendas;
                //ColaPrioridad<NodoPrioridad> robots;
                Nat cantInspec;

                bool operator == (const DatoEstacion& otro) const {
                  return sendas == otro.sendas && cantInspec == otro.cantInspec;
                }
            };

            Arreglo<DatoRobot> robots;
            Nat cantEsts;
            DiccRapido<DatoEstacion> estaciones;
            Conj<Ests> estsConectadas;
            const class Mapa& mapa;
            Nat proximoRUR;
            DiccRapido<Nat> infracTags;
            DatoTag tagMasInvol;
    };

    Ciudad::Ciudad(const class Mapa& mapa) : mapa(mapa), robots(32), proximoRUR(0) {
        Conj<Estacion>::const_Iterador itConj = mapa.Estaciones();
        Nat cant = 0;
        while (itConj.HaySiguiente()) {
            cant = cant + 1;
            itConj.Avanzar();
        }
        cantEsts = cant;
        tagMasInvol.elTag = "";
        tagMasInvol.inf = -1;

        itConj = mapa.Estaciones();
        while (itConj.HaySiguiente()) {
            DatoEstacion aux;
            aux.cantInspec = 0;
            estaciones.Definir(itConj.Siguiente(), aux);
            itConj.Avanzar();
        }

        Conj<Estacion>::const_Iterador it = mapa.Estaciones();
        while (it.HaySiguiente()) {
            Conj<Estacion>::const_Iterador itAux = mapa.Estaciones();
            while (itAux.HaySiguiente()) {
                if (mapa.Conectadas(it.Siguiente(), itAux.Siguiente())) {
                    Restriccion r = mapa.Rest(it.Siguiente(), itAux.Siguiente());
                    DatoEstacion datoAux = estaciones.Significado(it.Siguiente());
                    std::cout << datoAux.sendas.Definido(itAux.Siguiente()) << std::endl;
                    datoAux.sendas.Definir(itAux.Siguiente(), r);
                    Ests conexion;
                    conexion.estA = it.Siguiente();
                    conexion.estB = itAux.Siguiente();
                    estsConectadas.AgregarRapido(conexion);
                }
                /*else {
                    DatoEstacion datoAux = estaciones.Significado(it.Siguiente());
                    datoAux.sendas.Definir(itAux.Siguiente(), NULL);
                }*/
                itAux.Avanzar();
            }
            it.Avanzar();
        }
    }

    Ciudad::~Ciudad() {
        // TODO
    }

    const RUR Ciudad::ProximoRUR() const {
        return proximoRUR;
    }

    const class Mapa& Ciudad::Mapa() const {
        return mapa;
    }

    /*const itCiudad Ciudad::Robots() const {

    }*/

    Estacion Ciudad::EstacionActual(const RUR r) const {
        return robots[r].estActual;
    }

    const ConjRapido Ciudad::Tags(const RUR r) const {
        return robots[r].tags;
    }

    const Nat Ciudad::CantInfracciones(const RUR r) const {
        return robots[r].infracciones;
    }

    const Conj<Estacion>::const_Iterador Ciudad::Estaciones() const {
        return mapa.Estaciones();
    }
}
#endif
