#ifndef TAREA_H
#define TAREA_H

#include "estructuras.h"


Tarea crear_tarea();
void mostrar_tarea(const Tarea* t);
void actualizar_tarea(Tarea* t);
void mostrar_listado_tareas(const Tarea bd_tareas[], int cant_tareas);
void mostrar_listado_tareas_acotado(const Tarea bd_tareas[], int cant_tareas);

#endif // TAREA_H