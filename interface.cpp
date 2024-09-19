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
    
    inline selectMap createMainMenuMap()
    {
        // Node [5]
        selectMap map = newNode(5);
        // Node [6]
        map->right = newNode(6, true);
        // Node [4]
        map->up = newNode(4); map->up->down = map; map->up->right = map->right;
        map = map->up;
        // Node [3]
        map->up = newNode(3); map->up->down = map; map->up->right = map->right;
        map = map->up;
        // Node [2]
        map->up = newNode(2); map->up->down = map; map->up->right = map->right;
        map = map->up;
        // Node [1]
        map->up = newNode(1); map->up->down = map; map->up->right = map->right;
        map = map->up;
        // Node [0]
        map->up = newNode(0); map->up->down = map; map->up->right = map->right;
        map = map->up;
        // End
        return map;
    }/*
    */
}
/*================================================================================================================================================================
                        FUNCTIONS
================================================================================================================================================================*/

COORD GetCursorPosition()
{
    //HANDLE hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    return consoleInfo.dwCursorPosition;
}

void gotoCOORD(COORD position)
{
    //HANDLE console{ GetStdHandle(STD_OUTPUT_HANDLE) };
    SetConsoleCursorPosition(hConsole, position);
}

void printColor(const std::string_view& textToPrint,const int& colorCode, const int& backgroundColor)
{
    //HANDLE console{ GetStdHandle(STD_OUTPUT_HANDLE) };
    SetConsoleTextAttribute(hConsole, colorCode+16*backgroundColor); // every *15* color codes will loop
    std::cout << textToPrint;
    SetConsoleTextAttribute(hConsole, keys::defaultColor);
}

// ************************************************ Printing Functions ************************************************

// Imprime la pantalla principal del programa, no debe ser usado en un contexto normal.
void printMainMenu()
{
    printColor(menuDefs::background, color::dBlack,color::bBlack);  // Background
    
    clearMainWindow();
    COORD displayPos = { 19,13 };  // Menu Title
    printFormat(formattedText::mainTitle, { 22,5 }, UI_Colors::mainDisplay, UI_Colors::mainBackground);
    gotoCOORD(displayPos); printColor("========================================================================================================================", UI_Colors::mainDisplay);

    printFormat(formattedText::gestionDeComputadoras, { 54,15 },UI_Colors::unselectedButtonText, UI_Colors::unselectedButton); // Print Buttons
    printFormat(formattedText::gestionDeSesiones, { 54,20 }, UI_Colors::unselectedButtonText, UI_Colors::unselectedButton);
    printFormat(formattedText::gestionDeClientes, { 54,25 }, UI_Colors::unselectedButtonText, UI_Colors::unselectedButton);
    printFormat(formattedText::facturacion, { 54,30 }, UI_Colors::unselectedButtonText, UI_Colors::unselectedButton);
    printFormat(formattedText::reservas, { 54,35 }, UI_Colors::unselectedButtonText, UI_Colors::unselectedButton);
    printFormat(formattedText::reportes, { 54,40 }, UI_Colors::unselectedButtonText, UI_Colors::unselectedButton);
    printFormat(formattedText::salir, { 115,38 }, UI_Colors::unselectedSButtonText, UI_Colors::unselectedSButton);


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
    COORD displayPos = g_mainWindowStartPOS;  
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

// Console Functions


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