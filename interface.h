#ifndef INTERFACE_H
#define INTERFACE_H


// Includes 
#include <windows.h>
#include <conio.h>
#include <string_view>
#include "tempFile.h"

//#include <iostream>

/*================================================================================================================================================================
                        FUNCTION DECLARATION
================================================================================================================================================================*/
// Coords
COORD GetCursorPosition();
void gotoCOORD(COORD);
void printColor(const std::string_view&, const int&, const int& = 0);


/*================================================================================================================================================================
                        NAMESPACES
================================================================================================================================================================*/

namespace keys          // Guardar los codigos de teclas que se obtendran con el _getch(), y colores, por alguna razon
{
    constexpr int keyUP{ 72 };
    constexpr int keyLEFT{ 75 };
    constexpr int keyRIGHT{ 77 };
    constexpr int keyDOWN{ 80 };

    constexpr int selectColor{ 2 };
    constexpr int defaultColor{ 7 };
}

namespace color         // Codigos de color a usar para las interfaces
{
    constexpr int dBlack{ 0 };
    constexpr int dBlue{ 1 };
    constexpr int dGreen{ 2 };
    constexpr int dAqua{ 3 };
    constexpr int dRed{ 4 };
    constexpr int dPurple{ 5 };
    constexpr int dYellow{ 6 };
    constexpr int dWhite{ 7 };
    constexpr int bBlack{ 8 };
    constexpr int bBlue{ 9 };
    constexpr int bGreen{ 10 };
    constexpr int bAqua{ 11 };
    constexpr int bRed{ 12 };
    constexpr int bPurple{ 13 };
    constexpr int bYellow{ 14 };
    constexpr int bWhite{ 15 };

}

namespace UI_Colors
{
    using Color = int;

    constexpr Color unselectedButton{ color::dWhite };  // Colors for Primary Buttons
    constexpr Color selectedButton{ color::bAqua };
    constexpr Color unselectedButtonText{ color::dBlack };
    constexpr Color selectedButtonText{ color::dBlack };

    constexpr Color unselectedSButton {color::bBlack }; // Colors for Secondary Buttons
    constexpr Color selectedSButton{ color::dRed };
    constexpr Color unselectedSButtonText{ color::dBlack };
    constexpr Color selectedSButtonText{ color::dWhite };

    constexpr Color unselectedTButton{ color::bBlack }; // Colors for Third Buttons
    constexpr Color selectedTButton{ color::bYellow };
    constexpr Color unselectedTButtonText{ color::dBlack };
    constexpr Color selectedTButtonText{ color::dBlack };

    constexpr Color mainDisplay{ color::dWhite };
    constexpr Color mainBackground{ color::dBlack };
}

