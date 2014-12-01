
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
            void Definir(const String& s, T& valor);

            /**
             * Devuelve true si s esta definida en el diccionario.
             */
            bool Definido(const String& s) const;

            /**
             * Devuelve el significado de la clave s en el diccionario.
             * Requiere: Def?(s)
             */
            T& Significado(const String& s) const;

            /**
             * Devuelve las claves en el diccionario.
             */
            const Conj<String>& Claves() const;

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
                    const DiccRapido<T>* it_dicc_;

                    const_Iterador(const DiccRapido<T>* d);

                    friend typename DiccRapido<T>::const_Iterador DiccRapido<T>::CrearIt() const;
            };

        private:
            struct Nodo {
                Nodo() : siguientes(256), significado(NULL) {};
                Nodo(T& v) : siguientes(256), significado(&v) {};

                Arreglo<Nodo*> siguientes;
                T* significado;
            };

            Conj<String> claves;
            Nodo dicc;

            void DefinirAux(const String& s, T& valor);
    };

    template<class T>
    std::ostream& operator<<(std::ostream& os, const DiccRapido<T>&);

    template<class T>
    bool operator==(const DiccRapido<T>&, const DiccRapido<T>&);

    template<class T>
    DiccRapido<T>::DiccRapido() {}

    template<class T>
    void DiccRapido<T>::Definir(const String& s, T& valor) {
        if (claves.Pertenece(s) == false) {
            claves.Agregar(s);
            DefinirAux(s, valor);
        }
    }

    template<class T>
    void DiccRapido<T>::DefinirAux(const String& s, T& valor) {
        Nodo* aux = &dicc;
        int i = 0;
        while (i < s.length()) {
            if(!aux->siguientes.Definido((int)s[i])) {
                Nodo* nuevo = new Nodo();
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
    bool DiccRapido<T>::Definido(const String& s) const {
        const Nodo* aux = &dicc;
        int i = 0;
        while (i < s.length()) {
            if(!aux->siguientes.Definido((int)s[i])) {
                return false;
            } else {
                aux = aux->siguientes[(int)s[i]];
            }
            i = i + 1;
        }

        if (i < s.length() || aux->significado == NULL) {
            return false;
        } else {
            return true;
        }
    }

    template<class T>
    T& DiccRapido<T>::Significado(const String& s) const {
        assert(Definido(s) == true);
        const Nodo* aux = &dicc;
        int i = 0;
        while (i < s.length()) {
            aux = aux->siguientes[(int)s[i]];
            i = i + 1;
        }
        return *(aux->significado);
    }

    template<class T>
    const Conj<String>& DiccRapido<T>::Claves() const {
        return claves;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const DiccRapido<T>& a) {
        os << "[";
        return os << "]";
    }

    template<class T>
    bool operator == (const DiccRapido<T>& d1, const DiccRapido<T>& d2)
    {
      if (d1.Claves() == d2.Claves()) {
          Conj<String>::const_Iterador it = d1.Claves().CrearIt();
          while (it.HaySiguiente()) {
              if (d1.Significado(it.Siguiente()) != d2.Significado(it.Siguiente())) {
                  return false;
              }
              it.Avanzar();
          }
          return true;
      } else {
          return false;
      }
    }

    template<class T>
    typename DiccRapido<T>::const_Iterador DiccRapido<T>::CrearIt() const {
        return const_Iterador(this);
    }

    // Implementacion const_Iterador:

    template<class T>
    DiccRapido<T>::const_Iterador::const_Iterador(const DiccRapido<T>* d)
      : it_claves_(d->claves.CrearIt()), it_dicc_(d)
    {}

    template<class T>
    bool DiccRapido<T>::const_Iterador::HaySiguiente() const {
      return it_claves_.HaySiguiente();
    }

    template<class T>
    const String DiccRapido<T>::const_Iterador::SiguienteClave() const {
      #ifdef DEBUG
      assert(HaySiguiente());
      #endif

      return it_claves_.Siguiente();
    }

    template<class T>
    const T& DiccRapido<T>::const_Iterador::SiguienteSignificado() const {
      #ifdef DEBUG
      assert(HaySiguiente());
      #endif

      return (*it_dicc_).Significado(it_claves_.Siguiente());
    }

    template<class T>
    void DiccRapido<T>::const_Iterador::Avanzar() {
      #ifdef DEBUG
      assert(HaySiguiente());
      #endif

      it_claves_.Avanzar();
    }

}
#endif
