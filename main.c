#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<stdbool.h>
#include<string.h>
#include "BiblioTP.h"
#include "TOFbiblio.h"

#define MAX 32
#define nbI 20000
int ecrdir=0, lirdir=0;

int main()
{
    //les declarations
    int n,matr,ANEMAX,ANEMIN,choi,i,j,eff,k;
    LO_F *f , *F1,*F2,*F3,*F4,*F5,*F6;
    f = malloc(sizeof(LO_F));
    F1 = malloc(sizeof(LO_F));
    F2 = malloc(sizeof(LO_F));
    F3 = malloc(sizeof(LO_F));
    F4 = malloc(sizeof(LO_F));
    F5 = malloc(sizeof(LO_F));
    F6 = malloc(sizeof(LO_F));
    char Spe[50],Etabl[25],ch;
    bool repeter=true,trouv;
    int nump,nume, xf, yf;
    int choix=-1,c;
    bool exit = false;
    int clc,cpt;
   printf("***************creation aleatoire du fichier ENSEIGNANT-MESRS***********************************\n\n");
   printf (" Veuillez inserer le nombre des enseignants que vous voulez :\n ");
   scanf("%d",&n);
   srand(time(NULL));
   creation(n);
     printf(" Voulez vous affichier ? (oui= o/ non = n)\n");
     scanf("%c",&ch);
     scanf("%c",&ch);
            if((ch=='o')||(ch=='O'))
        {
            affichage(f,"ENSEIGNANT-MESRS.bin");}

     while(repeter)
     { menu();
         printf("veuillez inserer votre choix \n choix= ");
      scanf("%d",&choix);
         switch(choix)
         {
             case 1:
    {
        printf("\n\t\t *****Insertion d'un nouvel enregistrement***** \n\n");
        Ouvrir(f,"ENSEIGNANT-MESRS.bin",'A');
        Inser_enr(f);
        Fermer(f);
        printf("voulez vous affichier (oui= o/ non = n)\n?");
     scanf("%c",&ch);
     scanf("%c",&ch);
            if((ch=='o')||(ch=='O'))
        {affichage(f,"ENSEIGNANT-MESRS.bin");}

    }break;

    case 2:
    {
        printf("\n\t\t***********Modification d'etablissement d'un enseignant**************");
        printf("\nDonnez le matricule vous voulez modifier:");
        scanf("%d",&matr);
        //recherche_ind(matr,&i,&j,&trouv,&k,&eff,cpt);

        //if((trouv)&&(!eff))
           //{
            Ouvrir(f,"ENSEIGNANT-MESRS.bin",'a');
            Mod_Eta(f,matr);
            Fermer(f);
            printf("voulez vous affichier (oui= o/ non = n)\n?");
            scanf("%c",&ch);
            scanf("%c",&ch);
            if((ch=='o')||(ch=='O'))
        {affichage(f,"ENSEIGNANT-MESRS.bin");}
           //}else{printf("ce matricule n'existe pas\n");}



    }break;

    case 3:
    {printf("\n\t\t*******Suppression d'un enregistrement donne par le matricule****************");
         printf("\nDonnez le matricule vous voulez supprimer :");
        scanf("%d",&matr);
        printf("voulez vous vraiment le supprimer oui = o ?\n");
          scanf("%c",&ch);
            scanf("%c",&ch);
            if((ch=='o')||(ch=='O'))
        {

        //recherche_ind(matr,&i,&j,&trouv,&k,&eff,cpt);
        //if((trouv)&&(!eff))
           //{
               Ouvrir(f,"ENSEIGNANT-MESRS.bin",'a');
            Supp_Matr(f,matr);
            Fermer(f);
            printf("voulez vous l'afficher (oui= o/ non = n)\n?");
            scanf("%c",&ch);
            scanf("%c",&ch);
            if((ch=='o')||(ch=='O'))
        {affichage(f,"ENSEIGNANT-MESRS.bin");}
           //}else{printf("ce matricule n'existe pas\n");}
           }
         }break;

    case 4:
    {
      printf("\n\t\t*********Supprimer tous les enregistrements relatifs a une specialite*****");
        printf("voulez vous vraiment le supprimer oui = o ?");
          scanf("%c",&ch);
            scanf("%c",&ch);
            if((ch=='o')||(ch=='O'))
        {
      printf("\nDonnez la specialite que vous voulez supprimer: ");
     scanf("%s",Spe);
     Ouvrir(f,"ENSEIGNANT-MESRS.bin",'a');
     Supp_SPE(f,Spe);
      Fermer(f);
      printf("voulez vous affichier (oui= o/ non = n)\n?");
     scanf("%c",&ch);
     scanf("%c",&ch);
            if((ch=='o')||(ch=='O'))
        {affichage(f,"ENSEIGNANT-MESRS.bin");}}

    }break;

   case 5:
    {
     printf("\n\t\tAffichage de tous les enregistrement relatifs a une region militaire  ayant age entre deux tranches age donnee");
     printf("\n Voici la liste de tous les etablissements ageriens : \n ");
          //afficher le fichier des etablissements
    FILE *Fich=NULL;//pointeur sur fichier text "etablissements"
    char ch[Max_Etab] = ""; // Chaîne vide
    cpt=0;
    Fich=fopen("Etablissement.txt","r");//ouvrir le fichier des établissements en mode lecture seule
if (Fich != NULL)//tester s'il y a erreur lors de l'ouverture
    {
        while (fgets(ch, Max_Etab, Fich) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            cpt++;//incrémenter le compteur
            printf("%d %s %s\n",cpt,"-",ch);
        }

        fclose(Fich);//fermer le fichier
    }
else printf("fichier Etablissement inexistant");//cas ou le fichier n'existe pas dans le répertoire du programme
cpt=0;//remettre le compteur a 0
int num_etab=0;
printf("\nSelectionnez le numero de l'etablissement: \n");
    scanf("%d",&num_etab);
    Fich=fopen("Etablissement.txt","r");//ouvrir le fichier des etablissements en mode lecture seule
if (Fich != NULL)//tester s'il y a eurreur lors de l'ouverture
    {
        while (fgets(ch, Max_Etab, Fich) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            cpt++;//incrémenter le compteur
            if (cpt==num_etab){ //quand on arrive à la ligne qui correspond au numéro de l'etablissement
            strcpy(Etabl,ch);} //copier le nom de l'etablissement dans le buffer
            }
        }
        printf(" -> L'annee maximale : ");
        scanf("%d",&ANEMAX);
        printf(" -> L'annee minmale : ");
        scanf("%d",&ANEMIN);
        Affich_Etab_A(f,Etabl,ANEMIN,ANEMAX);
    }break;

    case 6:
    {
      printf("\n\t\t**********Affichage de tous les enregistrement relatifs a une categories de Grade**********");

      printf("\nDonnez le nom de Grade que vous voulez affichier");
     Affich_REG(f);
    }break;

    case 7:
    {printf("\n\t\t**************Codage/Decodage du fichier <-ENSEIGNANT-MESRS.bin->******************");

        printf("\n -> Voulez vous coder le fichier ENSEIGNANT-MESRS.bin (oui= o/ non = n)\n?");
        scanf("%c",&ch);
        scanf("%c",&ch);
        if((ch=='o')||(ch=='O')){ codage_fichier("ENSEIGNANT-MESRS.bin"); }
        printf("\n -> Voulez vous decoder le fichier ENSEIGNANT-MESRS.bin (oui= o/ non = n)\n?");
        scanf("%c",&ch);
        scanf("%c",&ch);
        if((ch=='o')||(ch=='O')){ decodage_fichier("ENSEIGNANT-MESRS.bin"); };
    }break;

    case 8:
        {printf("\n\t\t********** Affichage de l'entete et le nombre de LireDir et EcrireDir**********");
            Affichage_entete(f,"ENSEIGNANT-MESRS.bin");
            printf("\n  Nombre de liredir = %d",lirdir);
            printf("\n  Nombre de ecriredir = %d\n\n",ecrdir);
        } break;
        case 9:
        {printf("\n\t\t**********  representation graphique de l�organisation globale et interne des trois premiers blocs du fichier **********");
            affichage3bloc(f,"ENSEIGNANT-MESRS.bin");

        } break;
        case 0 :
            {
                ch_in_TOF(Index);
                return 0;
            }break;
    default: {printf("\n votre  choix est erronee\n\n");

    break;}
    }
      printf("voulez vous continuer ?\n");
       printf("N= non / O = oui \n");
       scanf("%c",&c);
        scanf("%c",&c);
       if(c=='n'||c=='N')
       {
          repeter=false;
       }else{repeter=true; }
     }
     ch_in_TOF(Index);
    return 0;
}
