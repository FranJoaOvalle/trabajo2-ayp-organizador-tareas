#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include "estructuras.h"


void buscar_tarea_nombre(const Tarea bd_tareas[], int cant_tareas);
void buscar_recordatorio_nombre(const Recordatorio bd_recordatorios[], int cant_recordatorios);
void buscar_tarea_por_estado(const Tarea bd_tareas[], int cant_tareas);

void buscar_tareas_con_etiqueta(const Tarea bd_tareas[], int cant_tareas,
                                const Etiqueta bd_etiquetas[], int cant_etiquetas,
                                const Relacion bd_relaciones[], int cant_relaciones);

void buscar_recordatorios_con_etiqueta(const Recordatorio bd_recordatorios[], int cant_recordatorios,
                                       const Etiqueta bd_etiquetas[], int cant_etiquetas,
                                       const Relacion bd_relaciones[], int cant_relaciones);

#endif //BUSQUEDA_H
