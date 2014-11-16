
#ifndef ARBOL_BINARIO_H_INCLUDED
#define ARBOL_BINARIO_H_INCLUDED

#include "TiposBasicos.h"

namespace tp {

    template<class T>
    class ArbolBinario{
        public:

            /**
             * Crea un ArbolBinario vacio (nil).
             */
            ArbolBinario();

            /**
             * Crea un ArbolBinario dados 2 sub-arboles (izquierdo y derecho) y una raiz.
             */
            ArbolBinario(ArbolBinario<T>& izq, raiz T, ArbolBinario<T>& der);

            /**
             * Constructor por copia.
             */
            ArbolBinario(const ArbolBinario<T>& otro);

            /**
             * Destructor.  Borra lo que hubiera en el ArbolBinario.
             */
            ~ArbolBinario();

            /**
             * Devuelve true si el arbol es nil.
             */
            bool EsNil() const;

            /**
             * Devuelve la raiz del arbol.
             * Requiere: not Nil?(arbol)
             */
            T Raiz() const;

            /**
             * Devuelve el sub-arbol izquierdo.
             * Requiere: not Nil?(arbol)
             */
            ArbolBinario<T>& Izq() const;

            /**
             * Devuelve el sub-arbol derecho.
             * Requiere: not Nil?(arbol)
             */
            ArbolBinario<T>& Der() const;

            /**
             * Devuelve el arbol padre.
             * Requiere: not Nil?(arbol)
             */
            ArbolBinario<T>& Padre() const;

            /**
             * Intercambia la raiz entre los arboles.
             * Requiere not Nil?(padre) and not Nil?(hijo) and 
             *      (Izq(padre) == hijo or Der(padre) == hijo)
             */
            Swap(ArbolBinario<T>& padre, ArbolBinario<T>& hijo);

            /**
             * Borra el sub-arbol izquierdo.
             * Requiere not Nil?(arbol) and not Nil?(Izq(arbol)) and Izq(arbol) es una hoja
             */
            BorrarHojaIzq(ArbolBinario<T>& arbol);

            /**
             * Borra el sub-arbol derecho.
             * Requiere not Nil?(arbol) and not Nil?(Der(arbol)) and Der(arbol) es una hoja
             */
            BorrarHojaDer(ArbolBinario<T>& arbol);

            /**
             * Agrega una hoja a la izquierda del arbol.
             * Requiere not Nil?(arbol) and Nil?(Izq(arbol)) and izq es una hoja
             */
            AgregarHojaIzq(ArbolBinario<T>& arbol, ArbolBinario<T>& izq);

            /**
             * Agrega una hoja a la derecha del arbol.
             * Requiere not Nil?(arbol) and Nil?(Der(arbol)) and der es una hoja
             */
            AgregarHojaDer(ArbolBinario<T>& arbol, ArbolBinario<T>& der);

            /**
             * Modifica la raiz del arbol.
             * Requiere not Nil?(arbol)
             */
            CambiarRaiz(ArbolBinario<T>& arbol, T raiz);

            /**
             * Devuelve la cantidad de nodos del arbol.
             */
            Nat Tamanho() const;

            /**
             * Devuelve la altura del arbol.
             */
            Nat Altura() const;

        private:
            struct Nodo
            {
                Nodo(const T& v) : dato(v), izq(NULL), der(NULL), padre(NULL) {}
                T valor;
                Nodo* izq;
                Nodo* der;
                Nodo* padre; 
            };

            Nodo* inicio;
            Nat altura;
            Nat tamanho;

    };

    template<class T>
    std::ostream& operator<<(std::ostream& os, const ArbolBinario<T>&);

    template <class T>
    ArbolBinario<T>::ArbolBinario() : inicio(NULL), altura(0), tamanho(0) {}

    template<class T>
    ArbolBinario<T>::ArbolBinario(ArbolBinario<T>& izq, T raiz, ArbolBinario<T>& der) {
        this.inicio = new Nodo(raiz, izq, der, NULL);
        if (izq != NULL) {
            (izq->inicio)->padre = this;
        }
        if (der != NULL) {
            (der->inicio)->padre = this;
        }
        this.tamanho = 1 + Tamanho(izq) + Tamanho(der);
        if (Altura(izq) < Altura(der)) {
            this.altura = 1 + Altura(der);
        } else {
            this.altura = 1 + Altura(izq);
        }
    }

    template<class T>
    ArbolBinario<T>::ArbolBinario(const ArbolBinario<T>& otro) {
        // TODO
    }

    template<class T>
    ArbolBinario<T>::~ArbolBinario() {
        // TODO
    }

    template<class T>
    bool ArbolBinario<T>::EsNil() const {
        return inicio == NULL;
    }

    template<class T>
    Nat ArbolBinario<T>::Tamanho() const {
        return tamanho;
    }

    template<class T>
    Nat ArbolBinario<T>::Altura() const {
        return altura;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const ArbolBinario<T>& arbol) {
        os << "[";
        return os << "]";
    }
}
#endif