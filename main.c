#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <signal.h>

#include "headers/etiqueta.h"
#include "headers/relaciones.h"
#include "headers/base_datos.h"
#include "headers/estructuras.h"
#include "headers/recordatorio.h"
#include "headers/tarea.h"
#include "headers/inputs.h"
#include "headers/sorts.h"
#include "headers/busqueda.h"
#include "headers/efectos.h"
#include "headers/borrar.h"

#define MAX_TAREAS 100
#define MAX_RECORDATORIOS 100
#define MAX_ETIQUETAS 100
#define MAX_RELACIONES 1000

Recordatorio bd_recordatorios[MAX_RECORDATORIOS];
Tarea bd_tareas[MAX_TAREAS];
Etiqueta bd_etiquetas[MAX_ETIQUETAS];
Relacion bd_relaciones[MAX_RELACIONES];

int cant_tareas, cant_recordatorios, cant_etiquetas, cant_relaciones;


void mostrar_menu(void);
void mostrar_menu_tareas(void);
void mostrar_menu_recordatorios(void);
void mostrar_menu_etiquetas(void);
void mostrar_usuario(void);
void guardar_al_salir(void);


int main(void)
{
    atexit(guardar_al_salir);
    signal(SIGINT, exit);
    signal(SIGTERM, exit);
    #ifndef _WIN32
        signal(SIGHUP, exit);
    #endif

    setlocale(LC_ALL, "");

    cargar_tareas(bd_tareas, &cant_tareas);
    cargar_recordatorios(bd_recordatorios, &cant_recordatorios);
    cargar_etiquetas(bd_etiquetas, &cant_etiquetas);
    cargar_relaciones(bd_relaciones, &cant_relaciones);

    int opcion;
    do
    {
        mostrar_menu();
        scanf("%d", &opcion);
        while (getchar() != '\n') {}

        switch(opcion)
        {
            case 1:
                mostrar_menu_tareas();
                break;

            case 2:
                mostrar_menu_recordatorios();
                break;

            case 3:
                mostrar_menu_etiquetas();
                break;

            case 4:
                limpiar_pantalla();
                printf("Presione cualquier tecla para cerrar el programa.\n");
                getchar();
                exit(0);

            default:
                break;
        }
    }
    while (opcion != 4);
}


void mostrar_menu(void)
{
    limpiar_pantalla();
    printf($C_CYAN"===== MENU PRINCIPAL =====\n\n"$RESET);
    mostrar_usuario();
    printf("1. Menu de Tareas\n");
    printf("2. Menu de Recordatorios\n");
    printf("3. Menu de Etiquetas\n");
    printf("4. Salir\n");
    printf("\nSeleccione una opción: ");
}


void mostrar_menu_tareas(void)
{
    int opcion_sub;
    do
    {
        limpiar_pantalla();
        printf($C_CYAN"===== MENU DE TAREAS =====\n\n"$RESET);
        printf("1. Crear nueva tarea\n");
        printf("2. Actualizar tarea\n");
        printf("3. Borrar tarea\n");
        printf("4. Mostrar listado de tareas\n");
        printf("5. Mostrar tareas por prioridad\n");
        printf("6. Mostrar tareas por fecha de creación\n");
        printf("7. Buscar tareas por nombre\n");
        printf("8. Buscar tareas por estado\n");
        printf("9. Volver\n");
        printf("\nSeleccione una opción: ");

        scanf("%d", &opcion_sub);
        while (getchar() != '\n') {}

        switch(opcion_sub)
        {
            case 1:
                limpiar_pantalla();
                if (cant_tareas >= MAX_TAREAS) printf($C_ROJO"ERROR: Ya ha alcanzado el máximo de tareas.\n"$RESET);
                else {
                    bd_tareas[cant_tareas] = crear_tarea();
                    cant_tareas++;
                }
                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 2:
                limpiar_pantalla();
                if (cant_tareas == 0) printf($C_AMARILLO"ADVERTENCIA: No existen tareas disponibles.\n"$RESET);
                else {
                    mostrar_listado_tareas_acotado(bd_tareas, cant_tareas);
                    const int index = input_entero_en_rango("\nSeleccione el número de tarea que desea actualizar: ",
                        1, cant_tareas);
                    actualizar_tarea(&bd_tareas[index - 1]);
                }
                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 3:
                limpiar_pantalla();
                if (cant_tareas == 0) printf($C_AMARILLO"ADVERTENCIA: No existen tareas disponibles.\n"$RESET);
                else borrar_tarea(bd_tareas, &cant_tareas, bd_relaciones, &cant_relaciones);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 4:
                limpiar_pantalla();
                if (cant_tareas == 0) printf($C_AMARILLO"ADVERTENCIA: No existen tareas disponibles.\n"$RESET);
                else mostrar_listado_tareas(bd_tareas, cant_tareas);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 5:
                limpiar_pantalla();
                if (cant_tareas == 0) printf($C_AMARILLO"ADVERTENCIA: No existen tareas disponibles.\n"$RESET);
                else ordenar_tareas_prioridad(bd_tareas, cant_tareas);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 6:
                limpiar_pantalla();
                if (cant_tareas == 0) printf($C_AMARILLO"ADVERTENCIA: No existen tareas disponibles.\n"$RESET);
                else ordenar_tareas_fecha(bd_tareas, cant_tareas);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 7:
                limpiar_pantalla();
                if (cant_tareas == 0) printf($C_AMARILLO"ADVERTENCIA: No existen tareas disponibles.\n"$RESET);
                else buscar_tarea_nombre(bd_tareas, cant_tareas);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 8:
                limpiar_pantalla();
                if (cant_tareas == 0) printf($C_AMARILLO"ADVERTENCIA: No existen tareas disponibles.\n"$RESET);
                else buscar_tarea_por_estado(bd_tareas, cant_tareas);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 9:
            default:
                break;
        }
    }
    while(opcion_sub != 9);
}