namespace formattedText
{
    using Display = std::string_view;
    // ******************************* Titulo *******************************
    constexpr Display mainTitle[7] =
    {
        {"  o888o                  t .                                      #####                             "},
        {" d'   '9               o888P #  ####  #    #    #####  ######    #     # #   # #####  ###### #####  "},
        {" 8        o88o   o88o  ' 8   # #    # ##   #    #    # #         #        # #  #    # #      #    # "},
        {" 8  888o d'  'b dP. `'   8   # #    # # #  #    #    # #####     #         #   #####  #####  #    # "},
        {" 8    '8 88888P  `8o.    8   # #    # #  # #    #    # #         #         #   #    # #      #####  "},
        {" Y.   .9 Y      o  `8.   Y . # #    # #   ##    #    # #         #     #   #   #    # #      #   #  "},
        {"  Y888P  'Y88P' 'Y88P'   'bP #  ####  #    #    #####  ######     #####    #   #####  ###### #    # "}
    };
    // ******************************* Main Menu *******************************
    constexpr std::string_view gestionDeComputadoras[3]{
        " \033[C                                              \033[C ",
        " \033[C             Gestion de Computadoras          \033[C ",
        " \033[C                                              \033[C " };
    constexpr std::string_view gestionDeSesiones[3]{
        " \033[C  20 horas             ayudaaa                \033[C ",
        " \033[C     Gestion de Clientes (Sin terminar)       \033[C ",
        " \033[C  aaaaaa                             :c       \033[C " };
    constexpr std::string_view gestionDeClientes[3]{
        " \033[C       OJO : falta terminar                   \033[C ",
        " \033[C             Simulacion de Sesiones (creo)    \033[C ",
        " \033[C   :D                                         \033[C " };
    constexpr std::string_view facturacion[3]{
        " \033[C                                              \033[C ",
        " \033[C         Facturacion (todavia nada :v)        \033[C ",
        " \033[C                                              \033[C " };
    constexpr std::string_view reservas[3]{
        " \033[C                                              \033[C ",
        " \033[C          Reservas (WIP = aun falta)          \033[C ",
        " \033[C                                              \033[C " };
    constexpr std::string_view reportes[3]{
        " \033[C                                              \033[C ",
        " \033[C          Reportes     ya sale, falta poco    \033[C ",
        " \033[C                                              \033[C " };
    // ******************************* Botones *******************************
    constexpr std::string_view hacerReserva[3]{
        " \033[C                 \033[C ",
        " \033[C  Hacer Reserva  \033[C ",
        " \033[C                 \033[C " };
    constexpr std::string_view verHistorial[3]{
        " \033[C                 \033[C ",
        " \033[C  Ver Historial  \033[C ",
        " \033[C                 \033[C " };
    constexpr std::string_view agregarComputadora[3]{
        " \033[C                 \033[C ",
        " \033[C     Agregar     \033[C ",
        " \033[C                 \033[C " };
    constexpr std::string_view mostrarComputadora[3]{
        " \033[C                 \033[C ",
        " \033[C     Mostrar     \033[C ",
        " \033[C                 \033[C " };
    constexpr std::string_view comenzarSesion[3]{
        " \033[C                 \033[C ",
        " \033[C Comenzar Sesion \033[C ",
        " \033[C                 \033[C " };
    constexpr std::string_view terminarSesion[3]{
        " \033[C                 \033[C ",
        " \033[C Terminar Sesion \033[C ",
        " \033[C                 \033[C " };
    constexpr std::string_view horaLibre[3]{
        " \033[C                 \033[C ",
        " \033[C    Hora Libre   \033[C ",
        " \033[C                 \033[C " };
    constexpr std::string_view horaFija[3]{
        " \033[C                 \033[C ",
        " \033[C    Hora Fija    \033[C ",
        " \033[C                 \033[C " };
    // ******************************* Uso General *******************************
    constexpr std::string_view salir[3]{
        "                   ",
        "       Salir       ",
        "                   " };
    constexpr std::string_view volver[3]{
        "                   ",
        "<<<<   Volver  <<<<",
        "                   " };
    // ******************************* Navegacion de Interfaz *******************************
    constexpr std::string_view pageStart[3]{
        "      ",
        "  <<  ",
        "      " };
    constexpr std::string_view pageBack[3]{
        "     ",
        "  <  ",
        "     " };
    constexpr std::string_view pageForward[3]{
        "     ",
        "  >  ",
        "     " };
    constexpr std::string_view pageEnd[3]{
        "      ",
        "  >>  ",
        "      " };
    constexpr std::string_view moveUp[1]{
        "  AA  " };
    constexpr std::string_view moveDown[1]{
        "  VV  " };
    constexpr std::string_view moveUp_wide[1]{
        "   AA   " };
    constexpr std::string_view moveDown_wide[1]{
        "   VV   " };
    constexpr std::string_view confirmOperation[3]{
        "*             *",
        "   CONFIRMAR   ",
        "*             *"};
    constexpr std::string_view redoOperation[3]{
        "*             *",
        "   REINTENTAR  ",
        "*             *" };
    constexpr std::string_view eliminar[3]{
        "*             *",
        "   ELIMINAR    ",
        "*             *" };
    namespace Elements
    {
        constexpr std::string_view computerInfo[3]{
            " \033[C                                     \033[C ",
            " \033[C    INFORMACION DE LA COMPUTADORA    \033[C ",
            " \033[C                                     \033[C ",};
        constexpr std::string_view makeReserve[3]{
            " \033[C                                     \033[C ",
            " \033[C            CREAR RESERVA            \033[C ",
            " \033[C                                     \033[C ", };
        constexpr std::string_view addComputer[3]{
            " \033[C                                     \033[C ",
            " \033[C         AGREGAR COMPUTADORA         \033[C ",
            " \033[C                                     \033[C ", };
        constexpr std::string_view elegirTipoSesion[3]{
            " \033[C                             \033[C ",
            " \033[C    ELEGIR TIPO DE SESION    \033[C ",
            " \033[C                             \033[C ", };
        constexpr std::string_view introducirHora[3]{
            " \033[C                             \033[C ",
            " \033[C     INTRODUZCA UNA HORA     \033[C ",
            " \033[C                             \033[C ", };
        constexpr std::string_view sesionAsignada[3]{
            " \033[C                             \033[C ",
            " \033[C       SESION ASIGNADA       \033[C ",
            " \033[C                             \033[C ", };
        constexpr std::string_view terminarSesion[3]{
            " \033[C                             \033[C ",
            " \033[C       TERMINAR SESION       \033[C ",
            " \033[C                             \033[C ", };
        constexpr std::string_view computer[11]{
            "    INFORMACION",
            ".o===============o.",
            "||'             '||",
            "||               ||",
            "||               ||",
            "||.             .||",
            "'8===============8'",
            "     //     \\\\",
            "    //_______\\\\",
            "",
            "    COMPUTADORA    "};
    }

}

