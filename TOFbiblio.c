#include <stdio.h>
#include <stdlib.h>
#define T_bloc 200
#define faux 0
#define vrai 1
#define Max 100000
#define Fac 0.5
#define nbI 20000
#include "TOFbiblio.h"


int N_AccEcr=0,N_AccLec=0;

TOF *ouvrir_tof(char *NOM_F,char MO)    //fonction pour l'ouverture de fichier
{
    // mod = 'A'ou'a' ancien (rb+) || mod = 'N'ou'n' nouveau (wb+)

    TOF (*S)=malloc(sizeof(TOF));
    char M[4];
    if ((MO == 'A') || (MO =='a')) sprintf(M,"rb+");   //ouverture d'un nouveau fichier
    else sprintf(M,"wb+");
    (S->F)=fopen(NOM_F,M);
    if (( MO == 'A') || ( MO =='a'))                     //ouverture d'un ancien fichier
    {

        fread(&(S->entete),sizeof(IndxEntete),1,S->F);

    }
    else
    {
        // Initialisation de l'entete
        (S->entete).NB_bloc=0;               //le nombre de blocs=0
        (S->entete).nbre_enreg=0;            //le nombre des enregestrements=0

        fwrite(&(S->entete),sizeof(IndxEntete),1,S->F);
    }
    return S;
}

void fermer_tof(TOF *S)     //proc�dure  poue la fermeture de fichier
{
    fseek(S->F,0,0);
    fwrite(&(S->entete),sizeof(IndxEntete),1,S->F);  // Mise a jour de l'ent�te
    fclose(S->F);
    S=NULL;
}

int ENTETE_TOF(TOF *S,int i)
{
    if (i==1) return S->entete.NB_bloc;
    if (i==2) return S->entete.nbre_enreg;
}

void LireDir_tof (TOF *S,int i,Buffer_tof *Buf)
{
  if (i<= ENTETE_TOF(S,1))
  {
      fseek(S->F,sizeof(IndxEntete)+(i-1)*sizeof(Indxbloc),SEEK_SET);
      fread(Buf,sizeof(Indxbloc),1,S->F);
      N_AccLec++;
  }
}


void EcrireDir_tof (TOF *S,int i,Buffer_tof Buf)
{
      fseek(S->F,sizeof(IndxEntete)+(i-1)*sizeof(Indxbloc),SEEK_SET);
      fwrite(&Buf,sizeof(Indxbloc),1,S->F);
      N_AccEcr++;
}

void Aff_ENTETE_tof(TOF *S,int i,int val)
{
    if (i==1) S->entete.NB_bloc=val;
    if (i==2) S->entete.nbre_enreg=val;
}

int Alloc_Bloc_tof(TOF *S)
{
    Aff_ENTETE_tof(S,1,ENTETE_TOF(S,1)+1);
    return ENTETE_TOF (S,1);
}


void ch_in_TOF (Ienreg T[nbI])
{ int key,j=0,i=1; Indxbloc Buf; int b=0;
TOF *S=ouvrir_tof("TOF.bin",'N');
   if (T[b].eff==0){
    if (j<(T_bloc*Fac))
        {
           Buf.Tab[j].Val=T[b].Val;
           Buf.Tab[j].eff=0;
           Buf.Tab[j].nblc=i;
           Buf.Tab[j].nenreg=j;
           b++;
           j++;
        }
        else {
            Buf.NB=j-1;
            EcrireDir_tof(S,i,Buf);
            i++;j=0;
           Buf.Tab[j].Val=T[b].Val;
           Buf.Tab[j].eff=0;
           Buf.Tab[j].nblc=i;
           Buf.Tab[j].nenreg=j;
            j++;
        }
}

Buf.NB=j-1;
EcrireDir_tof(S,i,Buf);
Aff_ENTETE_tof(S,1,i);
Aff_ENTETE_tof(S,2,1000);

fermer_tof(S);

}