void mostrar_menu_recordatorios(void)
{
    int opcion_sub;
    do
    {
        limpiar_pantalla();
        printf($C_CYAN"===== MENU DE RECORDATORIOS =====\n\n"$RESET);
        printf("1. Crear nuevo recordatorio\n");
        printf("2. Actualizar recordatorio\n");
        printf("3. Borrar recordatorio\n");
        printf("4. Mostrar listado de recordatorios\n");
        printf("5. Mostrar recordatorios por prioridad\n");
        printf("6. Mostrar recordatorios por fecha de creación\n");
        printf("7. Buscar recordatorios por nombre\n");
        printf("8. Volver\n");
        printf("\nSeleccione una opción: ");

        scanf("%d", &opcion_sub);
        while (getchar() != '\n') {}

        switch(opcion_sub)
        {
            case 1:
                limpiar_pantalla();
                if (cant_recordatorios >= MAX_RECORDATORIOS)
                    printf($C_ROJO"ERROR: Ya ha alcanzado el máximo de recordatorios.\n"$RESET);
                else {
                    bd_recordatorios[cant_recordatorios] = crear_recordatorio();
                    cant_recordatorios++;
                }
                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 2:
                limpiar_pantalla();
                if (cant_recordatorios == 0) printf($C_AMARILLO"ADVERTENCIA: No existen recordatorios disponibles.\n"$RESET);
                else {
                    mostrar_listado_recordatorios_acotado(bd_recordatorios, cant_recordatorios);
                    const int index = input_entero_en_rango("\nSeleccione el número de recordatorio que desea actualizar: ",
                        1, cant_recordatorios);
                    actualizar_recordatorio(&bd_recordatorios[index - 1]);
                }
                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 3:
                limpiar_pantalla();
                if (cant_recordatorios == 0) printf($C_AMARILLO"ADVERTENCIA: No existen recordatorios disponibles.\n"$RESET);
                else borrar_recordatorio(bd_recordatorios, &cant_recordatorios, bd_relaciones, &cant_relaciones);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 4:
                limpiar_pantalla();
                if (cant_recordatorios == 0) printf($C_AMARILLO"ADVERTENCIA: No existen recordatorios disponibles.\n"$RESET);
                else mostrar_listado_recordatorios(bd_recordatorios, cant_recordatorios);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 5:
                limpiar_pantalla();
                if (cant_recordatorios == 0) printf($C_AMARILLO"ADVERTENCIA: No existen recordatorios disponibles.\n"$RESET);
                else ordenar_recordatorios_prioridad(bd_recordatorios, cant_recordatorios);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 6:
                limpiar_pantalla();
                if (cant_recordatorios == 0) printf($C_AMARILLO"ADVERTENCIA: No existen recordatorios disponibles.\n"$RESET);
                else ordenar_recordatorios_fecha(bd_recordatorios, cant_recordatorios);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 7:
                limpiar_pantalla();
                if (cant_recordatorios == 0) printf($C_AMARILLO"ADVERTENCIA: No existen recordatorios disponibles.\n"$RESET);
                else buscar_recordatorio_nombre(bd_recordatorios, cant_recordatorios);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 8:
            default:
                break;
        }
    }
    while (opcion_sub != 8);
}


