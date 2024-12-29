#include "../headers/efectos.h"

#include <stdlib.h>

void limpiar_pantalla()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}