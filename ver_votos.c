#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nro_voto;
    int lista;
} RegistroVotos;

int votos_totales;

char *listas[] = { "Lista Celeste y Blanca", "Lista Los futuros Graduados", "Lista Recursantes", "Lista Accion Estudiantil" };

int main() {
    FILE *ArchVotos;

    ArchVotos = fopen("votos.dat", "rb");

    if (ArchVotos == NULL) {
        printf("Error al abrir el archivo de votos.\n");
        exit(1);
    }

    printf("Datos almacenados en el archivo de votos:\n");

    RegistroVotos RegVotos;
    while (fread(&RegVotos, sizeof(RegistroVotos), 1, ArchVotos) == 1) {
        printf("ID Voto: %d, Lista: %d. %s\n", RegVotos.nro_voto, RegVotos.lista, listas[RegVotos.lista -1]);
        votos_totales++;
    }

    printf("Cantidad de votos: %d", votos_totales);
    fclose(ArchVotos);

    return 0;
}
