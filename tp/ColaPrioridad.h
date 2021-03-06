#ifndef COLA_PRIORIDAD_H_INCLUDED
#define COLA_PRIORIDAD_H_INCLUDED

#include "../aed2.h"
#include "ArbolBinario.h"
#include "math.h"

namespace tp {

    template<class T>
    class ColaPrioridad {
        public:

            // forward declaration
            class Iterador;

            /**
             * Crea una Cola de Prioridad.
             */
            ColaPrioridad();

            /**
             * Encola un elemento a la Cola de Prioridad.
             */
             ColaPrioridad<T>::Iterador* Encolar(const T& elem);

            /**
             * Destructor.  Borra lo que hubiera en el ColaPrioridad.
             */
            ~ColaPrioridad();

            /**
             * Devuelve true si la Cola de Prioridad esta vacia.
             */
            bool EsVacia() const;

            /**
             * Devuelve el proximo de la Cola de Prioridad.
             * Requiere: not vacia?(colaPrior)
             */
            const T& Proximo() const;

            /**
             * Modifica la cola dada, desencolando al elemento de mayor prioridad
             * Requiere: not vacia?(colaPrior)
             */

            void Desencolar();

            class Iterador
            {
                public:

                    Iterador(ColaPrioridad<T>* co, ArbolBinario<T>* sub){
                        this->cola = co;
                        this->subCola = sub;
                    }

                    /**
                     * Devuelve true si el iterador apunta a un nodo valido.
                     */
                     bool HaySiguiente() const{
                         if (this->subCola->EsNil()){
                             return false;
                         }else{
                             return true;
                         }

                     }

                    /**
                     * Devuelve el alpha apuntado por el iterador.
                     * Requiere: haysiguiente?(it)
                     */
                    const T& Siguiente() const{
                        #ifdef DEBUG
                        assert(this->subCola->EsNil() == false);
                        #endif
                        return this->subCola->Raiz();
                    }

                    /**
                     * Desencola la subcola del iterador sin alterar el resto de la cola.
                     * Requiere: haysiguiente?(it)
                     */
                    void BorrarSiguiente();

                    ~Iterador() {
                        cola = NULL;
                        subCola = NULL;
                    }

                private:
                    ColaPrioridad<T>* cola;
                    ArbolBinario<T>* subCola;
            };


        private:
            /**
             * Sube un nodo hasta donde corresponda
             * Requiere: ulti deberia ser el ultimo nodo
             */
            void SubirUltimoNodo(ArbolBinario<T>* ulti);

            /**
             * Baja un nodo hasta donde corresponda
             * Requiere: prim deberia ser el primer nodo del arbol
             */
            void BajarPrimerNodo(ArbolBinario<T>& prim);

            Arreglo<int> CaminoParaInsertarNuevoNodo(ArbolBinario<T>& c);

            Arreglo<int> CaminoParaBorrarUltimoNodo(ArbolBinario<T>& c);

            ColaPrioridad(ArbolBinario<T>* a) : arbol(a) {};

            ArbolBinario<T>* arbol;
            Lista<Iterador*> iteradores;

            friend void Iterador::BorrarSiguiente();

    };

    template<class T>
    bool operator==(const ColaPrioridad<T>&, const ColaPrioridad<T>&);

    template<class T>
    std::ostream& operator<<(std::ostream& os, const ColaPrioridad<T>&);

    template<class T>
    ColaPrioridad<T>::ColaPrioridad() : arbol(new ArbolBinario<T>()) { }

    template<class T>
    ColaPrioridad<T>::~ColaPrioridad() {
        while (!this->EsVacia()) {
            ArbolBinario<T>* aux = arbol;
            Desencolar();
            if (EsVacia()) {
                //delete aux;
                break;
            }
        }

        typename Lista<Iterador*>::Iterador it = iteradores.CrearIt();
        while (it.HaySiguiente()) {
            Iterador* aux = it.Siguiente();
            delete aux;
            it.Avanzar();
        }

        delete (this->arbol);

    }

