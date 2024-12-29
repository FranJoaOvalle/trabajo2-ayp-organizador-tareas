#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdint.h>


typedef enum
{
    PENDIENTE = 0,
    EN_PROGRESO = 1,
    COMPLETADO = 2,
    CANCELADA = 3
}
Estado;
extern const char* ARR_ESTADOS[4];


typedef enum
{
    RECORDATORIO = 0,
    TAREA = 1
}
Tipo;
extern const char* ARR_TIPOS[2];


typedef struct
{
    uint32_t id;
    Tipo tipo;
    char nombre[32];
    char desc[128];
    uint8_t prioridad;
    uint64_t fecha_creacion;
}
Base;


typedef struct
{
    Base base;
    unsigned int periodo;
    uint64_t fecha_objetivo;
}
Recordatorio;


typedef struct
{
    Base base;
    uint64_t fecha_inicio;
    uint64_t fecha_fin;
    Estado estado;
}
Tarea;


typedef struct
{
    uint32_t id_etiqueta;
    char nombre_etiqueta[32];
}
Etiqueta;


typedef struct
{
    uint32_t id_base;
    Tipo tipo;
    uint8_t id_etiqueta;
}
Relacion;


#endif // ESTRUCTURAS_H