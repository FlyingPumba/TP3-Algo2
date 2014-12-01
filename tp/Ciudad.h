#ifndef CIUDAD_H_INCLUDED
#define CIUDAD_H_INCLUDED

#include "../aed2.h"
#include "DiccRapido.h"
#include "ConjRapido.h"
#include "Mapa.h"
#include "ColaPrioridad.h"
#include "RestriccionTP.h"

namespace tp {

    class Ciudad {
        public:

            class itArreglo;

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
            Ciudad::itArreglo Robots() const;

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

            class itArreglo
            {
                public:

                    itArreglo();

                    /**
                     * Devuelve true si quedan elementos validos por iterar.
                     */
                    bool HaySiguiente() const;

                    /**
                     * Devuelve el datoRobot al que apunta el iterador.
                     */
                    const struct DatoRobot& Siguiente() const;

                    /**
                     * Avanza el iterador a la posicion valida mas proxima.
                     */
                    void Avanzar();

                private:

                    Arreglo<struct DatoRobot>& arreglo;
                    Nat pos;

                    itArreglo(Arreglo<DatoRobot>& a);

                    friend typename Ciudad::itArreglo Ciudad::Robots() const;
            };

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

                bool operator <(const NodoPrioridad& otro) {
                    if (infracciones == otro.infracciones) {
                        return rur < otro.rur;
                    } else {
                        return infracciones < otro.infracciones;
                    }
                }

                bool operator >(const NodoPrioridad& otro) {
                    if (infracciones == otro.infracciones) {
                        return rur > otro.rur;
                    } else {
                        return infracciones > otro.infracciones;
                    }
                }

                bool operator == (const NodoPrioridad& otro) const {
                  return infracciones == otro.infracciones && rur == otro.rur;
                }
            };

            struct DatoTag {
                Caracteristica elTag;
                Nat inf;
            };

            struct DatoRobot {
                Estacion estActual;
                ConjRapido tags;
                Nat infracciones;
                ColaPrioridad<NodoPrioridad>::const_Iterador* posEstacion;
                DiccRapido< DiccRapido<bool> > sendasInfrac;
                bool esta;
            };

            struct DatoEstacion {
                DiccRapido<RestriccionTP> sendas;
                ColaPrioridad<NodoPrioridad> robots;
                Nat cantInspec;

                bool operator == (const DatoEstacion& otro) const {
                  return sendas == otro.sendas && cantInspec == otro.cantInspec;
                }
            };

