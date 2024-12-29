#ifndef SORTS_H
#define SORTS_H

#include "estructuras.h"


void ordenar_tareas_prioridad(const Tarea bd_tareas[], int cant_tareas);
void ordenar_tareas_fecha(const Tarea bd_tareas[], int cant_tareas);
void ordenar_recordatorios_prioridad(const Recordatorio bd_recordatorios[], int cant_recordatorios);
void ordenar_recordatorios_fecha(const Recordatorio bd_recordatorios[], int cant_recordatorios);

#endif //SORTS_H
