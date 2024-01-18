#include <stdio.h>

// Función Observador que modifica la población en función de la tasa modificada
void observador(int poblacion,float tasa_modif, float tasa_teorica, float med_variacion, float k) {

        if (tasa_modif <= media_teorica && med_variacion <= 0.5) {
            poblacion -= 1;
        }
        if (tasa_modif <= 1.5 && media_teorica - tasa_modif >= 0.1) {
            poblacion += 2;
        }
        if (tasa_modif > media_teorica && med_variacion > k) {
            poblacion -= 1;
        }
        if (tasa_modif > media_teorica) {
            poblacion += 1;
        }
        if (media_teorica - tasa_modif == 0.00) {
            poblacion = 0;
        }
    
}

// Función Manipulador que devuelve la tasa modificada
double manipulador(int poblacion, int longitud, float tasa_anterior, double p, float tasa_teorica ) {
    
    double tasa_modificada = tasa_virgen * (suma_elementos / longitud) + p;
    
    return tasa_modificada;
}

int main() {
    int longitud = 10; // Longitud de la población
    int poblacion=400;
    double tasa_virgen = 2.0; // Valor de la tasa virgen
    double p = 0.5; // Objetivos de manipulación
    
    double media_teorica = 7.0; // Valor de la media teórica
    double med_variacion = 0.4; // Valor de med_variacion
    double k = 0.6; // Valor de k
    
    // Llama al Manipulador para obtener la tasa modificada
    double tasa_modificada = manipulador(poblacion, longitud, tasa_virgen, p);
    
    // Llama al Observador para modificar la población en función de las condiciones y la tasa modificada
    observador(poblacion, longitud, tasa_modificada, media_teorica, med_variacion, k);
    
    // Imprime la población resultante
    printf("Población modificada:\n");
    for (int i = 0; i < longitud; i++) {
        printf("%d ", poblacion[i]);
    }
    printf("\n");
    
    // Imprime la tasa modificada
    printf("Tasa modificada: %lf\n", tasa_modificada);
    
    return 0;
}
