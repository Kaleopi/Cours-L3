#include <stdio.h>
#include <stdlib.h>
#include "prim.h"
#include "arete.h"
#include "graphe.h"


void prim_tri(Graphe *g){
    int MAX =g->nbSommet;
    int cost[MAX][MAX];
    int n;
    int spanning[MAX][MAX];
    int u,v,min_distance,distance[MAX],from[MAX];
	int visited[MAX],noOOB,i,min_cost,j;
    //creation matrice de cost
    for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(g->m_adj[i][j]==0){
				cost[i][j]=999999999;
            }else{
				cost[i][j]=g->m_adj[i][j];
				spanning[i][j]=0;
                }
		}
    }
    	//initialise visited[],distance[] and from[]
	distance[0]=0;
	visited[0]=1;
    	for(i=1;i<n;i++){
		distance[i]=cost[0][i];
		from[i]=0;
		visited[i]=0;
	}
    	min_cost=0;		//cout du passage
	noOOB=n-1;		//aucune arretes ajouter
	
	while(noOOB>0)
	{
		//trouve le chemin le plus court
		min_distance=999999999;
		for(i=1;i<n;i++)
			if(visited[i]==0&&distance[i]<min_distance)
			{
				v=i;
				min_distance=distance[i];
			}
			
		u=from[v];
//insertion du chemin le plus court	
    	spanning[u][v]=distance[v];
		spanning[v][u]=distance[v];
		noOOB--;
		visited[v]=1;
		
		//change la distance des visité
		for(i=1;i<n;i++)
			if(visited[i]==0&&cost[i][v]<distance[i])
			{
				distance[i]=cost[i][v];
				from[i]=v;
			}
		
		min_cost=min_cost+cost[u][v];
	}
	
	printf("%d",min_cost);
}