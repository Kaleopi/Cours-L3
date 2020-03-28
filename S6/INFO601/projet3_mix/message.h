#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#define TYPE_CONNEXION 0
#define TYPE_CONNEXION_AUTHORIZED 0
/**
 * @struct requete_t
 * @field type type de la requête (connexion, etc)
 */
typedef struct{
  long type;
}requete_t;

/**
 * @struct response_t
 * @field type type de la réponse
 */
typedef struct{
  long type;
  int port;
}reponse_t;

#endif /*_MESSAGE_H_*/
