// Includes
#include <windows.h>
#include <iostream>
#include <ctime>
//#include <utility>

#include "interface.h"
#include "tempFile.h"
/*================================================================================================================================================================
                        GLOBAL VARIABLES
================================================================================================================================================================*/



HANDLE hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };
/*================================================================================================================================================================
                        NAMESPACES
================================================================================================================================================================*/
namespace selectionMaps
{
    // UPDATED
    namespace MainMenu
    {
        const Button gestionDeComputadoras{ instDisplaySet<3>(formattedText::gestionDeComputadoras),{54,15}, primaryColorSet };
        const Button gestionDeSesiones{ instDisplaySet<3>(formattedText::gestionDeSesiones),{54,20}, primaryColorSet };
        const Button gestionDeClientes{ instDisplaySet<3>(formattedText::gestionDeClientes),{54,25}, primaryColorSet };
        const Button facturacion{ instDisplaySet<3>(formattedText::facturacion),{54,30}, primaryColorSet };
        const Button reservas{ instDisplaySet<3>(formattedText::reservas),{54,35}, primaryColorSet };
        const Button reportes{ instDisplaySet<3>(formattedText::reportes),{54,40}, primaryColorSet };
        const Button salir{ instDisplaySet<3>(formattedText::salir),{115,38}, secondaryColorSet };
    }
    namespace Reservas
    {
        const Button hacerReservas{ instDisplaySet<3>(formattedText::hacerReserva),{9,6}, ternaryColorSet };
        const Button verHistorial{ instDisplaySet<3>(formattedText::verHistorial),{9,11}, ternaryColorSet };
        const Button volver{ instDisplaySet<3>(formattedText::volver),{10,16}, secondaryColorSet };

        const Button confirmReserva{ instDisplaySet<3>(formattedText::hacerReserva),{116,28}, primaryColorSet };
        const Button cancelarReserva{ instDisplaySet<3>(formattedText::volver),{117,35}, secondaryColorSet };

        namespace SubConfirmar
        {
            const Button confirmar{ instDisplaySet<3>(formattedText::hacerReserva),{116,37}, primaryColorSet };
            const Button volver{ instDisplaySet<3>(formattedText::volver),{117,41}, secondaryColorSet };
        }
    }
    namespace GestionComputadoras
    {
        const extern Button agregarComputadora{ instDisplaySet<3>(formattedText::agregarComputadora),{19,42},ternaryColorSet };
        const extern Button mostrarComputadora{ instDisplaySet<3>(formattedText::mostrarComputadora),{47,42},ternaryColorSet };
        const extern Button volverMenu{ instDisplaySet<3>(formattedText::volver),{74,42},secondaryColorSet };

        namespace SubAgregar
        {
            const extern Button confirmar{ instDisplaySet<3>(formattedText::confirmOperation),{50,30},primaryColorSet };
            const extern Button reintentar{ instDisplaySet<3>(formattedText::redoOperation),{75,30},primaryColorSet };
            const extern Button volver{ instDisplaySet<3>(formattedText::volver),{85,36},quaternaryColorSet };
        }
        namespace SubMostrar
        {
            const extern Button eliminar{ instDisplaySet<3>(formattedText::eliminar),{125,25},secondaryColorSet };
            const extern Button volver{ instDisplaySet<3>(formattedText::volver),{123,30},primaryColorSet };
        }   
    }
    namespace SimulacionClientes
    {
        const extern Button comenzarSesion{ instDisplaySet<3>(formattedText::comenzarSesion),{14,5},primaryColorSet };
        const extern Button terminarSesion{ instDisplaySet<3>(formattedText::terminarSesion),{14,9},primaryColorSet };
        const extern Button volverMenu{ instDisplaySet<3>(formattedText::volver),{15,13},secondaryColorSet };

        namespace SubComenzarSesion
        {
            const extern Button horaLibre{ instDisplaySet<3>(formattedText::horaLibre),{14,30},ternaryColorSet };
            const extern Button horaFija{ instDisplaySet<3>(formattedText::horaFija),{14,35},ternaryColorSet };
            const extern Button volver{ instDisplaySet<3>(formattedText::volver),{22,43},quaternaryColorSet };
        }
    }
    namespace Reportes
    {
        const extern Button generarReporteUso{ instDisplaySet<4>(formattedText::reporteUso),{10,15},primaryColorSet };
        const extern Button generarReporteIngresos{ instDisplaySet<4>(formattedText::reporteIngreso),{10,21},primaryColorSet };
        const extern Button volverMenu{ instDisplaySet<3>(formattedText::volver),{11,27},secondaryColorSet };

        namespace SubConfirmation
        {
            const extern Button generarTxt{ instDisplaySet<3>(formattedText::generarTxt), {70,36}, ternaryColorSet };
            const extern Button volver{ instDisplaySet<3>(formattedText::volver), {108,36}, secondaryColorSet };
        }
    }

