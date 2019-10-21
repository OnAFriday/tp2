/*
 * lista.h
 *
 *  Created on: 21 may. 2019
 *      Author: cristian
 */

#ifndef LISTA_H_
#define LISTA_H_

#include "nodo.h"
#include <iostream>

#ifndef NULL
#define NULL 0
#endif

template<class T> class Lista {

    private:

        Nodo<T>* primero;

        Nodo<T>* ultimo;

        unsigned int tamanio;

        Nodo<T>* cursor;

    public:

        /*
         * post: Lista vacía.
         */
        Lista();

        /*
         * post: Lista que tiene los mismos elementos que otraLista.
         *       La instancia resulta en una copia de otraLista.
         */
        Lista(Lista<T>& otraLista);

        /*
         * post: indica si la Lista tiene algún elemento.
         */
        bool estaVacia();

        /*
         * post: devuelve la cantidad de elementos que tiene la Lista.
         */
        unsigned int contarElementos();

        /*
         * post: agrega el elemento al final de la Lista, en la posición:
         *       contarElementos() + 1.
         */
        void agregar(T elemento);

        /*
         * pre : posición pertenece al intervalo: [1, contarElementos() + 1]
         * post: agrega el elemento en la posición indicada.
         *
         */
        void agregar(T elemento, unsigned int posicion);

        /*
         * post: agrega todos los elementos de otraLista
         *       a partir de la posición contarElementos() + 1.
         */
        void agregar(Lista<T> &otraLista);

        /*
         * pre : posición pertenece al intervalo: [1, contarElementos()]
         * post: devuelve el elemento en la posición indicada.
         */
        T obtener(unsigned int posicion);

        /*
         * pre : posicioó pertenece al intervalo: [1, contarElementos()]
         * post: cambia el elemento en la posición indicada por el
         *       elemento dado.
         */
        void asignar(T elemento, unsigned int posicion);

        /*
         * pre : posición pertenece al intervalo: [1, contarElementos()]
         * post: remueve de la Lista el elemento en la posición indicada.
         */
        void remover(unsigned int posicion);

        /*
         * post: deja el cursor de la Lista preparado para hacer un nuevo
         *       recorrido sobre sus elementos.
         */
        void iniciarCursor();

        /*
         * pre : se ha iniciado un recorrido (invocando el método
         *       iniciarCursor()) y desde entonces no se han agregado o
         *       removido elementos de la Lista.
         * post: mueve el cursor y lo posiciona en el siguiente elemento
         *       del recorrido.
         *       El valor de retorno indica si el cursor quedó posicionado
         *       sobre un elemento o no (en caso de que la Lista esté vacía o
         *       no existan más elementos por recorrer.)
         */
        bool avanzarCursor();

        bool retrocederCursor();


        /*
         * pre : el cursor está posicionado sobre un elemento de la Lista,
         *       (fue invocado el método avanzarCursor() y devolvió true)
         * post: devuelve el elemento en la posición del cursor.
         *
         */
        T obtenerCursor();

        /*
         * post: libera los recursos asociados a la Lista.
         */
        ~Lista();

    private:

        /*
         * pre : posición pertenece al intervalo: [1, contarElementos()]
         * post: devuelve el nodo en la posición indicada.
         */
        Nodo<T>* obtenerNodo(unsigned int posicion); // NOTA: primitiva PRIVADA
};

/*
 * Excepción que representa el intento de acceder a un elemento
 * que no existe dentro de la Lista.
 */


template<class T> Lista<T>::Lista() {

    this->primero = NULL;
    this->ultimo = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
}

template<class T> Lista<T>::Lista(Lista<T>& otraLista) {

    this->primero = NULL;
    this->ultimo = NULL;
    this->tamanio = 0;
    this->cursor = NULL;

    /* copia los elementos de otraLista */
    this->agregar(otraLista);
}

template<class T> bool Lista<T>::estaVacia() {

    return (this->tamanio == 0);
}

template<class T> unsigned int Lista<T>::contarElementos() {

    return this->tamanio;
}

template<class T> void Lista<T>::agregar(T elemento) {

    this->agregar(elemento, this->tamanio + 1);
}

