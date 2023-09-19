
#ifndef BiblioTP_H_
#define BiblioTP_H_

#include <stdio.h>
#include <stdlib.h>
#include"MachAbs.h"
void creation(int n);/*module de création du fichier PERSONNEL-ANP_DZ.bin où chaque enregistrement est
composé de 9 champs precedement declarer*/
void charg_init(LO_F *fichier,int n);//consiste à remplir le fichier avec N enregistrements
void Inser_enr(LO_F *f);//Insertion d’un nouvel enregistrement au fichier.
void Mod_Eta(LO_F *f,int mat);//Modification de l'etablissement d’un enseignant.
void Supp_Matr(LO_F *f,int mat);//Suppression d'un enregistrement donné par matricule.
void Supp_SPE(LO_F* f,char FA[30]);//Suppression de tous les enregistrements relatifs à un etablissement donné.
void Affich_Etab_A();//Affichage de tous les enregistrements relatifs à un etablissement donnée entre deux années données
void Affich_REG(LO_F *f);//Affichage de tous les enregistrements appartenant à une region donnée
void code_fichier(LO_F *f);//Coder le fichier "ENSEIGNANT-MESRS.bin"
void decode_fichier(LO_F *f);//decoder le fichier "ENSEIGNANT-MESRS.bin"
void Affichage_entete();//Affichage de l’en-tête du fichier
void affichage3bloc(LO_F *f,char nom_fich[40]) ;//affichage graphique de l’organisation globale et interne des trois premiers blocs du fichier.
/*****************fonctions supplementaires *************************/
char* recherche_enreg( char *nomf , int val );//permet de rechercher une valeur d'indice val dans un fichier binaire
void recherche_ind(int val,int *i,int *j,bool *trouv,int *k,int *eff,int cpt);//permet d'e rechercher la valeurs et ses coordoonees a la table d'index
void Insert_ind( int val, int i, int j);//permet d'inserer la valeurs et ses coordoonees a la table d'index
void reorg_ind(Ienreg tab[]);//permet de reorganiser la table d'index
void affichage (LO_F *f,char nom_fich[40]);//affichage de tous les bloc de fichier principal "ENSEIGNANT-MESRS.bin"
int GenAleaMat( LO_F *f,int i , int j);//permet de generer aleatoirement des valeurs de matricule sans repetition
void Generation_Nom(char c[Max_Nom]);//module qui génère aléatoirement le prenom de l'enseignant
void Generation_Prenom(char c[Max_Nom]);//module qui génère aléatoirement le prenom de l'enseignant
void Generation_Sexe(char c[Max_S]); //module qui génère aléatoirement le sexe de l'enseignant
void Generation_Groupe_sanguin(char c[Max_GS]); //module qui génère aléatoirement le groupe sanguin de l'enseignant
void Generation_Specialite(char s[20]);//module qui génère aléatoirement la spécialité de l'enseignant
void Generation_Grade(char g[Max_Grade]);//module qui génère aléatoirement le grade de l'enseignant
void Generation_Dernier_Diplome(char diplome[Max_Dernier_Diplome]);//module qui génère aléatoirement le grade de l'enseignant
void Generation_Dates(char d_n[DMax],char d_r[DMax]);//module qui génère aléatoirement de la date de recrutement et de la date de naissance de l'enseignant
void Generation_Wilaya(char wilaya[30]);//module qui génère aléatoirement la wilaya de naissance de l'enseignant
void Generation_Etablissement_Reg(char x[],char y[]);//module qui génère aléatoirement l'établissement de l'enseignant
#endif // MDLTP_H_