    namespace Definitions
    {
        inline SelectionMap assignMainMenu()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(MainMenu::gestionDeComputadoras));
            map.append(map.createMember(MainMenu::gestionDeSesiones));
            map.append(map.createMember(MainMenu::gestionDeClientes));
            map.append(map.createMember(MainMenu::facturacion));
            map.append(map.createMember(MainMenu::reservas));
            map.append(map.createMember(MainMenu::reportes));
            map.append(map.createMember(MainMenu::salir));
            // Asignacion de Rutas
            SelectionMap::Member* end{ map.getAt(6) };
            SelectionMap::Member* target{ map.head };
            map.reset();
            map.traveler->linkTo(Direction::right, end,false);
            map.traveler->right->isReactive = true;
            for (int i{ 0 }; i < 5; ++i)
            {
                map.traveler = map.traveler->next;
                target->linkTo(Direction::down, map.traveler);
                target = target->next;
                map.traveler->linkTo(Direction::right, end,false);
            }
            map.reset();
            return map;
        }
        inline SelectionMap assignReservas()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(Reservas::hacerReservas));
            map.append(map.createMember(Reservas::verHistorial));
            map.append(map.createMember(Reservas::volver));
            // Asignacion de Rutas
            SelectionMap::Member* target{ map.head };
            map.reset();
            for (int i{ 0 }; i < 2; ++i)
            {
                map.traveler = map.traveler->next;
                target->linkTo(Direction::down, map.traveler);
                target = target->next;
            }
            map.reset();
            return map;
        }
        inline SelectionMap assignReservasConfirmation()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(Reservas::confirmReserva));
            map.append(map.createMember(Reservas::cancelarReserva));

            map.head->linkTo(Direction::down, map.head->next);

            map.reset();
            return map;
        }
        inline SelectionMap assignReservasContinue()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(Reservas::SubConfirmar::confirmar));
            map.append(map.createMember(Reservas::SubConfirmar::volver));

            map.head->linkTo(Direction::down, map.head->next);

            map.reset();
            return map;
        }
        inline SelectionMap assignOperacionesGestionComputadoras()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(GestionComputadoras::agregarComputadora));
            map.append(map.createMember(GestionComputadoras::mostrarComputadora));
            map.append(map.createMember(GestionComputadoras::volverMenu));
            // Asignacion de Rutas
            SelectionMap::Member* target{ map.head };
            map.reset();
            for (int i{ 0 }; i < 2; ++i)
            {
                map.traveler = map.traveler->next;
                target->linkTo(Direction::right, map.traveler);
                target = target->next;
            }
            map.reset();
            return map;
        }
        inline SelectionMap assignConfirmAgregarComputadoras()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(GestionComputadoras::SubAgregar::confirmar));
            map.append(map.createMember(GestionComputadoras::SubAgregar::reintentar));
            map.append(map.createMember(GestionComputadoras::SubAgregar::volver));
            // Asignacion de Rutas
            SelectionMap::Member* target{ map.head };
            map.reset();
            for (int i{ 0 }; i < 2; ++i)
            {
                map.traveler = map.traveler->next;
                target->linkTo(Direction::right, map.traveler);
                target = target->next;
            }
            target->isReactive = true;
            map.head->linkTo(Direction::down, target, false);
            map.head->right->linkTo(Direction::down, target, false);
            map.reset();
            return map;
        }
        inline SelectionMap assignOperacionesComputadoras()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(GestionComputadoras::SubMostrar::eliminar));
            map.append(map.createMember(GestionComputadoras::SubMostrar::volver));

            map.head->linkTo(Direction::down, map.head->next);

            map.reset();
            map.traveler = map.head->next;
            return map;
        }
        inline SelectionMap assignSimulacionClientes()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(SimulacionClientes::comenzarSesion));
            map.append(map.createMember(SimulacionClientes::terminarSesion));
            map.append(map.createMember(SimulacionClientes::volverMenu));
            // Asignacion de Rutas
            SelectionMap::Member* target{ map.head };
            map.reset();
            for (int i{ 0 }; i < 2; ++i)
            {
                map.traveler = map.traveler->next;
                target->linkTo(Direction::down, map.traveler);
                target = target->next;
            }
            map.reset();
            return map;
        }
        inline SelectionMap assignSeleccionTipoHoraSimulacion()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(SimulacionClientes::SubComenzarSesion::horaLibre));
            map.append(map.createMember(SimulacionClientes::SubComenzarSesion::horaFija));
            map.append(map.createMember(SimulacionClientes::SubComenzarSesion::volver));
            // Asignacion de Rutas
            SelectionMap::Member* target{ map.head };
            map.reset();
            for (int i{ 0 }; i < 2; ++i)
            {
                map.traveler = map.traveler->next;
                target->linkTo(Direction::down, map.traveler);
                target = target->next;
            }
            target->isReactive = true;
            map.head->linkTo(Direction::right, target, false);
            map.head->right->linkTo(Direction::right, target, false);
            map.reset();
            return map;
        }
        inline SelectionMap assignReportes()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(Reportes::generarReporteUso));
            map.append(map.createMember(Reportes::generarReporteIngresos));
            map.append(map.createMember(Reportes::volverMenu));
            // Asignacion de Rutas
            SelectionMap::Member* target{ map.head };
            map.reset();
            for (int i{ 0 }; i < 2; ++i)
            {
                map.traveler = map.traveler->next;
                target->linkTo(Direction::down, map.traveler);
                target = target->next;
            }
            map.reset();
            return map;
        }
        inline SelectionMap assignReportesConfirmation()
        {
            SelectionMap map{};
            using Direction = SelectionMap::Member::Direction;
            // Instanciacion de los miembros
            map.append(map.createMember(Reportes::SubConfirmation::generarTxt));
            map.append(map.createMember(Reportes::SubConfirmation::volver));

            map.head->linkTo(Direction::right, map.head->next);

            map.reset();
            return map;
        }
    }

    inline SelectionMap g_mainMenuMap{ Definitions::assignMainMenu() };
    inline SelectionMap g_reservasMap{ Definitions::assignReservas() };
    inline SelectionMap g_confirmReservasMap{ Definitions::assignReservasConfirmation() };
    inline SelectionMap g_continueReservasMap{ Definitions::assignReservasContinue() };
    extern SelectionMap g_operacionesGestionComputadorasMap{ Definitions::assignOperacionesGestionComputadoras() };
    extern SelectionMap g_confirmAgregarComputadorasMap{ Definitions::assignConfirmAgregarComputadoras() };
    extern SelectionMap g_operacionesComputadorasMap{ Definitions::assignOperacionesComputadoras() };
    extern SelectionMap g_simulacionClientesMap{ Definitions::assignSimulacionClientes() };
    extern SelectionMap g_seleccionTipoHoraSimulacion{ Definitions::assignSeleccionTipoHoraSimulacion()};
    extern SelectionMap g_reportesMap{ Definitions::assignReportes() };
    extern SelectionMap g_reportesConfirmationMap{ Definitions::assignReportesConfirmation() };

}
/*================================================================================================================================================================
                        FUNCTIONS
================================================================================================================================================================*/

