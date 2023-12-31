#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int legajo;
} RegistroEstudiante;

int main() {
    FILE *ArchEstudiantes;

    ArchEstudiantes = fopen("estudiantes.dat", "rb");

    if (ArchEstudiantes == NULL) {
        printf("Error al abrir el archivo de estudiantes.\n");
        exit(1);
    }

    printf("Numeros de legajo de estudiantes de votaron:\n");

    RegistroEstudiante RegEst;
    while (fread(&RegEst, sizeof(RegistroEstudiante), 1, ArchEstudiantes) == 1) {
        printf("Legajo: %d\n", RegEst.legajo);
    }

    fclose(ArchEstudiantes);

    return 0;
}
