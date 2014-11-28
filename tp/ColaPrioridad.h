
#ifndef AED2_ColaPrioridad_H_INCLUDED
#define AED2_ColaPrioridad_H_INCLUDED

#include "../aed2.h"
#include "ArbolBinario.h"

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

            ArbolBinario<T> arbol;

    };

    /**
     * Funciones globales de comparacion.  Con definir el == obtenemos
     * el != gratis :)
     */
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

}



#endif
