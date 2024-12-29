#ifndef BASE_DATOS_H
#define BASE_DATOS_H

#include "estructuras.h"


void cargar_tareas(Tarea bd_tareas[], int* cant_tareas);
void cargar_recordatorios(Recordatorio bd_recordatorios[], int* cant_recordatorios);
void cargar_etiquetas(Etiqueta bd_etiquetas[], int* cant_etiquetas);
void cargar_relaciones(Relacion bd_relaciones[], int* cant_relaciones);

void guardar_tareas(const Tarea bd_tareas[], int cant_tareas);
void guardar_recordatorios(const Recordatorio bd_recordatorios[], int cant_recordatorios);
void guardar_etiquetas(const Etiqueta bd_etiquetas[], int cant_etiquetas);
void guardar_relaciones(const Relacion bd_relaciones[], int cant_relaciones);

#endif // BASE_DATOS_H
