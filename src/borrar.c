#include "../headers/borrar.h"
#include "../headers/estructuras.h"
#include "../headers/inputs.h"
#include "../headers/recordatorio.h"
#include "../headers/tarea.h"

#include <stdint.h>


static void borrar_relaciones(Relacion bd_relaciones[], int* cant_relaciones, uint32_t id_base_borrada);


void borrar_tarea(Tarea bd_tareas[], int* cant_tareas, Relacion bd_relaciones[], int *cant_relaciones)
{
    int i;

    mostrar_listado_tareas_acotado(bd_tareas, *cant_tareas);
    const uint32_t indice_tarea_borrada = input_entero_en_rango("Ingrese el número de la tarea a borrar",
        1, *cant_tareas) - 1;

    const uint32_t id_tarea_borrada = bd_tareas[indice_tarea_borrada].base.id;

    borrar_relaciones(bd_relaciones, cant_relaciones, id_tarea_borrada);

    for (i = indice_tarea_borrada; i < *cant_tareas - 1; i++) bd_tareas[i] = bd_tareas[i + 1];

    (*cant_tareas)--;
}


void borrar_recordatorio(Recordatorio bd_recordatorios[], int* cant_recordatorios, Relacion bd_relaciones[], int *cant_relaciones)
{
    int i;

    mostrar_listado_recordatorios_acotado(bd_recordatorios, *cant_recordatorios);
    const uint32_t indice_recordatorio_borrado = input_entero_en_rango("Ingrese el número del recordatorio a borrar",
        1, *cant_recordatorios) - 1;

    const uint32_t id_recordatorio_borrado = bd_recordatorios[indice_recordatorio_borrado].base.id;

    borrar_relaciones(bd_relaciones, cant_relaciones, id_recordatorio_borrado);

    for (i = indice_recordatorio_borrado; i < *cant_recordatorios - 1; i++) bd_recordatorios[i] = bd_recordatorios[i + 1];

    (*cant_recordatorios)--;
}


static void borrar_relaciones(Relacion bd_relaciones[], int* cant_relaciones, const uint32_t id_base_borrada)
{
    int i, j;

    for (i = 0; i < *cant_relaciones; i++)
    {
        if (bd_relaciones[i].id_base == id_base_borrada)
        {
            for (j = i; j < *cant_relaciones - 1; j++) bd_relaciones[j] = bd_relaciones[j + 1];
            (*cant_relaciones)--;
            i--;
        }
    }
}