    template<class T>
    const T& ColaPrioridad<T>::Proximo() const {
        return this->arbol->Raiz();

    }

    template<class T>
    typename ColaPrioridad<T>::Iterador* ColaPrioridad<T>::Encolar(const T& elem) {
        if (this->EsVacia()) {
            ArbolBinario<T>* izq = new ArbolBinario<T>();
            ArbolBinario<T>* der = new ArbolBinario<T>();
            delete (this->arbol);
            this->arbol = new ArbolBinario<T>(*izq, elem, *der);
            ColaPrioridad<T>::Iterador* it = new Iterador(this, this->arbol);
            iteradores.AgregarAtras(it);
            return it;
        } else {

            Arreglo<int> camino = CaminoParaInsertarNuevoNodo(*this->arbol);
            int i = 0;
            ArbolBinario<T>* padre = this->arbol;
            while (i < camino.Tamanho() - 1) {
                if (camino[i] % 2 == 1) {
                    padre = &(padre->Der());
                } else {
                    padre = &(padre->Izq());
                }
                i++;
            }
            ArbolBinario<T>* izq = new ArbolBinario<T>();
            ArbolBinario<T>* der = new ArbolBinario<T>();
            ArbolBinario<T>* aux = new ArbolBinario<T>(*izq, elem, *der);

            if (camino[i] % 2 == 1) {
                ArbolBinario<T>* aux1 = &(padre->Der());
                padre->AgregarHojaDer(*aux);
                delete aux1;
                SubirUltimoNodo(aux);

            } else {
                ArbolBinario<T>* aux1 = &(padre->Izq());
                padre->AgregarHojaIzq(*aux);
                delete aux1;
                SubirUltimoNodo(aux);
            }
            ColaPrioridad<T>::Iterador* it = new Iterador(this, aux);
            iteradores.AgregarAtras(it);
            return it;
        }
    }

    template<class T>
    void ColaPrioridad<T>::Desencolar() {
        #ifdef DEBUG
	    assert(this->arbol->EsNil() != true);
        #endif

        if (arbol->Izq().EsNil() && arbol->Der().EsNil()){
            if (!this->EsVacia()) {
                if (this->arbol->Izq().EsNil()) {
                    delete &(this->arbol->Izq());
                }
                if (this->arbol->Der().EsNil()) {
                    delete &(this->arbol->Der());
                }
            }
            delete (this->arbol);
            ArbolBinario<T>* aux = new ArbolBinario<T>();
            this->arbol = aux;
        } else {
            int h = this->arbol->Altura() - 1;
            Arreglo<int> camino = CaminoParaBorrarUltimoNodo(*this->arbol);
            int i = 0;
            ArbolBinario<T>* ultimoNodo = this->arbol;
            while (i<h){
                if(camino[i]%2==1){
                    ultimoNodo= &(ultimoNodo->Der());
                } else {
                    ultimoNodo= &(ultimoNodo->Izq());
                }
                i++;
            }
            if (ultimoNodo->Padre() == this->arbol) {
                ArbolBinario<T>::Swap(*this->arbol, *ultimoNodo);
            } else {
                ArbolBinario<T>::CambiarPimeroPorUltimo(*this->arbol,*ultimoNodo);
            }

            ArbolBinario<T>* aux = this->arbol;
            this->arbol = ultimoNodo;
            ArbolBinario<T>* nil = new ArbolBinario<T>();
            if (camino[i-1] % 2 == 1) {
                aux->Padre()->BorrarHojaDer(*nil);
                if (aux->Izq().EsNil()) {
                    delete &(aux->Izq());
                }
                if (aux->Der().EsNil()) {
                    delete &(aux->Der());
                }
                delete aux;

            } else {
                aux->Padre()->BorrarHojaIzq(*nil);
                if (aux->Izq().EsNil()) {
                    delete &(aux->Izq());
                }
                if (aux->Der().EsNil()) {
                    delete &(aux->Der());
                }
                delete aux;

            }
            BajarPrimerNodo(*arbol);
        }
    }

