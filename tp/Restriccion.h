#ifndef RESTRICCION_H_INCLUDED
#define RESTRICCION_H_INCLUDED

#include "../aed2.h"
#include "ConjRapido.h"
#include "ArbolBinario.h"

namespace tp {

    class Restriccion {
        public:

            /**
             * Crea una restriccion para el tag dado.
             */
            Restriccion(const Caracteristica& tag);

            /**
             * Devuelve true si los tags cumplen con la restriccion.
             */
            bool Verifica(const ConjRapido& tags) const;

            /**
             * Destructor.
             */
            ~Restriccion();

            /**
             * Une las dos restricciones usan un operador AND.
             */
            static Restriccion& And(const Restriccion& r1, const Restriccion& r2) {
                Restriccion* rest = new Restriccion();
                String* str_and = new String("AND");
                ArbolBinario<String>* aux = new ArbolBinario<String>(*r1.arbol, *str_and, *r2.arbol);
                rest->arbol = aux;
                return *rest;
            }

            /**
             * Une las dos restricciones usan un operador AND.
             */
            static Restriccion& Or(const Restriccion& r1, const Restriccion& r2) {
                Restriccion* rest = new Restriccion();
                String* str_or = new String("OR");
                ArbolBinario<String>* aux = new ArbolBinario<String>(*r1.arbol, *str_or, *r2.arbol);
                rest->arbol = aux;
                return *rest;
            }

            /**
             * Une las dos restricciones usan un operador AND.
             */
            static Restriccion& Not(const Restriccion& r1) {
                ArbolBinario<String> der;
                Restriccion* rest = new Restriccion();
                String* str_not = new String("NOT");
                ArbolBinario<String>* aux = new ArbolBinario<String>(*r1.arbol, *str_not, der);
                rest->arbol = aux;
                return *rest;
            }

        private:
            ArbolBinario<String>* arbol;

            bool VerificaAux(const ArbolBinario<String>& arbol, const ConjRapido& tags) const;
            Restriccion();
    };

    Restriccion::Restriccion() : arbol(NULL) {}

    Restriccion::Restriccion(const Caracteristica& tag) {
        ArbolBinario<String> izq;
        ArbolBinario<String> der;
        ArbolBinario<String>* aux = new ArbolBinario<String>(izq, tag, der);
        arbol = aux;
    }

    bool Restriccion::Verifica(const ConjRapido& tags) const {
        return VerificaAux(*arbol, tags);
    }

    bool Restriccion::VerificaAux(const ArbolBinario<String>& arbol, const ConjRapido& tags) const {
        if (arbol.Raiz() == "AND") {
            return VerificaAux(arbol.Izq(), tags) && VerificaAux(arbol.Der(), tags);
        } else if (arbol.Raiz() == "OR") {
            return VerificaAux(arbol.Izq(), tags) || VerificaAux(arbol.Der(), tags);
        } else if (arbol.Raiz() == "NOT") {
            if (!arbol.Izq().EsNil()) {
                return !VerificaAux(arbol.Izq(), tags);
            } else {
                return !VerificaAux(arbol.Izq(), tags);
            }
        } else {
            return tags.Pertenece(arbol.Raiz());
        }
    }

    Restriccion::~Restriccion() {
        delete arbol;
    }
}
#endif
