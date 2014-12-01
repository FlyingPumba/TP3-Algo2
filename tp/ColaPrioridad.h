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
            class const_Iterador;

            /**
             * Crea una Cola de Prioridad.
             */
            ColaPrioridad();

            /**
             * Encola un elemento a la Cola de Prioridad.
             */
            ColaPrioridad<T>::const_Iterador Encolar(const T& elem);

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
            const T& Proximo() const;

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
                    void BorrarSiguiente();


                private:

                    ArbolBinario<T> cola;
                    ArbolBinario<T> subCola;
            };


        private:
            /**
             * Sube un nodo hasta donde corresponda
             * Requiere: ulti deberia ser el ultimo nodo
             */
            void SubirUltimoNodo(ArbolBinario<T> ulti);

            /**
             * Baja un nodo hasta donde corresponda
             * Requiere: prim deberia ser el primer nodo del arbol
             */
            void BajarPrimerNodo(ArbolBinario<T> prim);

            Arreglo<int> CaminoParaInsertarNuevoNodo(ArbolBinario<T> c);

            Arreglo<int> CaminoParaBorrarUltimoNodo(ArbolBinario<T> c);

            ArbolBinario<T> arbol;

    };

    template<class T>
    bool operator==(const ColaPrioridad<T>&, const ColaPrioridad<T>&);

    template<class T>
    std::ostream& operator<<(std::ostream& os, const ColaPrioridad<T>&);

    template<class T>
    ColaPrioridad<T>::ColaPrioridad(){
        ArbolBinario<T> aux;
        arbol = aux;
    }

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
    const T& ColaPrioridad<T>::Proximo() const {
        return this->arbol.Raiz();

    }

    template<class T>
    typename ColaPrioridad<T>::const_Iterador ColaPrioridad<T>::Encolar(const T& elem) {
        if (this->EsVacia()) {
            ArbolBinario<T> izq;
            ArbolBinario<T> der;
            this->arbol = ArbolBinario<T>(izq, elem, der);
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
            ArbolBinario<T> izq;
            ArbolBinario<T> der;
            ArbolBinario<T> aux = ArbolBinario<T>(izq, elem, der);

            //ArbolBinario<T> aux(ArbolBinario(), elem, ArbolBinario());
            if (camino[i] % 2 == 1) {
                padre.AgregarHojaDer(aux);
                SubirUltimoNodo(aux); // VER

            } else {

            }
        }
    }

    template<class T>
    void ColaPrioridad<T>::Desencolar() {
        if (arbol.Izq().EsNil() && arbol.Der().EsNil()){
            ArbolBinario<T> aux;
            this->arbol = aux;
        } else {
            int h = this->arbol.Altura();
            Arreglo<int> camino = CaminoParaBorrarUltimoNodo(this->arbol);
            int i = 0;
            ArbolBinario<T> ultimoNodo = this->arbol;
            while (i<h){
                if(camino[i]%2==1){
                    ultimoNodo= ultimoNodo.Der();
                } else {
                    ultimoNodo= ultimoNodo.Izq();
                }
                i++;
            }
            arbol.CambiarRaiz(ultimoNodo.Raiz());
            ArbolBinario<T> nil;
            if (camino[i] % 2 == 1) {
                ultimoNodo.Padre()->BorrarHojaDer(nil);
            } else {
                ultimoNodo.Padre()->BorrarHojaIzq(nil);
            }
            BajarPrimerNodo(arbol);
        }
    }

    template<class T>
    bool ColaPrioridad<T>::EsVacia() const {
        return this->arbol.EsNil();

    }

    // funciones privadas:
    template<class T>
    void ColaPrioridad<T>::SubirUltimoNodo(ArbolBinario<T> ulti) {
        bool subir = (ulti.Padre() != NULL);
        while (subir){
            if (ulti.Raiz() > ulti.Padre()->Raiz()){
                ArbolBinario<T>::Swap(*ulti.Padre(), ulti);
                subir = (ulti.Padre() != NULL);
            } else {
                subir = false;
            }
        }
    }

    template<class T>
    void ColaPrioridad<T>::BajarPrimerNodo(ArbolBinario<T> prim) {
        bool bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
        while (bajar){
            if (!prim.Izq().EsNil() && !prim.Der().EsNil()){
                if (prim.Raiz() < std::max(prim.Izq().Raiz(), prim.Der().Raiz())){
                    if (prim.Izq().Raiz() >= prim.Der().Raiz()){
                        ArbolBinario<T>::Swap(prim,prim.Izq());
                        bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
                    } else {
                        ArbolBinario<T>::Swap(prim,prim.Der());
                        bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
                    }
                } else {
                    bajar = false;
                }
            } else {
                if (!prim.Izq().EsNil()) {
                    if (prim.Izq().Raiz() > prim.Raiz()){
                        ArbolBinario<T>::Swap(prim, prim.Izq());
                        bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
                    } else {
                        bajar = false;
                    }
                } else {
                    if (prim.Der().Raiz() > prim.Raiz()){
                        ArbolBinario<T>::Swap(prim, prim.Der());
                        bajar = !prim.Izq().EsNil() || !prim.Der().EsNil();
                    } else {
                        bajar = false;
                    }
                }
            }

        }
    }

    template<class T>
    Arreglo<int> ColaPrioridad<T>::CaminoParaInsertarNuevoNodo(ArbolBinario<T> c) {
        int n= c.Tamanho() + 1;
        int len= log2(n);
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
    }

    template<class T>
    Arreglo<int> ColaPrioridad<T>::CaminoParaBorrarUltimoNodo(ArbolBinario<T> c) {
        int n= c.Tamanho();
        int len= log2(n);
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
    }

    // Implementacion del iterador:

    template<class T>
    void ColaPrioridad<T>::const_Iterador::BorrarSiguiente() {
        // TODO
    }
}
#endif
