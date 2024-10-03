#include "tempFile.h"


/*================================================================================================================================================================
                        FUNCTIONS
================================================================================================================================================================*/

void generateComputersList(doubleList<Computadora>*& target, const int& amount)
{
    for (int i{ 0 }; i < amount; ++i)
    {
        target->append(createEntry(Computadora{ i + 1,1.0f,{"Comp A","Comp B","Comp C","Comp D"},"Disponible",0 }));
    }
}