namespace menuDefs  // Para usar con el printColor
{
    constexpr std::string_view background =
        R"(                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               )";
}

namespace selectionMaps
{
    // Selection Maps

    struct ColorSet 
    {
        int FGselectColor{};
        int FGunselectColor{};
        int BGselectColor{};
        int BGunselectColor{};
    };
    // ***************************************************************** DEFINICIONES *****************************************************************
    constexpr ColorSet primaryColorSet{ UI_Colors::selectedButtonText,UI_Colors::unselectedButtonText,UI_Colors::selectedButton,UI_Colors::unselectedButton };
    constexpr ColorSet secondaryColorSet{ UI_Colors::selectedSButtonText,UI_Colors::unselectedSButtonText,UI_Colors::selectedSButton,UI_Colors::unselectedSButton };
    constexpr ColorSet ternaryColorSet{ UI_Colors::selectedTButtonText,UI_Colors::unselectedTButtonText,UI_Colors::selectedTButton,UI_Colors::unselectedTButton };
    constexpr ColorSet quaternaryColorSet{ color::bGreen,color::dWhite,color::dBlack,color::dBlack };
    constexpr ColorSet quinaryColorSet{ color::bGreen,color::dYellow,color::dBlack,color::dBlack };
    constexpr ColorSet senaryColorSet{ color::bGreen,color::dPurple,color::dBlack,color::dBlack };
    constexpr ColorSet septenaryColorSet{ color::bGreen,color::dRed,color::dBlack,color::dBlack };
    // ***************************************************************** STRUCT *****************************************************************
    struct Button
    {
        SingleList<std::string_view> displaySet{};
        COORD displayPos{};
        ColorSet colors{};
        // Functions
        void print(bool highlight=false) const
        {
            COORD returnPOS{ GetCursorPosition() };
            short yCoord{ displayPos.Y };
            SingleList<std::string_view> runnerSet{ displaySet };
            
            while (runnerSet.head)
            {   
                gotoCOORD({ displayPos.X ,yCoord });
                if (highlight) printColor(runnerSet.head->data, colors.FGselectColor, colors.BGselectColor);
                else printColor(runnerSet.head->data, colors.FGunselectColor, colors.BGunselectColor);
                ++yCoord;
                runnerSet.head = runnerSet.head->next;
            }
            gotoCOORD(returnPOS);

            //else printColor("NoHead!", 10, 9);
            //printColor("Print!", 10, 8);
        }
    };
    // ***************************************************************** FUNCIONES *****************************************************************
    template<int N>
    const SingleList<std::string_view> instDisplaySet(const std::string_view list[N])
    {
        SingleList<std::string_view> data;
        for (int i{ 0 }; i < N; ++i)
        {
            data.append(data.createEntry(list[i]));
        }
        return data;
    }
    template<int N>
    const SingleList<std::string_view> instDisplaySet(const std::string list[N])
    {
        SingleList<std::string> data;
        for (int i{ 0 }; i < N; ++i)
        {
            data.append(data.createEntry(list[i]));
        }
        return data;
    }
    // ***************************************************************** DEFINICIONES *****************************************************************
    namespace MainMenu
    {
        const extern Button gestionDeComputadoras;
        const extern Button gestionDeSesiones;
        const extern Button gestionDeClientes;
        const extern Button facturacion;
        const extern Button reservas;
        const extern Button reportes;
        const extern Button salir;
    }