void mostrar_menu_etiquetas(void)
{
    int opcion_sub;
    do
    {
        limpiar_pantalla();
        printf($C_CYAN"===== MENU DE ETIQUETAS =====\n\n"$RESET);
        printf("1. Crear nueva etiqueta\n");
        printf("2. Mostrar listado de etiquetas\n");
        printf("3. Añadir etiqueta a tarea\n");
        printf("4. Añadir etiqueta a recordatorio\n");
        printf("5. Buscar tareas por etiqueta\n");
        printf("6. Buscar recordatorios por etiqueta\n");
        printf("7. Volver\n");
        printf("\nSeleccione una opción: ");

        scanf("%d", &opcion_sub);
        while (getchar() != '\n') {}

        switch(opcion_sub)
        {
            case 1:
                limpiar_pantalla();
                if (cant_etiquetas >= MAX_ETIQUETAS) printf($C_ROJO"ERROR: Ya ha alcanzado el máximo de etiquetas.\n"$RESET);
                else {
                    bd_etiquetas[cant_etiquetas] = crear_etiqueta(cant_etiquetas);
                    cant_etiquetas++;
                }
                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 2:
                limpiar_pantalla();
                if (cant_etiquetas == 0) printf($C_AMARILLO"ADVERTENCIA: No existen etiquetas disponibles.\n"$RESET);
                else mostrar_listado_etiqueta(bd_etiquetas, cant_etiquetas);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 3:
                limpiar_pantalla();
                if (cant_relaciones >= MAX_RELACIONES) {
                    printf($C_ROJO"ERROR: Ya ha alcanzado el máximo de relaciones.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                if (cant_tareas == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No hay tareas disponibles para asignar etiquetas.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                if (cant_etiquetas == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No hay etiquetas disponibles para asignar.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }

                bd_relaciones[cant_relaciones] = crear_relacion_tarea(bd_tareas, cant_tareas,
                    bd_etiquetas, cant_etiquetas);
                cant_relaciones++;

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 4:
                limpiar_pantalla();
                if (cant_relaciones >= MAX_RELACIONES) {
                    printf($C_ROJO"ERROR: Ya ha alcanzado el máximo de relaciones.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                if (cant_recordatorios == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No hay recordatorios disponibles para asignar etiquetas.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                if (cant_etiquetas == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No hay etiquetas disponibles para asignar.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }

                bd_relaciones[cant_relaciones] = crear_relacion_recordatorio(bd_recordatorios, cant_recordatorios,
                    bd_etiquetas, cant_etiquetas);
                cant_relaciones++;

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 5:
                limpiar_pantalla();
                if (cant_relaciones == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No existen relaciones entre eventos y etiquetas.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                if (cant_tareas == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No hay tareas disponibles para asignar etiquetas.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                if (cant_etiquetas == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No hay etiquetas disponibles para asignar.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                buscar_tareas_con_etiqueta(bd_tareas, cant_tareas, bd_etiquetas, cant_etiquetas,
                    bd_relaciones, cant_relaciones);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 6:
                limpiar_pantalla();
                if (cant_relaciones == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No existen relaciones entre eventos y etiquetas.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                if (cant_tareas == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No hay recordatorios disponibles para asignar etiquetas.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                if (cant_etiquetas == 0) {
                    printf($C_AMARILLO"ADVERTENCIA: No hay etiquetas disponibles para asignar.\n"$RESET);
                    printf("\nPresione Enter para continuar...\n"); getchar();
                    break;
                }
                buscar_recordatorios_con_etiqueta(bd_recordatorios, cant_recordatorios, bd_etiquetas, cant_etiquetas,
                    bd_relaciones, cant_relaciones);

                printf("\nPresione Enter para continuar...\n"); getchar();
                break;

            case 7:
            default:
                break;
        }
    }
    while (opcion_sub != 7);
}

void mostrar_usuario(void)
{
    const char* usuario;

    #ifdef _WIN32
        usuario = getenv("USERNAME");
    #else
        nombre_usuario = getenv("USER");
    #endif

    if (usuario) printf("Bienvenido, "$C_AZUL"%s"$RESET"!\n", usuario);
    else printf("Bienvenido, "$C_AZUL"Invitado"$RESET"!\n");

    printf("\n");
}


void guardar_al_salir(void)
{
    guardar_tareas(bd_tareas, cant_tareas);
    guardar_recordatorios(bd_recordatorios, cant_recordatorios);
    guardar_etiquetas(bd_etiquetas, cant_etiquetas);
    guardar_relaciones(bd_relaciones, cant_relaciones);
}