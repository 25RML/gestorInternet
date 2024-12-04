// Includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <string>

#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "tempFile.h"
#include "reportes.h"   
#include "global.h"

#include <filesystem> // Para trabajar con directorios
// *************************************** Funciones ***************************************

void mainReportes()
{
    gotoCOORD({ 0, 0 });
    // Imprimir Menus
    printColor(menuDefs::background, color::dBlack, color::bBlack);     // Reset Background
    printWindow(27, 18, { 7,13 }, color::dBlack, color::dPurple);       // Imprimir ventana de Operaciones
    printWindow(100, 35, { 48,6 }, color::dBlack, color::bYellow);      // Imprimir ventana de vista
    printWindow(64, 2, { 68,5 }, color::bYellow, color::dYellow);       // Ventana de Titulo
    gotoCOORD({ 91,6 }); printColor("\033[4mCREACION DE REPORTES\033[0m", color::dBlack, color::bYellow);   // Titulo

    gotoCOORD({ 0,0 }); // Estetico solamente, volver a 0,0
    int inputSelection{ 0 };
    bool continueSelection{ true };
    while (continueSelection)
    {
        selectionMaps::g_reportesMap.printAll();
        inputSelection = selectionMaps::g_reportesMap.startSelection(true);
        switch (inputSelection)
        {
        case 1: // Crear Reporte de Uso
            do
            {
                printRectangle({ 49,9 }, 98, 32, color::dBlack);

                int idSelector{ selectComputer(g_registroComputadoras,{52,11},8,4) };
                if (!idSelector) break;

                DoubleList<Computadora>::Node* node{ g_registroComputadoras.getAt(idSelector - 1) };
                if (!node) break;  // Validar puntero nulo

                Computadora& target = node->data; // Acceso directo al objeto

                printRectangle({ 49,9 }, 98, 32, color::dBlack);
                printFormat(formattedText::Elements::computerInfo, { 78,15 }, color::dBlack, color::dBlue);
                mostrarInformacionComputadora(node, { 78,19 });

                selectionMaps::g_reportesConfirmationMap.printAll();
                int createTxtQuestion{ selectionMaps::g_reportesConfirmationMap.startSelection(true) };
                if (createTxtQuestion == 2) continue;

                // Crear Reporte
                generarReporteUsoTxt(&target, g_registroSesiones);
                printRectangle({ 49,9 }, 98, 32, color::dBlack);
                gotoCOORD({ 75,24 }); printColor("Reporte de uso generado exitosamente en carpeta correspondiente.", color::bYellow);

                break;
            } while (1);
            break;

        case 2: // Crear Reporte de Ingresos
            do
            {
                printRectangle({ 49,9 }, 98, 32, color::dBlack);

                int idSelector{ selectComputer(g_registroComputadoras,{52,11},8,4) };
                if (!idSelector) break;

                DoubleList<Computadora>::Node* node{ g_registroComputadoras.getAt(idSelector - 1) };
                if (!node) break;  // Validar puntero nulo

                Computadora& target = node->data; // Acceso directo al objeto

                printRectangle({ 49,9 }, 98, 32, color::dBlack);
                printFormat(formattedText::Elements::computerInfo, { 78,15 }, color::dBlack, color::dBlue);
                mostrarInformacionComputadora(node, { 78,19 });

                selectionMaps::g_reportesConfirmationMap.printAll();
                int createTxtQuestion{ selectionMaps::g_reportesConfirmationMap.startSelection(true) };
                if (createTxtQuestion == 2) continue;

                // Crear Reporte
                generarReporteIngresosTxt(&target, g_registroSesiones);
                printRectangle({ 49,9 }, 98, 32, color::dBlack);
                gotoCOORD({ 75,24 }); printColor("Reporte de ingresos generado exitosamente en carpeta correspondiente.", color::bYellow);

                break;
            } while (1);
            break;

        case 3: // Salir
            continueSelection = false;
            break;
        }
    }

    gotoCOORD({ 0,0 });
    printColor(menuDefs::background, color::dBlack, color::bBlack);
}



// Generar reporte de uso en archivo .txt
void generarReporteUsoTxt(Computadora* comp, SingleList<Sesion>& sesiones) {
    // Rutas de carpetas
    std::string basePath = "Reportes/ReporteDeUsos/";
    std::string folderPath = basePath + "Computadora_" + std::to_string(comp->ID);

    // Crear carpetas si no existen
    std::filesystem::create_directories(folderPath);

    // Crear archivo en la carpeta correspondiente
    std::string filename = folderPath + "/ReporteUso_" + std::to_string(comp->ID) + ".txt";
    std::ofstream file(filename);

    if (file.is_open()) {
        file << "Reporte de Uso de Computadora ID: " << comp->ID << "\n";
        file << "Estado: " << comp->estado << " (0: Libre, 1: Ocupada, 2: Reservada, 3: No Disponible)\n";
        file << "Tiempo de Uso Total: " << comp->tiempoDeUsoTotalSegundos << " horas\n\n";

        auto actual = sesiones.head;
        if (!actual) {
            file << "No hay sesiones registradas.\n";
        }
        else {
            while (actual) {
                file << "Fecha: " << actual->data.fecha.day << "/" << actual->data.fecha.month << "/" << actual->data.fecha.year
                    << ", Hora Inicio: " << actual->data.horaInicio.hour << ":" << actual->data.horaInicio.minute
                    << ", Hora Salida: " << actual->data.horaSalida.hour << ":" << actual->data.horaSalida.minute
                    << ", Costo: $" << std::fixed << std::setprecision(2) << actual->data.costo << "\n";
                actual = actual->next;
            }
        }

        file.close();
    }
}

// Generar reporte de ingresos en archivo .txt
void generarReporteIngresosTxt(Computadora* comp, SingleList<Sesion>& sesiones) {
    // Rutas de carpetas
    std::string basePath = "Reportes/ReporteDeIngresos/";
    std::string folderPath = basePath + "Computadora_" + std::to_string(comp->ID);

    // Crear carpetas si no existen
    std::filesystem::create_directories(folderPath);

    // Crear archivo en la carpeta correspondiente
    std::string filename = folderPath + "/ReporteIngresos_" + std::to_string(comp->ID) + ".txt";
    std::ofstream file(filename);

    if (file.is_open()) {
        file << "Reporte de Ingresos de Computadora ID: " << comp->ID << "\n\n";

        double totalIngresos = 0.0;
        auto actual = sesiones.head;  // Asegúrate de que `head` sea un miembro.
        if (!actual) {
            file << "No hay sesiones registradas.\n";
        }
        else {
            while (actual) {
                totalIngresos += actual->data.costo;
                file << "Fecha: " << actual->data.fecha.day << "/" << actual->data.fecha.month << "/" << actual->data.fecha.year
                    << ", Ingreso: $" << std::fixed << std::setprecision(2) << actual->data.costo << "\n";
                actual = actual->next;
            }
        }

        file << "\nTotal de Ingresos: $" << std::fixed << std::setprecision(2) << totalIngresos << "\n";
        file.close();
    }
}
