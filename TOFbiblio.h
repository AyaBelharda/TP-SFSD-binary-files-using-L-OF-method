
#define TOFBIBLIO_H

#include <stdio.h>
#include <stdlib.h>
#include "MachAbs.h"

#define T_bloc 200
#define faux 0
#define vrai 1
#define Max 100000
#define Fac 0.5
#define nbI 20000



/*********************************************************************************/


typedef struct Indxbloc
{ Ienreg Tab[T_bloc];
  int NB; // nombres des elements dans le bloc;
} Indxbloc;

typedef struct IndxEntete
{
    int NB_bloc;  //nombre de blocs utilis�s
    int nbre_enreg;  //nombre d'enregistrement dans le fichiers;

} IndxEntete;

typedef struct Indxbloc Buffer_tof;  //le Buffer_tof o� on r�cup�re on bloc
Buffer_tof buf;

typedef struct TOF     //structure de fichier
{
    FILE *F;             //poiteur vers le fichier
    IndxEntete entete;       //l'entete de fichier
} TOF;


TOF *ouvrir_tof(char *NOM_F,char MO) ;
void fermer_tof(TOF *S);
int ENTETE_TOF(TOF *S,int i);
void LireDir_tof (TOF *S,int i,Buffer_tof *Buf);
void EcrireDir_tof (TOF *S,int i,Buffer_tof Buf);
void Aff_ENTETE_tof(TOF *S,int i,int val);
int Alloc_Bloc_tof(TOF *S);
void Recherche_DEC_TOF(TOF *S,int key,int* i,int* j,int *Trouv);
void ch_in_TOF (Ienreg T[]);