    namespace Reservas
    {
        const extern Button hacerReservas;
        const extern Button verHistorial;
        const extern Button volver;

        const extern Button confirmReserva;
        const extern Button cancelarReserva;

        namespace SubConfirmar
        {
            const extern Button confirmar;
            const extern Button volver;
        } 
    }
    namespace GestionComputadoras
    {
        const extern Button agregarComputadora;
        const extern Button mostrarComputadora;
        const extern Button volverMenu;

        namespace SubAgregar
        {
            const extern Button confirmar;
            const extern Button reintentar;
            const extern Button volver;
        }
        namespace SubMostrar
        {
            const extern Button eliminar;
            const extern Button volver;
        }
    }
    namespace SimulacionClientes
    {
        const extern Button comenzarSesion;
        const extern Button terminarSesion;
        const extern Button volverMenu;

        namespace SubComenzarSesion
        {
            const extern Button horaLibre;
            const extern Button horaFija;
            const extern Button volver;
        }
    }
    // ***************************************************************** STRUCT *****************************************************************
    struct SelectionMap
    {
        struct Member
        {
            enum class Direction
            {
                right,
                left,
                down,
                up
            };

            Button data{};
            // Settings
            bool isReactive{ false };
            bool enabled{ true };
            // Movements
            Member* left{};
            Member* right{};
            Member* up{};
            Member* down{};

            Member* next{};

            // Functions

            void linkTo(const Direction point, Member* const target, const bool both = true)
            {
                switch (point)
                {
                case Direction::right:
                    right = target;
                    if (both) target->left = this;
                    break;
                case Direction::left:
                    left = target;
                    if (both) target->right = this;
                    break;
                case Direction::down:
                    down = target;
                    if (both) target->up = this;
                    break;
                case Direction::up:
                    up = target;
                    if (both) target->down = this;
                    break;
                default:
                    break;
                }
            }
        };
        Member* head{};
        Member* traveler{ head };

        // Functions
        Member* createMember(const Button& buttonData) const
        {
            Member* node = new(struct Member);
            node->data = buttonData;
            return node;
        }
        void append(Member* const member)
        {
            if (!head)
            {
                head = member;
                return;
            }
            Member* runner{ head };
            while (runner->next) runner = runner->next;
            runner->next = member;
        }
        size_t getSize()
        {
            Member* runner{ head };
            size_t size{ 0 };
            while (runner)
            {
                runner = runner->next;
                ++size;
            }
            return size;
        }
        Member* const getAt(size_t pos)
        {
            if (pos < 0) // Transform Negative into Positive
            {
                pos += getSize();
                if (pos < 0) return nullptr; // Out of scope
            }
            Member* runner{ head };
            while (runner)
            {
                if (pos == 0) break;
                runner = runner->next;
                --pos;
            }
            if (pos > 0) return nullptr; // Out of range
            return runner;  // Normal behaviour: Returns intended pointer
        }

        // Imprime todo el mapa, falta rework
        void printAll() const
        {
            Member* runner{ head };
            while (runner)
            {
                runner->data.print();
                runner = runner->next;
            }
        }
        void deleteAll() const
        {
            Member* eraser{};
            Member* runner{ head };
            while (runner)
            {
                eraser = runner;
                runner = runner->next;
                eraser->data.displaySet.deleteAll();
                delete(eraser);

                
            }
        }

