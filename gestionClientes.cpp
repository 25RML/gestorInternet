// Includes
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <map>

#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "gestionClientes.h"
#include "gestionSesiones.h" // Para 'guardarSesiones' y 'cargarSesiones'
#include "global.h"
#include "tempFile.h" // Para la definición de Sesion
// ************* Variables *************

extern std::map<std::string, int> horasConteo;
extern std::map<std::string, double> gastosTotales;

// ************* Funciones *************

void mainGestionClientes()
{
    gotoCOORD({ 0,0 });
    // Imprimir Menus
    printColor(menuDefs::background, color::dBlack, color::bBlack);     // Reset Background
    printWindow(25, 14, { 12,3 }, color::dBlack, color::dRed);          // Imprimir ventana de Operaciones
    printWindow(37, 25, { 6,20 }, color::dBlack, color::dYellow);       // Imprimir ventana de Sub Operaciones
    printWindow(102, 36, { 50,7 }, color::dBlack, color::bGreen);       // Imprimir ventana de Vista

    printWindow(64, 2, { 68,6 }, color::bGreen, color::dGreen);         // Ventana de Titulo
    gotoCOORD({ 91,7 }); printColor("\033[4mSIMULADOR DE CLIENTES\033[0m", color::dBlack, color::bGreen);   // Titulo

    gotoCOORD({ 0,0 }); // Estetico solamente, volver a 0,0
    int inputSelection{ 0 };
    bool continueSelection{ true };
    while (continueSelection)
    {
        printRectangle({ 7,21 }, 35, 25, color::dBlack);                                    // Imprime un rectangulo de color negro (resetea la ventana de sub-operaciones/vista)
        selectionMaps::g_simulacionClientesMap.printAll();                                  // Imprime los Botones
        inputSelection = selectionMaps::g_simulacionClientesMap.startSelection(true);       // Elegir operacion del menu de operaciones

        switch (inputSelection)
        {
        case 1:             // *************** Comenzar Sesion ***************
        {
            printFormat(formattedText::Elements::elegirTipoSesion, { 8,21 }, color::dBlack, color::dYellow);

            selectionMaps::g_seleccionTipoHoraSimulacion.printAll();
            switch (selectionMaps::g_seleccionTipoHoraSimulacion.startSelection(true))
            {
            case 1:         // Asignar computadora al azar (Hora Libre)
            {
                size_t sizeRegistro{ g_registroComputadoras.getSize() };                    // Numero de Computadoras en registro
                DoubleList<Computadora>::Node* computadora{ g_registroComputadoras.head };  // Crea un puntero de "recorrido" usando la cabeza del registro global de computadoras

                int pc{};
                srand(time(nullptr));
                do {
                    pc = rand() % sizeRegistro;
                    computadora = g_registroComputadoras.getAt(pc);
                } while (computadora->data.estado != 0);

                computadora->data.estado = 1;                       // Cambia el estado a "Ocupado"
                std::string cliente{ nombresClientes[rand() % 20] };// Se usa 20 porque solo existen 20 nombres

                std::time_t currentDate{}; std::time(&currentDate); //
                std::tm dateInfo{};                                 //  Usado para obtener la Hora (y Fecha)
                localtime_s(&dateInfo, &currentDate);               //

                // Crear una nueva sesión y almacenarla en el registro global de sesiones
                Sesion nuevaSesion = {
                    computadora->data.ID,       // ID Computadora
                    0,                          // ID Cliente, 0 porque no se usa el struct de cliente
                    {static_cast<short>(dateInfo.tm_hour),static_cast<short>(dateInfo.tm_min)}, // Hora de Inicio
                    {23,59},                    // Hora de Salida, hora máxima para hora libre
                    {static_cast<short>(dateInfo.tm_year + 1900),static_cast<short>(dateInfo.tm_mon + 1),static_cast<short>(dateInfo.tm_mday)},   // Fecha
                    0.0                         // Costo inicial
                };

                // Guardar la sesión en el registro global de sesiones
                g_registroSesiones.push(g_registroSesiones.createEntry(nuevaSesion));

                // Asociar la sesión actual con la computadora
                computadora->data.sesionActiva = &g_registroSesiones.head->data;

                // Guardar el tiempo de inicio en tiempo real
                computadora->data.tiempoInicioReal = std::chrono::steady_clock::now();

                // ************ PARTE INTERFAZ ************
                printRectangle({ 7,21 }, 35, 25, color::dBlack);                                                // Reset background
                printFormat(formattedText::Elements::sesionAsignada, { 8,21 }, color::dBlack, color::dYellow);  // Print flavor element

                gotoCOORD({ 12,32 }); printColor("Se ha iniciado una sesion.", color::bYellow, color::dBlack);
                gotoCOORD({ 12,33 }); printColor("- Computadora (ID): ", color::bYellow, color::dBlack); std::cout << computadora->data.ID;
                gotoCOORD({ 12,34 }); printColor("- Cliente: ", color::bYellow, color::dBlack); std::cout << cliente;

                _getch();
                // END
            }
            break;
            case 2:         // Asignar computadora por hora
            {
                printRectangle({ 7,21 }, 35, 25, color::dBlack);                                                // Reset background
                printFormat(formattedText::Elements::introducirHora, { 8,23 }, color::dBlack, color::dYellow);

                size_t sizeRegistro{ g_registroComputadoras.getSize() };                    // Numero de Computadoras en Registro
                Hora definirHora{ getHora({17,28},true) };                                  // Obtener la Hora usando una funcion bonita
                DoubleList<Computadora>::Node* computadora{ g_registroComputadoras.head };  // Crea un puntero de "recorrido" usando la cabeza del registro global de computadoras

                int pc;
                srand(time(nullptr));
                do {
                    pc = rand() % sizeRegistro;
                    computadora = g_registroComputadoras.getAt(pc);
                } while (computadora->data.estado != 0); // Buscar por computadora Libre

                computadora->data.estado = 1;                       // Cambia el estado a "Ocupado"
                std::string cliente{ nombresClientes[rand() % 20] };// Se usa 20 porque solo existen 20 nombres

                std::time_t currentDate{}; std::time(&currentDate); //
                std::tm dateInfo{};                                 //  Usado para obtener la Hora (y Fecha)
                localtime_s(&dateInfo, &currentDate);               //

                Hora horaInicio{ static_cast<short>(dateInfo.tm_hour),static_cast<short>(dateInfo.tm_min) };
                Hora horaFinal{ horaInicio };
                horaFinal.minute += definirHora.minute;
                if (horaFinal.minute >= 60)
                {
                    horaFinal.minute -= 60;
                    ++horaFinal.hour;
                }
                horaFinal.hour += definirHora.hour;               // Obtener Hora Final

                // Crear una nueva sesión y almacenarla en el registro global de sesiones
                Sesion nuevaSesion = {
                    computadora->data.ID,       // ID Computadora
                    0,                          // ID Cliente, 0 porque no se usa el struct de cliente
                    horaInicio,                 // Hora de Inicio
                    horaFinal,                  // Hora de Salida
                    {static_cast<short>(dateInfo.tm_year + 1900),static_cast<short>(dateInfo.tm_mon + 1),static_cast<short>(dateInfo.tm_mday)},   // Fecha
                    0.0                         // Costo inicial
                };

                // Guardar la sesión en el registro global de sesiones
                g_registroSesiones.push(g_registroSesiones.createEntry(nuevaSesion));

                // Asociar la sesión actual con la computadora
                computadora->data.sesionActiva = &g_registroSesiones.head->data;

                // Guardar el tiempo de inicio en tiempo real
                computadora->data.tiempoInicioReal = std::chrono::steady_clock::now();

                // ************ PARTE INTERFAZ ************
                printRectangle({ 7,21 }, 35, 25, color::dBlack);                                                // Reset background
                printFormat(formattedText::Elements::sesionAsignada, { 8,21 }, color::dBlack, color::dYellow);  // Print flavor element

                gotoCOORD({ 12,32 }); printColor("Se ha iniciado una sesion.", color::bYellow, color::dBlack);
                gotoCOORD({ 12,33 }); printColor("- Computadora (ID): ", color::bYellow, color::dBlack); std::cout << computadora->data.ID;
                gotoCOORD({ 12,34 }); printColor("- Cliente: ", color::bYellow, color::dBlack); std::cout << cliente;

                _getch();
                // END

            }
            break;
            case 3:
                break;
            }
        }
        break;
        case 2:     // ******************* Terminar Sesion *******************
        {
            printRectangle({ 7,21 }, 35, 25, color::dBlack);
            printFormat(formattedText::Elements::terminarSesion, { 8,21 }, color::dBlack, color::dYellow);
            gotoCOORD({ 12,32 }); printColor("Elija una computadora con", color::bYellow, color::dBlack);
            gotoCOORD({ 16,33 }); printColor("una sesion activa", color::bYellow, color::dBlack);

            do
            {
                int idSelector{ selectComputer(g_registroComputadoras,{55,13},8,4) };
                if (!idSelector) break;
                // Computer Info & Operations
                DoubleList<Computadora>::Node* target{ g_registroComputadoras.getAt(idSelector - 1) };

                if (target->data.estado != 1)   // Si no está en uso
                {
                    printRectangle({ 7,28 }, 35, 18, color::dBlack);
                    gotoCOORD({ 12,32 }); printColor("La computadora elegida", color::bYellow, color::dBlack);
                    gotoCOORD({ 12,33 }); printColor("no se encuentra en uso", color::bYellow, color::dBlack);
                }
                else
                {
                    // Obtener la sesión activa de la computadora
                    Sesion* sesionActual = target->data.sesionActiva;

                    // Actualizar la hora de salida de la sesión
                    std::time_t currentDate{}; std::time(&currentDate);
                    std::tm dateInfo{};
                    localtime_s(&dateInfo, &currentDate);

                    Hora horaActual{ static_cast<short>(dateInfo.tm_hour),static_cast<short>(dateInfo.tm_min) };
                    sesionActual->horaSalida = horaActual;

                    // Calcular el tiempo real transcurrido
                    auto tiempoFinReal = std::chrono::steady_clock::now();
                    auto tiempoTranscurridoReal = std::chrono::duration_cast<std::chrono::seconds>(tiempoFinReal - target->data.tiempoInicioReal).count();

                    // Convertir el tiempo real a tiempo del programa
                    int tiempoProgramadoHoras = tiempoTranscurridoReal / 60; // 1 minuto real = 1 hora en el programa
                    int tiempoProgramadoMinutos = tiempoTranscurridoReal % 60; // 1 segundo real = 1 minuto en el programa

                    // Actualizar el estado de la computadora
                    target->data.estado = 0; // La computadora ya está libre
                    target->data.sesionActiva = nullptr;

                    // ************ PARTE INTERFAZ ************
                    printRectangle({ 7,21 }, 35, 25, color::dBlack);
                    gotoCOORD({ 12,32 }); printColor("Se termino la sesion de", color::bYellow, color::dBlack);
                    gotoCOORD({ 12,33 }); printColor("la computadora elegida", color::bYellow, color::dBlack);
                    gotoCOORD({ 12,34 }); printColor("- Tiempo: ", color::bYellow, color::dBlack);
                    if (tiempoProgramadoHoras < 10) std::cout << "0";
                    std::cout << tiempoProgramadoHoras << ":";
                    if (tiempoProgramadoMinutos < 10) std::cout << "0";
                    std::cout << tiempoProgramadoMinutos;

                    _getch();
                }

            } while (1);
        }
        break;
        case 3:
            continueSelection = false;
            break;
        }
    }

    gotoCOORD({ 0,0 });
    printColor(menuDefs::background, color::dBlack, color::bBlack);
}

