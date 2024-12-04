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

// Función para terminar sesión de forma automática (para hora fija)
void autoTerminateSession(int computerID, std::time_t start_time, Hora duration)
{
    // Map program duration to real-life time
    // Real-life minutes = program hours
    // Real-life seconds = program minutes
    int real_life_seconds = duration.hour * 60 + duration.minute;

    // Sleep for the mapped real-life time
    std::this_thread::sleep_for(std::chrono::seconds(real_life_seconds));

    // After sleep, terminate the session
    // Access the global registroComputadoras y registroSesiones
    // Find the Sesion with computerID and matching start_time
    SingleList<Sesion>::Node* current = g_registroSesiones.head;
    Sesion* sesionTerminar = nullptr;
    while (current)
    {
        if (current->data.idComputadora == computerID &&
            current->data.start_time == start_time &&
            current->data.is_fixed_duration)
        {
            sesionTerminar = &current->data;
            break;
        }
        current = current->next;
    }

    if (sesionTerminar)
    {
        // Terminar la sesión
        sesionTerminar->horaSalida = sesionTerminar->horaInicio;
        sesionTerminar->horaSalida.sumarTiempo(duration);
        sesionTerminar->costo = g_mainTarifa * duration.hour + (g_mainTarifa / 60.0) * duration.minute; // Ajustar según la fórmula de costo real

        // Actualizar estado de la computadora
        DoubleList<Computadora>::Node* computerNode = g_registroComputadoras.getAt(computerID - 1);
        if (computerNode)
        {
            computerNode->data.estado = 0;
            computerNode->data.tiempoDeUsoTotalSegundos += duration.hour * 3600 + duration.minute * 60;
        }

        // Guardar sesiones
        guardarSesiones();

        // Mostrar mensaje opcional
        // Por ejemplo, imprimir en consola que la sesión ha terminado automáticamente
        // Puedes implementar una forma de notificar al usuario que la sesión ha terminado
    }
}

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
                srand(static_cast<unsigned int>(time(nullptr)));
                do {
                    pc = rand() % static_cast<int>(sizeRegistro);
                    computadora = g_registroComputadoras.getAt(pc);
                    if (!computadora) break; // Evitar punteros nulos
                } while (computadora->data.estado != 0); // No verificar conflicto en "hora libre"

                if (!computadora) {
                    gotoCOORD({ 12,32 }); printColor("No hay computadoras disponibles.", color::bRed, color::dBlack);
                    _getch();
                    break;
                }

                computadora->data.estado = 1;                       // Cambia el estado a "Ocupado"
                std::string cliente{ "Cliente" + std::to_string(rand() % 1000) }; // Genera un nombre de cliente genérico

                std::time_t currentDate{}; std::time(&currentDate); //
                std::tm dateInfo{};                                 //  Usado para obtener la Hora (y Fecha)
                localtime_s(&dateInfo, &currentDate);               //

                // Crear la Sesion
                Sesion nuevaSesion{
                    computadora->data.ID,       // ID Computadora
                    0,                          // ID Cliente, 0 porque no se usa el struct de cliente (?) pd:necesita fix
                    {static_cast<short>(dateInfo.tm_hour),static_cast<short>(dateInfo.tm_min)}, // Hora de Inicio (static cast porque use short en lugar de int :c)
                    {23,59},                    // Hora de Salida, como es hora libre, la seteamos al maximo (solo acaba cuando el gerente dice que acaba, a menos que acabe el dia primero)
                    {static_cast<short>(dateInfo.tm_year + 1900),static_cast<short>(dateInfo.tm_mon + 1),static_cast<short>(dateInfo.tm_mday)},   // Fecha (corregido tm_mon +1)
                    0.0,                         // Costo (en 0 porque todavia no finalizo la sesion :p)
                    currentDate,                 // start_time
                    false,                       // is_fixed_duration
                    {0,0}                         // fixed_duration
                };

                // Agregar la sesión al registro
                g_registroSesiones.push(g_registroSesiones.createEntry(nuevaSesion));

                // ************ PARTE INTERFAZ ************
                printRectangle({ 7,21 }, 35, 25, color::dBlack);                                                // Reset background
                printFormat(formattedText::Elements::sesionAsignada, { 8,21 }, color::dBlack, color::dYellow);  // Print flavor element

                gotoCOORD({ 12,32 }); printColor("Se ha iniciado una sesion.", color::bYellow, color::dBlack);
                gotoCOORD({ 12,33 }); printColor("- Computadora (ID): ", color::bYellow, color::dBlack); std::cout << computadora->data.ID;
                gotoCOORD({ 12,34 }); printColor("- Cliente: ", color::bYellow, color::dBlack); std::cout << cliente;

                //
                //      Si pueden hacer que se imprima la hora como en el programa que enviaron seria excelente, pero si no, no hay problema
                //

                _getch();
                // END
            }
            break;
            case 2:         // Asignar computadora por hora fija
            {
                printRectangle({ 7,21 }, 35, 25, color::dBlack);                                                // Reset background
                printFormat(formattedText::Elements::introducirHora, { 8,23 }, color::dBlack, color::dYellow);

                size_t sizeRegistro{ g_registroComputadoras.getSize() };                    // Numero de Computadoras en Registro
                Hora definirHora{ getHora({17,28}, true) };                                  // Obtener la Hora usando una funcion bonita c:
                DoubleList<Computadora>::Node* computadora{ g_registroComputadoras.head };  // Crea un puntero de "recorrido" usando la cabeza del registro global de computadoras

                int pc;
                srand(static_cast<unsigned int>(time(nullptr)));
                do {
                    pc = rand() % static_cast<int>(sizeRegistro);
                    computadora = g_registroComputadoras.getAt(pc);
                    if (!computadora) break; // Evitar punteros nulos
                } while (computadora->data.estado != 0); // Buscar por computadora Libre   NOTA: VA A ITERAR INFINITAMENTE SI NO EXISTE COMPUTADORA LIBRE (ARREGLAR ESO PORFA)

                if (!computadora) {
                    gotoCOORD({ 12,32 }); printColor("No hay computadoras disponibles.", color::bRed, color::dBlack);
                    _getch();
                    break;
                }

                computadora->data.estado = 1;                       // Cambia el estado a "Ocupado"
                std::string cliente{ "Cliente" + std::to_string(rand() % 1000) }; // Genera un nombre de cliente genérico

                std::time_t currentDate{}; std::time(&currentDate); //
                std::tm dateInfo{};                                 //  Usado para obtener la Hora (y Fecha)
                localtime_s(&dateInfo, &currentDate);               //

                Hora horaInicio{ static_cast<short>(dateInfo.tm_hour),static_cast<short>(dateInfo.tm_min) };
                Hora horaFinal{ horaInicio };
                horaFinal.sumarTiempo(definirHora);               // Obtener Hora Final

                // Crear la Sesion con hora fija
                Sesion nuevaSesion{
                    computadora->data.ID,       // ID Computadora
                    0,                          // ID Cliente, 0 porque no se usa el struct de cliente (?) pd:necesita fix
                    horaInicio, // Hora de Inicio (static cast porque use short en lugar de int :c)
                    horaFinal,                    // Hora de Salida, como es hora fija
                    {static_cast<short>(dateInfo.tm_year + 1900),static_cast<short>(dateInfo.tm_mon + 1),static_cast<short>(dateInfo.tm_mday)},   // Fecha (corregido tm_mon +1)
                    0.0,                         // Costo (a definir)
                    currentDate,                 // start_time
                    true,                        // is_fixed_duration
                    definirHora                  // fixed_duration
                };

                // Agregar la sesión al registro
                g_registroSesiones.push(g_registroSesiones.createEntry(nuevaSesion));

                // Iniciar el hilo para auto-terminar la sesión
                std::thread(autoTerminateSession, computadora->data.ID, currentDate, definirHora).detach();

                // ************ PARTE INTERFAZ ************
                printRectangle({ 7,21 }, 35, 25, color::dBlack);                                                // Reset background
                printFormat(formattedText::Elements::sesionAsignada, { 8,21 }, color::dBlack, color::dYellow);  // Print flavor element

                gotoCOORD({ 12,32 }); printColor("Se ha iniciado una sesion con hora fija.", color::bYellow, color::dBlack);
                gotoCOORD({ 12,33 }); printColor("- Computadora (ID): ", color::bYellow, color::dBlack); std::cout << computadora->data.ID;
                gotoCOORD({ 12,34 }); printColor("- Cliente: ", color::bYellow, color::dBlack); std::cout << cliente;
                gotoCOORD({ 12,35 }); printColor("- Duracion: ", color::bYellow, color::dBlack); std::cout << definirHora.hour << " hora(s) - " << definirHora.minute << " minuto(s)";

                //
                //      Si pueden hacer que se imprima la hora como en el programa que enviaron seria excelente, pero si no, no hay problema
                //

                _getch();
                // END
            }
            break;
            case 3:
                break;
            }
        }
        break;
        case 2:     // ******************* Eliminar Sesion *******************
        {
            printRectangle({ 7,21 }, 35, 25, color::dBlack);
            printFormat(formattedText::Elements::terminarSesion, { 8,21 }, color::dBlack, color::dYellow);
            gotoCOORD({ 12,32 }); printColor("Elija una computadora con", color::bYellow, color::dBlack);
            gotoCOORD({ 16,33 }); printColor("una sesion activa", color::bYellow, color::dBlack);

            bool sessionFound = false;

            do
            {
                int idSelector{ selectComputer(g_registroComputadoras,{55,13},8,4) };
                if (!idSelector) break;
                // Computer Info & Operations
                DoubleList<Computadora>::Node* target{ g_registroComputadoras.getAt(idSelector - 1) };

                if (target->data.estado != 1)   // Si no esta en uso
                {
                    printRectangle({ 7,28 }, 35, 18, color::dBlack);
                    gotoCOORD({ 12,32 }); printColor("La computadora elegida", color::bYellow, color::dBlack);
                    gotoCOORD({ 12,33 }); printColor("no se encuentra en uso", color::bYellow, color::dBlack);
                }
                else
                {

                    target->data.estado = 0; // La computadora ya esta libre

                    // Calcular tiempo usado
                    std::time_t end_time = std::time(nullptr);
                    SingleList<Sesion>::Node* current = g_registroSesiones.head;
                    Sesion* sesionTerminar = nullptr;
                    while (current)
                    {
                        if (current->data.idComputadora == idSelector &&
                            ((current->data.is_fixed_duration) ||
                                (!current->data.is_fixed_duration && current->data.horaSalida.hour == 23 && current->data.horaSalida.minute == 59)))
                        {
                            sesionTerminar = &current->data;
                            break;
                        }
                        current = current->next;
                    }

                    if (sesionTerminar)
                    {
                        // Calcular tiempo transcurrido
                        int elapsed_seconds = static_cast<int>(difftime(end_time, sesionTerminar->start_time));
                        short elapsed_hours = elapsed_seconds / 60; // real-life minutes to program hours
                        short elapsed_minutes = elapsed_seconds % 60; // real-life seconds to program minutes

                        // Asignar hora de salida
                        sesionTerminar->horaSalida.hour = (sesionTerminar->horaInicio.hour + elapsed_hours) % 24;
                        sesionTerminar->horaSalida.minute = (sesionTerminar->horaInicio.minute + elapsed_minutes) % 60;

                        // Calcular costo (ajustar según la tarifa)
                        sesionTerminar->costo = g_mainTarifa * elapsed_hours + (g_mainTarifa / 60.0) * elapsed_minutes; // Ajustar según la fórmula de costo real

                        // Actualizar tiempo de uso total de la computadora
                        target->data.tiempoDeUsoTotalSegundos += elapsed_hours * 3600 + elapsed_minutes * 60;

                        // Mostrar mensaje con tiempo
                        printRectangle({ 7,21 }, 35, 25, color::dBlack);
                        if (sesionTerminar->is_fixed_duration) {
                            gotoCOORD({ 12,32 }); printColor("Se termino la sesion de la computadora - tiempo interrumpido ", color::bYellow, color::dBlack);
                            std::cout << elapsed_hours << " hora(s) - " << elapsed_minutes << " minuto(s)" << std::endl;
                        }
                        else {
                            gotoCOORD({ 12,32 }); printColor("Se termino la sesion de la computadora elegida - ", color::bYellow, color::dBlack);
                            std::cout << elapsed_hours << " hora(s) - " << elapsed_minutes << " minuto(s)" << std::endl;
                        }

                        // Actualizar gastos y horas si es necesario
                        // Aquí se debería actualizar las estructuras de clientes si están implementadas

                        // Guardar datos (si es necesario)
                        guardarSesiones(); // Implementar la llamada para guardar inmediatamente

                        sessionFound = true;
                        break; // Salir del bucle después de terminar la sesión
                    }
                    else
                    {
                        gotoCOORD({ 112,32 }); printColor("No se encontró la sesión a terminar.", color::bRed, color::dBlack);
                    }

                }

            } while (!sessionFound);

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
