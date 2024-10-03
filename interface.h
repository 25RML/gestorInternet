#pragma once
// Includes 
#include <windows.h>
#include <conio.h>
#include <string_view>

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

namespace formattedText         // Strings para usar con la funcion printFormat()
{
    /*struct fString {    // Definicion de las variables fString
        std::string_view storeText;
        int fColor;
        int bColor;
    };*/
    using Button = std::string_view;
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
    constexpr Button gestionDeComputadoras[3] =
    {
        {" \033[C                                              \033[C "},
        {" \033[C             Gestion de Computadoras          \033[C "},
        {" \033[C                                              \033[C "}
    };
    constexpr Button gestionDeSesiones[3] =
    {
        {" \033[C                                              \033[C "},
        {" \033[C               Gestion de Sesiones            \033[C "},
        {" \033[C                                              \033[C "}
    };
    constexpr Button gestionDeClientes[3] =
    {
        {" \033[C                                              \033[C "},
        {" \033[C               Gestion de Clientes            \033[C "},
        {" \033[C                                              \033[C "}
    };
    constexpr Button facturacion[3] =
    {
        {" \033[C                                              \033[C "},
        {" \033[C                   Facturacion                \033[C "},
        {" \033[C                                              \033[C "}
    };
    constexpr Button reservas[3] =
    {
        {" \033[C                                              \033[C "},
        {" \033[C                    Reservas                  \033[C "},
        {" \033[C                                              \033[C "}
    };
    constexpr Button reportes[3] =
    {
        {" \033[C                                              \033[C "},
        {" \033[C                    Reportes                  \033[C "},
        {" \033[C                                              \033[C "}
    };
    // ******************************* Reportes *******************************
    constexpr Button hacerReserva[3] =
    {
        {" \033[C                 \033[C "},
        {" \033[C  Hacer Reserva  \033[C "},
        {" \033[C                 \033[C "}
    };
    constexpr Button verHistorial[3] =
    {
        {" \033[C                 \033[C "},
        {" \033[C  Ver Historial  \033[C "},
        {" \033[C                 \033[C "}
    };
    // ******************************* Uso General *******************************
    constexpr Button salir[3] =
    {
        {"                   "},
        {"       Salir       "},
        {"                   "}
    };
    constexpr Button volver[3] =
    {
        {"                   "},
        {"<<<<   Volver  <<<<"},
        {"                   "}
    };
}

namespace menuDefs  // Para usar con el printColor
{
    constexpr std::string_view background =
        R"(                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               
                                                                                                                                                               )";
}

namespace selectionLists
{
    template <int N>
    struct selectionMember
    {
        std::string_view displaySet[N]; // N define el numero de lineas de texto de un display de una opcion
        COORD displayPos;
        int FGselectColor;
        int FGunselectColor;
        int BGselectColor;
        int BGunselectColor;
    };
    // ******************************* Main Menu *******************************
    constexpr selectionMember<3> mainMenuOptions[7] { // Esta inicializacion es horrible, lo se
        {   {
                formattedText::gestionDeComputadoras[0],
                formattedText::gestionDeComputadoras[1],    
                formattedText::gestionDeComputadoras[2],
            }, {54,15}, // POS
            UI_Colors::selectedButtonText,UI_Colors::unselectedButtonText,
            UI_Colors::selectedButton,UI_Colors::unselectedButton},
        {   {
                formattedText::gestionDeSesiones[0],
                formattedText::gestionDeSesiones[1],
                formattedText::gestionDeSesiones[2],
            }, {54,20}, // POS
            UI_Colors::selectedButtonText,UI_Colors::unselectedButtonText,
            UI_Colors::selectedButton,UI_Colors::unselectedButton},
        {   {
                formattedText::gestionDeClientes[0],
                formattedText::gestionDeClientes[1],
                formattedText::gestionDeClientes[2],
            }, {54,25}, // POS
            UI_Colors::selectedButtonText,UI_Colors::unselectedButtonText,
            UI_Colors::selectedButton,UI_Colors::unselectedButton},
        {   {
                formattedText::facturacion[0],
                formattedText::facturacion[1],
                formattedText::facturacion[2],
            }, {54,30}, // POS
            UI_Colors::selectedButtonText,UI_Colors::unselectedButtonText,
            UI_Colors::selectedButton,UI_Colors::unselectedButton},
        {   {
                formattedText::reservas[0],
                formattedText::reservas[1],
                formattedText::reservas[2],
            }, {54,35}, // POS
            UI_Colors::selectedButtonText,UI_Colors::unselectedButtonText,
            UI_Colors::selectedButton,UI_Colors::unselectedButton},
        {   {
                formattedText::reportes[0],
                formattedText::reportes[1],
                formattedText::reportes[2],
            }, {54,40}, // POS
            UI_Colors::selectedButtonText,UI_Colors::unselectedButtonText,
            UI_Colors::selectedButton,UI_Colors::unselectedButton},
        {   {
                formattedText::salir[0],
                formattedText::salir[1],
                formattedText::salir[2],
            }, {115,38}, // POS
            UI_Colors::selectedSButtonText,UI_Colors::unselectedSButtonText,
            UI_Colors::selectedSButton,UI_Colors::unselectedSButton}};
    // ******************************* Reservas *******************************
    constexpr selectionMember<3> reservasOptions[3]{
        {   {
                formattedText::hacerReserva[0],
                formattedText::hacerReserva[1],
                formattedText::hacerReserva[2],
            }, {9,6}, // POS
            UI_Colors::selectedTButtonText,UI_Colors::unselectedTButtonText,
            UI_Colors::selectedTButton,UI_Colors::unselectedTButton},
        {   {
                formattedText::verHistorial[0],
                formattedText::verHistorial[1],
                formattedText::verHistorial[2],
            }, {9,11}, // POS
            UI_Colors::selectedTButtonText,UI_Colors::unselectedTButtonText,
            UI_Colors::selectedTButton,UI_Colors::unselectedTButton},
        {   {
                formattedText::volver[0],
                formattedText::volver[1],
                formattedText::volver[2],
            }, {10,16}, // POS
            UI_Colors::selectedSButtonText,UI_Colors::unselectedSButtonText,
            UI_Colors::selectedSButton,UI_Colors::unselectedSButton} };
}