// ************ AGREGADO PARA N4 ************

bool VerificarConflicto(const Fecha& fechaSesion, const Hora& horaInicioSesion, const Hora& horaFinSesion, const Computadora& computadora) {

    SingleList<Reserva>::Node* nodoActual = computadora.colaReservas.head;// Obtener la cabeza de la lista de reservas de la computadora

    while (nodoActual) { // Recorrer la lista de reservas mientras haya reservas
        const Reserva& reserva = nodoActual->data; // Obtener los datos de la reserva actual

        if (fechaSesion.year == reserva.fecha.year && fechaSesion.month == reserva.fecha.month && fechaSesion.day == reserva.fecha.day) {

            bool hayConflicto = false; // Inicialización de variable la variable para detectar conflicto

            if (horaInicioSesion.hour < reserva.horaFinal.hour ||  // La sesión empieza antes de que la reserva termine
                (horaInicioSesion.hour == reserva.horaFinal.hour && horaInicioSesion.minute < reserva.horaFinal.minute)) {

                if (horaFinSesion.hour > reserva.horaInicio.hour ||  // La sesión termina después de que la reserva empieza
                    (horaFinSesion.hour == reserva.horaInicio.hour && horaFinSesion.minute > reserva.horaInicio.minute)) {

                    hayConflicto = true; // Se detectó un conflicto
                }
            }

            if (hayConflicto) { // Si hay conflicto, no se puede crear la sesión
                return false; // Retorna false indicando que hay un conflicto
            }
        }

        nodoActual = nodoActual->next; // Pasar al siguiente nodo de la lista
    }

    return true; // Si no hay conflicto, retornar true

}