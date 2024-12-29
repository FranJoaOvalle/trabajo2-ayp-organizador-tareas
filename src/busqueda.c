#include "../headers/busqueda.h"
#include "../headers/tarea.h"
#include "../headers/recordatorio.h"
#include "../headers/inputs.h"
#include "../headers/etiqueta.h"
#include "../headers/efectos.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>


static void str_to_lower(char* str);


void buscar_tarea_nombre(const Tarea bd_tareas[], const int cant_tareas)
{
    int i;
    char target[32];
    input_string_alfanumerico("Ingrese el nombre que desea buscar", target, sizeof(target), 0);

    str_to_lower(target);

    int encontrado = 0;

    limpiar_pantalla();
    for (i = 0; i < cant_tareas; i++)
    {
        char tarea_nombre_lower[32];
        strcpy(tarea_nombre_lower, bd_tareas[i].base.nombre);
        str_to_lower(tarea_nombre_lower);

        if (strcmp(target, tarea_nombre_lower) == 0)
        {
            printf($E_UNDERLINE""$E_BOLD"Tarea exacta encontrada:\n"$RESET);
            mostrar_tarea(&bd_tareas[i]);
            encontrado = 1;
        }
        else if (strstr(tarea_nombre_lower, target) != NULL)
        {
            printf($E_UNDERLINE""$E_BOLD"Posible tarea encontrada (coincidencia parcial):\n"$RESET);
            mostrar_tarea(&bd_tareas[i]);
            encontrado = 1;
        }
    }

    if (!encontrado) printf("No se encontró ninguna tarea que coincida con el criterio de búsqueda.\n");
}


void buscar_recordatorio_nombre(const Recordatorio bd_recordatorios[], const int cant_recordatorios)
{
    int i;
    char target[32];
    input_string_alfanumerico("Ingrese el nombre que desea buscar", target, sizeof(target), 0);

    str_to_lower(target);

    int encontrado = 0;

    limpiar_pantalla();
    for (i = 0; i < cant_recordatorios; i++)
    {
        char recordatorio_nombre_lower[32];
        strcpy(recordatorio_nombre_lower, bd_recordatorios[i].base.nombre);
        str_to_lower(recordatorio_nombre_lower);

        if (strcmp(target, recordatorio_nombre_lower) == 0)
        {
            printf($E_UNDERLINE""$E_BOLD"Recordatorio exacto encontrado:\n"$RESET);
            mostrar_recordatorio(&bd_recordatorios[i]);
            encontrado = 1;
        }
        else if (strstr(recordatorio_nombre_lower, target) != NULL)
        {
            printf($E_UNDERLINE""$E_BOLD"Posible recordatorio (coincidencia parcial):\n"$RESET);
            mostrar_recordatorio(&bd_recordatorios[i]);
            encontrado = 1;
        }
    }

    if (!encontrado) printf("No se encontró ningún recordatorio que coincida con el criterio de búsqueda.\n");
}


void buscar_tarea_por_estado(const Tarea bd_tareas[], const int cant_tareas)
{
    int i, encontrado = 0;

    const Estado target = input_estado("Ingrese el estado de tareas a buscar");

    limpiar_pantalla();
    for (i = 0; i < cant_tareas; i++)
    {
        if (bd_tareas[i].estado == target)
        {
            if (!encontrado) printf($E_UNDERLINE""$E_BOLD"Tarea(s) encontrada(s):\n\n"$RESET);
            mostrar_tarea(&bd_tareas[i]);
            encontrado = 1;
        }
    }

    if (!encontrado) printf("No se encontró ninguna tarea que coincida con el criterio de búsqueda.\n");
}


void buscar_tareas_con_etiqueta(const Tarea bd_tareas[], const int cant_tareas,
                                const Etiqueta bd_etiquetas[], const int cant_etiquetas,
                                const Relacion bd_relaciones[], const int cant_relaciones)
{
    int i, j;
    int encontrado = 0;

    mostrar_listado_etiqueta(bd_etiquetas, cant_etiquetas);
    const int index_e = input_entero_en_rango(
        "\nSeleccione el número de etiqueta a buscar", 1, cant_etiquetas) - 1;

    const unsigned int id_etiqueta = bd_etiquetas[index_e].id_etiqueta;

    limpiar_pantalla();
    for (i = 0; i < cant_relaciones; i++)
    {
        if (bd_relaciones[i].id_etiqueta == id_etiqueta)
        {
            for (j = 0; j < cant_tareas; j++)
            {
                if (bd_relaciones[i].id_base == bd_tareas[j].base.id)
                {
                    if (!encontrado)
                        printf($E_UNDERLINE""$E_BOLD"Tareas encontradas con la etiqueta '%s'"$RESET":\n\n",
                            bd_etiquetas[index_e].nombre_etiqueta);

                    mostrar_tarea(&bd_tareas[j]);
                    encontrado = 1;
                }
            }
        }
    }
    if (!encontrado) printf("No se encontraron tareas con la etiqueta seleccionada.\n");
}


void buscar_recordatorios_con_etiqueta(const Recordatorio bd_recordatorios[], const int cant_recordatorios,
                                       const Etiqueta bd_etiquetas[], const int cant_etiquetas,
                                       const Relacion bd_relaciones[], const int cant_relaciones)
{
    int i, j;
    int encontrado = 0;

    mostrar_listado_etiqueta(bd_etiquetas, cant_etiquetas);
    const int index_e = input_entero_en_rango(
        "\nSeleccione el número de etiqueta a buscar", 1, cant_etiquetas) - 1;

    const unsigned int id_etiqueta = bd_etiquetas[index_e].id_etiqueta;

    limpiar_pantalla();
    for (i = 0; i < cant_relaciones; i++)
    {
        if (bd_relaciones[i].id_etiqueta == id_etiqueta)
        {
            for (j = 0; j < cant_recordatorios; j++)
            {
                if (bd_relaciones[i].id_base == bd_recordatorios[j].base.id)
                {
                    if (!encontrado)
                        printf($E_UNDERLINE""$E_BOLD"Relaciones encontradas con la etiqueta '%s'"$RESET":\n\n",
                            bd_etiquetas[index_e].nombre_etiqueta);

                    mostrar_recordatorio(&bd_recordatorios[j]);
                    encontrado = 1;
                }
            }
        }
    }
    if (!encontrado) printf("No se encontraron recordatorios con la etiqueta seleccionada.\n");
}



static void str_to_lower(char* str)
{
    int i;
    for (i = 0; str[i]; i++) str[i] = tolower(str[i]);
}