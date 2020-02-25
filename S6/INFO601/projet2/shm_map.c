#include "shm_map.h"

void initialiser_carte(carte_t *carte){
    int i;
    int j;
    for(i=0 ; i<LINE ; i++){
        for(j=0 ; j<COL ; j++){
            carte->carte[i][j] = '0';
        }
    }
}