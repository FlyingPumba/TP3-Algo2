
#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "aed2.h"

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
            void Agregar(String est);

            /**
             * Conecta dos estaciones del mapa.
             */
            void Conectar(String est1, String est2, Restriccion& r);

            /**
             * Destructor.
             */
            ~Mapa();

            /**
             * Devuelve las estaciones del mapa.
             */
            Conj<String>::const_Iterador Estaciones() const;

            /**
             * Devuelve true si las estaciones estan conectadas.
             * Requiere: est1 y est2 pertenecen a las estaciones del mapa.
             */
            bool EstanConectadas(String est1, String est2);

            /**
             * Devuelve la restriccion de la senda que una las estaciones.
             * Requiere: est1 y est2 pertenecen a las estaciones del mapa, y ademas estan conectadas.
             */
            Restriccion& Restriccion(String est1, String est2) const;

        private:
            struct Nodo {
                Nodo(const String est1, const String est1, const Restriccion* r) : est1(est1), est2(est2), rest(r) {};

                String est1;
                String est2;
                Restriccion* rest;
            };

            Conj<String> estaciones;
            Conj<Nodo> sendas;

    };

    std::ostream& operator<<(std::ostream& os, const Arreglo<T>&);

    Mapa<T>::Mapa() {}

    void Mapa::Agregar(String est) {
        assert(estaciones.Pertenece(est) == false);
        estaciones.AgregarRapido(est);
    }

    void Mapa::Conectar(String est1, String est2, Restriccion& r) {
        assert(estaciones.Pertenece(est1) == true);
        assert(estaciones.Pertenece(est2) == true);
        Nodo aux(est1, est2, &r);
        sendas.AgregarRapido(aux);
    }

    ~Mapa() {
        // TODO
    }

    Conj<String>::const_Iterador Mapa::Estaciones() const {
        return estaciones.CrearIt();
    }

    bool Mapa::EstanConectadas() {
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

    Restriccion& Mapa::Restriccion(String est1, String est2) const {
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