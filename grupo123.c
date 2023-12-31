#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

#define MAX_LISTAS 4

//Ambiente
char listas[MAX_LISTAS][50];
int votos[MAX_LISTAS];
int cantvotos, opcion, legajo;

typedef struct {
    int nro_voto;
    int lista;
} RegistroVotos;

typedef struct {
    int legajo;
} RegistroEstudiante;

RegistroVotos RegVotos;
FILE *ArchVotos;

RegistroEstudiante RegEst;
FILE *ArchEstudiantes;

bool leer_numero(int* resultado) {
    //Revisamos si los datos de entrada son valores númericos o no para no romper el sistema.
    if (scanf("%d", resultado) == 1) {
        return true;
    } else {
        while (getchar() != '\n');  // Limpiar el búfer de entrada para evitar problemas.
        return false;
    }
}

void limpiarvotos() {
    //Limpiamos el arreglo "votos".
    for (int i = 0; i < MAX_LISTAS; i++) {
        votos[i] = 0;
    }
}

void mostrar_ranking() {
    //Mostramos el ranking de votos.
    printf("Ranking de votos:\n");
    for (int i = 0; i < MAX_LISTAS; i++) {
        printf("%d. %s: %d\n", i + 1, listas[i], votos[i]);
    }
}

void procesarvotos() {
    //Limpiamos el arreglo "votos" para utilizar los datos del archivo de registro.
    limpiarvotos();

    //Leemos el archivo de registro con los votos y asignarlas a los arreglos para después procesarlos.
    rewind(ArchVotos);
    while (fread(&RegVotos, sizeof(RegistroVotos), 1, ArchVotos) == 1) {
        votos[RegVotos.lista - 1]++;
    }

    // Mediante el método de ordenamiento por burbuja ordenamos el ranking de votos.
    for (int i = 0; i < MAX_LISTAS - 1; i++) {
        for (int j = 0; j < MAX_LISTAS - 1; j++) {
            if (votos[j] < votos[j + 1]) {

                int temp_votos = votos[j];
                votos[j] = votos[j + 1];
                votos[j + 1] = temp_votos;

                char temp_listas[50];
                strcpy(temp_listas, listas[j]);
                strcpy(listas[j], listas[j + 1]);
                strcpy(listas[j + 1], temp_listas);
            }
        }
    }

    mostrar_ranking();
}

void registrar_voto(int opcion) {

    while (opcion < 1 || opcion > MAX_LISTAS) {
        printf("Lista no valida, por favor vuelve a intentarlo: ");
        scanf("%d", &opcion);
    }

    votos[opcion - 1]++;
    cantvotos = cantvotos + 1;

    RegVotos.nro_voto = cantvotos;
    RegVotos.lista = opcion;
    fwrite(&RegVotos, sizeof(RegistroVotos), 1, ArchVotos);

    RegEst.legajo = legajo;
    fwrite(&RegEst, sizeof(RegistroEstudiante), 1, ArchEstudiantes);

    printf("Tu voto fue registrado con exito, gracias por utilizar el sistema.\n");

    //Limpiar pantalla despues de 5 segundos.
    Sleep(5000);
    system("cls");
}

void mostrar_listas() {
    printf("Listas disponibles:\n");
    for (int i = 0; i < MAX_LISTAS; i++) {
        printf("%d. %s\n", i + 1, listas[i]);
    }
}

void ingresar_lista() {
    mostrar_listas();
    printf("Ingrese el numero de lista por la cual desea votar (1-4): ");
    while (!leer_numero(&opcion)) {
        printf("Entrada no válida. Ingrese el numero de lista por la cual desea votar (1-4): ");
    }
    registrar_voto(opcion);
}

void solicitar_legajo() {
    printf("Bienvenido al sistema de votacion del Centro de Estudiantes (CET)\n");
    printf("Por favor ingresa tu numero de legajo: ");
    while (!leer_numero(&legajo)) {
        printf("Entrada no valida. Por favor, vuelve a intentarlo: ");
    }
    ingresar_lista();
}

void inicializar_program() {
    // Agregamos los elementos al arreglo "listas"
    strcpy(listas[0], "Lista Celeste y Blanca");
    strcpy(listas[1], "Lista Los futuros Graduados");
    strcpy(listas[2], "Lista Recursantes");
    strcpy(listas[3], "Lista Accion Estudiantil");

    // Inicializamos las variables del programa
    RegVotos.nro_voto = -1;
    RegVotos.lista = -1;
    RegEst.legajo = -1;

    cantvotos = 0;
    opcion = 0;
    legajo = 0;

    limpiarvotos();
}

//Proceso
int main() {

    ArchVotos = fopen("votos.dat", "a+");
    ArchEstudiantes = fopen("estudiantes.dat", "a+");

    inicializar_program();

    do {
        // Obtener la hora actual del sistema
        time_t tiempo_actual = time(NULL);
        int horaActual = localtime(&tiempo_actual)->tm_hour;

        // Verificar si es el horario permitido para votar (entre las 8 y las 20 horas).
        if (horaActual >= 8 && horaActual < 20) {
            solicitar_legajo();
        } else {
            printf("El horario de votacion ha finalizado. Procesando votos...\n");

            //Limpiamos pantalla despues de 5 segundos.
            Sleep(5000);
            system("cls");

            //Procesamos los votos
            procesarvotos();
            break; // Salimos del bucle si el horario está fuera del rango.
        }
    } while (1);

    fclose(ArchVotos);
    fclose(ArchEstudiantes);
    return 0;
}

//Fin proceso
