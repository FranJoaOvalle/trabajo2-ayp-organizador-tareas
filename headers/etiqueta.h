#ifndef ETIQUETA_H
#define ETIQUETA_H

#include "estructuras.h"


Etiqueta crear_etiqueta(int index);
void mostrar_etiqueta(const Etiqueta* e);
void mostrar_listado_etiqueta(const Etiqueta bd_etiquetas[], int cant_etiquetas);

#endif // ETIQUETA_H