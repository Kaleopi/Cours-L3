//https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
//https://gist.github.com/brijeshb42/11312064
//https://fr.wikipedia.org/wiki/Algorithme_de_Bellman-Ford

#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
void BellmanFord(struct Graphe* g, int src){
    int V = g->V; //V = nombre de sommets
    int E = g->E; //E = nombre d'arêtes
    int dist[V];

    //1: initialiser toutes les distances depuis la source à infini
    for(int i=0 ; i<V ; i++){
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    //2: relachement     for(int i=1 ; i<=V-1 ;i++){
        for(int j=0 ; j<E ; j++){
            int u = g->edge[j].src; //g->edge = tableau d'arêtes du graphe
            int v = g->edge[j].dest;
            int weight = g->edge[j].weight;
            if(dist[u] != INT_MAX && dist[u]+weight < dist[v]){
                dist[v] = dist[u] + weight;
            }
        }
    }

    //3:  checker les cycles de poids négatifs
    for(int i=0 ; i<E ; i++){
        int u = g->edge[i].src;
        int v = g->edge[i].dest;
        int weight = g->edge[i].weight;
        if(dist[u] != INT_MAX && dist[u]+weight < dist[v]){
            printf("Le graphe contient un cycle de poids négatifs.");
            return;
        }
    }

    printArr(dist, V); // fonction print tableau
    return;

}
