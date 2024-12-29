#ifndef RELACIONES_H
#define RELACIONES_H

#include "estructuras.h"

Relacion crear_relacion_tarea(const Tarea bd_tareas[], int cant_tareas, const Etiqueta bd_etiquetas[], int cant_etiquetas);
Relacion crear_relacion_recordatorio(const Recordatorio bd_recordatorios[], int cant_recordatorios,
                                     const Etiqueta bd_etiquetas[], int cant_etiquetas);

#endif //RELACIONES_H