template<class T> void Lista<T>::agregar(T elemento, unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->tamanio + 1)) {

        Nodo<T>* nuevo = new Nodo<T>(elemento);

        if (posicion == 1) {

        	nuevo->cambiarSiguiente(this->primero);

        	if (this->estaVacia()) {
        		this->ultimo = nuevo;
        	} else {
				this->primero->cambiarAnterior(nuevo);
        	}

        	this->primero = nuevo;

        } else if (posicion == this->contarElementos() + 1) {

        	this->ultimo->cambiarSiguiente(nuevo);
        	nuevo->cambiarAnterior(this->ultimo);
        	this->ultimo = nuevo;

        } else {

        	Nodo<T>* siguiente = this->obtenerNodo(posicion);
        	nuevo->cambiarSiguiente(siguiente);
        	Nodo<T>* anterior = siguiente->obtenerAnterior();
        	nuevo->cambiarAnterior(anterior);

        	anterior->cambiarSiguiente(nuevo);
        	siguiente->cambiarAnterior(nuevo);
        }

        this->tamanio++;

        /* cualquier recorrido actual queda invalidado */
        this->iniciarCursor();

    } else {

        std::cout << "Excepcion en agregar";
    }
}

template<class T> void Lista<T>::agregar(Lista<T> &otraLista) {

    otraLista.iniciarCursor();

    while (otraLista.avanzarCursor()) {

        this->agregar(otraLista.obtenerCursor());
    }
}

template<class T> T Lista<T>::obtener(unsigned int posicion) {

    T elemento;

    if ((posicion > 0) && (posicion <= this->tamanio)) {

        elemento = this->obtenerNodo(posicion)->obtenerDato();

    } else {

        std::cout << "Excepcion en obtener";
    }

    return elemento;
}

template<class T> void Lista<T>::asignar(T elemento, unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->tamanio)) {

        this->obtenerNodo(posicion)->cambiarDato(elemento);

    } else {

        std::cout << "Excepcion en asignar";
    }
}

template<class T> void Lista<T>::remover(unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->tamanio)) {

        Nodo<T>* removido;

        if (posicion == 1) {

            if (this->contarElementos() == 1) {
            	removido = this->obtenerNodo(posicion);
            	this->primero = this->ultimo = NULL;

            } else {

            	removido = this->obtenerNodo(posicion);
				this->primero = this->primero->obtenerSiguiente();
				this->primero->cambiarAnterior(NULL);
            }
        } else if (posicion == this->contarElementos()) {

        	removido = this->ultimo;
        	Nodo<T>* anterior = this->ultimo->obtenerAnterior();
        	anterior->cambiarSiguiente(NULL);
        	this->ultimo = anterior;

        } else {

            Nodo<T>* anterior = this->obtenerNodo(posicion - 1);
            removido = anterior->obtenerSiguiente();
            Nodo<T>* posterior = removido->obtenerSiguiente();
            anterior->cambiarSiguiente(removido->obtenerSiguiente());
            posterior->cambiarAnterior(removido->obtenerAnterior());
        }

        delete removido;
        this->tamanio--;

        /* cualquier recorrido actual queda invalidado */
        this->iniciarCursor();

    } else {

        std::cout << "Excepcion en remover";
    }
}

template<class T> void Lista<T>::iniciarCursor() {

    this->cursor = NULL;
}

template<class T> bool Lista<T>::avanzarCursor() {

    if (this->cursor == NULL) {

        this->cursor = this->primero;

    } else {

        this->cursor = this->cursor->obtenerSiguiente();
    }

    /* pudo avanzar si el cursor ahora apunta a un nodo */
    return (this->cursor != NULL);
}

template<class T> bool Lista<T>::retrocederCursor() {

    if (this->cursor == NULL) {

        this->cursor = this->ultimo;

    } else {

        this->cursor = this->cursor->obtenerAnterior();
    }

    /* pudo retroceder si el cursor ahora apunta a un nodo */
    return (this->cursor != NULL);
}

template<class T> T Lista<T>::obtenerCursor() {

    T elemento;

    if (this->cursor != NULL) {

        elemento = this->cursor->obtenerDato();

    } else {

        std::cout << "Excepcion en obtenerCursor";
    }

    return elemento;
}

template<class T> Lista<T>::~Lista() {

    while (this->primero != NULL) {

        Nodo<T>* aBorrar = this->primero;
        this->primero = this->primero->obtenerSiguiente();

        delete aBorrar;
    }
}

template<class T> Nodo<T>* Lista<T>::obtenerNodo(unsigned int posicion) {

    Nodo<T>* actual = this->primero;
    for (unsigned int i = 1; i < posicion; i++) {

        actual = actual->obtenerSiguiente();
    }

    return actual;
}


#endif /* LISTA_H_ */
