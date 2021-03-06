
#ifndef CONJ_RAPIDO_H_INCLUDED
#define CONJ_RAPIDO_H_INCLUDED

#include "../aed2.h"
#include "DiccRapido.h"

namespace tp {

    class ConjRapido {
        public:

            // forward declaration
            class const_Iterador;

            /**
             * Crea un conjunto vacio.
             */
            ConjRapido();

            /**
             * Agrega un elemento al conjunto.
             */
            void Agregar(const String& elem);

            /**
             * Destructor
             */
            ~ConjRapido();

            /**
             * Devuelve true si el elemento pertenece al conjunto.
             */
            bool Pertenece(const String& elem) const;

            /**
             * Devuelve true si el conjunto esta vacio.
             */
            bool EsVacio() const;

            /**
             * Devuelve la cantidad de elementos del conjunto.
             */
            Nat Cardinal() const;

            /**
             * Devuelve un iterador para el conjunto.
             */
            const_Iterador CrearIt() const;

            class const_Iterador
            {
                public:

                    const_Iterador();

                    /**
                     * Devuelve true si quedan elementos por iterar.
                     */
                    bool HaySiguiente() const;

                    /**
                     * Devuelve la clave del elemento al que apunta el iterador.
                     */
                    const String Siguiente() const;

                    /**
                     * Avanza el iterador al siguiente elemento.
                     */
                    void Avanzar();

                private:

                    DiccRapido<bool>::const_Iterador it_dicc_;

                    const_Iterador(const ConjRapido* c);

                    friend ConjRapido::const_Iterador ConjRapido::CrearIt() const;
            };

        private:

            DiccRapido<bool> dicc;
            Nat size;

    };

    ConjRapido::ConjRapido() : size(0) {}

    void ConjRapido::Agregar(const String& elem) {
        if (!dicc.Definido(elem)) {
            bool aux = true;
            dicc.Definir(elem, aux);
            size = size + 1;
        }
    }

    ConjRapido::~ConjRapido() {
        // Solo hace falta que se destruya el diccionario, y lo hace el compilador
    }

    bool ConjRapido::Pertenece(const String& elem) const {
         return dicc.Definido(elem);
    }

    bool ConjRapido::EsVacio() const {
         return size == 0;
    }

    Nat ConjRapido::Cardinal() const {
        return size;
    }

    ConjRapido::const_Iterador ConjRapido::CrearIt() const {
        return const_Iterador(this);
    }

    // Implementacion const_Iterador:

    ConjRapido::const_Iterador::const_Iterador(const ConjRapido* c)
      : it_dicc_(c->dicc.CrearIt()) {}

    bool ConjRapido::const_Iterador::HaySiguiente() const {
      return it_dicc_.HaySiguiente();
    }

    const String ConjRapido::const_Iterador::Siguiente() const {
      #ifdef DEBUG
      assert(HaySiguiente());
      #endif

      return it_dicc_.SiguienteClave();
    }

    void ConjRapido::const_Iterador::Avanzar() {
      #ifdef DEBUG
      assert(HaySiguiente());
      #endif

      it_dicc_.Avanzar();
    }
}
#endif
