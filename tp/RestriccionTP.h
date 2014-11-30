#ifndef RESTRICCION_TP_H_INCLUDED
#define RESTRICCION_TP_H_INCLUDED

#include "../aed2.h"
#include "ConjRapido.h"
#include "ArbolBinario.h"

namespace tp {

    class RestriccionTP {
        public:

            /**
             * Crea una restriccion para el tag dado.
             */
            RestriccionTP(const Caracteristica& tag);

            /**
             * Devuelve true si los tags cumplen con la restriccion.
             */
            bool Verifica(const ConjRapido& tags) const;

            /**
             * Destructor.
             */
            ~RestriccionTP();

            //bool operator == (const RestriccionTP& otro) const;

            /**
             * Une las dos restricciones usan un operador AND.
             */
            static RestriccionTP& And(const RestriccionTP& r1, const RestriccionTP& r2) {
                RestriccionTP* rest = new RestriccionTP();
                String* str_and = new String("AND");
                ArbolBinario<String>* aux = new ArbolBinario<String>(*r1.arbol, *str_and, *r2.arbol);
                rest->arbol = aux;
                return *rest;
            }

            /**
             * Une las dos Restricciones usan un operador AND.
             */
            static RestriccionTP& Or(const RestriccionTP& r1, const RestriccionTP& r2) {
                RestriccionTP* rest = new RestriccionTP();
                String* str_or = new String("OR");
                ArbolBinario<String>* aux = new ArbolBinario<String>(*r1.arbol, *str_or, *r2.arbol);
                rest->arbol = aux;
                return *rest;
            }

            /**
             * Une las dos restricciones usan un operador AND.
             */
            static RestriccionTP& Not(const RestriccionTP& r1) {
                ArbolBinario<String> der;
                RestriccionTP* rest = new RestriccionTP();
                String* str_not = new String("NOT");
                ArbolBinario<String>* aux = new ArbolBinario<String>(*r1.arbol, *str_not, der);
                rest->arbol = aux;
                return *rest;
            }

        private:
            ArbolBinario<String>* arbol;

            bool VerificaAux(const ArbolBinario<String>& arbol, const ConjRapido& tags) const;
            RestriccionTP();
    };

    bool operator == (const RestriccionTP& r1, const RestriccionTP& r2);

    RestriccionTP::RestriccionTP() : arbol(NULL) {}

    RestriccionTP::RestriccionTP(const Caracteristica& tag) {
        ArbolBinario<String> izq;
        ArbolBinario<String> der;
        ArbolBinario<String>* aux = new ArbolBinario<String>(izq, tag, der);
        arbol = aux;
    }

    bool RestriccionTP::Verifica(const ConjRapido& tags) const {
        return VerificaAux(*arbol, tags);
    }

    bool RestriccionTP::VerificaAux(const ArbolBinario<String>& arbol, const ConjRapido& tags) const {
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

    RestriccionTP::~RestriccionTP() {
        delete arbol;
    }

    /*bool RestriccionTP::operator == (const RestriccionTP& otro) const {
        return *(arbol) == *(otro.arbol);
    }*/

    bool operator == (const RestriccionTP& r1, const RestriccionTP& r2) {
        return true;
    }
}
#endif
