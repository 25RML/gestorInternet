// Includes
#include <iostream>

#include "global.h"
#include "reservas.h"
#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "tempFile.h"

// *************************************** Funciones ***************************************

void mainReservas()
{
	// Imprimir Pseudo-Interfaz
	printColor(menuDefs::background, color::dBlack, color::bBlack);  // Reset Background
	printWindow(25, 16, {7,4},color::dBlack,color::dYellow); // Print Window
	printWindow(110, 40, { 39,4 }, color::dBlack, color::dBlue);
	printWindow(60, 2, { 65,3 }, color::bAqua, color::bBlue);
	//printButtons<3, 3>(selectionLists::reservasOptions);
	gotoCOORD({ 78,4 }); printColor("\033[4mGESTOR DE RESERVAS DE COMPUTADORAS\033[0m", color::dBlack, color::bAqua);

	gotoCOORD({ 0,0 }); // Estetico solamente, volver a 0,0
	int inputSelection{ 0 };
	bool continueSelection{ true };
	while (continueSelection)
	{
		selectionMaps::g_reservasMap.printAll();
		switch (inputSelection = selectionMaps::g_reservasMap.startSelection(true))
		//switch (inputSelection = setSelection<3, 3>(selectionLists::reservasOptions, selectionMaps::reportesMap))
		{
		case 1:
			{
				printRectangle({ 103,8 }, 1, 36, color::bBlue, '#');
				//int idSelector{};
				do
				{
					printRectangle({ 104,8 }, 44, 36, color::dBlack);
					// Selection
					int idSelector{ selectComputer(g_registroComputadoras, { 43,9 }, 5, 5) };		// Elegir Computadora
					if (!idSelector) break;
					// Printing UI
					printFormat(formattedText::Elements::computerInfo, { 106,8 }, color::dBlack, color::dBlue);
					DoubleList<Computadora>::Node* target{ g_registroComputadoras.getAt(idSelector - 1) };
					mostrarInformacionComputadora(target, { 107,12 });
					gotoCOORD({ 105,22 }); printColor(std::string(43, '#'), color::bBlue, color::dBlack);

					do
					{
						printRectangle({ 104,24 }, 44, 20, color::dBlack);

						selectionMaps::g_confirmReservasMap.printAll();
						idSelector = selectionMaps::g_confirmReservasMap.startSelection(true);
						if (idSelector == 2) break;
						// ********************************** HACER RESERVA **********************************
						printRectangle({ 104,24 }, 44, 16, color::dBlack);

						printFormat(formattedText::Elements::makeReserve, { 106,24 }, color::dBlack, color::dBlue);
						// Fecha
						gotoCOORD({ 107,28 }); printColor("Fecha : ", color::dBlue, color::dBlack);
						Fecha fechaReserve{ getFecha({114,32},true) };
						gotoCOORD({ 115,28 });
						if (fechaReserve.day < 10) std::cout << "0";
						std::cout << fechaReserve.day << '/';
						if (fechaReserve.month < 10) std::cout << "0";
						std::cout << fechaReserve.month << "/";
						std::cout << fechaReserve.year;
						// Hora
						gotoCOORD({ 130,28 }); printColor("Hora : ", color::dBlue, color::dBlack);
						Hora horaReserve{ getHora({119,32},true) };
						gotoCOORD({ 137,28 });
						if (horaReserve.hour < 10) std::cout << "0";
						std::cout << horaReserve.hour << ':';
						if (horaReserve.minute < 10) std::cout << "0";
						std::cout << horaReserve.minute;

						FullTime tiempoInicio{ horaReserve,fechaReserve };
						// Especificar Cantidad de Hora
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
		case 2:
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
		case 3:
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