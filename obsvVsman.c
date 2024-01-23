#include <stdio.h>
#include <stdlib.h> // Necesario para rand()

// Función Observador que modifica la población en función de la tasa modificada
void observador(int *poblacion, float *tasa_modif, float tasa_teorica, int base, int *Deltadiferencia) {
    float tasa_actual = *tasa_modif;

    if (tasa_actual >= tasa_teorica && tasa_actual >= 0.1 && tasa_actual - tasa_teorica <= 0.3) {
        (*poblacion) += 10000;
    }
    if (tasa_actual > tasa_teorica && tasa_actual - tasa_teorica > 0.3) {
        (*poblacion) += 100000;
    }
    if (tasa_actual < tasa_teorica && -tasa_actual + tasa_teorica > 0.1) {
        (*Deltadiferencia)++;
        (*poblacion) -= 10000;
        if (*poblacion < 0) (*poblacion) = base;
    }
    if (tasa_actual < tasa_teorica && -tasa_actual + tasa_teorica >= 0.1 && *Deltadiferencia > 20) {
        (*Deltadiferencia) = 0;
        (*poblacion) -= 1000001;       
        if ((*poblacion) < 0) (*poblacion) = base;
    }
    if (tasa_actual < tasa_teorica && tasa_actual <= 0.1 && tasa_teorica - tasa_actual > 0.5 && tasa_teorica - tasa_actual <= 0.8) {
        (*poblacion) -= 0.8 * (*poblacion);
        if ((*poblacion) < 0) (*poblacion) = base;
    }
}

// Función Manipulador que devuelve la tasa modificada
void manipulador(int *poblacion, float *tasa_modif, int *limite_objetivo, int *tope, int *disminuir, float tasa_teorica, int base, int p) {
    float tasa_actual = *tasa_modif;
    float delta_tasa =  0.1 + (float)rand() / (RAND_MAX / 0.2);

    if ((*poblacion) <= p && (*limite_objetivo) < (*tope) && (*disminuir) != 0) {
        tasa_actual = tasa_teorica + delta_tasa;
        if (tasa_actual > 1) tasa_actual = 1.0;
        (*limite_objetivo)++;
    }
    if ((*poblacion) <= p && (*limite_objetivo) == (*tope) && (*disminuir) != 0) {
        delta_tasa++;
        (*limite_objetivo) = 0;
    }
    if (((*poblacion) >= p || (*disminuir) == 1) && (*poblacion) != base) {
        if ((*disminuir) == 0) {
            (*disminuir) = 1;
        }
        tasa_actual = tasa_teorica - delta_tasa;
        if (tasa_actual < 0) tasa_actual = 0;
        (*limite_objetivo)++;
    }
    *tasa_modif = tasa_actual;
}

int main() {
    int longitud = 5000; // Longitud de la simulación
    int base = 10000;
    int poblacion = base;
    float limite_manipulador = 1000000; // Límite de manipulación
    float tasa_teorica = 0.3; // Valor de la media teórica
    float tasa_modificada = tasa_teorica;
    int limite_objetivo = 0, tope = 10, disminuir = 2, diferencia = 0;

    for (int i = 0; i < longitud; i++) {
        // Llama al Manipulador para obtener la tasa modificada
        manipulador(&poblacion, &tasa_modificada, &limite_objetivo, &tope, &disminuir, tasa_teorica, base, limite_manipulador);

        // Llama al Observador para modificar la población en función de las condiciones y la tasa modificada
        observador(&poblacion, &tasa_modificada, tasa_teorica, base, &diferencia);

        // Imprimir la población y la tasa actual
        printf("Ciclo %d: Población = %d, Tasa = %f, Diferencia = %d\n", i + 1, poblacion, tasa_modificada, diferencia);
    }

    return 0;
}
