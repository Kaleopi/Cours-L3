#include "shm_map.h"

/**
 * initialise la carte du segment partagé à '0'
 * @param carte carte_t du segment
 * @return void
 */
void initialiser_carte(carte_t *carte){
    int i;
    int j;
    for(i=0 ; i<LINE ; i++){
        for(j=0 ; j<COL ; j++){
            carte->carte[i][j] = 0;
        }
    }
}