COORD GetCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    return consoleInfo.dwCursorPosition;
}

void gotoCOORD(COORD position)
{
    SetConsoleCursorPosition(hConsole, position);
}

void printColor(const std::string_view& textToPrint,const int& colorCode, const int& backgroundColor)
{
    SetConsoleTextAttribute(hConsole, colorCode+16*backgroundColor); 
    std::cout << textToPrint;
    SetConsoleTextAttribute(hConsole, keys::defaultColor);
}

// ************************************************ Printing Functions ************************************************

// Imprime la pantalla principal del programa, no debe ser usado en un contexto normal.
void printMainMenu()
{
    printWindow(Windows::mainWindowSizeX, Windows::mainWindowSizeY, Windows::mainWindowStartPOS,color::dBlack,color::dWhite);
    //clearMainWindow();
    printFormat(formattedText::mainTitle, { 22,5 }, UI_Colors::mainDisplay, UI_Colors::mainBackground);
    gotoCOORD({19,13}); printColor(std::string(120, '='), UI_Colors::mainDisplay);
    
    selectionMaps::g_mainMenuMap.printAll();
    //printButtons<7,3>(selectionLists::mainMenuOptions);
}

// Imprime texto en unas coordenadas usando el struct COORD de windows.h. (COORD example = {x,y})
void printCOORD(const std::string_view& printText, const COORD& Pos)
{
    COORD returnPOS{ GetCursorPosition() };
    //HANDLE console{ GetStdHandle(STD_OUTPUT_HANDLE) };
    SetConsoleCursorPosition(hConsole, Pos);
    std::cout << printText;
    SetConsoleCursorPosition(hConsole, returnPOS);
}

// Limpia la ventana principal del programa, tratarlo como un system("CLS")
void clearMainWindow()
{
    COORD displayPos{ Windows::mainWindowStartPOS };
    for (int i{ 0 }; i < 41; ++i)
    {
        gotoCOORD(displayPos);
        printColor(std::string(120,' '), keys::defaultColor);
        if (i > 0) printColor("  ", keys::defaultColor, color::dWhite);
        ++displayPos.Y;
    }
    displayPos.X += 2;
    gotoCOORD(displayPos); printColor(std::string(120, ' '), keys::defaultColor, color::dWhite);
}

