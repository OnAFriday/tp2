#ifndef NODO_H_
#define NODO_H_

#ifndef NULL
#define NULL 0
#endif

template<class Tipo> class Nodo {

private:

	Tipo dato;

	Nodo<Tipo>* anterior;
	Nodo<Tipo>* siguiente;

public:

	Nodo(Tipo dato) {

		this->dato = dato;
		this->anterior = NULL;
		this->siguiente = NULL;
	}

	Tipo obtenerDato() {

		return this->dato;
	}

	void cambiarDato(Tipo nuevoDato) {

		this->dato = nuevoDato;
	}

	Nodo<Tipo>* obtenerSiguiente() {

		return this->siguiente;
	}

	void cambiarSiguiente(Nodo<Tipo>* nuevoSiguiente) {

		this->siguiente = nuevoSiguiente;
	}

	Nodo<Tipo>* obtenerAnterior() {

		return this->anterior;
	}

	void cambiarAnterior(Nodo<Tipo>* nuevoSiguiente) {

		this->anterior = nuevoSiguiente;
	}
};

#endif /* NODO_H_ */
