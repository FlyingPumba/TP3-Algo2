
#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "../aed2.h"

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
            void Conectar(Estacion est1, Estacion est2, Restriccion r);

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
            bool EstanConectadas(Estacion est1, Estacion est2);

            /**
             * Devuelve la restriccion de la senda que una las estaciones.
             * Requiere: est1 y est2 pertenecen a las estaciones del mapa, y ademas estan conectadas.
             */
            Restriccion Rest(Estacion est1, Estacion est2) const;

        private:
            struct Nodo {
                Nodo(const Estacion est1, const Estacion est2, const Restriccion r) : est1(est1), est2(est2), rest(r) {};

                Estacion est1;
                Estacion est2;
                Restriccion rest;

                bool Nodo::operator == (const typename Nodo otro) const
                {
                  return est1 == otro.est1 && est2 == oto.est2 && rest = otro.rest;
                }
            };

            Conj<Estacion> estaciones;
            Conj<Nodo> sendas;

    };

    std::ostream& operator<<(std::ostream& os, const Mapa&);

    Mapa::Mapa() {}

    void Mapa::Agregar(Estacion est) {
        assert(estaciones.Pertenece(est) == false);
        estaciones.AgregarRapido(est);
    }

    void Mapa::Conectar(Estacion est1, Estacion est2, Restriccion r) {
        assert(estaciones.Pertenece(est1) == true);
        assert(estaciones.Pertenece(est2) == true);
        assert(EstanConectadas(est1, est2) == false);
        Nodo aux(est1, est2, r);
        sendas.AgregarRapido(aux);
    }

    ~Mapa() {
        // TODO
    }

    Conj<Estacion>::const_Iterador Mapa::Estaciones() const {
        return estaciones.CrearIt();
    }

    bool Mapa::EstanConectadas(Estacion est1, Estacion est2) {
        Conj<Nodo>::const_Iterador it = sendas.CrearIt();
        while (it.HaySiguiente()) {
            Nodo aux = it.Siguiente();
            if ((aux.est1 == est1 && aux.est2 == est2) || 
                (aux.est1 == est2 && aux.est2 == est1)) {
                return true;
            }
        }
        return false;
    }

    Restriccion Mapa::Rest(Estacion est1, Estacion est2) const {
        Conj<Nodo>::const_Iterador it = sendas.CrearIt();
        while (it.HaySiguiente()) {
            Nodo aux = it.Siguiente();
            if ((aux.est1 == est1 && aux.est2 == est2) || 
                (aux.est1 == est2 && aux.est2 == est1)) {
                return aux.rest;
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const Mapa& a) {
        os << "[";
        return os << "]";
    }
}
#endif