            Arreglo<DatoRobot>* robots;
            Nat cantEsts;
            DiccRapido<DatoEstacion> estaciones;
            Conj<Ests> estsConectadas;
            const class Mapa& mapa;
            Nat proximoRUR;
    };

    Ciudad::Ciudad(const class Mapa& mapa) : mapa(mapa), proximoRUR(0) {
        Conj<Estacion>::const_Iterador itConj = mapa.Estaciones();
        Nat cant = 0;
        while (itConj.HaySiguiente()) {
            cant = cant + 1;
            itConj.Avanzar();
        }
        cantEsts = cant;
        robots = new Arreglo<DatoRobot>(32);

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
                    RestriccionTP& r = mapa.Rest(it.Siguiente(), itAux.Siguiente());
                    DatoEstacion datoAux = estaciones.Significado(it.Siguiente());
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

    void Ciudad::Entrar(const ConjRapido& tags, const Estacion est) {
        if (robots->Tamanho() == proximoRUR + 1) {
            Arreglo<DatoRobot>* aux =  new Arreglo<DatoRobot>(32);
            int i = 0;
            while (i < robots->Tamanho()) {
                aux->Definir(i, (*robots)[i]);
                i = i + 1;
            }
            delete robots;
            robots = aux;
        }

        NodoPrioridad* nodo = new NodoPrioridad();
        nodo->infracciones = 0;
        nodo->rur = proximoRUR;

        DatoEstacion datoAux = estaciones.Significado(est);
        ColaPrioridad<NodoPrioridad>::const_Iterador itCola = datoAux.robots.Encolar(*nodo);

        DatoRobot* datoRobot = new DatoRobot();
        Conj<Ests>::const_Iterador it = estsConectadas.CrearIt();
        while (it.HaySiguiente()) {
            Estacion estA = it.Siguiente().estA;
            Estacion estB = it.Siguiente().estB;
            if (!datoRobot->sendasInfrac.Definido(estA)) {
                DiccRapido<bool>* dicc = new DiccRapido<bool>();
                datoRobot->sendasInfrac.Definir(estA, *dicc);
            }
            DiccRapido<RestriccionTP>& diccAux = estaciones.Significado(estA).sendas;
            RestriccionTP& rest = diccAux.Significado(estB);

            DiccRapido<bool>& dicc = datoRobot->sendasInfrac.Significado(estA);
            if (rest.Verifica(tags)) {
                bool aux = true;
                dicc.Definir(estB, aux);
            } else {
                bool aux = false;
                dicc.Definir(estB, aux);
            }

            it.Avanzar();
        }
        datoRobot->esta = true;
        datoRobot->posEstacion = &itCola;
        robots->Definir(proximoRUR, *datoRobot);
        proximoRUR = proximoRUR + 1;
    }

    void Ciudad::Mover(const RUR rur, const Estacion est) {
        DiccRapido<bool>& diccAux = (*robots)[rur].sendasInfrac.Significado(EstacionActual(rur));
        ColaPrioridad<NodoPrioridad>& colaEstB = estaciones.Significado(est).robots;
        (*robots)[rur].posEstacion->BorrarSiguiente();
        if (diccAux.Significado(est)) {
            (*robots)[rur].infracciones = (*robots)[rur].infracciones + 1;
        }
        NodoPrioridad* nodo = new NodoPrioridad();
        nodo->infracciones = (*robots)[rur].infracciones;
        nodo->rur = rur;
        ColaPrioridad<NodoPrioridad>::const_Iterador itCola = colaEstB.Encolar(*nodo);
        (*robots)[rur].posEstacion = &itCola;
    }

    void Ciudad::Inspeccion(const Estacion est) {
        DatoEstacion datoEst = estaciones.Significado(est);
        if (!datoEst.robots.EsVacia()) {
            if (datoEst.robots.Proximo().infracciones != 0) {
                RUR r = datoEst.robots.Proximo().rur;
                datoEst.robots.Desencolar();
                (*robots)[r].esta = false;
            }
        }
    }

    Ciudad::~Ciudad() {
        delete robots;
    }

    const RUR Ciudad::ProximoRUR() const {
        return proximoRUR;
    }

    const class Mapa& Ciudad::Mapa() const {
        return mapa;
    }

    Ciudad::itArreglo Ciudad::Robots() const {
        return itArreglo(*robots);
    }

    Estacion Ciudad::EstacionActual(const RUR r) const {
        return (*robots)[r].estActual;
    }

    const ConjRapido Ciudad::Tags(const RUR r) const {
        return (*robots)[r].tags;
    }

    const Nat Ciudad::CantInfracciones(const RUR r) const {
        return (*robots)[r].infracciones;
    }

    const Conj<Estacion>::const_Iterador Ciudad::Estaciones() const {
        return mapa.Estaciones();
    }

    // Implementacion del iterador:

    typename Ciudad::itArreglo(Arreglo<DatoRobot>& a) : arreglo(a), pos(0) {
        if (a[0].esta) {
            Avanzar();
        }
    }

    bool Ciudad::itArreglo::HaySiguiente() const {
        bool res = false;
        if (pos + 1 <= arreglo.Tamanho() -1) {
            int i = pos + 1;
            while (i < arreglo.Tamanho() -1) {
                if (arreglo[i].esta) {
                    res = true;
                    i = arreglo.Tamanho();
                } else {
                    i = i +1;
                }
            }
        }
        return res;
    }

    const DatoRobot& Ciudad::itArreglo::Siguiente() const {
        return arreglo[pos];
    }

    void Ciudad::itArreglo::Avanzar() {
        int i = pos + 1;
        while (i < arreglo.Tamanho() -1) {
            if (arreglo[i].esta) {
                pos = i;
                i = arreglo.Tamanho();
            } else {
                i = i +1;
            }
        }
    }
}
#endif
