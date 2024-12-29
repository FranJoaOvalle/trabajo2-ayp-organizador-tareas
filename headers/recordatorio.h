#ifndef RECORDATORIO_H
#define RECORDATORIO_H

#include "estructuras.h"


Recordatorio crear_recordatorio();
void mostrar_recordatorio(const Recordatorio* r);
void actualizar_recordatorio(Recordatorio* r);
void mostrar_listado_recordatorios(const Recordatorio recordatorios[], int cant_recordatorios);
void mostrar_listado_recordatorios_acotado(const Recordatorio recordatorios[], int cant_recordatorios);

#endif // RECORDATORIO_H