#include "../headers/sorts.h"
#include "../headers/estructuras.h"
#include "../headers/efectos.h"
#include "../headers/recordatorio.h"
#include "../headers/tarea.h"

#include <stdio.h>
#include <stdlib.h>


void ordenar_tareas_prioridad(const Tarea bd_tareas[], const int cant_tareas)
{
    int i, j;
    int *indices = malloc(cant_tareas * sizeof(int));
    if (!indices)
    {
        printf($B_ROJO"ERROR FATAL: No se pudo reservar memoria.\n"$RESET);
        exit(1);
    }

    for (i = 0; i < cant_tareas; i++) indices[i] = i;

    for (i = 0; i < cant_tareas - 1; i++)
    {
        for (j = 0; j < cant_tareas - i - 1; j++)
        {
            if (bd_tareas[indices[j]].base.prioridad < bd_tareas[indices[j + 1]].base.prioridad)
            {
                const int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf($E_UNDERLINE""$E_BOLD"Tareas ordenadas por prioridad:\n\n"$RESET);
    for (i = 0; i < cant_tareas; i++)
    {
        const int index = indices[i];
        mostrar_tarea(&bd_tareas[index]);
    }
    free(indices);
}


void ordenar_tareas_fecha(const Tarea bd_tareas[], const int cant_tareas)
{
    int i, j;
    int *indices = malloc(cant_tareas * sizeof(int));
    if (!indices)
    {
        printf($B_ROJO"ERROR FATAL: No se pudo reservar memoria.\n"$RESET);
        exit(1);
    }

    for (i = 0; i < cant_tareas; i++) indices[i] = i;

    for (i = 0; i < cant_tareas - 1; i++)
    {
        for (j = 0; j < cant_tareas - i - 1; j++)
        {
            if (bd_tareas[indices[j]].base.fecha_creacion > bd_tareas[indices[j + 1]].base.fecha_creacion)
            {
                const int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf($E_UNDERLINE""$E_BOLD"Tareas ordenadas por fecha de creación:\n\n"$RESET);
    for (i = 0; i < cant_tareas; i++)
    {
        const int index = indices[i];
        mostrar_tarea(&bd_tareas[index]);
    }
    free(indices);
}


void ordenar_recordatorios_prioridad(const Recordatorio bd_recordatorios[], const int cant_recordatorios)
{
    int i, j;
    int *indices = malloc(cant_recordatorios * sizeof(int));
    if (!indices)
    {
        printf($B_ROJO"ERROR FATAL: No se pudo reservar memoria.\n"$RESET);
        exit(1);
    }

    for (i = 0; i < cant_recordatorios; i++) indices[i] = i;

    for (i = 0; i < cant_recordatorios - 1; i++)
    {
        for (j = 0; j < cant_recordatorios - i - 1; j++)
        {
            if (bd_recordatorios[indices[j]].base.prioridad < bd_recordatorios[indices[j + 1]].base.prioridad)
            {
                const int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf($E_UNDERLINE""$E_BOLD"Recordatorios ordenados por prioridad:\n\n"$RESET);
    for (i = 0; i < cant_recordatorios; i++)
    {
        const int index = indices[i];
        mostrar_recordatorio(&bd_recordatorios[index]);
    }
    free(indices);
}


void ordenar_recordatorios_fecha(const Recordatorio bd_recordatorios[], const int cant_recordatorios)
{
    int i, j;
    int *indices = malloc(cant_recordatorios * sizeof(int));
    if (!indices)
    {
        printf($B_ROJO"ERROR FATAL: No se pudo reservar memoria.\n"$RESET);
        exit(1);
    }

    for (i = 0; i < cant_recordatorios; i++) indices[i] = i;

    for (i = 0; i < cant_recordatorios - 1; i++)
    {
        for (j = 0; j < cant_recordatorios - i - 1; j++)
        {
            if (bd_recordatorios[indices[j]].base.fecha_creacion > bd_recordatorios[indices[j + 1]].base.fecha_creacion)
            {
                const int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf($E_UNDERLINE""$E_BOLD"Recordatorios ordenados por fecha de creación:\n\n"$RESET);
    for (i = 0; i < cant_recordatorios; i++)
    {
        const int index = indices[i];
        mostrar_recordatorio(&bd_recordatorios[index]);
    }
    free(indices);
}