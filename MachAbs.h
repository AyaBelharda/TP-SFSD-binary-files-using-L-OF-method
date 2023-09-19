#ifndef MACHABS_H
#define MACHABS_H

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#define MAX 32
#define nbI 20000
#define DMax 11
#define Max_S 9
#define Max_Wilaya 40
#define Max_Specialite 25
#define Max_Dernier_Diplome 25
#define Max_Nom 31
#define Max_reg 10
#define Max_Grade 25
#define Max_Etab 100
#define Max_GS 4

/*****declaration des structures*****/

struct enreg {
    int champ1;
    char champ2[50];//
};

typedef struct Ienreg {
    int Val;//la valeurs qu'on vaut indexer
    int nblc;//numero de bloc ou la val existe
    int nenreg;//numero de enregistrement ou la val existe
    int eff;//champs d'effacement dans le fichier
   // int NbInd;//more like champs for the last indice !
}Ienreg;

typedef struct Etab
{
    char reg[Max_reg];
    char eta[Max_Etab];

} Etab;

typedef struct Tenreg
{
    int matricule;
    char Nom[Max_Nom];
    char Prenom[Max_Nom];
    char Date_Naissance[DMax];
    char Wilaya_Naissance[Max_Wilaya];
    char Sexe[Max_S];
    char Groupe_Sanguin[Max_GS];
    char Date_Recrutement[DMax];
    char Grade[Max_Grade];
    char Specialite[Max_Specialite];
    char Dernier_Diplome[Max_Dernier_Diplome];
    Etab Etablissement;

} Tenreg;

/*****structure de bloc (code/decode) ************/
typedef struct Tenreg2
{
    char matricule[10];
    char Nom[Max_Nom];
    char Prenom[Max_Nom];
    char Date_Naissance[DMax];
    char Wilaya_Naissance[Max_Wilaya];
    char Sexe[Max_S];
    char Groupe_Sanguin[Max_GS];
    char Date_Recrutement[DMax];
    char Grade[Max_Grade];
    char Specialite[Max_Specialite];
    char Dernier_Diplome[Max_Dernier_Diplome];
    Etab Etablissement;
}Tenreg2;

/*****structure de bloc (pour codage/decodage) ************/

typedef struct Tbloc2 Tbloc2;
struct Tbloc2
{   int NB; //nb d'enregistrements dans le tableau
    //tab t,
    Tenreg2 Tab[MAX]; // tableau d'enregistrements
    int suiv;    //prochain bloc
};
/*********************************************************/

Ienreg Index[nbI];


//typedef Tenreg tab [MAX];

/*****structure de bloc ************/

typedef struct Tbloc Tbloc;
struct Tbloc
{   int NB; //nb d'enregistrements dans le tableau
    //tab t,
    Tenreg Tab[MAX]; // tableau d'enregistrements
    int suiv;    //prochain bloc
};
 /****structure de l'entete ************/

typedef struct Entete_LO_F
{
  int nb_der; //nb de dernier bloc
  int nb_enr; //nb d'enregistrements dans le fichier
  int nb_tete;  //nb de 1er bloc
}Entete_LO_F;

 /*******structure du fichier LO_F**********/

typedef struct LO_F
{
    FILE *fichier;
    Entete_LO_F *entete;
} LO_F;

typedef struct Tbloc Buffer;

/*********la machine abstraite : implementation ***********/

void Ouvrir(LO_F *f,char nom[35],char m);//ouverture du fichier binaire
void Fermer(LO_F *f);//fermeture du fichier binaire
Tbloc Allocbloc(LO_F *f);//allocation d'un nouveau bloc dans le fichier bin
void LirDir(LO_F *f,int i,Buffer *buf);//lecture d'un bloc i
void EcrirDir(LO_F *f,int i,Buffer *buf);//ecriture d'un bloc i
void Aff_entete(LO_F *f,int i,int elt);//affectation d'element dans le champs i dans lentete
int Entete(LO_F *f,int i);//affichage d'element i dans l'entete

#endif
