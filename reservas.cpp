// Includes
#include <iostream>

#include "global.h"
#include "reservas.h"
#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "tempFile.h"

// *************************************** Funciones ***************************************

/*
*	FUNCION mainReservas()
*	:: Todo el proceso desde que se elije desde el menú, hasta que se sale
*	:: - Las funciones de salida (de la opción) se ejecutan desde esta funcion también
*/
void mainReservas()
{
	/*
	*	------------------------ Funciones para imprimir las interfaces ------------------------ 
	*/
	printColor(menuDefs::background, color::dBlack, color::bBlack);								// Imprime el fondo (recuadro de color gris que cubre toda la ventana)
	printWindow(25, 16, {7,4},color::dBlack,color::dYellow);									// Imprime una ventana con fondo amarillo oscuro.
	printWindow(110, 40, { 39,4 }, color::dBlack, color::dBlue);								// Imprime una ventana con fondo azul oscuro.
	printWindow(60, 2, { 65,3 }, color::bAqua, color::bBlue);									// Imprime una ventana con fondo azul oscuro y de color aqua
	gotoCOORD({ 78,4 }); printColor("\033[4mGESTOR DE RESERVAS DE COMPUTADORAS\033[0m", color::dBlack, color::bAqua);	// Imprime un texto sobre la ventana coloreada anterior
	gotoCOORD({ 0,0 });																			// Regresa a 0,0 para el cursor
	/*
	*	------------------------ Bucle de recorrido para las opciones principales ------------------------
	*/
	int inputSelection{ 0 };
	bool continueSelection{ true };
	while (continueSelection)
	{
		selectionMaps::g_reservasMap.printAll();												// Imprime todo el mapa de botones
		switch (inputSelection = selectionMaps::g_reservasMap.startSelection(true))				// Comienza la seleccion de una opción
		{
		case 1:		// -------------------------------- Opcion 1: Hacer Reserva --------------------------------
			{
				printRectangle({ 103,8 }, 1, 36, color::bBlue, '#');										// Linea Separadora de Interfaz (estético)
				do
				{
					printRectangle({ 104,8 }, 44, 36, color::dBlack);										// Reimprimir fondo negro (cleanup)
					// ========= Seleccion de Computadoras ========= 
					int idSelector{ selectComputer(g_registroComputadoras, { 43,9 }, 5, 5) };				// Elegir Computadora
					if (!idSelector) break;																	// Si es volver (idSelector==0), salir del bucle
					DoubleList<Computadora>::Node* target{ g_registroComputadoras.getAt(idSelector - 1) };	// Vincular la computadora elegida a un puntero
					// ========= Imprimir UI ========= 
					printFormat(formattedText::Elements::computerInfo, { 106,8 }, color::dBlack, color::dBlue);	// Imprimir Elemento de Interfaz
					mostrarInformacionComputadora(target, { 107,12 });										// Informacion (UI)
					gotoCOORD({ 105,22 }); printColor(std::string(43, '#'), color::bBlue, color::dBlack);	// Imprimir Separador (UI)
					// ========= Bucle de Crear Reserva con computadora escogida ========= 
					do
					{
						printRectangle({ 104,24 }, 44, 20, color::dBlack);									// Reimprimir recuadro inferior derecho negro (cleanup)

						selectionMaps::g_confirmReservasMap.printAll();										// Imprimir botones de Confirmación
						idSelector = selectionMaps::g_confirmReservasMap.startSelection(true);				// Comenzar selección de botones de confirmación
						if (idSelector == 2) break;															// Volver si no se confirmó (opcion 2)
						/*
						 ********************************** PROCESO DE HACER RESERVA **********************************
						*/
						printRectangle({ 104,24 }, 44, 16, color::dBlack);									// Reimprimir recuadro inferior derecho negro (cleanup)
						printFormat(formattedText::Elements::makeReserve, { 106,24 }, color::dBlack, color::dBlue);	// Elemento Gr fico
						// -

						Fecha fechaReserve = { 0, 0, 0 };
						Hora horaReserve = { 0, 0 };
						bool reservaValida = false;

						while (!reservaValida) {
							// ========= Introducir Fecha =========
							gotoCOORD({ 107,28 }); printColor("Fecha : ", color::dBlue, color::dBlack);			// UI
							Fecha fechaReserve{ getFecha({114,32},true) };
							gotoCOORD({ 115,28 });																// -
							if (fechaReserve.day < 10) std::cout << "0";										//  |
							std::cout << fechaReserve.day << '/';												//  |- Impresi n de la fecha
							if (fechaReserve.month < 10) std::cout << "0";										//  |
							std::cout << fechaReserve.month << "/" << fechaReserve.year;						// -
							// ========= Introducir Hora =========
							gotoCOORD({ 130,28 }); printColor("Hora : ", color::dBlue, color::dBlack);			// UI
							Hora horaReserve{ getHora({119,32},true) };
							gotoCOORD({ 137,28 });																// -
							if (horaReserve.hour < 10) std::cout << "0";										//  |
							std::cout << horaReserve.hour << ':';												//  |- Impresi n de la hora
							if (horaReserve.minute < 10) std::cout << "0";										//  |
							std::cout << horaReserve.minute;													// -
							if (esReservaEnElPasado(fechaReserve, horaReserve)) {
								gotoCOORD({ 102, 32 });
								printColor("¡Error! No se puede hacer una reserva en el pasado.", color::bRed);
								gotoCOORD({ 100, 33 });
								printColor("Por favor, ingrese una fecha y hora válidas.", color::bRed);
								_getch();
							}
							else {
								FullTime tiempoInicio{ horaReserve, fechaReserve };
								reservaValida = true;
							}
						}
						FullTime tiempoInicio{ horaReserve,fechaReserve };
						// ========= Especificar N° de horas a usar el servicio =========
						gotoCOORD({ 107,29 }); printColor("Tiempo de Uso : ", color::dBlue, color::dBlack);
						Hora tiempoDeUso{ getHora({119,32},true) };
						gotoCOORD({ 137,29 });
						if (tiempoDeUso.hour < 10) std::cout << "0";
						std::cout << tiempoDeUso.hour << ':';
						if (tiempoDeUso.minute < 10) std::cout << "0";
						std::cout << tiempoDeUso.minute;
						// Mostrar Hora de Termino
						FullTime tiempoFinal{ tiempoInicio };
						tiempoFinal.sumarTiempo(tiempoDeUso);
						gotoCOORD({ 107,30 }); printColor("Hora de Termino :             ", color::dBlue, color::dBlack);
						if (tiempoFinal.hora.hour < 10) std::cout << "0";
						std::cout << tiempoFinal.hora.hour << ':';
						if (tiempoFinal.hora.minute < 10) std::cout << "0";
						std::cout << tiempoFinal.hora.minute;

						// Check Parity
						Reserva toInsert{ fechaReserve,horaReserve,tiempoFinal.hora };
						int insertionID{ checkParity(target->data.colaReservas,toInsert) };

						if (insertionID)
						{
							target->data.colaReservas.insert(target->data.colaReservas.createEntry(toInsert),insertionID-1);

							gotoCOORD({ 112,32 }); printColor("Reserva Realizada con exito", color::bGreen);
							gotoCOORD({ 110,33 }); printColor("Desea realizar otra reserva en", color::bGreen);
							gotoCOORD({ 118,34 }); printColor("esta computadora?", color::bGreen);

							selectionMaps::g_continueReservasMap.printAll();
							if (selectionMaps::g_continueReservasMap.startSelection() == 2) break;
						}
						else
						{
							gotoCOORD({ 113,33 }); printColor("No se encuentra un espacio", color::bRed);
							gotoCOORD({ 111,34 }); printColor("disponible para la computadora", color::bRed);
							gotoCOORD({ 112,35 }); printColor("actualmente seleccionada...", color::bRed);

							printFormat(formattedText::volver, { 117,37 }, color::dBlack, color::bAqua);

							_getch();
						}
					} while (1);
				} while (1);
			}
			break;
		case 2:		// -------------------------------- Opcion 2: Ver Historial de Reservas --------------------------------
			{
				COORD linePrint{ 103,8 };
				for (int i{ 0 }; i < 36; ++i)
				{
					gotoCOORD(linePrint);
					printColor("#", color::bBlue, color::dBlack);
					++linePrint.Y;
				}
			}
			selectComputer(g_registroComputadoras, { 43,9 }, 5, 5);
			break;
		case 3:		// -------------------------------- Opcion 3: Volver al menú principal --------------------------------
			continueSelection = false;
			break;
		}
	}

	// END

	gotoCOORD({ 0,0 });
	//computadorasMain.deleteAll(); fflush(stdout);
	printColor(menuDefs::background, color::dBlack, color::bBlack);  // Reset Background
}

