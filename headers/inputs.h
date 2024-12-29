#ifndef INPUTS_H
#define INPUTS_H

#include "estructuras.h"
#include <stdint.h>


int input_entero_en_rango(const char* msj, int min, int max);
void input_string_alfanumerico(const char* msj, char* input, size_t len, int permitir_vacio);
Tipo input_tipo(const char* msj);
Estado input_estado(const char* msj);
uint64_t input_fecha(char* msj);

#endif // INPUTS_H