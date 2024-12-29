#ifndef EFECTOS_H
#define EFECTOS_H

#define $O_ROJO      "\x1b[31m"
#define $O_VERDE     "\x1b[32m"
#define $O_AMARILLO  "\x1b[33m"
#define $O_AZUL      "\x1b[34m"
#define $O_MAGENTA   "\x1b[35m"
#define $O_CYAN      "\x1b[36m"

#define $C_ROJO      "\x1b[91m"
#define $C_VERDE     "\x1b[92m"
#define $C_AMARILLO  "\x1b[93m"
#define $C_AZUL      "\x1b[94m"
#define $C_MAGENTA   "\x1b[95m"
#define $C_CYAN      "\x1b[96m"

#define $E_BOLD      "\x1b[1m"
#define $E_DIM       "\x1b[2m"
#define $E_UNDERLINE "\x1b[4m"
#define $E_BLINK     "\x1b[5m"

#define $B_ROJO      "\x1b[101m"

#define $RESET       "\x1b[0m"

void limpiar_pantalla(void);

#endif //EFECTOS_H
