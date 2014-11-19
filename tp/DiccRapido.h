
#ifndef DICC_RAPIDO_H_INCLUDED
#define DICC_RAPIDO_H_INCLUDED

#include "../aed2.h"

namespace aed2 {

    template<class T>
    class DiccRapido {
        public:

            /**
             * Genera un diccionario vacio.
             */
            DiccRapido();

            /**
             * Agrega a al diccionario con la clave s.
             */
            Definir(String s, const T& valor);

            /**
             * Devuelve true si s esta definida en el diccionario.
             */
            bool Definido(String s);

            /**
             * Devuelve el significado de la clave s en el diccionario.
             * Requiere: Def?(s)
             */
            T& Significado(String s) const;

            /**
             * Destructor.
             */
            ~DiccRapido();

            /**
             * Devuelve un iterador para el diccionario.
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
                const String SiguienteClave() const;

                /**
                 * Devuelve el significado del elemento al que apunta el iterador.
                 */
                const T& SiguienteSignificado() const;

                /**
                 * Avanza el iterador al siguiente elemento.
                 */
                void Avanzar();

            private:

                Conj<String>::const_Iterador it_claves_;
                typename DiccRapido<T> it_dicc_;

                const_Iterador(const DiccRapido<T>* d);

                friend typename DiccRapido<T>::const_Iterador DiccRapido<T>::CrearIt() const;
            };

        private:
            struct Nodo {
                Nodo() : significado(NULL) {};
                Nodo(const T& v) : significado(&v) {};

                Arreglo<Nodo> arreglo(256);
                T* significado;
            };

            Conj<String> claves;
            Nodo dicc;
    };

    template<class T>
    std::ostream& operator<<(std::ostream& os, const DiccRapido<T>&);

    template<class T>
    DiccRapido<T>::DiccRapido() {}

    template<class T>
    DiccRapido<T>::Definir(String s, const T& valor); {
        //claves.Agregar(s);
    }

    template<class T>
    DiccRapido<T>::~DiccRapido() {
        // TODO
    }

    template<class T>
    bool DiccRapido<T>::Definido(String s) const {
        return false;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const DiccRapido<T>& a) {
        os << "[";
        return os << "]";
    }
}
#endif
