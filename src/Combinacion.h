/*
 * Combinacion.h
 *
 *  Created on: 9 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_COMBINACION_H_
#define SRC_COMBINACION_H_
#include <string>
class Combinacion {
	typedef unsigned int ui;
public:
	Combinacion(std::string nombre, ui id, std::string destino);
	std::string verNombre();
	std::string verTipoTransporte();
	ui verId();
	std::string verDestino();
	~Combinacion();
};

#endif /* SRC_COMBINACION_H_ */
