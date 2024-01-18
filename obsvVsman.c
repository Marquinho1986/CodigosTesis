#include <stdio.h>

// Función Observador que modifica la población en función de la tasa modificada
 int * observador(int *poblacion,float tasa_modif, float tasa_teorica,int base,int *Deltadiferencia) {
      srand(time(NULL));
      //float m = 0.1 + (rand() / (float)RAND_MAX) * 0.4;
      //float k = 0.1 + (rand() / (float)RAND_MAX) * 0.4;
    
        
        if (tasa_modif > tasa_teorica &&  tasa_modif > = 0.1 && tasa_modif - tasa_teorica<= 0.3) {
            (*poblacion) += 10000;
        }
        if (tasa_modif > tasa_teorica && tasa_modif - tasa_teorica >= 0.3) {
            (*poblacion) += 100000;
        }
        if (tasa_modif < tasa_teorica && tasa_modif - tasa_teorica >= 0.1) {
            Deltadiferencia++;
            (*poblacion) -= 100000;
            if (*poblacion < 0) *poblacion=base;
        }
       if (tasa_modif < tasa_teorica && tasa_modif - tasa_teorica >= 0.1 && *Deltadiferencia > 10) {
            *Deltadiferencia=0
            (*poblacion) -= 100000;
            if (poblacion < 0) *poblacion=base;
        }
       if  (tasa_modif <= tasa_teorica && tasa_modif <= 0.1 && tasa_teorica - tasa_modif > 0.5 && tasa_teorica - tasa_modif <= 0.8) {
            
            *poblacion -= 0.8*poblacion;
            
            if (*poblacion < 0) *poblacion=base;
            
        }
       if ( tasa_modif == 0) {
            ContadortasaCero++;
           if (ContadortasaCero == 3)
            *poblacion== base;
         }    
      
 return *poblacion;
}

// Función Manipulador que devuelve la tasa modificada
 float manipulador(int *poblacion, double p, float tasa_teorica,int base ) {
    
    float tasa_modif;
    float delta_tasa=0.1;
    int limite objetivo=0,tope=10,disminuir=0;
    
    if (poblacion <= p && limite objetivo < tope && disminuir !=0){ 
    
        tasa_modif = tasa_teorica + delta_tasa;
        if (tasa_modif > 1) tasa_modif=1.0;
        limite_objetivo++;
     }
      if (poblacion <= p && limite objetivo == tope && disminuir !=0){ 
        
        delta_tasa++;
        limite_objetivo=0;
     }
     
     if ((poblacion>=p || disminuir==1) && poblacion != base){
       if ( disminuir==0){ 
         
          disminuir=1;
       }
        tasa_modif = tasa_teorica - delta_tasa;
        if (tasa_modif < 0) tasa_modif=0;
        limite_objetivo++;
     }
     
return tasa_modif;
}
int main() {
    int longitud = 10; // Longitud de la población
    int base=10000;
    int poblacion=base;
    int limite_manipulador=base*10
    float tasa_teorica = 0.3; // Valor de la media teórica
    float tasa_modificada;
   
    
    // Llama al Manipulador para obtener la tasa modificada
        tasa_modificada = manipulador(&poblacion,limite_manipulador,tasa_teorica,base);
    
    // Llama al Observador para modificar la población en función de las condiciones y la tasa modificada
        poblacion=observador(&poblacion,tasa_modificada, tasa_teorica,base);
    
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