void printWindow(const short& sizeX, const short& sizeY, COORD pos, const int& colorFG, const int& colorBG)
{
    for (int i{ 0 }; i < (sizeY + 1); ++i)
    {
        gotoCOORD(pos);
        printColor(std::string((sizeX), ' '), keys::defaultColor,colorFG);
        if (i > 0) printColor("  ", keys::defaultColor, colorBG);
        ++pos.Y;
    }
    pos.X += 2;
    gotoCOORD(pos); printColor(std::string((sizeX), ' '), keys::defaultColor, colorBG);
}

void printRectangle(const COORD& pos, const int dimX, const int dimY, const int color, const char sample)
{
    COORD returnPos{ GetCursorPosition() };
    COORD printer{ pos };
    for (int i{ 0 }; i < dimY; ++i)
    {
        gotoCOORD(printer);
        printColor(std::string(dimX, sample), color);
        ++printer.Y;
    }
    gotoCOORD(returnPos);
}

void mostrarInformacionComputadora(DoubleList<Computadora>::Node* target, COORD pos)
{
    COORD returnPos{ GetCursorPosition() };

    gotoCOORD(pos); printColor("ID : ", color::dBlue, color::dBlack); std::cout << target->data.ID; ++pos.Y;
    gotoCOORD(pos); printColor("Estado : ", color::dBlue, color::dBlack);
    switch (target->data.estado)
    {
    case 0:
        std::cout << "Libre"; break;
    case 1:
        std::cout << "En Uso"; break;
    case 2:
        std::cout << "Reservada"; break;
    case 3:
        std::cout << "No Disponible"; break;
    } ++pos.Y;
    gotoCOORD(pos); printColor("Mod. de Precio : ", color::dBlue, color::dBlack); std::cout << target->data.modificadorDePrecio; ++pos.Y;
    gotoCOORD(pos); printColor("Tiempo de Uso : ", color::dBlue, color::dBlack); std::cout << target->data.tiempoDeUsoTotalSegundos << 's'; ++pos.Y;
    gotoCOORD(pos); printColor("Componentes : ", color::dBlue, color::dBlack); pos.X += 2; ++pos.Y;
    gotoCOORD(pos); std::cout << "- " << target->data.componentes[0]; ++pos.Y;
    gotoCOORD(pos); std::cout << "- " << target->data.componentes[1]; ++pos.Y;
    gotoCOORD(pos); std::cout << "- " << target->data.componentes[2]; ++pos.Y;
    gotoCOORD(pos); std::cout << "- " << target->data.componentes[3];

    gotoCOORD(returnPos);
}

// ************************************************ Console Functions ************************************************

void setWindowSize(int width, int height)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void lockConsole()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

    style &= ~WS_MAXIMIZEBOX; 
    //style &= ~WS_CAPTION;
    style &= ~WS_SIZEBOX;
    SetWindowLong(consoleWindow, GWL_STYLE, style);

    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

