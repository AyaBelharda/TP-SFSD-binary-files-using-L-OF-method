
#ifndef BiblioTP_H_
#define BiblioTP_H_

#include <stdio.h>
#include <stdlib.h>
#include"MachAbs.h"
void creation(int n);/*module de cr�ation du fichier PERSONNEL-ANP_DZ.bin o� chaque enregistrement est
compos� de 9 champs precedement declarer*/
void charg_init(LO_F *fichier,int n);//consiste � remplir le fichier avec N enregistrements
void Inser_enr(LO_F *f);//Insertion d�un nouvel enregistrement au fichier.
void Mod_Eta(LO_F *f,int mat);//Modification de l'etablissement d�un enseignant.
void Supp_Matr(LO_F *f,int mat);//Suppression d'un enregistrement donn� par matricule.
void Supp_SPE(LO_F* f,char FA[30]);//Suppression de tous les enregistrements relatifs � un etablissement donn�.
void Affich_Etab_A();//Affichage de tous les enregistrements relatifs � un etablissement donn�e entre deux ann�es donn�es
void Affich_REG(LO_F *f);//Affichage de tous les enregistrements appartenant � une region donn�e
void code_fichier(LO_F *f);//Coder le fichier "ENSEIGNANT-MESRS.bin"
void decode_fichier(LO_F *f);//decoder le fichier "ENSEIGNANT-MESRS.bin"
void Affichage_entete();//Affichage de l�en-t�te du fichier
void affichage3bloc(LO_F *f,char nom_fich[40]) ;//affichage graphique de l�organisation globale et interne des trois premiers blocs du fichier.
/*****************fonctions supplementaires *************************/
char* recherche_enreg( char *nomf , int val );//permet de rechercher une valeur d'indice val dans un fichier binaire
void recherche_ind(int val,int *i,int *j,bool *trouv,int *k,int *eff,int cpt);//permet d'e rechercher la valeurs et ses coordoonees a la table d'index
void Insert_ind( int val, int i, int j);//permet d'inserer la valeurs et ses coordoonees a la table d'index
void reorg_ind(Ienreg tab[]);//permet de reorganiser la table d'index
void affichage (LO_F *f,char nom_fich[40]);//affichage de tous les bloc de fichier principal "ENSEIGNANT-MESRS.bin"
int GenAleaMat( LO_F *f,int i , int j);//permet de generer aleatoirement des valeurs de matricule sans repetition
void Generation_Nom(char c[Max_Nom]);//module qui g�n�re al�atoirement le prenom de l'enseignant
void Generation_Prenom(char c[Max_Nom]);//module qui g�n�re al�atoirement le prenom de l'enseignant
void Generation_Sexe(char c[Max_S]); //module qui g�n�re al�atoirement le sexe de l'enseignant
void Generation_Groupe_sanguin(char c[Max_GS]); //module qui g�n�re al�atoirement le groupe sanguin de l'enseignant
void Generation_Specialite(char s[20]);//module qui g�n�re al�atoirement la sp�cialit� de l'enseignant
void Generation_Grade(char g[Max_Grade]);//module qui g�n�re al�atoirement le grade de l'enseignant
void Generation_Dernier_Diplome(char diplome[Max_Dernier_Diplome]);//module qui g�n�re al�atoirement le grade de l'enseignant
void Generation_Dates(char d_n[DMax],char d_r[DMax]);//module qui g�n�re al�atoirement de la date de recrutement et de la date de naissance de l'enseignant
void Generation_Wilaya(char wilaya[30]);//module qui g�n�re al�atoirement la wilaya de naissance de l'enseignant
void Generation_Etablissement_Reg(char x[],char y[]);//module qui g�n�re al�atoirement l'�tablissement de l'enseignant
#endif // MDLTP_H_

