// Includes
#include <windows.h>
#include <iostream>

#include "interface.h"
/*================================================================================================================================================================
                        GLOBAL VARIABLES
================================================================================================================================================================*/



HANDLE hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };
/*================================================================================================================================================================
                        NAMESPACES
================================================================================================================================================================*/

namespace selectionMaps
{
    // ******************************* Main Menu *******************************

    // La id es la id del orden de la lista de opciones. Ej: lista[i] -> i = id
    inline selectMap newNode(int id, bool isReactive)
    {
        selectMap createdNode = new(struct List_4Way);
        createdNode->id = id;
        createdNode->isReactive = isReactive;

        createdNode->left = NULL;
        createdNode->right = NULL;
        createdNode->up = NULL;
        createdNode->down = NULL;

        return createdNode;
    }
    // Crea el mapa de opciones para el menu principal
    inline selectMap createMainMenuMap()
    {
        // Node [5]
        selectMap map = newNode(5);
        // Node [6]
        map->right = newNode(6, true);
        // Nodes [4~0]
        for (int i{ 4 }; i >= 0; --i)
        {
            map->up = newNode(i); map->up->down = map; map->up->right = map->right;
            map = map->up;
        }
        return map;
    }
    // Crea el mapa de opciones para la opcion de reportes
    inline selectMap createReportesMap()
    {
        // Node [2]
        selectMap map = newNode(2);
        // Nodes [1~0]
        for (int i{ 1 }; i >= 0; --i)
        {
            map->up = newNode(i); map->up->down = map;
            map = map->up;
        }
        return map;
    }
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
    SetConsoleTextAttribute(hConsole, colorCode+16*backgroundColor); // every *16* color codes will loop
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
    gotoCOORD({19,13}); printColor("========================================================================================================================", UI_Colors::mainDisplay);
    printButtons<7,3>(selectionLists::mainMenuOptions);
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
        printColor("                                                                                                                        ", keys::defaultColor);
        if (i > 0) printColor("  ", keys::defaultColor, color::dWhite);
        ++displayPos.Y;
    }
    displayPos.X += 2;
    gotoCOORD(displayPos); printColor("                                                                                                                        ", keys::defaultColor, color::dWhite);
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


// ************************************************ Console Functions ************************************************

// Sets the size of the Console (cmd)
void setWindowSize(int width, int height)
{
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the screen buffer size
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Set the window size
    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

// Forbids any resizing on the console
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