int selectComputer(DoubleList<Computadora> lista, const COORD& pos, int x, int y)
{
    using Direction = selectionMaps::SelectionMap::Member::Direction;

    selectionMaps::SelectionMap computerMap{};
    // Creacion de Botones modelo
    const std::string_view computerButton[4]{
        "<+----+>",
        "[|    |]",
        "<+----+>",
        "  /__\\  " };
    std::string_view pageButton[3]{
        "    ",
        " 1  ",
        "    " };
    // Asignando los primeros 4 botones
    COORD assignerPos{ pos };

    assignerPos.X += (6 * x - 22);
    assignerPos.Y += 5 * y + 2;
    computerMap.append(computerMap.createMember({ selectionMaps::instDisplaySet<3>(formattedText::pageStart),assignerPos,selectionMaps::primaryColorSet })); assignerPos.X += 9;
    computerMap.append(computerMap.createMember({ selectionMaps::instDisplaySet<3>(formattedText::pageBack),assignerPos,selectionMaps::primaryColorSet })); assignerPos.X += 8;
    computerMap.append(computerMap.createMember({ selectionMaps::instDisplaySet<3>(pageButton),assignerPos,selectionMaps::primaryColorSet })); assignerPos.X += 7;
    computerMap.append(computerMap.createMember({ selectionMaps::instDisplaySet<3>(formattedText::pageForward),assignerPos,selectionMaps::primaryColorSet })); assignerPos.X += 8;
    computerMap.append(computerMap.createMember({ selectionMaps::instDisplaySet<3>(formattedText::pageEnd),assignerPos,selectionMaps::primaryColorSet })); assignerPos.Y += 4;
    assignerPos.X = pos.X + 6 * x - 12;
    computerMap.append(computerMap.createMember({ selectionMaps::instDisplaySet<3>(formattedText::volver),assignerPos,selectionMaps::secondaryColorSet }));
    // Mapping first keys
    computerMap.reset();
    selectionMaps::SelectionMap::Member* memberLinker{ computerMap.head };

    {
        selectionMaps::SelectionMap::Member* exitLinker{ computerMap.getAt(5)};
        for (int i{ 0 }; i < 5; ++i) // Hacer solo 5 veces
        {
            computerMap.traveler = computerMap.traveler->next;
            memberLinker->linkTo(Direction::right, computerMap.traveler);
            memberLinker->linkTo(Direction::down, exitLinker, false);
            memberLinker->isReactive = true;
            memberLinker = memberLinker->next;
        }
    }
    memberLinker->isReactive = true;
    computerMap.reset();
    // Comenzar adicion de Computadoras a las paginas
    DoubleList<selectionMaps::SelectionMap> pages{}; pages.append(pages.createEntry({}));   // 1: Crea la variable y crea una pagina;
    DoubleList<Computadora> runner{lista};                                                  // 2: Crea una variable runner para recorrer la "lista"
    SingleList<std::string> idIndex{}; SingleList<std::string> idIndex_Assigner{};          // 3: Crea una lista simple de string para la asignacion de IDs al display
    int timesAdded{ 0 };
    
    // Creation of Selection List (Computer Interface)
    do
    {
        selectionMaps::SelectionMap::Member* adder{};
        assignerPos = pos;
        while (runner.head && timesAdded < x * y)
        {
            ++timesAdded;
            {
                selectionMaps::ColorSet buttonColor{};
                switch (runner.head->data.estado)
                {
                case 0:
                    buttonColor = selectionMaps::quaternaryColorSet; break;
                case 1:
                    buttonColor = selectionMaps::quinaryColorSet; break;
                case 2:
                    buttonColor = selectionMaps::senaryColorSet; break;
                case 3:
                    buttonColor = selectionMaps::septenaryColorSet; break;
                }


                if (!adder)
                {
                    pages.head->data.append(computerMap.createMember({ selectionMaps::instDisplaySet<4>(computerButton),assignerPos,buttonColor }));
                    adder = pages.head->data.head;
                }
                else
                {
                    adder->next = computerMap.createMember({ selectionMaps::instDisplaySet<4>(computerButton),assignerPos,buttonColor });
                    adder = adder->next;
                }

                if (runner.head->data.ID < 10) idIndex.append(idIndex.createEntry({ "[| " + std::to_string(runner.head->data.ID) + "  |]"}));
                else idIndex.append(idIndex.createEntry({ "[| " + std::to_string(runner.head->data.ID) + " |]" }));
                if (!idIndex_Assigner.head) idIndex_Assigner.head = idIndex.head;
                else idIndex_Assigner.head = idIndex_Assigner.head->next;

                adder->data.displaySet.head->next->data = idIndex_Assigner.head->data;
            }
            
            // Linker
            if (timesAdded == 1) pages.head->data.reset();
            else if (timesAdded % x == 1)
            {
                pages.head->data.traveler = pages.head->data.traveler->next;
                for (int i{ 0 }; i < x - 1; ++i) memberLinker = memberLinker->left;
                memberLinker->linkTo(Direction::down, pages.head->data.traveler);
            }
            else
            {
                pages.head->data.traveler = pages.head->data.traveler->next;
                memberLinker->linkTo(Direction::right, pages.head->data.traveler);

                if (timesAdded > x) memberLinker->up->right->linkTo(Direction::down, pages.head->data.traveler);// For adding vertical connections
            }
            memberLinker = pages.head->data.traveler;
            // Mover
            runner.head = runner.head->next;
            assignerPos.X += 12;
            // Assignment Reset
            if (timesAdded % x == 0)
            {
                assignerPos.X = pos.X;
                assignerPos.Y += 5;
            }
        } // Ended Booking
        // Linkeando botones finales a los botones de control
        for (int i{ 0 }; i < x; ++i)
        {
            memberLinker->linkTo(Direction::down, computerMap.head, false);
            if (!memberLinker->left) break;
            memberLinker = memberLinker->left;
        }

        if (!runner.head) break; // Añadiendo otra pagina si todavia existiese data

        pages.append(pages.createEntry({}));
        pages.head = pages.head->next;
        timesAdded = 0;

    } while (1);
    while (pages.head->prev) pages.head = pages.head->prev; 
    int page{ 1 };
    selectionMaps::SelectionMap::Member* pageChanger{ computerMap.getAt(5) }; 
    computerMap.append(pages.head->data.head);
    computerMap.traveler = pageChanger->next;
    // Lets See then
    int selectOption{ 0 };
    computerMap.printAll();
    bool reloadPrint{true};
    
    gotoCOORD({ pos.X,static_cast<short>(pos.Y + 5 * y) }); printColor(std::string((12 * x - 3), '='), color::bWhite, color::dBlack);

    while (1)
    {
        pageChanger->next = pages.head->data.head;
        {
            selectionMaps::SelectionMap::Member* mapLinker{ computerMap.head };
            for (int i{ 0 }; i < 5; ++i)
            {
                mapLinker->linkTo(Direction::up, pageChanger->next, false);
                mapLinker = mapLinker->next;
            }
        }

        if (reloadPrint)
        {
            // Refresh Page
            gotoCOORD(pos);
            for (int j{ 0 }; j < (5 * y - 1); ++j)
            {
                gotoCOORD({ pos.X,static_cast<short>(pos.Y + j) });
                printColor(std::string((12 * x - 3), ' '), color::dBlack, color::dBlack);
            }
            // Change Page number
            std::string pageStr{ std::to_string(page) };
            if (page < 10) computerMap.head->next->next->data.displaySet.head->next->data = { "  " + pageStr + "  " };
            else computerMap.head->next->next->data.displaySet.head->next->data = { "  " + pageStr + " " };
            // Imprimir Mapa de Botones
            computerMap.printAll();
        } reloadPrint = false;

        gotoCOORD({ 0,0 });
        selectOption = computerMap.startSelection(false); // Input
        
        if (selectOption <= 6) switch (selectOption)
        {
        case 1: // Move to first page
            if (page <= 1) continue;
            while (pages.head->prev) pages.head = pages.head->prev;
            page = 1;
            reloadPrint = true;
            continue;
        case 2: // Move to previus page
            if (page <= 1) continue;
            pages.head = pages.head->prev;
            --page;
            reloadPrint = true;
            continue;
        case 3: // Page (Do nothing)
            continue;
        case 4: // Move to next page
            if (!pages.head->next) continue;
            pages.head = pages.head->next;
            ++page;
            reloadPrint = true;
            continue;
        case 5: // Move to last page
            if (!pages.head->next) continue;
            while (pages.head->next)
            {
                pages.head = pages.head->next;
                ++page;
            }
            reloadPrint = true;
            continue;
        case 6: // Salir
            selectOption = 0;
            break;
        }
        // END  
        while (pages.head->prev) pages.head = pages.head->prev;


        while (pages.head)
        {
            pages.head->data.deleteAll();
            pages.deleteOnly(0);
            //pages.head = pages.head->next;
        }
        //idIndex_Assigner.deleteAll();
        idIndex.deleteAll();
        pages.deleteAll();
        pageChanger->next = nullptr;
        //runner.deleteAll();
        computerMap.deleteAll();

        if (!selectOption) return 0;
        return selectOption - 6 + x * y * (page-1);
    }
}

