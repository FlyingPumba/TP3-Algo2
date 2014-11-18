
#ifndef ARBOL_BINARIO_H_INCLUDED
#define ARBOL_BINARIO_H_INCLUDED

#include "aed2.h"

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
            ArbolBinario(ArbolBinario<T>& izq, const T& raiz, ArbolBinario<T>& der);

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
             * Modifica la raiz del arbol.
             * Requiere not Nil?(arbol)
             */
            void CambiarRaiz(const T& raiz);

            /**
             * Devuelve la cantidad de nodos del arbol.
             */
            Nat Tamanho() const;

            /**
             * Devuelve la altura del arbol.
             */
            Nat Altura() const;

            // Metodos estaticos:

            /**
             * Intercambia la raiz entre los arboles.
             * Requiere not Nil?(padre) and not Nil?(hijo) and
             *      (Izq(padre) == hijo or Der(padre) == hijo)
             */
            static void Swap(ArbolBinario<T>& padre, ArbolBinario<T>& hijo) {
                assert(padre.EsNil() != true);
                assert(hijo.EsNil() != true);
                assert(padre.Izq() == hijo || padre.Der() == hijo);
                // copio los datos del padre al hijo y viceversa
                T datoPadre = (*padre.inicio).dato;
                T datoHijo = (*hijo.inicio).dato;
                padre.CambiarRaiz(datoHijo);
                hijo.CambiarRaiz(datoPadre);
                // arreglo los punteros
                // TODO y los padres ??
                if (padre.Der() == hijo) {
                    (*padre.inicio).der = (*hijo.inicio).der;
                    (*hijo.inicio).der = &padre;
                    ArbolBinario<T>* aux = (*padre.inicio).izq;
                    (*padre.inicio).izq = (*hijo.inicio).izq;
                    (*hijo.inicio).izq = aux;
                } else {
                    (*padre.inicio).izq = (*hijo.inicio).izq;
                    (*hijo.inicio).izq = &padre;
                    ArbolBinario<T>* aux = (*padre.inicio).der;
                    (*padre.inicio).der = (*hijo.inicio).der;
                    (*hijo.inicio).der = aux;
                }
            }
            
            /**
             * Borra el sub-arbol izquierdo.
             * Requiere not Nil?(arbol) and not Nil?(Izq(arbol)) and Izq(arbol) es una hoja
             */
            static void BorrarHojaIzq(ArbolBinario<T>& arbol) {

            }
            
            /**
             * Borra el sub-arbol derecho.
             * Requiere not Nil?(arbol) and not Nil?(Der(arbol)) and Der(arbol) es una hoja
             */
            static void BorrarHojaDer(ArbolBinario<T>& arbol) {

            }
            
            /**
             * Agrega una hoja a la izquierda del arbol.
             * Requiere not Nil?(arbol) and Nil?(Izq(arbol)) and izq es una hoja
             */
            static void AgregarHojaIzq(ArbolBinario<T>& arbol, ArbolBinario<T>& izq) {

            }
            
            /**
             * Agrega una hoja a la derecha del arbol.
             * Requiere not Nil?(arbol) and Nil?(Der(arbol)) and der es una hoja
             */
            static void AgregarHojaDer(ArbolBinario<T>& arbol, ArbolBinario<T>& der) {

            }

        private:
            struct Nodo
            {
                Nodo(ArbolBinario<T>* i, const T& v, ArbolBinario<T>* d, ArbolBinario<T>* p) : dato(v), izq(i), der(d), padre(p) {};
                Nodo(ArbolBinario<T>* i, const T& v, ArbolBinario<T>* d) : dato(v), izq(i), der(d), padre(NULL){};
                Nodo(const T& v) : dato(v), izq(NULL), der(NULL), padre(NULL) {};

                T dato;
                ArbolBinario<T>* izq;
                ArbolBinario<T>* der;
                ArbolBinario<T>* padre;
            };

            Nodo* inicio;
            Nat altura;
            Nat tamanho;

    };

    template<class T>
    std::ostream& operator<<(std::ostream& os, const ArbolBinario<T>&);

    template<class T>
    bool operator==(const ArbolBinario<T>& a, const ArbolBinario<T>& b);

    template <class T>
    ArbolBinario<T>::ArbolBinario() : inicio(NULL), altura(0), tamanho(0) {}

    template<class T>
    ArbolBinario<T>::ArbolBinario(ArbolBinario<T>& izq, const T& raiz, ArbolBinario<T>& der) {
        inicio = new Nodo(&izq, raiz, &der);
        if (izq.inicio != NULL) {
            (*izq.inicio).padre = this;
        }
        if (der.inicio != NULL) {
            (*der.inicio).padre = this;
        }
        tamanho = 1 + izq.Tamanho() + der.Tamanho();
        if (izq.Altura() < der.Altura()) {
            altura = 1 + der.Altura();
        } else {
            altura = 1 + izq.Altura();
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
    ArbolBinario<T>& ArbolBinario<T>::Izq() const {
        assert(inicio != NULL);
        return *(*inicio).izq;
    }

    template<class T>
    ArbolBinario<T>& ArbolBinario<T>::Der() const {
        assert(inicio != NULL);
        return *(*inicio).der;
    }

    template<class T>
    T ArbolBinario<T>::Raiz() const {
        assert(inicio != NULL);
        return (*inicio).dato;
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
    void ArbolBinario<T>::CambiarRaiz(const T& raiz) {
        assert(inicio != NULL);
        (*inicio).dato = raiz;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const ArbolBinario<T>& arbol) {
        os << "[";
        return os << "]";
    }

    template<class T>
    bool operator==(const ArbolBinario<T>& a, const ArbolBinario<T>& b) {
        if (a.EsNil()) {
            return b.EsNil();
        } else if (b.EsNil()) {
            return false;
        } else if (a.Raiz() == b.Raiz()) {
            return a.Izq() == b.Izq() && a.Der() == b.Der();
        } else {
            return false;
        }
    }
}
#endif
