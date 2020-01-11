
#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

#define INF 99999
#define V 4

void afficher_soluce(int dist[][V]){
  for (int i = 0; i < V; i++) {
     for (int j = 0; j < V; j++)  {
         if (dist[i][j] == INF){
             printf("%s", "INF");
         }else{
             printf ("%d", dist[i][j]);
     }
     printf("\n");
    }
  }
}

void floydWarshall (int graph[][V]) {
   int dist[V][V], i, j, k;
   for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
          }
        }
        for (k = 0; k < V; k++) {
          for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {

                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
                  }
                }
              }

    // affichage
    afficher_soluce(dist);
}
