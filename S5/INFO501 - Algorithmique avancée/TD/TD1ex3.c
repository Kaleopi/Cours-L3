Typedef Struct{
  int nbSommets;
  int oriente;
  int value
  liste_t* l_adj;
  int** m_adj;
  int* m_stockage;
}graphe_t;

//init graphe_t
int init_graph_t(graphe_t graphe,char* nom_fichier){
  FILE* fichier;
  char ch_temp;
  int i,j,longueur;
  cellule_t* cellule=NULL;
  if ((Fichier=fopen(nom_fichier))){
    fscanf(fichier,"%s",ch_temp);
    fscanf(fichier,'%d',&graph->n_sommets);
  }
    //t allocation et init des liste d'ajacences
    fscanf(ficheir,'%s',ch_temp);
    fscanf(fichier,'%d',&graphe->oriente);
      //oriente
      if(!graphe->oriente){
        if(!strcomp(ch_temp,"debut_def_arrêtes")){
          while(strcomp(ch_temp,"fin_def_arrêtes")){
            fscanf(fichier,'%s',ch_temp);
            if(strcomp(ch_temp,"fin_def_arretes")){
              i=atoi(chtemp);
              fscanf(fichier,'%d',&s);
            }
          }
        }
      }
    }
}
