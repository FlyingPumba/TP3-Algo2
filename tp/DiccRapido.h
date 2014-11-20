
#ifndef DICC_RAPIDO_H_INCLUDED
#define DICC_RAPIDO_H_INCLUDED

#include "../aed2.h"

namespace tp {

    template<class T>
    class DiccRapido {
        public:

            // forward declaration
            class const_Iterador;

            /**
             * Genera un diccionario vacio.
             */
            DiccRapido();

            /**
             * Agrega a al diccionario con la clave s.
             */
            void Definir(String s, const T& valor);

            /**
             * Agrega a al diccionario con la clave s.
             * Requiere: s no pertenece a las claves del diccionario.
             */
            void DefinirRapido(String s, const T& valor);

            /**
             * Devuelve true si s esta definida en el diccionario.
             */
            bool Definido(String s) const;

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
                    DiccRapido<T> it_dicc_;

                    const_Iterador(const DiccRapido<T>* d);

                    friend typename DiccRapido<T>::const_Iterador DiccRapido<T>::CrearIt() const;
            };

        private:
            struct Nodo {
                Nodo() : siguientes(256), significado(NULL) {};
                Nodo(const T& v) : siguientes(256), significado(&v) {};

                Arreglo<Nodo*> siguientes;
                const T* significado;
            };

            Conj<String> claves;
            Nodo dicc;

            void DefinirAux(String s, const T& valor);
    };

    template<class T>
    std::ostream& operator<<(std::ostream& os, const DiccRapido<T>&);

    template<class T>
    DiccRapido<T>::DiccRapido() {}

    template<class T>
    void DiccRapido<T>::Definir(String s, const T& valor) {
        if (claves.Pertenece(s) == false) {
            claves.Agregar(s);
            DefinirAux(s, valor);
        }
    }

    template<class T>
    void DiccRapido<T>::DefinirRapido(String s, const T& valor) {
        claves.AgregarRapido(s);
        DefinirAux(s, valor);
    }

    template<class T>
    void DiccRapido<T>::DefinirAux(String s, const T& valor) {
        Nodo* aux = &dicc;
        int i = 0;
        while (i < s.length()) {
            if(!aux->siguientes.Definido((int)s[i])) {
                Nodo* nuevo = new Nodo(s[i]);
                aux->siguientes.Definir((int)s[i], nuevo);
            }
            aux = aux->siguientes[(int)s[i]];
            i = i + 1;
        }

        aux->significado = &valor;
    }

    template<class T>
    DiccRapido<T>::~DiccRapido() {
        // TODO
    }

    template<class T>
    bool DiccRapido<T>::Definido(String s) const {
        return claves.Pertenece(s);
    }

    template<class T>
    T& DiccRapido<T>::Significado(String s) const {
        assert(Definido(s) == true);
        const Nodo* aux = &dicc;
        int i = 0;
        while (i < s.length()) {
            aux = aux->siguientes[(int)s[i]];
            i = i + 1;
        }
        T sig(*(aux->significado));
        return sig;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const DiccRapido<T>& a) {
        os << "[";
        return os << "]";
    }
}
#endif
