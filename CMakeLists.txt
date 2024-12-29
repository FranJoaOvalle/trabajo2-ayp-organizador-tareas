cmake_minimum_required(VERSION 3.29)
project(trabajo2_copy C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc")

include_directories(headers)

add_executable(trabajo2_copy
    headers/base.h
    headers/base_datos.h
    headers/estructuras.h
    headers/etiqueta.h
    headers/inputs.h
    headers/recordatorio.h
    headers/tarea.h
    src/base.c
    src/base_datos.c
    src/estructuras.c
    src/etiqueta.c
    src/inputs.c
    src/recordatorio.c
    src/tarea.c
    main.c
    src/sorts.c
    headers/sorts.h
    src/busqueda.c
    headers/busqueda.h
    src/relaciones.c
    headers/relaciones.h
    headers/efectos.h
        src/efectos.c
        src/borrar.c
        headers/borrar.h
)
