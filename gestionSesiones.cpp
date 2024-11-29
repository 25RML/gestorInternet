// Includes
#include <iostream>
#include <fstream>
#include <sstream>

#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "global.h"

// *************************************** Funciones ***************************************

void mainGestionSesiones()
{
	gotoCOORD(Windows::mainWindowStartPOS); // Version alterna del gotoxy
	std::cout << "Hello World!";
}






void guardarSesiones()
{
	std::ofstream file("sesions.txt");
	if (!file) return;

	SingleList<Sesion>::Node* copyMain = g_registroSesiones.head;
	while (copyMain) {
		file << copyMain->data.costo << '\n';
		file << copyMain->data.fecha.day << '\n';
		file << copyMain->data.fecha.month << '\n';
		file << copyMain->data.fecha.year << '\n';
		file << copyMain->data.horaInicio.hour << '\n';
		file << copyMain->data.horaInicio.minute << '\n';
		file << copyMain->data.horaSalida.hour << '\n';
		file << copyMain->data.horaSalida.minute << '\n';
		file << copyMain->data.idCliente << '\n';
		file << copyMain->data.idComputadora << '\n';

		copyMain = copyMain->next;
	}
}

void cargarSesiones(bool resetBoot = true)
{

	if (resetBoot) g_registroSesiones.deleteAll();
	std::ifstream file("sesions.txt");
	if (!file) return;

	Sesion toAdd{};
	int count{0};

	SingleList<Sesion>::Node* end{ g_registroSesiones.head };

	std::string lineOutput;
	while (std::getline(file, lineOutput)) {
		++count;
		switch (count)
		{
		case 1:
			toAdd.costo = std::stod(lineOutput);
			break;
		case 2:
			toAdd.fecha.day = std::stoi(lineOutput);
			break;
		case 3:
			toAdd.fecha.month = std::stoi(lineOutput);
			break;
		case 4:
			toAdd.fecha.year = std::stoi(lineOutput);
			break;
		case 5:
			toAdd.horaInicio.hour = std::stoi(lineOutput);
			break;
		case 6:
			toAdd.horaInicio.minute = std::stoi(lineOutput);
			break;
		case 7:
			toAdd.horaSalida.hour = std::stoi(lineOutput);
			break;
		case 8:
			toAdd.horaSalida.minute = std::stoi(lineOutput);
			break;
		case 9:
			toAdd.idCliente = std::stoi(lineOutput);
			break;
		case 10:
			toAdd.idComputadora = std::stoi(lineOutput);

			end->data = toAdd;
			end = end->next;
			count = 0;

			break;
		default:
			break;
		}
	}
	file.close();
}