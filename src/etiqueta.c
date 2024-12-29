#include "../headers/estructuras.h"
#include "../headers/etiqueta.h"
#include "../headers/inputs.h"
#include "../headers/efectos.h"

#include <stdio.h>


Etiqueta crear_etiqueta(const int index)
{
    Etiqueta e;

    input_string_alfanumerico("Ingrese el nombre de la etiqueta", e.nombre_etiqueta, sizeof(e.nombre_etiqueta), 0);
    e.id_etiqueta = index + 1;

    return e;
}


void mostrar_listado_etiqueta(const Etiqueta bd_etiquetas[], const int cant_etiquetas)
{
    int i;
    printf($E_UNDERLINE""$E_BOLD"Listando todas las etiquetas:\n\n"$RESET);
    for (i = 0; i < cant_etiquetas; i++) mostrar_etiqueta(&bd_etiquetas[i]);
}


void mostrar_etiqueta(const Etiqueta* e)
{
    printf($E_UNDERLINE"Etiqueta #%u"$RESET": %s\n", e->id_etiqueta, e->nombre_etiqueta);
}