Hora getHora(const COORD& pos, const bool cleanup)
{
    using Direction = selectionMaps::SelectionMap::Member::Direction;
    COORD movePos{ pos };
    selectionMaps::SelectionMap hourMap{};
    // Adicion de Botones
    std::string_view hourButtonDisplay[3]{
        "      ",
        "      ",
        "      " };
    std::string_view minuteButtonDisplay[3]{
        "      ",
        "      ",
        "      " };
    hourMap.append(hourMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveUp),movePos,selectionMaps::ternaryColorSet })); movePos.Y += 2;
    hourMap.append(hourMap.createMember({ selectionMaps::instDisplaySet<3>(hourButtonDisplay),movePos,selectionMaps::primaryColorSet })); movePos.Y += 4;
    hourMap.append(hourMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveDown),movePos,selectionMaps::ternaryColorSet })); movePos.Y = pos.Y; movePos.X += 9;
    hourMap.append(hourMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveUp),movePos,selectionMaps::ternaryColorSet })); movePos.Y += 2;
    hourMap.append(hourMap.createMember({ selectionMaps::instDisplaySet<3>(minuteButtonDisplay),movePos,selectionMaps::primaryColorSet })); movePos.Y += 4;
    hourMap.append(hourMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveDown),movePos,selectionMaps::ternaryColorSet })); movePos.X = pos.X; movePos.Y += 2;
    hourMap.append(hourMap.createMember({ selectionMaps::instDisplaySet<3>(formattedText::confirmOperation),movePos,selectionMaps::secondaryColorSet }));
    // Vinculando Botones
    hourMap.reset();
    selectionMaps::SelectionMap::Member* memberLinker{ hourMap.getAt(4) }; 
    selectionMaps::SelectionMap::Member* minuteBox{ memberLinker };
    selectionMaps::SelectionMap::Member* horaBox{};
    selectionMaps::SelectionMap::Member* auxLinker{ hourMap.head };
    {
        selectionMaps::SelectionMap::Member* confirmLinker{ hourMap.getAt(6) }; confirmLinker->isReactive = true;
        for (int i{ 0 }; i < 3; ++i)
        {
            auxLinker = auxLinker->next;
            hourMap.traveler->linkTo(Direction::right, memberLinker, false);
            if (i != 2) hourMap.traveler->linkTo(Direction::down, auxLinker);
            else hourMap.traveler->linkTo(Direction::down, confirmLinker, false);
            hourMap.traveler = hourMap.traveler->next;
        }
        memberLinker = hourMap.getAt(1);
        horaBox = memberLinker;
        for (int i{ 0 }; i < 3; ++i)
        {
            auxLinker = auxLinker->next;
            hourMap.traveler->linkTo(Direction::left, memberLinker, false);
            if (i != 2) hourMap.traveler->linkTo(Direction::down, auxLinker);
            else hourMap.traveler->linkTo(Direction::down, confirmLinker, false);
            hourMap.traveler = hourMap.traveler->next;
        }
    }
    
    hourMap.reset();
    // Obteniendo Input
    short hourTime{ 0 };
    short minuteTime{ 0 };
    int inputSelection{ 0 };
    bool change{ true };
    printCOORD(":", { static_cast<short>(pos.X + 7),static_cast<short>(pos.Y + 3) });

    do {
        

        if (change)
        {
            if (hourTime>=10) horaBox->data.displaySet.head->next->data = { "   " + std::to_string(hourTime) + "  " };
            else horaBox->data.displaySet.head->next->data = { "   0" + std::to_string(hourTime) + "  " };
            if (minuteTime >= 10) minuteBox->data.displaySet.head->next->data = { "   " + std::to_string(minuteTime) + "  " };
            else minuteBox->data.displaySet.head->next->data = { "   0" + std::to_string(minuteTime) + "  " };

            change = false;
            hourMap.printAll();
        }

        switch (inputSelection = hourMap.startSelection())
        {
        case 1:
            if (hourTime >= 23) hourTime = -1;
            ++hourTime;
            change = true;

            break;
        case 2:
            break;
        case 3:
            if (hourTime <= 0) hourTime = 24;
            --hourTime;
            change=true;
            break;
        case 4:
            if (minuteTime >= 59) minuteTime = -1;
            ++minuteTime;
            change=true;
            break;
        case 5:
            break;
        case 6:
            if (minuteTime <= 0) minuteTime = 60;
            --minuteTime;
            change=true;
            break;
        case 7:
            inputSelection = 0;
            break;
        }
    } while (inputSelection);
    if (cleanup) printRectangle(pos, 15, 11, color::dBlack);
    hourMap.deleteAll();
    return { hourTime,minuteTime };
}

