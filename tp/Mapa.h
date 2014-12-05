#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "../aed2.h"
#include "RestriccionTP.h"

namespace tp {

    class Mapa{
        public:

            /**
             * Genera un mapa nuevo.
             */
            Mapa();

            /**
             * Agrega una estacion al Mapa.
             * Requiere: est no pertenece a las estaciones del mapa.
             */
            void Agregar(Estacion est);

            /**
             * Conecta dos estaciones del mapa.
             * Requiere: est1 y est2 pertenecen a las estaciones del mapa, y no estan conectadas.
             */
            void Conectar(Estacion est1, Estacion est2, RestriccionTP& r);

            /**
             * Destructor.
             */
            ~Mapa();

            /**
             * Devuelve las estaciones del mapa.
             */
            Conj<Estacion>::const_Iterador Estaciones() const;

            /**
             * Devuelve true si las estaciones estan conectadas.
             * Requiere: est1 y est2 pertenecen a las estaciones del mapa.
             */
            bool Conectadas(Estacion est1, Estacion est2) const;

            /**
             * Devuelve la restriccion de la senda que una las estaciones.
             * Requiere: est1 y est2 pertenecen a las estaciones del mapa, y ademas estan conectadas.
             */
            RestriccionTP& Rest(Estacion est1, Estacion est2) const;

        private:
            struct Nodo {
                Nodo(const Estacion est1, const Estacion est2, RestriccionTP& r) : est1(est1), est2(est2), rest(r) {};

                Estacion est1;
                Estacion est2;
                RestriccionTP& rest;

                bool operator == (const Nodo otro) const {
                  return est1 == otro.est1 && est2 == otro.est2 && rest == otro.rest;
                }

                bool operator != (const Nodo otro) const {
                  return est1 != otro.est1 || est2 != otro.est2 || !(rest == otro.rest);
                }
            };

            Conj<Estacion> estaciones;
            Conj<Nodo> sendas;

    };

    Mapa::Mapa() {}

    void Mapa::Agregar(Estacion est) {
        assert(estaciones.Pertenece(est) == false);
        estaciones.Agregar(est);
    }

    void Mapa::Conectar(Estacion est1, Estacion est2, RestriccionTP& r) {
        assert(estaciones.Pertenece(est1) == true);
        assert(estaciones.Pertenece(est2) == true);
        assert(Conectadas(est1, est2) == false);
        Nodo aux(est1, est2, r);
        sendas.Agregar(aux);
    }

    Mapa::~Mapa() {
        // No hace falta borrar nada, no se hacen llamadas a new
    }

    Conj<Estacion>::const_Iterador Mapa::Estaciones() const {
        return estaciones.CrearIt();
    }

    bool Mapa::Conectadas(Estacion est1, Estacion est2) const {
        #ifdef DEBUG
        assert(estaciones.Pertenece(est1) == true);
        assert(estaciones.Pertenece(est2) == true);
        #endif
        Conj<Nodo>::const_Iterador it = sendas.CrearIt();
        while (it.HaySiguiente()) {
            Nodo aux = it.Siguiente();
            if ((aux.est1 == est1 && aux.est2 == est2) ||
                (aux.est1 == est2 && aux.est2 == est1)) {
                return true;
            }
            it.Avanzar();
        }
        return false;
    }

    RestriccionTP& Mapa::Rest(Estacion est1, Estacion est2) const {
        #ifdef DEBUG
        assert(estaciones.Pertenece(est1) == true);
        assert(estaciones.Pertenece(est2) == true);
        //assert(Conectadas(est1, est2) == true);
        #endif
        Conj<Nodo>::const_Iterador it = sendas.CrearIt();
        while (it.HaySiguiente()) {
            Nodo aux = it.Siguiente();
            if ((aux.est1 == est1 && aux.est2 == est2) ||
                (aux.est1 == est2 && aux.est2 == est1)) {
                return aux.rest;
            }
            it.Avanzar();
        }
    }
}
#endif
