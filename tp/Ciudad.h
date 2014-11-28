#ifndef CIUDAD_H_INCLUDED
#define CIUDAD_H_INCLUDED

#include "../aed2.h"
#include "DiccRapido.h"
#include "ConjRapido.h"
//#include "ColaPrioridad.h"

namespace tp {

    class Ciudad {
        public:

            /**
             * Genera una ciudad nueva
             */
            Ciudad(const Mapa mapa);

            /**
             * Agrega un robot a la ciudad. La estacion actual del robot es la estacion pasada por parametro.
             * Requiere: est in estaciones(c)
             */
            Entrar(const ConjRapido& tags, const Estacion est);

            /**
             * Mueve el robot dado de su estacion actual a la estacion de destino. 
             * Sí el robot comete una infraccion, la cantidad de sus infracciones aumenta en 1.
             * Requiere: est in estaciones(c)
             */
            Mover(const RUR rur, const Estacion est);

            /**
             * Saca de circulacion el robot con mayor cantidad de infracciones en la estacion dada, desempatando por RUR.
             * Requiere: est in estaciones(c)
             */
            Inspeccion(const Estacion est);

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
            const Mapa Mapa() const;

            /**
             * Devuelve un iterador a los robots de la ciudad.
             */
            const itCiudad Robots() const;

            /**
             * Devuelve la estacion actual del robot.
             * Requiere: r in robots(c)
             */
            const Estacion Estacion(const RUR r) const;

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
            Nat cantEsts;
    };

    std::ostream& operator<<(std::ostream& os, const Ciudad&);

    Ciudad::Ciudad(Mapa mapa) : size(tamanio) {

    }

    Ciudad::~Ciudad() {
        // TODO
    }

    std::ostream& operator<<(std::ostream& os, const Ciudad& c) {
        os << "[";
        return os << "]";
    }
}
#endif