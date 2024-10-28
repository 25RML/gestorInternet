#include "tempFile.h"


/*================================================================================================================================================================
                        FUNCTIONS
================================================================================================================================================================*/

void generateComputersList(DoubleList<Computadora>& target, const int& amount)
{
    for (int i{ 0 }; i < amount; ++i)
    {
        target.append(target.createEntry(Computadora{ i + 1,1.0f,{"Comp A","Comp B","Comp C","Comp D"},"Disponible",0,{} }));
    }
}

DoubleList<Computadora>::Node* getByComputerID(DoubleList<Computadora> target, const int& id)
{
    if (!target.head) return nullptr;
    while ((target.head->data.ID != id) && (!target.head))
    {
        target.head = target.head->next;
    }
    return target.head;
}