        void move(size_t steps)
        {
            while (steps > 0)
            {
                if (!traveler) return;
                traveler = traveler->next;
                --steps;
            }
        }
        void reset()
        {
            traveler = head;
        }
        // Set Selection
        int startSelection(bool reset=false)
        {
            if (reset) this->reset();
            if (!traveler) return 0;
            int inputCH{};
            do
            {
                // Print Selected
                traveler->data.print(true);
                // Select
                inputCH = _getch();
                if (inputCH == 13) break;
                else if (inputCH && inputCH != 224);
                else
                {
                    traveler->data.print();
                    switch (inputCH = _getch())
                    {
                    case keys::keyLEFT:
                        if (!traveler->left || !traveler->left->enabled) break;
                        else if (traveler->left->isReactive) traveler->left->right = traveler;
                        traveler = traveler->left;
                        break;
                    case keys::keyRIGHT:
                        if (!traveler->right || !traveler->right->enabled) break;
                        else if (traveler->right->isReactive) traveler->right->left = traveler;
                        traveler = traveler->right;
                        break;
                    case keys::keyDOWN:
                        if (!traveler->down || !traveler->down->enabled) break;
                        else if (traveler->down->isReactive) traveler->down->up = traveler;
                        traveler = traveler->down;
                        break;
                    case keys::keyUP:
                        if (!traveler->up || !traveler->up->enabled) break;
                        else if (traveler->up->isReactive) traveler->up->down = traveler;
                        traveler = traveler->up;
                        break;
                    }
                }
            } while (1);

            Member* reserve{ head };
            int output{ 1 };
            while (traveler != reserve)
            {
                reserve = reserve->next;
                ++output;
            }
            return output;
        }
    };
    // ***************************************************************** FUNCIONES *****************************************************************
    namespace Definitions
    {
        inline SelectionMap assignMainMenu();

        inline SelectionMap assignReservas();
        inline SelectionMap assignReservasConfirmation();
        inline SelectionMap assignReservasContinue();

        inline SelectionMap assignOperacionesGestionComputadoras();
        inline SelectionMap assignConfirmAgregarComputadoras();
        inline SelectionMap assignOperacionesComputadoras();

        inline SelectionMap assignSimulacionClientes();
        inline SelectionMap assignSeleccionTipoHoraSimulacion();
    }
    // ***************************************************************** DEFINICIONES *****************************************************************
    extern SelectionMap g_mainMenuMap;
    extern SelectionMap g_reservasMap;
    extern SelectionMap g_confirmReservasMap;
    extern SelectionMap g_continueReservasMap;
    extern SelectionMap g_operacionesGestionComputadorasMap;
    extern SelectionMap g_confirmAgregarComputadorasMap;
    extern SelectionMap g_operacionesComputadorasMap;
    extern SelectionMap g_simulacionClientesMap;
    extern SelectionMap g_seleccionTipoHoraSimulacion;


}

namespace Windows
{
    constexpr COORD mainWindowStartPOS{ 19,4 };
    constexpr short mainWindowSizeX{ 120 };
    constexpr short mainWindowSizeY{ 40 };
}


/*================================================================================================================================================================
                        FUNCTION DECLARATION
================================================================================================================================================================*/
// Printing Functions
void printMainMenu();
void printWindow(const short& sizeX, const short& sizeY, COORD pos, const int& colorFG, const int& colorBG);
void printCOORD(const std::string_view&, const COORD&);
void clearMainWindow(); 
void printRectangle(const COORD& pos, const int dimX, const int dimY, const int color, const char sample = ' ');
void mostrarInformacionComputadora(DoubleList<Computadora>::Node* target, COORD pos);
// Console
void setWindowSize(int, int);
void lockConsole();
Fecha getFecha(const COORD& pos, const bool cleanup = false);
Hora getHora(const COORD& pos, const bool cleanup = false);
std::string getInputBox(COORD pos, short size, bool onlyInt = false);
// ********************************************** Templates ***********************************************

template <size_t N>     // Print Format using size N
void printFormat(const std::string_view(&textLine)[N], COORD Pos, int fColor, int bColor)
{
    COORD returnPOS{ GetCursorPosition() };

    for (int i{ 0 }; i < N; ++i) {
        gotoCOORD(Pos);
        printColor(textLine[i], fColor, bColor);
        ++Pos.Y;
    }
    gotoCOORD(returnPOS);

}

int selectComputer(DoubleList<Computadora> lista, const COORD& pos, int x, int y);


#endif // !INTERFACE_H