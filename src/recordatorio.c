#include "../headers/base.h"
#include "../headers/recordatorio.h"
#include "../headers/inputs.h"
#include "../headers/efectos.h"

#include <stdio.h>
#include <time.h>

static void mostrar_recordatorio_acotado(const Recordatorio* r);


Recordatorio crear_recordatorio()
{
    printf($E_UNDERLINE""$E_BOLD"Creando nuevo recordatorio:\n"$RESET);

    Recordatorio r;

    r.base = crear_base();
    r.base.tipo = RECORDATORIO;
    
    r.periodo = input_entero_en_rango("Ingrese cada cuántos dias repetir el recordatorio", 0, 365);

    r.fecha_objetivo = input_fecha("Ingrese la fecha objetivo");

    printf($C_VERDE"Recordatorio creado correctamente!\n"$RESET);

    return r;
}


void mostrar_recordatorio(const Recordatorio* r)
{
    const time_t obj = r->fecha_objetivo;

    char f_objetivo[20];
    strftime(f_objetivo, sizeof(f_objetivo), "%d-%m-%Y %H:%M:%S (%a %b %d, %Y)", localtime(&obj));

    mostrar_base(&r->base);
    printf("Fecha objetivo: %s\n", f_objetivo);
    printf("Esta tarea se repetirá cada %u día(s).\n\n", r->periodo);
}


void mostrar_listado_recordatorios(const Recordatorio recordatorios[], const int cant_recordatorios)
{
    int i;
    printf($E_UNDERLINE""$E_BOLD"Listando todos los recordatorios:\n\n"$RESET);
    for (i = 0; i < cant_recordatorios; i++) mostrar_recordatorio(&recordatorios[i]);
}


void mostrar_listado_recordatorios_acotado(const Recordatorio recordatorios[], const int cant_recordatorios)
{
    int i;
    for (i = 0; i < cant_recordatorios; i++)
    {
        printf($E_UNDERLINE"Recordatorio %u"$RESET": ", i+1);
        mostrar_recordatorio_acotado(&recordatorios[i]);
    }
}


void actualizar_recordatorio(Recordatorio* r)
{
    actualizar_base(&r->base);

    const unsigned int nuevo_periodo = input_entero_en_rango("Ingrese el nuevo periodo para recordar", 0, 365);

    r->periodo = nuevo_periodo;

    printf($C_VERDE"Recordatorio actualizado correctamente!\n"$RESET);
}


static void mostrar_recordatorio_acotado(const Recordatorio* r)
{
    printf("%s --- %s\n", r->base.nombre, r->base.desc);
}