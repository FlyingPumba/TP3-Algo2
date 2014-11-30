#ifndef COLA_PRIORIDAD_H_INCLUDED
#define COLA_PRIORIDAD_H_INCLUDED

#include "../aed2.h"
#include "ArbolBinario.h"
#include "math.h"

namespace tp {

    template<class T>
    class ColaPrioridad{
        public:

            // forward declaration
            class const_iterador;

            /**
             * Crea una Cola de Prioridad.
             */
            ColaPrioridad();

            /**
             * Encola un elemento a la Cola de Prioridad.
             */
            void Encolar(const T& elem);

            /**
             * Constructor por copia.  Los elementos de otro se copian
             * en el mismo orden a this, y pasan a ser Colas de Prioridad independientes
             */
            ColaPrioridad<T>(const ColaPrioridad<T>& otro);

            /**
             * Operacion de asignacion.  Borra lo que se que habia en this
             * y copia los elementos de otro en el mismo orden.
             */
            ColaPrioridad<T>& operator=(const ColaPrioridad<T>& otro);

            /**
             * Destructor.  Borra lo que hubiera en el ColaPrioridad.
             */
            ~ColaPrioridad();

            /**
             * Devuelve true si la Cola de Prioridad esta vacia.
             */
            bool EsVacia() const;

            /**
             /**
             * Devuelve el proximo de la Cola de Prioridad.
             * Requiere: not vacia?(colaPrior)
             */
            T& Proximo() const;

            /**
             * Modifica la cola dada, desencolando al elemento de mayor prioridad
             * Requiere: not vacia?(colaPrior)
             */

            void Desencolar();

            const_Iterador CrearIt() const;

            class const_Iterador
            {
                public:

                    const_Iterador();

                    /**
                     * Devuelve true si el iterador apunta a un nodo valido.
                     */
                    bool HaySiguiente() const;

                    /**
                     * Devuelve el alpha apuntado por le iterador.
                     * Requiere: haysiguiente?(it)
                     */
                    const T& Siguiente() const;

                    /**
                     * Desencola la subcola del iterador sin alterar el resto de la cola.
                     * Requiere: haysiguiente?(it)
                     */
                    BorrarSiguiente();


                private:

                    ArbolBinario<T> cola;
                    ArbolBinario<T> subCola;
            };


        private:
            /**
             * Sube un nodo hasta donde corresponda
             * Requiere: ulti deberia ser el ultimo nodo
             */
            void subirUltimoNodo(ArbolBinario<T> ulti);

            /**
             * Baja un nodo hasta donde corresponda
             * Requiere: prim deberia ser el primer nodo del arbol
             */
            void bajarUltimoNodo(ArbolBinario<T> prim);

            Arreglo<int> caminoParaInsertarNuevoNodo(ArbolBinario<T> c);

            ArbolBinario<T> arbol;

    };

    template<class T>
    bool operator==(const ColaPrioridad<T>&, const ColaPrioridad<T>&);

    template<class T>
    std::ostream& operator<<(std::ostream& os, const ColaPrioridad<T>&);

    template<class T>
    ColaPrioridad<T>::ColaPrioridad() : arbol(ArbolBinario()) {}


    template<class T>
    ColaPrioridad<T>::ColaPrioridad(const ColaPrioridad<T>& otro) {
        //TODO
    }

    template<class T>
    ColaPrioridad<T>& ColaPrioridad<T>::operator=(const ColaPrioridad<T>& otro) {
        //TODO
    }

    template<class T>
    ColaPrioridad<T>::~ColaPrioridad() {
        //TODO
    }

    template<class T>
    T& ColaPrioridad<T>::Proximo() const {
        return this->arbol.Raiz();

    }

    template<class T>
    void ColaPrioridad<T>::Encolar(const T& elem) const {
        if (this.EsVacia()) {
            this->arbol(ArbolBinario(ArbolBinario(),elem,ArbolBinario()));
        } else {
            int h = this->arbol.Altura() - 1;
            Arreglo<int> camino = CaminoParaInsertarNuevoNodo(this->arbol);
            int i = 0;
            ArbolBinario<T> padre = this->arbol;
            while (i < h - 1) {
                if (camino[i] % 2 == 1) {
                    padre = padre.Der();
                } else {
                    padre = padre.Izq();
                }
                i++;
            }
            ArbolBinario<T> aux(ArbolBinario(), elem, ArbolBinario());
            if (camino[i] % 2 == 1) {
                padre.AgregarHojaDer(aux);
                Nodo<T> nodoAux.SubirUltimoNodo(padre.Der()); // VER

            } else {

            }
        }


    }

    template<class T>
    bool ColaPrioridad<T>::EsVacia() const {
        return this->arbol.EsNil();

    }


    //funciones privadas:
    template<class T>
    void ColaPrioridad<T>::subirUltimoNodo(ArbolBinario<T> ulti) {
        bool subir= (ulti.padre != NULL);
        while (subir){
            if (ulti.Raiz > ulti.Padre.Raiz){
                Swap(ulti.padre*, ulti);
                subir= (ulti.padre != NULL);
            } else {
                subir=false;
            }
        }
    }

    template<class T>
    void ColaPrioridad<T>::bajarUltimoNodo(ArbolBinario<T> prim) {
        bool bajar= (!(EsNil(prim.izq)) || !(EsNil(prim.der)));
        while (bajar){
            if (!(EsNil(prim.izq)) && !(EsNil(prim.der))){
                if (prim.raiz < max(prim.izq.raiz, prim.der.raiz)){
                    if (prim.izq.raiz >= prim.der.raiz){
                        Swap(prim,prim.izq);
                        bajar= (!(EsNil(prim.izq)) || !(EsNil(prim.der)));
                    } else {
                        Swap(prim,prim.der);
                        bajar= (!(EsNil(prim.izq)) || !(EsNil(prim.der)));
                    }
                } else {
                    bajar= false;
                }
            } else {
                if (!(EsNil(prim.izq))){
                    if (prim.izq.raiz > prim.raiz){
                        swap(prim, prim.izq);
                        bajar= (!(EsNil(prim.izq)) || !(EsNil(prim.der)));
                    } else {
                        bajar= false;
                    }
                } else {
                    if (prim.der.raiz > prim.raiz){
                        swap(prim, prim.der);
                        bajar= (!(EsNil(prim.izq)) || !(EsNil(prim.der)));
                    } else {
                        bajar= false;
                    }
                }
            }

        }
    }

    template<class T>
    Arreglo<int> ColaPrioridad<T>::caminoParaInsertarNuevoNodo(ArbolBinario<T> c){
        int n= c.Tamanho+1;
        int len= log2(n); //arriba esta el include math.h, espero que funcione
        Arreglo<int> camino= Arreglo(len);
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
    }
}
#endif