int checkParity(const SingleList<Reserva> origin, const Reserva& toAdd)
{
	SingleList<Reserva>::Node* traveler{ origin.head };
	int times{1};
	while (traveler)
	{
		// Revisar por disparidad de fecha
		if (traveler->data.fecha.year > toAdd.fecha.year) return times;
		else if (traveler->data.fecha.year == toAdd.fecha.year)
		{
			if (traveler->data.fecha.month > toAdd.fecha.month) return times;
			else if (traveler->data.fecha.month == toAdd.fecha.month)
			{
				if (traveler->data.fecha.day > toAdd.fecha.day) return times;
				else if (traveler->data.fecha.day == toAdd.fecha.day)
				{	// All three Dates are the same (Check for disparity in hours)
					if ((traveler->data.horaFinal.hour * 60 + traveler->data.horaFinal.minute) > (toAdd.horaInicio.hour * 60 + toAdd.horaInicio.minute)) return 0;
					if ((traveler->data.horaInicio.hour * 60 + traveler->data.horaInicio.minute) < (toAdd.horaFinal.hour * 60 + toAdd.horaFinal.minute)) return 0;
				}
			}
		}
		++times;
		traveler = traveler->next;
	}
	if (!traveler) ++times;
	return times-1;
}
Fecha obtenerFechaActual() {
	std::time_t t = std::time(nullptr);
	std::tm now;
	localtime_s(&now, &t);

	Fecha fechaActual;
	fechaActual.year = now.tm_year + 1900;  // El año empieza desde 1900
	fechaActual.month = now.tm_mon + 1;     // El mes empieza desde 0
	fechaActual.day = now.tm_mday;           // Día del mes

	return fechaActual;
}

// Función para obtener la hora actual del sistema
Hora obtenerHoraActual() {
	std::time_t t = std::time(nullptr);
	std::tm now;
	localtime_s(&now, &t);

	Hora horaActual;
	horaActual.hour = now.tm_hour;    // Hora
	horaActual.minute = now.tm_min;   // Minuto

	return horaActual;
}

bool esReservaEnElPasado(Fecha fechaReserva, Hora horaReserva) {
	Fecha fechaActual = obtenerFechaActual();
	Hora horaActual = obtenerHoraActual();

	if (fechaReserva.year < fechaActual.year) return true; // Comparar año, mes, día
	if (fechaReserva.year == fechaActual.year) {
		if (fechaReserva.month < fechaActual.month) return true;
		if (fechaReserva.month == fechaActual.month) {
			if (fechaReserva.day < fechaActual.day) return true;
			if (fechaReserva.day == fechaActual.day) {
				if (horaReserva.hour < horaActual.hour) return true; // Comparar hora y minuto
				if (horaReserva.hour == horaActual.hour) {
					if (horaReserva.minute < horaActual.minute) return true;
				}
			}
		}
	}
	return false;
}