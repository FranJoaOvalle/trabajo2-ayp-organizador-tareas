#include "../headers/base_datos.h"
#include "../headers/estructuras.h"
#include "../headers/efectos.h"

#include <stdio.h>
#include <inttypes.h>

void cargar_tareas(Tarea bd_tareas[], int* cant_tareas)
{
	Tarea t;
	int i = 0;
	char *nombre_archivo = "../bd/tareas.txt";

	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL) {
		printf($C_ROJO"ERROR: No se pudo abrir el archivo %s\n"$RESET, nombre_archivo);
		*cant_tareas = 0;
		return;
	}

	while (fscanf(archivo, "%"SCNu32"|%u|%31[^|]|%127[^|]|%u|%"SCNu64"|%"SCNu64"|%"SCNu64"|%u\n",
				  &t.base.id, &t.base.tipo, t.base.nombre, t.base.desc,
				  &t.base.prioridad, &t.base.fecha_creacion,
				  &t.fecha_inicio, &t.fecha_fin, &t.estado) == 9)
	{
		bd_tareas[i] = t;
		i++;
	}

	*cant_tareas = i;
	fclose(archivo);
}


void cargar_recordatorios(Recordatorio bd_recordatorios[], int* cant_recordatorios)
{
	Recordatorio r;
	int i = 0;
	char *nombre_archivo = "../bd/recordatorios.txt";

	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL) {
		printf($C_ROJO"ERROR: No se pudo abrir el archivo %s\n"$RESET, nombre_archivo);
		*cant_recordatorios = 0;
		return;
	}

	while (fscanf(archivo, "%"SCNu32"|%u|%31[^|]|%127[^|]|%u|%"SCNu64"|%u|%"SCNu64"\n",
				  &r.base.id, &r.base.tipo, r.base.nombre, r.base.desc,
				  &r.base.prioridad, &r.base.fecha_creacion,
				  &r.periodo, &r.fecha_objetivo) == 8)
	{
		bd_recordatorios[i] = r;
		i++;
	}

	*cant_recordatorios = i;
	fclose(archivo);
}


void cargar_etiquetas(Etiqueta bd_etiquetas[], int* cant_etiquetas)
{
	Etiqueta e;
	int i = 0;
	char *nombre_archivo = "../bd/etiquetas.txt";

	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL) {
		printf($C_ROJO"ERROR: No se pudo abrir el archivo %s\n"$RESET, nombre_archivo);
		*cant_etiquetas = 0;
		return;
	}

	while (fscanf(archivo, "%u %31[^|\n]\n", &e.id_etiqueta, e.nombre_etiqueta) == 2)
	{
		bd_etiquetas[i] = e;
		i++;
	}

	*cant_etiquetas = i;
	fclose(archivo);
}


void cargar_relaciones(Relacion bd_relaciones[], int* cant_relaciones)
{
	Relacion rel;
	int i = 0;
	char *nombre_archivo = "../bd/relaciones.txt";

	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL) {
		printf($C_ROJO"ERROR: No se pudo abrir el archivo %s\n"$RESET, nombre_archivo);
		*cant_relaciones = 0;
		return;
	}

	while (fscanf(archivo, "%"SCNu32" %u %u", &rel.id_base, &rel.tipo, &rel.id_etiqueta) == 3)
	{
		bd_relaciones[i] = rel;
		i++;
	}

	*cant_relaciones = i;
	fclose(archivo);
}


void guardar_tareas(const Tarea bd_tareas[], const int cant_tareas)
{
	int i;
	const char *nombre_archivo = "../bd/tareas.txt";
	FILE *archivo = fopen(nombre_archivo, "w");

	if (archivo == NULL) {
		printf($C_ROJO"ERROR: No se pudo abrir el archivo %s\n"$RESET, nombre_archivo);
		return;
	}

	for (i = 0; i < cant_tareas; i++) {
		const Tarea t = bd_tareas[i];

		fprintf(archivo, "%"PRIu32"|%u|%s|%s|%u|%"PRIu64"|%"PRIu64"|%"PRIu64"|%u",
				t.base.id, t.base.tipo, t.base.nombre, t.base.desc, t.base.prioridad, t.base.fecha_creacion,
				t.fecha_inicio, t.fecha_fin, t.estado);
		if (i < cant_tareas - 1) fprintf(archivo, "\n");
	}
	fclose(archivo);
}


void guardar_recordatorios(const Recordatorio bd_recordatorios[], const int cant_recordatorios)
{
	int i;
	const char *nombre_archivo = "../bd/recordatorios.txt";
	FILE *archivo = fopen(nombre_archivo, "w");

	if (archivo == NULL) {
		printf($C_ROJO"ERROR: No se pudo abrir el archivo %s\n"$RESET, nombre_archivo);
		return;
	}

	for (i = 0; i < cant_recordatorios; i++) {
		const Recordatorio r = bd_recordatorios[i];

		fprintf(archivo, "%"PRIu32"|%u|%s|%s|%u|%"PRIu64"|%u|%"PRIu64"",
				r.base.id, r.base.tipo, r.base.nombre, r.base.desc, r.base.prioridad, r.base.fecha_creacion,
				r.periodo, r.fecha_objetivo);
		if (i < cant_recordatorios - 1) fprintf(archivo, "\n");
	}
	fclose(archivo);
}


void guardar_etiquetas(const Etiqueta bd_etiquetas[], const int cant_etiquetas)
{
	int i;
	const char *nombre_archivo = "../bd/etiquetas.txt";
	FILE *archivo = fopen(nombre_archivo, "w");

	if (archivo == NULL) {
		printf($C_ROJO"ERROR: No se pudo abrir el archivo %s\n"$RESET, nombre_archivo);
		return;
	}

	for (i = 0; i < cant_etiquetas; i++) {
		const Etiqueta e = bd_etiquetas[i];

		fprintf(archivo, "%u %s", e.id_etiqueta, e.nombre_etiqueta);
		if (i < cant_etiquetas - 1) fprintf(archivo, "\n");
	}
	fclose(archivo);
}


void guardar_relaciones(const Relacion bd_relaciones[], const int cant_relaciones)
{
	int i;
	const char *nombre_archivo = "../bd/relaciones.txt";
	FILE *archivo = fopen(nombre_archivo, "w");

	if (archivo == NULL) {
		printf($C_ROJO"ERROR: No se pudo abrir el archivo %s\n"$RESET, nombre_archivo);
		return;
	}

	for (i = 0; i < cant_relaciones; i++) {
		const Relacion rel = bd_relaciones[i];

		fprintf(archivo, "%"PRIu32" %u %u", rel.id_base, rel.tipo, rel.id_etiqueta);
		if (i < cant_relaciones - 1) fprintf(archivo, "\n");
	}
	fclose(archivo);
}