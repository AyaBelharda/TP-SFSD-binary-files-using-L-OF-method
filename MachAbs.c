#include <stdio.h>
#include <stdlib.h>
#include "MachAbs.h"



void Ouvrir(LO_F *f,char nom[35],char m)//m represent le mode
{
     f->entete=malloc(sizeof(Entete_LO_F));
if ((m=='N')||(m=='n'))//mode new si on vaut crée un nouveau fichier
{   f->fichier=fopen(nom,"wb+");//on ouvert le fichier en mode d'ecriture binaire
    f->entete->nb_tete=-1;//initialisation du premier bloc de fichier
    f->entete->nb_der=0;//initialisation de nombre de bloc a 0
    f->entete->nb_enr=0;//initialisation de nombre d'enreg a 0
    fwrite(f->entete,sizeof(Entete_LO_F),1,f->fichier);//enregistrement de l'entete de nouveau fichier
}
else
{
 if ((m=='A')||(m=='a'))//mode ancient si le fichier existe deja
 {  f->fichier =fopen(nom,"rb+");//ouverture de fichie en mode lecture binaire avec possibilite d'ecriture
 if(f->fichier == NULL)
 {
     printf("\n il ya un erreur / le fichier n'existe pas ");
 }
 else
 {
     fread(f->entete,sizeof(Entete_LO_F),1,f->fichier);}//lecture de l'entete de fichier
 }

 else printf("le mode est erroné");//si m!=a et m!=n
}}


void Fermer(LO_F *f)
{
    rewind(f->fichier);//rotourne vers le debut de fichier
    fwrite(f->entete,sizeof(Entete_LO_F),1,f->fichier); //enregistrement des modification
    fclose(f->fichier);//fermeture de fichier f
    free(f->entete) ;// on libere la zone utilisé d'entete
}
Tbloc Allocbloc(LO_F *f)
{
    Tbloc buf;
    int i ;
    buf.NB=0;
    buf.suiv=-1;

}
void LirDir(LO_F *f,int i,Buffer *buf)
{
rewind(f->fichier);
fseek(f->fichier,sizeof(Entete_LO_F)+i*sizeof(Tbloc),SEEK_SET);
fread(buf,sizeof(Tbloc),1,f->fichier);
}
void EcrirDir(LO_F *f,int i,Buffer *buf)
{  rewind(f->fichier);
    fseek(f->fichier,sizeof(Entete_LO_F)+i*sizeof(Tbloc),SEEK_SET);
    fwrite(buf,sizeof(Tbloc),1,f->fichier);
}
void Aff_entete(LO_F *f,int i,int elt)
{
 switch(i)
 {
 case 1 :
   {
       f->entete->nb_der=elt;//affectation de nb de dernier bloc
    break;}
 case 2:
    { f->entete->nb_tete=elt;//affectation du nb de 1er bloc
         break;
     }
     case 3:
     {  f->entete->nb_enr=elt;// affectation nb d'enregistrements dans le fichier
         break;
     }

 default: {printf("\n\t\veuillez reessayer");
   break;}
}

}
int Entete(LO_F *f,int i)
{
 switch(i)
 {
 case 1 :
   {
      return (f->entete->nb_der);
    break;}
 case 2:
     { return( f->entete->nb_tete);
         break;
     }
     case 3:
     { return( f->entete->nb_enr);
         break;
     }
 default: {printf("\n\t\veuillez reessayer");
 return 1;
   break;}}}