    template<class T>
    bool ColaPrioridad<T>::EsVacia() const {
        return this->arbol->EsNil();
    }

    // funciones privadas:
    template<class T>
    void ColaPrioridad<T>::SubirUltimoNodo(ArbolBinario<T>* ulti) {
        bool subir = (ulti->Padre() != NULL);
        while (subir){
            if (ulti->Raiz() > ulti->Padre()->Raiz()) {
                ArbolBinario<T>::Swap(*ulti->Padre(), *ulti);
                subir = (ulti->Padre() != NULL);
            } else {
                subir = false;
            }
        }
        if (this->arbol->Padre() == ulti) {
            this->arbol = ulti;
        }
    }

    template<class T>
    void ColaPrioridad<T>::BajarPrimerNodo(ArbolBinario<T>& prim) {
        bool bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
        while (bajar){
            if (!prim.Izq().EsNil() && !prim.Der().EsNil()) {
                if (prim.Raiz() < std::max(prim.Izq().Raiz(), prim.Der().Raiz())){
                    if (prim.Izq().Raiz() >= prim.Der().Raiz()) {
                        //this->arbol = &prim.Izq();
                        ArbolBinario<T>::Swap(prim,prim.Izq());
                        bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
                    } else {
                        //this->arbol = &prim.Der();
                        ArbolBinario<T>::Swap(prim,prim.Der());
                        bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
                    }
                } else {
                    bajar = false;
                }
            } else {
                if (!prim.Izq().EsNil()) {
                    if (prim.Izq().Raiz() > prim.Raiz()) {
                        //this->arbol = &prim.Izq();
                        ArbolBinario<T>::Swap(prim, prim.Izq());
                        bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
                    } else {
                        bajar = false;
                    }
                } else {
                    if (prim.Der().Raiz() > prim.Raiz()) {
                        //this->arbol = &prim.Der();
                        ArbolBinario<T>::Swap(prim, prim.Der());
                        bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
                    } else {
                        bajar = false;
                    }
                }
            }

        }
        //tengo que arreglar el puntero this->arbol
        ArbolBinario<T>* inicio = &prim;
        while(inicio->Padre() != NULL) {
            inicio = inicio->Padre();
        }
        this->arbol = inicio;
    }

    template<class T>
    Arreglo<int> ColaPrioridad<T>::CaminoParaInsertarNuevoNodo(ArbolBinario<T>& c) {
        int n= c.Tamanho() + 1;
        int len= log(n)/log(2);
        Arreglo<int> camino(len);
        int i=1;
        while (i<=len){
            if(n%2 == 0){
                camino.Definir(len-i, 0);
            } else {
                camino.Definir(len-i, 1);
            }
            n=n/2;
            i++;
        }
        return camino;
    }

    template<class T>
    Arreglo<int> ColaPrioridad<T>::CaminoParaBorrarUltimoNodo(ArbolBinario<T>& c) {
        int n= c.Tamanho();
        int len= log(n)/log(2);
        Arreglo<int> camino(len);
        int i=1;
        while (i<=len){
            if(n%2 == 0){
                camino.Definir(len-i, 0);
            } else {
                camino.Definir(len-i, 1);
            }
            n = n / 2;
            i++;
        }
        return camino;
    }

    // Implementacion del iterador:

    template<class T>
    void ColaPrioridad<T>::Iterador::BorrarSiguiente() {
        ArbolBinario<T>* aux= this->subCola;

        while (aux->Padre() != NULL){
            ArbolBinario<T>::Swap(*(aux->Padre()), *aux);
        }

        cola->arbol = aux;
        cola->Desencolar();
    }
}
#endif