Fecha getFecha(const COORD& pos, const bool cleanup)
{
    using Direction = selectionMaps::SelectionMap::Member::Direction;
    COORD movePos{ pos };
    selectionMaps::SelectionMap dateMap{};
    // Adicion de Botones
    std::string_view dayButtonDisplay[3]{
        "      ",
        "      ",
        "      " };
    std::string_view monthButtonDisplay[3]{
        "      ",
        "      ",
        "      " };
    std::string_view yearButtonDisplay[3]{
        "        ",
        "        ",
        "        " };
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveUp),movePos,selectionMaps::ternaryColorSet })); movePos.Y += 2;
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<3>(dayButtonDisplay),movePos,selectionMaps::primaryColorSet })); movePos.Y += 4;
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveDown),movePos,selectionMaps::ternaryColorSet })); movePos.Y = pos.Y; movePos.X += 9;
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveUp),movePos,selectionMaps::ternaryColorSet })); movePos.Y += 2;
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<3>(monthButtonDisplay),movePos,selectionMaps::primaryColorSet })); movePos.Y += 4;
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveDown),movePos,selectionMaps::ternaryColorSet })); movePos.Y = pos.Y; movePos.X += 9;
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveUp_wide),movePos,selectionMaps::ternaryColorSet })); movePos.Y += 2;
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<3>(yearButtonDisplay),movePos,selectionMaps::primaryColorSet })); movePos.Y += 4;
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<1>(formattedText::moveDown_wide),movePos,selectionMaps::ternaryColorSet })); movePos.X = pos.X + 5; movePos.Y += 2;
    dateMap.append(dateMap.createMember({ selectionMaps::instDisplaySet<3>(formattedText::confirmOperation),movePos,selectionMaps::secondaryColorSet }));
    // Vinculando Botones
    dateMap.reset();
    selectionMaps::SelectionMap::Member* memberLinker{ dateMap.head };
    selectionMaps::SelectionMap::Member* dayBox{};
    selectionMaps::SelectionMap::Member* monthBox{};
    selectionMaps::SelectionMap::Member* yearBox{};
    {
        selectionMaps::SelectionMap::Member* confirmLinker{ dateMap.getAt(9) }; confirmLinker->isReactive = true;

        for (int i{ 0 }; i < 3; ++i)
        {
            for (int j{ 0 }; j < 3; ++j)
            {
                dateMap.traveler = dateMap.traveler->next;
                if (j == 1)
                {
                    switch (i)
                    {
                    case 0:
                        dayBox = memberLinker;
                    case 1:
                        monthBox = memberLinker;
                    case 2:
                        yearBox = memberLinker;
                    }
                }
                if (j != 2)
                {
                    memberLinker->linkTo(Direction::down, dateMap.traveler);
                    if (i > 0) memberLinker->left->down->linkTo(Direction::right, dateMap.traveler);
                }
                else
                {
                    memberLinker->linkTo(Direction::down, confirmLinker, false);
                    memberLinker->up->up->linkTo(Direction::right, dateMap.traveler);
                }

                memberLinker = dateMap.traveler;
            }
        }
    }

    dateMap.reset();
    // Obteniendo Input
    std::time_t currentDate{}; std::time(&currentDate);
    std::tm dateInfo{};
    localtime_s(&dateInfo, &currentDate);

    short dayDate{ static_cast<short>(dateInfo.tm_mday) };
    short monthDate{ static_cast<short>(dateInfo.tm_mon + 1) };
    short yearDate{ static_cast<short>(dateInfo.tm_year + 1900) };
    
    int inputSelection{ 0 };
    bool change{ true };
    printCOORD("/", { static_cast<short>(pos.X + 7),static_cast<short>(pos.Y + 3) });
    printCOORD("/", { static_cast<short>(pos.X + 16),static_cast<short>(pos.Y + 3) });

    do {
        if (change)
        {
            if (dayDate >= 10) dayBox->data.displaySet.head->next->data = { "   " + std::to_string(dayDate) + "  " };
            else dayBox->data.displaySet.head->next->data = { "   0" + std::to_string(dayDate) + "  " };
            if (monthDate >= 10) monthBox->data.displaySet.head->next->data = { "   " + std::to_string(monthDate) + "  " };
            else monthBox->data.displaySet.head->next->data = { "   0" + std::to_string(monthDate) + "  " };

            yearBox->data.displaySet.head->next->data = { "   " + std::to_string(yearDate) + "  " };

            change = false;
            dateMap.printAll();
        }

        switch (inputSelection = dateMap.startSelection())
        {
        case 1:
            if (dayDate>=31) break;
            ++dayDate;
            change = true;

            break;
        case 2:
            break;
        case 3:
            if (dayDate <= 0) break;
            --dayDate;
            change = true;
            break;
        case 4:
            if (monthDate >= 12) break;
            ++monthDate;
            change = true;
            break;
        case 5:
            break;
        case 6:
            if (monthDate <= 0) break;
            --monthDate;
            change = true;
            break;
        case 7:
        case 8:
        case 9:
            break;
        case 10:
            inputSelection = 0;
            break;
        }
    } while (inputSelection);
    if (cleanup) printRectangle(pos, 26, 11, color::dBlack);
    dateMap.deleteAll();
    return { yearDate,monthDate,dayDate };
}

