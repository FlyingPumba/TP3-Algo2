#ifndef ARBOL_BINARIO_H_INCLUDED
#define ARBOL_BINARIO_H_INCLUDED

#include "../aed2.h"

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
             * Operacion de asignacion.  Borra lo que se que habia en this y copia las referencias al otro.
             * El inicio de los dos arboles pasan a apuntar a la misma dirección de memoria.
             */
            ArbolBinario<T>& operator = (const ArbolBinario<T>& otro);

            /**
             * Destructor.
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
            const T& Raiz() const;

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
            ArbolBinario<T>* Padre() const;

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

            /**
             * Borra el sub-arbol izquierdo.
             * Requiere not Nil?(arbol) and not Nil?(Izq(arbol)) and Izq(arbol) es una hoja
             */
            void BorrarHojaIzq(ArbolBinario<T>& nil);

            /**
             * Borra el sub-arbol derecho.
             * Requiere not Nil?(arbol) and not Nil?(Der(arbol)) and Der(arbol) es una hoja
             */
            void BorrarHojaDer(ArbolBinario<T>& nil);

            /**
             * Agrega una hoja a la izquierda del arbol.
             * Requiere not Nil?(arbol) and Nil?(Izq(arbol)) and izq es una hoja
             */
            void AgregarHojaIzq(ArbolBinario<T>& izq);

            /**
             * Agrega una hoja a la derecha del arbol.
             * Requiere not Nil?(arbol) and Nil?(Der(arbol)) and der es una hoja
             */
            void AgregarHojaDer(ArbolBinario<T>& der);

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
                // NO copio los datos del padre al hijo y viceversa porque quiero que la dir conserve su valor inicial
                //const T* punteroAux = (*padre.inicio).dato;
                //(*padre.inicio).dato = (*hijo.inicio).dato;
                //(*hijo.inicio).dato = punteroAux;
                // cambio los padres
                (*hijo.inicio).padre = (*padre.inicio).padre;
                (*padre.inicio).padre = &hijo;
                // arreglo la altura
                padre.altura = padre.altura - 1;
                hijo.altura = hijo.altura + 1;
                // cambio los tamanhos
                Nat auxTamanho = padre.tamanho;
                padre.tamanho = hijo.tamanho;
                hijo.tamanho = auxTamanho;
                // arreglo los punteros
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
                // tengo que arreglar el enlace izq o der del padre del padre (sino dos subir fallan)
                if ((*hijo.inicio).padre != NULL) {
                    if (hijo.inicio->padre->inicio->izq == &padre) {
                        hijo.inicio->padre->inicio->izq = &hijo;

                    } else {
                        hijo.inicio->padre->inicio->der = &hijo;
                    }
                }
                //tengo que arreglar el padre del hijo del ex hijo (si un trabalenguas)
                if (!padre.Izq().EsNil()) {
                    padre.inicio->izq->inicio->padre = &padre;
                }
                if (!padre.Der().EsNil()) {
                    padre.inicio->der->inicio->padre = &padre;
                }
                if (!hijo.Izq().EsNil()) {
                    hijo.inicio->izq->inicio->padre = &hijo;
                }
                if (!hijo.Der().EsNil()) {
                    hijo.inicio->der->inicio->padre = &hijo;
                }

            }
            static void CambiarPimeroPorUltimo(ArbolBinario<T>& prim, ArbolBinario<T>& ult) {
                assert(prim.EsNil() != true);
                assert(ult.EsNil() != true);
                // cambio los padres
                (*prim.inicio).padre = (*ult.inicio).padre;
                (*ult.inicio).padre = NULL;
                // cambio las alturas
                Nat auxAltura = prim.altura;
                prim.altura = ult.altura;
                ult.altura = auxAltura;
                // cambio los tamanhos
                Nat auxTamanho = prim.tamanho;
                prim.tamanho = ult.tamanho;
                ult.tamanho = auxTamanho;
                // arreglo la izquierda
                ArbolBinario<T>* aux1 = (*prim.inicio).izq;
                (*prim.inicio).izq = (*ult.inicio).izq;
                (*ult.inicio).izq = aux1;
                // arreglo la derecha
                ArbolBinario<T>* aux2 = (*prim.inicio).der;
                (*prim.inicio).der = (*ult.inicio).der;
                (*ult.inicio).der = aux2;
                //tengo que arreglar el padre del hijo del de (ahora) prim
                if (!ult.Izq().EsNil()) {
                    ult.inicio->izq->inicio->padre = &ult;
                }
                if (!ult.Der().EsNil()) {
                    ult.inicio->der->inicio->padre = &ult;
                }
                // tengo que arreglar la izq y la der de izq y lo mismo con der
                if (!ult.Izq().EsNil()){
                    if (ult.inicio->izq->inicio->izq == &ult) {
                        ult.inicio->izq->inicio->izq = &prim;
                    }
                    if (ult.inicio->izq->inicio->der == &ult) {
                        ult.inicio->izq->inicio->der = &prim;
                    }
                }
                if (!ult.Der().EsNil()){
                    if (ult.inicio->der->inicio->izq == &ult) {
                        ult.inicio->der->inicio->izq = &prim;
                    }
                    if (ult.inicio->der->inicio->der == &ult) {
                        ult.inicio->der->inicio->der = &prim;
                    }
                }
            }

        private:
            struct Nodo
            {
                Nodo(ArbolBinario<T>& i, const T& v, ArbolBinario<T>& d, ArbolBinario<T>* p) : dato(&v), izq(&i), der(&d), padre(p) {};
                Nodo(ArbolBinario<T>& i, const T& v, ArbolBinario<T>& d) : dato(&v), izq(&i), der(&d), padre(NULL){};

                const T* dato;
                ArbolBinario<T>* izq;
                ArbolBinario<T>* der;
                ArbolBinario<T>* padre;
            };

            Nodo* inicio;
            Nat altura;
            Nat tamanho;

            void Destruir();
            void Asignar(const ArbolBinario<T>& otro);

    };

    template<class T>
    std::ostream& operator<<(std::ostream& os, const ArbolBinario<T>&);

    template<class T>
    bool operator==(const ArbolBinario<T>& a, const ArbolBinario<T>& b);

    template <class T>
    ArbolBinario<T>::ArbolBinario() : inicio(NULL), altura(0), tamanho(0) {}

    template<class T>
    ArbolBinario<T>::ArbolBinario(ArbolBinario<T>& izq, const T& raiz, ArbolBinario<T>& der) {
        inicio = new Nodo(izq, raiz, der);
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
    ArbolBinario<T>& ArbolBinario<T>::operator=(const ArbolBinario<T>& otro) {
        if(this != &otro) {
            Destruir();
            Asignar(otro);
        }
        return *this;
    }

    template<class T>
    ArbolBinario<T>::~ArbolBinario() {
        Destruir();
    }

    template<class T>
    bool ArbolBinario<T>::EsNil() const {
        return inicio == NULL;
    }

    template<class T>
    ArbolBinario<T>& ArbolBinario<T>::Izq() const {
        assert(inicio != NULL);
        return *(inicio->izq);
    }

    template<class T>
    ArbolBinario<T>& ArbolBinario<T>::Der() const {
        assert(inicio != NULL);
        return *(inicio->der);
    }

    template<class T>
    const T& ArbolBinario<T>::Raiz() const {
        assert(inicio != NULL);
        assert((*inicio).dato != NULL);
        return *(inicio->dato);
    }

    template<class T>
    ArbolBinario<T>* ArbolBinario<T>::Padre() const {
        assert(inicio != NULL);
        return inicio->padre;
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
        (*inicio).dato = &raiz;
    }

    template<class T>
    void ArbolBinario<T>::Destruir() {
        if (!(this->EsNil())) {
            this->inicio->padre = NULL;
            delete (this->inicio);
        }
    }

    template<class T>
    void ArbolBinario<T>::Asignar(const ArbolBinario<T>& otro) {
        if (otro.EsNil()) {
            tamanho = 0;
            altura = 0;
            inicio = NULL;
        } else {
            // TODO
        }
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const ArbolBinario<T>& arbol) {
        if (!arbol.EsNil()) {
            if (!arbol.Izq().EsNil()) {
                os << arbol.Izq() << " ";
            }
            os << "-" << arbol.Raiz() << "-";
            if (!arbol.Der().EsNil()) {
                os << arbol.Der() << " ";
            }
        }
        return os;
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

    template<class T>
    void ArbolBinario<T>::BorrarHojaIzq(ArbolBinario<T>& nil) {
        assert(this->EsNil() != true);
        assert(nil.EsNil() == true);
        assert(this->Izq().EsNil() != true);
        assert(this->Izq().Izq().EsNil() == true && this->Izq().Der().EsNil() == true);
        this->inicio->izq = &nil;
       // nil.inicio->padre = this;
        this->tamanho = this->tamanho - 1;
        if (this->inicio->der->EsNil()) {
            this->altura = this->altura - 1;
        }
        ArbolBinario<T>* aux = this->inicio->padre;
        while (aux != NULL) {
            ArbolBinario<T>* lado;
            if (aux->inicio->izq == this) {
                lado = aux->inicio->der;
            } else {
                lado = aux->inicio->izq;
            }
            if (lado->EsNil() != true) {
                if (this->altura > lado->altura) {
                    aux->altura = 1 + this->altura;
                } else {
                    aux->altura = 1 + lado->altura;
                }
            }
            aux->tamanho = aux->tamanho - 1;
            aux = aux->inicio->padre;
        }
    }

    template<class T>
    void ArbolBinario<T>::BorrarHojaDer(ArbolBinario<T>& nil) {
        assert(this->EsNil() != true);
        assert(nil.EsNil() == true);
        assert(this->Der().EsNil() != true);
        assert(this->Der().Izq().EsNil() == true && this->Der().Der().EsNil() == true);
        this->inicio->der = &nil;
      //  nil.inicio->padre = this;
        this->tamanho = this->tamanho - 1;
        if (this->inicio->izq->EsNil()) {
            this->altura = this->altura - 1;
        }
        ArbolBinario<T>* aux = this->inicio->padre;
        while (aux != NULL) {
            ArbolBinario<T>* lado;
            if (aux->inicio->izq == this) {
                lado = aux->inicio->der;
            } else {
                lado = aux->inicio->izq;
            }
            if (lado->EsNil() != true) {
                if (this->altura > lado->altura) {
                    aux->altura = 1 + this->altura;
                } else {
                    aux->altura = 1 + lado->altura;
                }
            }
            aux->tamanho = aux->tamanho - 1;
            aux = aux->inicio->padre;
        }
    }

    template<class T>
    void ArbolBinario<T>::AgregarHojaIzq(ArbolBinario<T>& izq) {
        assert(this->EsNil() != true);
        assert(this->Izq().EsNil() == true);
        assert(izq.Izq().EsNil() == true && izq.Der().EsNil() == true);
        this->inicio->izq = &izq;
        izq.inicio->padre = this;
        this->tamanho = this->tamanho + 1;
        if (this->inicio->der->EsNil()) {
            this->altura = this->altura + 1;
        }
        ArbolBinario<T>* aux = this->inicio->padre;
        while (aux != NULL) {
            ArbolBinario<T>* lado;
            if (aux->inicio->izq == this) {
                lado = aux->inicio->der;
            } else {
                lado = aux->inicio->izq;
            }
            if (lado->EsNil() != true) {
                if (this->altura > lado->altura) {
                    aux->altura = 1 + this->altura;
                } else {
                    aux->altura = 1 + lado->altura;
                }
            }
            aux->tamanho = aux->tamanho + 1;
            aux = aux->inicio->padre;
        }
    }

    template<class T>
    void ArbolBinario<T>::AgregarHojaDer(ArbolBinario<T>& der) {
        assert(this->EsNil() != true);
        assert(this->Der().EsNil() == true);
        assert(der.Izq().EsNil() == true && der.Der().EsNil() == true);
        this->inicio->der = &der;
        der.inicio->padre = this;
        this->tamanho = this->tamanho + 1;
        if (this->inicio->izq->EsNil()) {
            this->altura = this->altura + 1;
        }
        ArbolBinario<T>* aux = this->inicio->padre;
        while (aux != NULL) {
            ArbolBinario<T>* lado;
            if (aux->inicio->izq == this) {
                lado = aux->inicio->der;
            } else {
                lado = aux->inicio->izq;
            }
            if (lado->EsNil() != true) {
                if (this->altura > lado->altura) {
                    aux->altura = 1 + this->altura;
                } else {
                    aux->altura = 1 + lado->altura;
                }
            }
            aux->tamanho = aux->tamanho + 1;
            aux = aux->inicio->padre;
        }
    }
}
#endif
