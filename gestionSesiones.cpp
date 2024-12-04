// Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "gestionSesiones.h"
#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "global.h"
#include "tempFile.h" // Para la definición de Sesion

// ************* Funciones *************

void mainGestionSesiones()
{
    gotoCOORD(Windows::mainWindowStartPOS); // Version alterna del gotoxy
    std::cout << "Hello World!";
}

void guardarSesiones()
{
    std::ofstream file("sesions.txt");
    if (!file) {
        std::cerr << "Error al abrir el archivo para guardar sesiones.\n";
        return;
    }

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
        file << copyMain->data.start_time << '\n'; // Nuevo campo: tiempo de inicio en real-life
        file << static_cast<int>(copyMain->data.is_fixed_duration) << '\n'; // Nuevo campo: si es hora fija
        file << copyMain->data.fixed_duration.hour << '\n'; // Nuevo campo: duración fija horas
        file << copyMain->data.fixed_duration.minute << '\n'; // Nuevo campo: duración fija minutos

        copyMain = copyMain->next;
    }

    file.close();
}

void cargarSesiones(bool resetBoot)
{
    if (resetBoot) g_registroSesiones.deleteAll();
    std::ifstream archivo("sesions.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para cargar sesiones.\n";
        return;
    }

    Sesion toAdd{};
    int count{ 0 };

    std::string lineOutput;
    while (std::getline(archivo, lineOutput)) {
        ++count;
        switch (count)
        {
        case 1:
            toAdd.costo = std::stod(lineOutput);
            break;
        case 2:
            toAdd.fecha.day = static_cast<short>(std::stoi(lineOutput));
            break;
        case 3:
            toAdd.fecha.month = static_cast<short>(std::stoi(lineOutput));
            break;
        case 4:
            toAdd.fecha.year = static_cast<short>(std::stoi(lineOutput));
            break;
        case 5:
            toAdd.horaInicio.hour = static_cast<short>(std::stoi(lineOutput));
            break;
        case 6:
            toAdd.horaInicio.minute = static_cast<short>(std::stoi(lineOutput));
            break;
        case 7:
            toAdd.horaSalida.hour = static_cast<short>(std::stoi(lineOutput));
            break;
        case 8:
            toAdd.horaSalida.minute = static_cast<short>(std::stoi(lineOutput));
            break;
        case 9:
            toAdd.idCliente = std::stoi(lineOutput);
            break;
        case 10:
            toAdd.idComputadora = std::stoi(lineOutput);
            break;
        case 11:
            toAdd.start_time = static_cast<std::time_t>(std::stoll(lineOutput)); // Leer start_time
            break;
        case 12:
            toAdd.is_fixed_duration = (std::stoi(lineOutput) != 0); // Leer is_fixed_duration
            break;
        case 13:
            toAdd.fixed_duration.hour = static_cast<short>(std::stoi(lineOutput)); // Leer fixed_duration horas
            break;
        case 14:
            toAdd.fixed_duration.minute = static_cast<short>(std::stoi(lineOutput)); // Leer fixed_duration minutos

            // Insertar la sesión en la lista
            g_registroSesiones.append(g_registroSesiones.createEntry(toAdd));

            // Reiniciar la sesión y el paso
            toAdd = Sesion();
            count = 0;
            break;
        default:
            break;
        }
    }
    archivo.close();
}
