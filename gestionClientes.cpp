// Includes
#include <iostream>

#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "gestionClientes.h"
#include "global.h"
// *************************************** Variables ***************************************

extern std::map<std::string, int> horasConteo;
extern std::map<std::string, double> gastosTotales;

// *************************************** Funciones ***************************************

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
        case 1:             // ******************************************* Comenzar Sesion *******************************************
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
                }
#ifdef ADDED_PARTS
                while (computadora->data.estado != 0 ||
                    !verificarConflicto(/* Sesión que estás creando */, computadora->data.colaReservas)); // Verifica conflicto
#endif // ADDED_PARTS
#ifndef ADDED_PARTS
                while (computadora->data.estado != 0);
#endif // !ADDED_PARTS

                
                
                
                // *********************************** FIN AGREGADO PARA N4 ********************************

                computadora->data.estado = 1;                       // Cambia el estado a "Ocupado"
                std::string cliente{ nombresClientes[rand() % 20] };// Se usa 20 porque solo existen 20 nombres, no hay otra forma :p

                std::time_t currentDate{}; std::time(&currentDate); //
                std::tm dateInfo{};                                 //  Usado para obtener la Hora (y Fecha)
                localtime_s(&dateInfo, &currentDate);               //

                SingleList<Sesion>::Node* entry{ g_registroSesiones.createEntry(     // Creamos la sesion y la almacenamos en el registro global de sesiones (o algo asi)
                    {
                        computadora->data.ID,       // ID Computadora
                        0,                          // ID Cliente, 0 porque no se usa el struct de cliente (?) pd:necesita fix
                        {static_cast<short>(dateInfo.tm_hour),static_cast<short>(dateInfo.tm_min)}, // Hora de Inicio (static cast porque use short en lugar de int :c)
                        {23,59},                    // Hora de Salida, como es hora libre, la seteamos al maximo (solo acaba cuando el gerente dice que acaba, a menos que acabe el dia primero)
                        {static_cast<short>(dateInfo.tm_year + 1900),static_cast<short>(dateInfo.tm_mon),static_cast<short>(dateInfo.tm_mday)},   // Fecha (largaso por mi error del short :c)
                        0.0                         // Costo (en 0 porque todavia no finalizo la sesion :p)
                    }
                ) };


                g_registroSesiones.push(g_registroSesiones.createEntry(     // Creamos la sesion y la almacenamos en el registro global de sesiones (o algo asi)
                    {
                        computadora->data.ID,       // ID Computadora
                        0,                          // ID Cliente, 0 porque no se usa el struct de cliente (?) pd:necesita fix
                        {static_cast<short>(dateInfo.tm_hour),static_cast<short>(dateInfo.tm_min)}, // Hora de Inicio (static cast porque use short en lugar de int :c)
                        {23,59},                    // Hora de Salida, como es hora libre, la seteamos al maximo (solo acaba cuando el gerente dice que acaba, a menos que acabe el dia primero)
                        {static_cast<short>(dateInfo.tm_year+1900),static_cast<short>(dateInfo.tm_mon),static_cast<short>(dateInfo.tm_mday)},   // Fecha (largaso por mi error del short :c)
                        0.0                         // Costo (en 0 porque todavia no finalizo la sesion :p)
                    }
                ));     // Para mas detalles ver la definicion del struct en "tempFile.h" de "Sesion" y la definicion de las listas en el mismo archivo

                // *********************************** PARTE INTERFAZ ***********************************
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
            case 2:         // Asignar computadora por hora
            {
                printRectangle({ 7,21 }, 35, 25, color::dBlack);                                                // Reset background
                printFormat(formattedText::Elements::introducirHora, { 8,23 }, color::dBlack, color::dYellow);

                size_t sizeRegistro{ g_registroComputadoras.getSize() };                    // Numero de Computadoras en Registro
                Hora definirHora{ getHora({17,28},true) };                                  // Obtener la Hora usando una funcion bonita c:
                DoubleList<Computadora>::Node* computadora{ g_registroComputadoras.head };  // Crea un puntero de "recorrido" usando la cabeza del registro global de computadoras

                int pc;
                srand(time(nullptr));
                do {
                    pc = rand() % sizeRegistro;
                    computadora = g_registroComputadoras.getAt(pc);
                } while (computadora->data.estado != 0); // Buscar por computadora Libre   NOTA: VA A ITERAR INFINITAMENTE SI NO EXISTE COMPUTADORA LIBRE (ARREGLAR ESO PORFA)
                
                computadora->data.estado = 1;                       // Cambia el estado a "Ocupado"
                std::string cliente{ nombresClientes[rand() % 20] };// Se usa 20 porque solo existen 20 nombres, no hay otra forma :p

                std::time_t currentDate{}; std::time(&currentDate); //
                std::tm dateInfo{};                                 //  Usado para obtener la Hora (y Fecha)
                localtime_s(&dateInfo, &currentDate);               //
                
                Hora horaInicio{ static_cast<short>(dateInfo.tm_hour),static_cast<short>(dateInfo.tm_min) };
                Hora horaFinal{horaInicio};
                horaFinal.minute += definirHora.minute;
                if (horaFinal.minute >= 60)
                {
                    horaFinal.minute -= 60;
                    ++horaFinal.hour;
                } horaFinal.hour += definirHora.hour;               // Obtener Hora Final
                
                
                g_registroSesiones.push(g_registroSesiones.createEntry(     // Creamos la sesion y la almacenamos en el registro global de sesiones (o algo asi)
                    {
                        computadora->data.ID,       // ID Computadora
                        0,                          // ID Cliente, 0 porque no se usa el struct de cliente (?) pd:necesita fix
                        horaInicio, // Hora de Inicio (static cast porque use short en lugar de int :c)
                        horaFinal,                    // Hora de Salida, como es hora libre, la seteamos al maximo (solo acaba cuando el gerente dice que acaba, a menos que acabe el dia primero)
                        {static_cast<short>(dateInfo.tm_year + 1900),static_cast<short>(dateInfo.tm_mon),static_cast<short>(dateInfo.tm_mday)},   // Fecha (largaso por mi error del short :c)
                        0.0                         // Tarifaaaaaaaaaaaaaaaa, osea, esta por hacer :p, este si debe de tener tarifa definida asi que les encargo.
                                                    // La ecuacion debe ser algo tipo "g_mainTarifa * modPrecio * horas", pero no toma en cuenta los minutos, si pueden hacerlo piola
                    }
                ));     // Para mas detalles ver la definicion del struct en "tempFile.h" de "Sesion" y la definicion de las listas en el mismo archivo

                // *********************************** PARTE INTERFAZ ***********************************
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
            case 3:
                break;
            }
        }
        break;
        case 2:     // ******************************************************* Eliminar Sesion *******************************************************
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

                if (target->data.estado != 1)   // Si no esta en uso
                {
                    printRectangle({ 7,28 }, 35, 18, color::dBlack);
                    gotoCOORD({ 12,32 }); printColor("La computadora elegida", color::bYellow, color::dBlack);
                    gotoCOORD({ 12,33 }); printColor("no se encuentra en uso", color::bYellow, color::dBlack);
                }
                else
                {

                    //time_t fin = time(0);
                    //double tiempoUsado = difftime(fin, computadoras[pc].inicio) / 60;
                    //double monto = tiempoUsado * computadoras[pc].tarifa;

                    //computadoras[pc].ocupada = false;
                    //horasConteo[computadoras[pc].cliente] += tiempoUsado / 60;
                    //gastosTotales[computadoras[pc].cliente] += monto;

                    //guardarGastos();
                    //guardarHoras();

                    //cout << "El cliente " << computadoras[pc].cliente << " ha finalizado su tiempo en la PC " << (pc + 1) << endl;
                    //cout << "Tiempo usado: " << tiempoUsado << " minutos\n";
                    //cout << "Monto a cobrar: S/." << monto << endl;

                    target->data.estado = 0; // La computadora ya esta libre

                    // Por hacer:
                    //  - Calcular tarifa y almacenarla en la sesion con la id de la computadora
                    //  - Reagregar el guardado por archivos
                    //  - Guardar hora final en el registro de sesiones
                    //  - Implementar Clientes (no se como hacerlo xd)
                    //

                    printRectangle({ 7,21 }, 35, 25, color::dBlack);
                    gotoCOORD({ 12,32 }); printColor("Se termino la sesion de", color::bYellow, color::dBlack);
                    gotoCOORD({ 12,33 }); printColor("la computadora elegida", color::bYellow, color::dBlack);
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

// *********************************** AGREGADO PARA N4 ***********************************


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



// ************************************************************************** REFERENCIA **************************************************************************

/*
using namespace std;

void cargarEstado() {
    ifstream file("clientes.txt");
    for (int i = 0; i < 20 && file; i++) {
        file >> computadoras[i].cliente >> computadoras[i].ocupada;
        file >> computadoras[i].inicio >> computadoras[i].total;
    }
    file.close();
}

void guardarEstado() {
    ofstream file("clientes.txt");
    for (int i = 0; i < 20; i++) {
        file << computadoras[i].cliente << " " << computadoras[i].ocupada << " ";
        file << computadoras[i].inicio << " " << computadoras[i].total << endl;
    }
    file.close();
}

void cargarHoras() {
    ifstream file("horasconteo.txt");
    if (!file) return;
    string cliente;
    int horas;
    while (file >> cliente >> horas) {
        horasConteo[cliente] = horas;
    }
    file.close();
}

void guardarHoras() {
    ofstream file("horasconteo.txt");
    for (const auto& pair : horasConteo) {
        file << pair.first << " " << pair.second << endl;
    }
    file.close();
}

void cargarGastos() {
    ifstream file("gastos.txt");
    if (!file) return;
    string cliente;
    double gasto;
    while (file >> cliente >> gasto) {
        gastosTotales[cliente] = gasto;
    }
    file.close();
}

void guardarGastos() {
    ofstream file("gastos.txt");
    for (const auto& pair : gastosTotales) {
        file << pair.first << " " << pair.second << endl;
    }
    file.close();
}

void horasGratis() {
    vector<string> clientesConHorasGratis;
    for (const auto& pair : horasConteo) {
        if (pair.second >= 5) {
            clientesConHorasGratis.push_back(pair.first);
        }
    }

    if (clientesConHorasGratis.empty()) {
        cout << "No hay clientes con horas acumuladas suficientes para horas gratis.\n";
        return;
    }

    srand(time(0));
    string clienteSeleccionado = clientesConHorasGratis[rand() % clientesConHorasGratis.size()];
    cout << "El cliente " << clienteSeleccionado << " ha recibido una hora gratis.\n";
    horasConteo[clienteSeleccionado] -= 5;

    ofstream file("horasfree.txt", ios::app);
    file << clienteSeleccionado << " ha recibido una hora gratis.\n";
    file.close();
}

void observarRegistros() {
    cout << left << setw(25) << "Nombre del Cliente"
        << setw(20) << "Horas Alquiladas"
        << setw(25) << "Horas Gratis Disponibles"
        << setw(20) << "Total Gastado" << endl;
    cout << string(90, '-') << endl;

    for (const auto& cliente : nombresClientes) {
        int horasGratis = horasConteo[cliente];
        double totalGastado = gastosTotales[cliente];
        cout << left << setw(25) << cliente
            << setw(20) << horasConteo[cliente]
            << setw(25) << horasGratis
            << setw(20) << totalGastado << endl;
    }
}
*/
