#include "../headers/base.h"
#include "../headers/inputs.h"
#include "../headers/efectos.h"

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <string.h>


static uint32_t hash_tarea(const Base* b);

Base crear_base()
{
    Base b;

    input_string_alfanumerico("Ingrese el nombre de la tarea", b.nombre, sizeof(b.nombre), 0);

    input_string_alfanumerico("Describa la tarea", b.desc, sizeof(b.desc), 0);

    b.prioridad = input_entero_en_rango("Ingrese la prioridad de la tarea", 1, 255);

    b.fecha_creacion = (uint64_t)time(NULL);

    b.id = hash_tarea(&b);

    return b;

}


void mostrar_base(const Base* b)
{
    const time_t temp = b->fecha_creacion;
    char f_creacion[20];
    strftime(f_creacion, sizeof(f_creacion), "%a %b %d, %Y", localtime(&temp));

    printf("Nombre: %s | Tipo: %s | Prioridad: %u\n", b->nombre, ARR_TIPOS[b->tipo], b->prioridad);
    printf("Descripción: %s\n", b->desc);
    printf("Fecha de creación: %s\n", f_creacion);
}


void actualizar_base(Base* b)
{
    limpiar_pantalla();
    printf($E_UNDERLINE""$E_BOLD"Actualizando %s: %s\n\n"$RESET, ARR_TIPOS[b->tipo], b->nombre);

    char nuevo_nombre[32];
    char nueva_desc[128];

    input_string_alfanumerico("Ingrese el nuevo nombre (deje en blanco si no desea cambiar el valor)", nuevo_nombre, sizeof(nuevo_nombre), 1);
    input_string_alfanumerico("Ingrese la nueva descripción (deje en blanco si no desea cambiar el valor)", nueva_desc, sizeof(nueva_desc), 1);
    const uint8_t nueva_prioridad = input_entero_en_rango("Ingrese la nueva prioridad", 0, 255);

    if (nuevo_nombre[0] != '\0')
    {
        strncpy(b->nombre, nuevo_nombre, sizeof(b->nombre) - 1);
        b->nombre[sizeof(b->nombre) - 1] = '\0';
    }

    if (nueva_desc[0] != '\0')
    {
        strncpy(b->desc, nueva_desc, sizeof(b->desc) - 1);
        b->desc[sizeof(b->desc) - 1] = '\0';
    }

    b->prioridad = nueva_prioridad;
}


static uint32_t hash_tarea(const Base* b)
{
    uint32_t hash = 5381;
    int c;

    char buffer[512];
    snprintf(buffer, sizeof(buffer), "%s|%s|%llu", b->nombre, b->desc, b->fecha_creacion);

    const char* ptr = buffer;
    while ((c = *ptr++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}