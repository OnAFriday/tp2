/*
 * EstacionFerrocarril.h
 *
 *  Created on: 9 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_ESTACIONFERROCARRIL_H_
#define SRC_ESTACIONFERROCARRIL_H_
#include<string>
class EstacionFerrocarril {
private:
typedef unsigned int ui;
double longitud;
double latitud;
ui id;
std::string nombre, linea, barrio;

public:
	EstacionFerrocarril(double longitud, double latitud,
			ui id, std::string nombre,
			std::string linea,
			std::string barrio);
	double verCoordenadaLongitud();
	double verCoordenadaLatitud();
	ui verId();
	std::string verLineaFerrcarril();
	std::string verUbicacion();
	~EstacionFerrocarril();
};

#endif /* SRC_ESTACIONFERROCARRIL_H_ */
