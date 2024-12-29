#include "../headers/estructuras.h"
#include "../headers/inputs.h"
#include "../headers/efectos.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>


static int fecha_valida(int anio, int mes, int dia);
static int es_bisiesto(int anio);

int input_entero_en_rango(const char* msj, const int min, const int max)
{
    int n;

    do
    {
        printf("%s (min: %d, max: %d): ", msj, min, max);

        if (scanf("%d", &n) != 1)
        {
            while (getchar() != '\n') {}
            printf($C_ROJO"ERROR: Por favor ingrese un número válido.\n"$RESET);
            continue;
        }

        if (n < min)
            printf($C_ROJO"ERROR: El número ingresado debe ser mayor o igual a %d.\n"$RESET, min);
        else if (n > max)
            printf($C_ROJO"ERROR: El número ingresado debe ser menor o igual a %d.\n"$RESET, max);
    }
    while (n < min || n > max);

    while (getchar() != '\n') {}
    return n;
}


void input_string_alfanumerico(const char* msj, char* input, const size_t len, const int permitir_vacio)
{
    int i, invalido;
    printf("%s: ", msj);

    do
    {
        invalido = 0;

        if (!fgets(input, len, stdin))
        {
            printf($C_ROJO"ERROR: No se pudo leer el texto ingresado."$RESET"\nIntente nuevamente: ");
            continue;
        }

        input[strcspn(input, "\n")] = '\0';
        fflush(stdin);

        if (!permitir_vacio && input[0] == '\0')
        {
            printf($C_ROJO"ERROR: No se permite ingresar texto vacío."$RESET"\nIntente nuevamente: ");
            invalido = 1;
            continue;
        }

        for (i = 0; i < len && input[i] != '\0'; i++)
        {
            if (!isalnum(input[i]) && input[i] != ' ' && input[i] != '.' && input[i] != ',' && input[i] != '\'')
            {
                invalido = 1;
                break;
            }
        }

        if (invalido) printf($C_ROJO"ERROR: El texto ingresado no es válido."$RESET"\nIntente nuevamente: ");
    }
    while (invalido);
}



Tipo input_tipo(const char* msj)
{
    Tipo input;
    printf("%s.\n", msj);
    printf("(0 = Recordatorio | 1 = Tarea): ");

    do
    {
        if (scanf("%d", &input) != 1)
        {
            printf($C_ROJO"ERROR: Entrada no válida."$RESET"\nIntente nuevamente: ");
            continue;
        }

        if (input > TAREA)
            printf($C_ROJO"El valor ingresado no se encuentra en el rango admitido."$RESET"\nIntente nuevamente: ");
    }
    while (input > TAREA);

    while (getchar() != '\n') {}
    return input;
}


Estado input_estado(const char* msj)
{
    Estado input;
    printf("%s.\n", msj);
    printf("(0 = Pendiente | 1 = En progreso | 2 = Terminada | 3 = Cancelada): ");

    do
    {
        if (scanf("%d", &input) != 1)
        {
            printf($C_ROJO"ERROR: Entrada no válida."$RESET"\nIntente nuevamente: ");
            continue;
        }

        if (input > CANCELADA)
            printf($C_ROJO"El valor ingresado no se encuentra en el rango admitido."$RESET"\nIntente nuevamente: ");
    }
    while (input > CANCELADA);

    while (getchar() != '\n') {}
    return input;
}


uint64_t input_fecha(char* msj)
{
    int valido = 0;
    int anio, mes, dia;
    char input[11];
    struct tm temp = {0};
    uint64_t timestamp = 0;

    do
	{
        printf("%s (DD-MM-AAAA): ", msj);

        if (fgets(input, sizeof(input), stdin) == NULL)
		{
            printf($C_ROJO"ERROR: No se pudo leer el texto ingresado."$RESET"\nIntente nuevamente: ");
            continue;
        }
        
        input[strcspn(input, "\n")] = '\0';
        fflush(stdin);

        if (sscanf(input, "%d-%d-%d", &dia, &mes, &anio) == 3)
		{
            if (fecha_valida(anio, mes, dia))
			{
                temp.tm_year = anio - 1900;
                temp.tm_mon = mes - 1;
                temp.tm_mday = dia;

                const time_t t = mktime(&temp);
                if (t != -1)
				{
                    valido = 1;
                    timestamp = (uint64_t)t;
                }
				else printf($C_ROJO"ERROR: La fecha esta fuera del rango permitido.\n"$RESET);
            }
			else printf($C_ROJO"ERROR: Fecha inválida. Asegúrese de que la fecha sea válida en el calendario.\n"$RESET);
        }
		else printf($C_ROJO"ERROR: Formato inválido. Use el formato DD-MM-AAAA.\n"$RESET);
    }
	while (!valido);

    return timestamp;
}


static int es_bisiesto(const int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}


static int fecha_valida(const int anio, const int mes, const int dia)
{
    if (anio < 1970 || mes < 1 || mes > 12 || dia < 1) return 0;

    int dias_en_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2 && es_bisiesto(anio)) dias_en_mes[1] = 29;

    return dia <= dias_en_mes[mes - 1];
}