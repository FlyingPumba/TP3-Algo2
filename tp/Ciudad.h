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

            friend class itArreglo;

            /**
             * Genera una ciudad nueva
             */
            Ciudad(const Mapa& mapa);

            /**
             * Agrega un robot a la ciudad. La estacion actual del robot es la estacion pasada por parametro.
             * Requiere: est in estaciones(c)
             */
            void Entrar(const ConjRapido& tags, Estacion est);

            /**
             * Mueve el robot dado de su estacion actual a la estacion de destino.
             * Sí el robot comete una infraccion, la cantidad de sus infracciones aumenta en 1.
             * Requiere: est in estaciones(c)
             */
            void Mover(RUR rur, Estacion est);

            /**
             * Saca de circulacion el robot con mayor cantidad de infracciones en la estacion dada, desempatando por RUR.
             * Requiere: est in estaciones(c)
             */
            void Inspeccion(Estacion est);

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
            class itArreglo& Robots() const;

            /**
             * Devuelve la estacion actual del robot.
             * Requiere: r in robots(c)
             */
            Estacion EstacionActual(RUR r) const;

            /**
             * Devuelve los tags actual del robot.
             * Requiere: r in robots(c)
             */
            const ConjRapido& Tags(RUR r) const;

            /**
             * Devuelve la cantidad de infracciones del robot.
             * Requiere: r in robots(c)
             */
            const Nat CantInfracciones(RUR r) const;

            /**
             * Devuelve las estaciones que componen la ciudad.
             */
            const Conj<Estacion>::const_Iterador Estaciones() const;

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

                bool operator <(const NodoPrioridad& otro) const {
                    if (infracciones == otro.infracciones) {
                        return rur < otro.rur;
                    } else {
                        return infracciones < otro.infracciones;
                    }
                }

                bool operator >(const NodoPrioridad& otro) const {
                    if (infracciones == otro.infracciones) {
                        return rur > otro.rur;
                    } else {
                        return infracciones > otro.infracciones;
                    }
                }

                bool operator >=(const NodoPrioridad& otro) const {
                    return *this == otro || *this > otro;
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
                DatoRobot(Estacion est, ColaPrioridad<NodoPrioridad>::Iterador* it, const ConjRapido& tags, DiccRapido< DiccRapido<bool> >* dicc) : estActual(est), tags(tags), infracciones(0), posEstacion(it), sendasInfrac(dicc), esta(true){};

                Estacion estActual;
                const ConjRapido& tags;
                Nat infracciones;
                ColaPrioridad<NodoPrioridad>::Iterador* posEstacion;
                DiccRapido< DiccRapido<bool> >* sendasInfrac;
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
            const Ciudad::DatoRobot& Siguiente() const;

            /**
             * Avanza el iterador a la posicion valida mas proxima.
             */
            void Avanzar();

        private:

            Arreglo<Ciudad::DatoRobot>& arreglo;
            Nat pos;

            itArreglo(Arreglo<Ciudad::DatoRobot>& a);

            friend itArreglo& Ciudad::Robots() const;
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
            DatoEstacion* aux = new DatoEstacion();
            aux->cantInspec = 0;
            estaciones.Definir(itConj.Siguiente(), *aux);
            itConj.Avanzar();
        }

        Conj<Estacion>::const_Iterador it = mapa.Estaciones();
        while (it.HaySiguiente()) {
            Conj<Estacion>::const_Iterador itAux = mapa.Estaciones();
            while (itAux.HaySiguiente()) {
                if (mapa.Conectadas(it.Siguiente(), itAux.Siguiente())) {
                    RestriccionTP& r = mapa.Rest(it.Siguiente(), itAux.Siguiente());
                    DatoEstacion& datoAux = estaciones.Significado(it.Siguiente());
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

    void Ciudad::Entrar(const ConjRapido& tags, Estacion est) {
        #ifdef DEBUG
        assert(estaciones.Definido(est));
        #endif

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

        DatoEstacion& datoAux = estaciones.Significado(est);
        ColaPrioridad<NodoPrioridad>::Iterador* itCola = datoAux.robots.Encolar(*nodo);
        DiccRapido< DiccRapido<bool> >* dicc = new DiccRapido< DiccRapido<bool> >();

        DatoRobot* datoRobot = new DatoRobot(est, itCola, tags, dicc);

        Conj<Ests>::const_Iterador it = estsConectadas.CrearIt();
        while (it.HaySiguiente()) {
            Estacion estA = it.Siguiente().estA;
            Estacion estB = it.Siguiente().estB;
            if (!datoRobot->sendasInfrac->Definido(estA)) {
                DiccRapido<bool>* dicc = new DiccRapido<bool>();
                datoRobot->sendasInfrac->Definir(estA, *dicc);
            }
            DiccRapido<RestriccionTP>& diccAux = estaciones.Significado(estA).sendas;
            RestriccionTP& rest = diccAux.Significado(estB);

            DiccRapido<bool>& dicc = datoRobot->sendasInfrac->Significado(estA);
            if (rest.Verifica(tags)) {
                bool* aux = new bool();
                *aux = false;
                dicc.Definir(estB, *aux);
            } else {
                bool* aux = new bool();
                *aux = true;
                dicc.Definir(estB, *aux);
            }

            it.Avanzar();
        }
        robots->Definir(proximoRUR, *datoRobot);
        proximoRUR = proximoRUR + 1;

        delete datoRobot;
    }

    void Ciudad::Mover(RUR rur, Estacion est) {
        #ifdef DEBUG
        assert(estaciones.Definido(est));
        assert(mapa.Conectadas(est, (*robots)[rur].estActual));
        #endif

        DiccRapido<bool>& diccAux = (*robots)[rur].sendasInfrac->Significado(EstacionActual(rur));
        ColaPrioridad<NodoPrioridad>& colaEstB = estaciones.Significado(est).robots;
        const NodoPrioridad& aux = (*robots)[rur].posEstacion->Siguiente();
        (*robots)[rur].posEstacion->BorrarSiguiente();
        delete &aux;
        if (diccAux.Significado(est)) {
            (*robots)[rur].infracciones = (*robots)[rur].infracciones + 1;
        }
        NodoPrioridad* nodo = new NodoPrioridad();
        nodo->infracciones = (*robots)[rur].infracciones;
        nodo->rur = rur;
        ColaPrioridad<NodoPrioridad>::Iterador* itCola = colaEstB.Encolar(*nodo);
        (*robots)[rur].posEstacion = itCola;
        (*robots)[rur].estActual = est;
    }

    void Ciudad::Inspeccion(Estacion est) {
        #ifdef DEBUG
        assert(estaciones.Definido(est));
        #endif

        DatoEstacion& datoEst = estaciones.Significado(est);
        if (!datoEst.robots.EsVacia()) {
            if (datoEst.robots.Proximo().infracciones != 0) {
                const NodoPrioridad& nodo = datoEst.robots.Proximo();
                RUR r = nodo.rur;
                datoEst.robots.Desencolar();
                delete &nodo;
                (*robots)[r].esta = false;
            }
        }
    }

    Ciudad::~Ciudad() {
        // borro todos los robots del arreglo
        int i = 0;
        while (i < robots->Tamanho() && robots->Definido(i)) {

            DatoRobot& datoRobot = (*robots)[i];
            Conj<String> claves = datoRobot.sendasInfrac->Claves();
            Conj<String>::Iterador it = claves.CrearIt();
            while (it.HaySiguiente()) {

                Conj<String> claves2 = datoRobot.sendasInfrac->Significado(it.Siguiente()).Claves();
                Conj<String>::Iterador it2 = claves2.CrearIt();
                while (it2.HaySiguiente()) {
                    bool& aux = datoRobot.sendasInfrac->Significado(it.Siguiente()).Significado(it2.Siguiente());
                    delete &aux;
                    it2.Avanzar();
                }


                DiccRapido<bool>& dicc = datoRobot.sendasInfrac->Significado(it.Siguiente());
                delete &dicc;
                it.Avanzar();
            }

            delete datoRobot.sendasInfrac;
            i = i + 1;
        }

        delete robots;

        Conj<String> claves = estaciones.Claves();
        Conj<String>::Iterador it = claves.CrearIt();
        while (it.HaySiguiente()) {
            DatoEstacion& dato = estaciones.Significado(it.Siguiente());
            ColaPrioridad<NodoPrioridad>& robs = dato.robots;
            while (!robs.EsVacia()) {
                const NodoPrioridad& nodo = robs.Proximo();
                robs.Desencolar();
                delete &nodo;
            }

            delete &dato;
            it.Avanzar();
        }
    }

    const RUR Ciudad::ProximoRUR() const {
        return proximoRUR;
    }

    const class Mapa& Ciudad::Mapa() const {
        return mapa;
    }

    itArreglo& Ciudad::Robots() const {
        itArreglo* it = new itArreglo(*robots);;
        return *it;
    }

    Estacion Ciudad::EstacionActual(RUR r) const {
        #ifdef DEBUG
        assert(robots->Definido(r));
        #endif
        return (*robots)[r].estActual;
    }

    const ConjRapido& Ciudad::Tags(RUR r) const {
        #ifdef DEBUG
        assert(robots->Definido(r));
        #endif
        return (*robots)[r].tags;
    }

    const Nat Ciudad::CantInfracciones(RUR r) const {
        #ifdef DEBUG
        assert(robots->Definido(r));
        #endif
        return (*robots)[r].infracciones;
    }

    const Conj<Estacion>::const_Iterador Ciudad::Estaciones() const {
        return mapa.Estaciones();
    }

    // Implementacion del iterador:

    itArreglo::itArreglo(Arreglo<Ciudad::DatoRobot>& a) : arreglo(a), pos(0) {
        if (arreglo.Definido(0) && !a[0].esta) {
            Avanzar();
        }
    }

    bool itArreglo::HaySiguiente() const {
        int i = pos;
        bool res = false;
        while (i < arreglo.Tamanho() && arreglo.Definido(i)) {
            if (arreglo[i].esta) {
                res = true;
                break;
            } else {
                i = i + 1;
            }
        }
        return res;
    }

    const Ciudad::DatoRobot& itArreglo::Siguiente() const {
        return arreglo[pos];
    }

    void itArreglo::Avanzar() {
        #ifdef DEBUG
        assert(HaySiguiente());
        #endif
        int i = pos + 1;
        bool hayUnoValido = false;
        while (i < arreglo.Tamanho() && arreglo.Definido(i)) {
            if (arreglo[i].esta) {
                pos = i;
                hayUnoValido = true;
                break;
            } else {
                i = i + 1;
            }
        }
        if (!hayUnoValido) {
            pos = arreglo.Tamanho();
        }
    }
}
#endif
