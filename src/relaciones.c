#include "../headers/relaciones.h"
#include "../headers/estructuras.h"
#include "../headers/tarea.h"
#include "../headers/inputs.h"
#include "../headers/etiqueta.h"

#include <stdio.h>

#include "recordatorio.h"

Relacion crear_relacion_tarea(const Tarea bd_tareas[], const int cant_tareas,
                              const Etiqueta bd_etiquetas[], const int cant_etiquetas)
{
    mostrar_listado_tareas_acotado(bd_tareas, cant_tareas);
    const int index_t = input_entero_en_rango(
        "\nSeleccione el número de tarea para asignar etiqueta", 1, cant_tareas) - 1;

    mostrar_listado_etiqueta(bd_etiquetas, cant_etiquetas);
    const int index_e = input_entero_en_rango(
        "\nSeleccione el número de etiqueta a asignar", 1, cant_etiquetas) - 1;

    const Relacion rel = {
        bd_tareas[index_t].base.id,
        bd_tareas[index_t].base.tipo,
        bd_etiquetas[index_e].id_etiqueta
    };

    printf("Relación asignada exitosamente entre tarea '%s' y etiqueta '%s'.\n",
           bd_tareas[index_t].base.nombre, bd_etiquetas[index_e].nombre_etiqueta);

    return rel;
}


Relacion crear_relacion_recordatorio(const Recordatorio bd_recordatorios[], const int cant_recordatorios,
                                     const Etiqueta bd_etiquetas[], const int cant_etiquetas)
{
    mostrar_listado_recordatorios_acotado(bd_recordatorios, cant_recordatorios);
    const int index_r = input_entero_en_rango(
        "\nSeleccione el número de recordatorio para asignar etiqueta", 1, cant_recordatorios) - 1;

    mostrar_listado_etiqueta(bd_etiquetas, cant_etiquetas);
    const int index_e = input_entero_en_rango(
        "\nSeleccione el número de etiqueta a asignar", 1, cant_etiquetas) - 1;

    const Relacion rel = {
        bd_recordatorios[index_r].base.id,
        bd_recordatorios[index_r].base.tipo,
        bd_etiquetas[index_e].id_etiqueta
    };

    printf("Relación asignada exitosamente entre recordatorio '%s' y etiqueta '%s'.\n",
           bd_recordatorios[index_r].base.nombre, bd_etiquetas[index_e].nombre_etiqueta);

    return rel;
}