namespace selectionMaps
{
    struct List_4Way
    {
        int id;
        bool isReactive;

        List_4Way* left;
        List_4Way* right;
        List_4Way* up;
        List_4Way* down;
    };
    using selectMap = List_4Way*;

    // ******************************* Main Menu *******************************
    // La id es la id del orden de la lista de opciones. Ej: lista[i] -> i = id
    selectMap newNode(int id, bool isReactive = false);
    selectMap createMainMenuMap();
    selectMap createReportesMap();

    inline selectMap mainMenuMap{ createMainMenuMap() };
    inline selectMap reportesMap{ createReportesMap() };

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
// Coords
COORD GetCursorPosition();
void gotoCOORD(COORD);
void printColor(const std::string_view&, const int&, const int& = 0);

// Printing Functions
void printMainMenu();
void printWindow(const short& sizeX, const short& sizeY, COORD pos, const int& colorFG, const int& colorBG);
void printCOORD(const std::string_view&, const COORD&);
void clearMainWindow(); 
// Console
void setWindowSize(int, int);
void lockConsole();

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

template <int N, int T>  // Se encarga de permitirle al usuario elegir una opcion usando colorcitos y variables con nombres largos que no se entienden a primera vista   
int setSelection(const selectionLists::selectionMember<T> optionList[N], selectionMaps::selectMap& map)
{
    int inputCH{};
    do
    {
        // Print Selected
        printFormat(optionList[map->id].displaySet, optionList[map->id].displayPos, optionList[map->id].FGselectColor, optionList[map->id].BGselectColor);
        // Select
        inputCH = _getch();
        if (inputCH == 13) break;
        else if (inputCH && inputCH != 224);
        else
        {
            printFormat(optionList[map->id].displaySet, optionList[map->id].displayPos, optionList[map->id].FGunselectColor, optionList[map->id].BGunselectColor);
            switch (inputCH = _getch())
            {
            case keys::keyLEFT:

                if (map->left == NULL) break;
                else if (map->left->isReactive) map->left->right = map;

                if (map->isReactive)
                {
                    selectionMaps::selectMap tempMap = map;
                    map = map->left;
                    tempMap->left = NULL;
                }
                else map = map->left;

                break;
            case keys::keyRIGHT:

                if (map->right == NULL) break;
                else if (map->right->isReactive) map->right->left = map;

                if (map->isReactive)
                {
                    selectionMaps::selectMap tempMap = map;
                    map = map->right;
                    tempMap->right = NULL;
                }
                else map = map->right;

                break;
            case keys::keyDOWN:

                if (map->down == NULL) break;
                else if (map->down->isReactive) map->down->up = map;

                if (map->isReactive)
                {
                    selectionMaps::selectMap tempMap = map;
                    map = map->down;
                    tempMap->down = NULL;
                }
                else map = map->down;

                break;
            case keys::keyUP:

                if (map->up == NULL) break;
                else if (map->up->isReactive) map->up->down = map;

                if (map->isReactive)
                {
                    selectionMaps::selectMap tempMap = map;
                    map = map->up;
                    tempMap->up = NULL;
                }
                else map = map->up;

                break;
            }
        }
    } while (1);
    return map->id;
}

template <int N, int T>
void printButtons(const selectionLists::selectionMember<T> optionList[N])
{
    for (int i{ 0 }; i < N; ++i)
    {
        printFormat(optionList[i].displaySet, optionList[i].displayPos, optionList[i].FGunselectColor, optionList[i].BGunselectColor);
    }
}