std::string getInputBox(COORD pos, short size, bool onlyInt)
{
    COORD returnPos{ GetCursorPosition() };
    std::string output{};
    char input{};
    bool valid{};
    int sizeStr{0};
    bool period{ false };

    gotoCOORD(pos); printColor(std::string(size, ' '), color::dBlack, color::bWhite); pos.X += 1;
    gotoCOORD(pos);

    SetConsoleTextAttribute(hConsole, color::dBlack + 16 * color::bWhite); // Set Word to black color
    do
    {
        valid = false;
        input = _getch();

        if (input == 13) break;
        //46
        if (input >= 48 && input <= 57) valid = true;
        if (input == 46 && onlyInt)
        {
            if (!period)
            {
                valid = true;
                period = true;
            }
        }
        if (!onlyInt)
        {
            if ((input == 28 || input == 29) || (input >= 64 && input <= 91) || input == 93) valid = true;
            if ((input == 45 || input == 46) || (input >= 97 && input <= 122) || input == 95 || input == 32) valid = true;
        }
        if (valid && sizeStr < (size - 2))
        {
            output.push_back(input);
            std::cout << input;
            ++sizeStr;
        }
        if (input == 8 && sizeStr>0)
        {
            if (output.back() == '.') period = false;
            output.pop_back();
            std::cout << "\b \b";
            --sizeStr;
        }

    } while (1);
    if (sizeStr == 0 && onlyInt)
    {
        std::cout << "0.00";
        output = "0";
    }

    SetConsoleTextAttribute(hConsole, color::dBlack);

    gotoCOORD(returnPos);
    return output;
}
