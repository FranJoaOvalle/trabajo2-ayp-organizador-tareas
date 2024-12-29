#include "../headers/base.h"
#include "../headers/inputs.h"
#include "../headers/tarea.h"
#include "../headers/efectos.h"

#include <stdio.h>
#include <time.h>

static void mostrar_tarea_acotada(const Tarea* t);


Tarea crear_tarea()
{
    printf($E_UNDERLINE""$E_BOLD"Creando nueva tarea:\n\n"$RESET);

    Tarea t;

    t.base = crear_base();
    t.base.tipo = TAREA;
    
    t.fecha_inicio = input_fecha("Ingrese la fecha de inicio");

    t.fecha_fin = input_fecha("Ingrese la fecha de termino");

    t.estado = PENDIENTE;

    printf($C_VERDE"Tarea creada correctamente!\n"$RESET);

    return t;
}


void mostrar_tarea(const Tarea* t)
{
    const time_t ini = t->fecha_inicio;
    const time_t fin = t->fecha_fin;

    char f_inicio[20];
    char f_fin[20];

    strftime(f_inicio, sizeof(f_inicio), "%d-%m-%Y %H:%M:%S (%a %b %d, %Y)", localtime(&ini));
    strftime(f_fin, sizeof(f_fin), "%a %b %d, %Y", localtime(&fin));

    mostrar_base(&t->base);
    printf("Fecha de inicio: %s\n", f_inicio);
    printf("Fecha de fin: %s\n", f_fin);
    printf("Estado de la tarea: %s\n\n", ARR_ESTADOS[t->estado]);
}


void mostrar_listado_tareas(const Tarea bd_tareas[], const int cant_tareas)
{
    int i;
    printf($E_UNDERLINE""$E_BOLD"Listando todas las tareas:\n\n"$RESET);
    for (i = 0; i < cant_tareas; i++) mostrar_tarea(&bd_tareas[i]);
}


void mostrar_listado_tareas_acotado(const Tarea bd_tareas[], const int cant_tareas)
{
    int i;
    for (i = 0; i < cant_tareas; i++)
    {
        printf($E_UNDERLINE"Tarea %d"$RESET": ", i+1);
        mostrar_tarea_acotada(&bd_tareas[i]);
    }
}


void actualizar_tarea(Tarea* t)
{
    actualizar_base(&t->base);

    const Estado nuevo_estado = input_estado("Ingrese el nuevo estado de la tarea");

    t->estado = nuevo_estado;

    printf($C_VERDE"Tarea actualizada correctamente!\n"$RESET);
}


static void mostrar_tarea_acotada(const Tarea* t)
{
    printf("%s --- %s\n", t->base.nombre, t->base.desc);
}