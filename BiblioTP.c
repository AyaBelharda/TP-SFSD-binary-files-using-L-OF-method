#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<string.h>

#include "MachAbs.h"
#define DMax 11
#define Max_S 9
#define Max_Wilaya 40
#define Max_Specialite 25
#define Max_Dernier_Diplome 25
#define Max_Nom 31
#define Max_reg 10
#define Max_Grade 25
#define Max_Etab 200
#define Max_GS 4

struct Tenreg e;
 LO_F *f;
   Tbloc *buf;
int ecrdir, lirdir;
int cpt;


       void menu (void)

		{
		printf ("\n\n\n\n\n\n\n\n\n\n\n\t||                                  ********************                                                    ||\n");
	    printf ("\t||               ********************* MENU PRINCIPAL  **********************                               ||\n");
	    printf ("\t||                                   ******************                                                     ||\n");
	    printf ("\t||__________________________________________________________________________________________________________||\n");
	    printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -1. Ajout d'un nouvel enseignant au fichier ENSEIGNANT-MESRS.bin                                         ||\n");
		printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -2. Modification de l'etablissement universitaire d'un enseignant                                        ||\n");
		printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -3. Suppression d'un enregistrement donne par le matricule                                               ||\n");
		printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -4. Suppression de tous les enregistrements relatifs a une specialite donnee                             ||\n");
		printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -5. Affichage des enseignants de meme etablissement ayant une anciennete 2 valeurs                       ||\n");
		printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -6. Consultation des enseignants exercant dans une region donnee                                         ||\n");
		printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -7. Codage et decodage du fichier ENSEIGNANT-MESRS.bin                                                   ||\n");
		printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -8. Affichage de l'entete et le nombre de LireDir et EcrireDir                                           ||\n");
		printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -9. representation graphique de l'organisation globale et interne des trois premiers blocs du fichier    ||\n");
		printf ("\t||                                                                                                          ||\n");
		printf ("\t|| -0. Quitter                                                                                              ||\n");
		printf ("\t||                                                                                                          ||\n");
        printf ("\t||__________________________________________________________________________________________________________||\n");
        }





/**************************** FONCTIONS RELIER A L'INDEX *************************************/
void recherche_ind(int val,int *i,int *j,bool *trouv,int *k,int *eff,int cpt)//recherche dichotomique dans la table d'index
{ int bi,bs,p,nb;
//LO_F *f;
//bool continu;
*trouv = false;
nb = cpt;//to be changed because it can be more than that if there's supp logic or can it be right?
bi=0; bs=nb ; //continu=true;

while((!(*trouv)) &&( bi<= bs))
{
    (*k) = ((bi+bs) / 2);
  if (val < Index[*k].Val)
    bs = (*k)-1 ;
  if (val > Index[*k].Val)
        bi = (*k)+1 ;
  if ((val == Index[*k].Val) /*&& (Index[*k].eff == 0)*/)
  {         (*trouv) = true;
            (*i) = Index[*k].nblc;
            *j = Index[*k].nenreg;
            *eff = Index[*k].eff;
            }

  }
  if (!(*trouv) )
  {
    *k = bi;

  }



}

//insertion dans la table index
void Insert_ind( int val, int i, int j)
{  int m , p , nb , eff;
bool trouv;
// LO_F *f;

  recherche_ind(val,&i,&j,&trouv,&p,&eff,cpt);//on recherche la valeur val dans la table d'index
  nb = cpt;
  if ((trouv) && (eff==0))//si il existe et non efface
  {
      printf("impossible de l'inserer \n");
  }
  else {
        m = nb+1 ;//indice de derniere case de tableau d'index
    while ( m > p)//on fait le decalage
    {
        Index[m] = Index [m-1] ;
          m--;
    }

    Index[p].Val=val;
    Index[p].eff=0;
    Index[p].nblc = i;
    Index[p].nenreg = j;

  }

}
void reorg_ind(Ienreg tab[])//reorganisation dans un seul parcours dans le tableau lui meme
{ int k=0;
    for(int i=0;i<nbI;i++)
    {
        if(tab[i].eff==0)
        {//on reecrer les valeurs non effacer logiquemnt seulement
            tab[k].Val=tab[i].Val;
            tab[k].nblc=tab[i].nblc;
            tab[k].nenreg=tab[i].nenreg;
            tab[k].eff=0;
            tab[i].eff=1;
            k++;
        }
        else{//or maybe it needs to be removed later
            printf("valeur inexistante");
        }
    }

}

/*-----------------------------------------------------------------------------------------------------------------------------*/
               /**************************** FIN DES FONCTIONS RELIER A L'INDEX *************************************/


               /************************************ DEBUT DE  CREATION *********************************************/
/*-----------------------------------------------------------------------------------------------------------------------------*/
//module de creation générale
void creation(int n)
{ f=malloc(sizeof(LO_F));
    Ouvrir(f,"ENSEIGNANT-MESRS.bin",'N');

    charg_init(f,n);

      Fermer(f);
      printf("\n --> creation termine .\n");
}

//module qui génère aléatoirement un matricule
int GenAleaMat( LO_F *f,int i , int j)
{
    int aleat ,nb,eff;
    bool repeat=false,trouv;

aleat=(rand()%(999999-111111)*(rand()%25))+111111;//ça permet de generer un nombre aleatoure entre 111111 et 999999
recherche_ind(aleat,&i,&j,&repeat,&nb,&eff,cpt);//cherchons si ce matrcle n'existe pas deja

while((repeat) || (eff==1))//si ça existe deja
{
      aleat=(rand()%(999999-111111)*(rand()%25))+111111;
        recherche_ind(aleat,&i,&j,&repeat,&nb,&eff,cpt);

}
return aleat;}

//module qui génère aléatoirement le prenom de l'enseignant
void Generation_Nom(char c[Max_Nom]){//cette procédure génère le nom et le prénom de l'enseignant(e) aléatoirement
    int q=0,i=0;
    char cn[Max_Nom]={};
    strcpy(c,"");
    //srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
    q = rand()%26+4; //le nombre de caractères du nom
    for(i=0;i<q;i++){
    cn[i] = rand()%26+'a';//on génère aléatoirement un caractère
    }
    strcpy(c,cn);
    };
//module qui génère aléatoirement le prenom de l'enseignant
void Generation_Prenom(char c[Max_Nom]){//cette procédure génère le nom et le prénom de l'enseignant(e) aléatoirement
    int q=0,i=0;
    char cn[Max_Nom]={};
    strcpy(c,"");
    //srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
    q = rand()%26+4; //le nombre de caractères du nom
    for(i=0;i<q;i++){
    cn[i] = rand()%26+'a';//on génère aléatoirement un caractère
    }
    strcpy(c,cn);
    };

 //module qui génère aléatoirement le sexe de l'enseignant
void Generation_Sexe(char c[Max_S]){//cette procédure génère le sexe de l'enseignant(e) aléatoirement
    int q=0;
    //srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
    q=rand()%2+1;//on génère aléatoirement le sexe
    if (q==1){
        strcpy(c,"Masculin");
    }
    if (q==2){
        strcpy(c,"Feminin");
    }
    };

 //module qui génère aléatoirement le groupe sanguin de l'enseignant
void Generation_Groupe_sanguin(char c[Max_GS]){//cette procédure génère le groupe de l'enseignant(e) aléatoirement
   int q=0;
   //srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
   q=rand()%8+1;//on génère aléatoirement le groupe sanguin
   switch (q) {
          case 1://le groupage de l'enseignat est: O+
             {
                strcpy(c,"O+");
              }
          break;
          case 2://le groupage de l'enseignat est: A+
             {
                strcpy(c,"A+");
              }
          break;
          case 3://le groupage de l'enseignat est: B+
             {
                strcpy(c,"B+");
              }
          break;
          case 4://le groupage de l'enseignat est:O-
             {
                strcpy(c,"O-");
              }
          break;
          case 5://le groupage de l'enseignat est: A-
             {
                strcpy(c,"A-");
              }
          break;
          case 6://le groupage de l'enseignat est: AB+
             {
                strcpy(c,"AB+");
              }
          break;
          case 7://le groupage de l'enseignat est: B-
             {
                strcpy(c,"B-");
              }
          break;
          case 8://le groupage de l'enseignat est: AB-
             {
                strcpy(c,"AB-");
              }
          break;
   }
   }

 //module qui génère aléatoirement la spécialité de l'enseignant
   void Generation_Specialite(char s[20]){//cette procédure génère la spécialité de l'enseignant(e) aléatoirement
   int P=0;
   //srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
   P=rand()%9+1;//on génère aléatoirement le matricule de la spécialité
   switch (P) {
          case 1://La spécialité de l'enseignant est: Informatique
             {
                strcpy(s,"Informatique");
              }
          break;
          case 2://La spécialité de l'enseignant est: Architecture
             {
                strcpy(s,"Architecture");
              }
          break;
          case 3://La spécialité de l'enseignant est: Medecine
             {
                strcpy(s,"Medecine");
              }
          break;
          case 4://La spécialité de l'enseignant est: Agronomie
             {
                strcpy(s,"Agronomie");
              }
          break;
          case 5://La spécialité de l'enseignant est: Psychologie
             {
                strcpy(s,"Psychologie");
              }
          break;
          case 6://La spécialité de l'enseignant est: Journalisme
             {
                strcpy(s,"Journalisme");
              }
          break;
          case 7://La spécialité de l'enseignant est: Ingenierie
             {
                strcpy(s,"Ingenierie");
              }
          break;
          case 8://La spécialité de l'enseignant est: Pharmacie
             {
                strcpy(s,"Pharmacie");
              }
          break;
         case 9://La spécialité de l'enseignant est: Commerce
             {
                strcpy(s,"Commerce");
              }
          break;

         case 10://La spécialité de l'enseignant est: Mathematiques
             {
                strcpy(s,"Mathematiques");
              }
          break;
   }
   }

//module qui génère aléatoirement le grade de l'enseignant
void Generation_Grade(char g[Max_Grade]){//cette procédure génère le grade de l'enseignant(e) aléatoirement
   int gg=0;
   //srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
   gg=rand()%5+1;//on génère aléatoirement le grade
   switch (gg) {
          case 1://Professeur(e)
             {
                strcpy(g,"Professeur");
              }
          break;
          case 2://Le grade de l'enseignant est: Maître de conférences Rang A
             {
                strcpy(g,"");//initialiser la chaine à vide
                strcat(g,"Maitre");
                strcat(g," ");
                strcat(g,"De");
                strcat(g," ");
                strcat(g,"Conferences");
                strcat(g," ");
                strcat(g,"Rang");
                strcat(g," ");
                strcat(g,"A");
              }
          break;
          case 3://Le grade de l'enseignant est: Maître de conférences Rang B
             {

                strcpy(g,"");//initialiser la chaine à vide
                strcat(g,"Maitre");
                strcat(g," ");
                strcat(g,"De");
                strcat(g," ");
                strcat(g,"Conferences");
                strcat(g," ");
                strcat(g,"Rang");
                strcat(g," ");
                strcat(g,"B");
              }
          break;
          case 4://Le grade de l'enseignant est: Maître assistant(e) Rang A
             {

                strcpy(g,"");//initialiser la chaine à vide
                strcat(g,"Maitre");
                strcat(g," ");
                strcat(g,"Assistant");
                strcat(g," ");
                strcat(g,"Rang");
                strcat(g," ");
                strcat(g,"A");
              }
          break;
          case 5://Le grade de l'enseignant est: Maître assistant(e) Rang B
             {
                strcpy(g,"");//initialiser la chaine à vide
                strcat(g,"Maitre");
                strcat(g," ");
                strcat(g,"Assistant");
                strcat(g," ");
                strcat(g,"Rang");
                strcat(g," ");
                strcat(g,"B");
              }
          break;
          case 6://Le grade de l'enseignant est: Assistant
             {
                strcpy(g,"Assistant");
              }
          break;
   }
   }

//module qui génère aléatoirement le grade de l'enseignant
void Generation_Dernier_Diplome(char diplome[Max_Dernier_Diplome]){//cette procédure génère le dernier diplome de l'enseignant(e) aléatoirement
   int dd=0;
   //srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
   dd=rand()%5+1;//on génère aléatoirement le dernier diplome
   switch (dd) {
          case 1://Le dernier diplome de l'enseignant est: Doctorat d’Etat
             {
                strcpy(diplome,"");
                strcat(diplome,"Doctorat");
                strcat(diplome," ");
                strcat(diplome,"D'Etat");
              }
          break;
          case 2://Le dernier diplome de l'enseignant est: Doctorat en sciences
             {
                strcpy(diplome,"");
                strcat(diplome,"Doctorat");
                strcat(diplome," ");
                strcat(diplome,"En");
                strcat(diplome," ");
                strcat(diplome,"Sciences");
              }
          break;
          case 3://Le dernier diplome de l'enseignant est: Doctorat D-LMD
             {

                strcpy(diplome,"");
                strcat(diplome,"Doctorat");
                strcat(diplome," ");
                strcat(diplome,"D-LMD");
              }
          break;
          case 4://Le dernier diplome de l'enseignant est: PhD
             {

                strcpy(diplome,"PHD");
              }
          break;
          case 5://Le dernier diplome de l'enseignant est: Habilitation Universitaire
             {
                strcpy(diplome,"");
                strcat(diplome,"Habiliation");
                strcat(diplome," ");
                strcat(diplome,"Universitaire");
              }
          break;
          case 6://Le dernier diplome de l'enseignant est: Magistere
             {
                strcpy(diplome,"Magistere");
              }
          break;

   }
   }

//module qui génère aléatoirement de la date de recrutement et de la date de naissance de l'enseignant
   void Generation_Dates(char d_n[DMax],char d_r[DMax]){
    int AN=0 , M=0, J=0 ,AR=0;
    char str[DMax];
    AN=rand()%45+1953;//génerer aléatoirement l'année de naissance (entre 1953 et 1998)
    M=rand()%11+1;//génerer aléatoirement le mois de naissance (entre 1 et 12)
  //  srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
    if (M==2) {     //si le mois est fevrier
        if (AN % 4 == 0) { J = rand()%28+1; }  //Si l'année est bisextille => max des jours est 29
        else { J = rand()%27+1; };  //Si l'année n'est pas bisextille => max des jours est 28
    }
    else {
            if (((M % 2 == 1) && (M <= 7)) || ((M % 2 == 0) && (M > 7))){   //Pour les mois ayant 31 jours
                J = rand()%30+1;
            }
            else { J = rand()%29+1; };  //Pour les mois ayant 30 jours
            }
    strcpy(d_n,"");
    itoa(J,str,10);//convertion du jour en un entier en décimal
    strcat(d_n,str);
    strcat(d_n,"/");
    itoa(M,str,10);//convertion du mois en un entier en décimal
    strcat(d_n,str);
    strcat(d_n,"/");
    itoa(AN,str,10);//convertion de l'année en un entier en décimal
    strcat(d_n,str);
    //on procède maintenant à générer la date de recrutement en se basant sur la date de naissance pour ne pas creer de confusions

    AR=rand()%37+1985;
    M=rand()%11+1;
//srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
    if (M==2) {     //si le mois est fevrier
        if (AR % 4 == 0) { J = rand()%28+1; }  //Si l'année est bisextille => max des jours est 29
        else { J = rand()%27+1; };  //Si l'année n'est pas bisextille => max des jours est 28
    }
    else {
            if (((M % 2 == 1) && (M <= 7)) || ((M % 2 == 0) && (M > 7))){   //Pour les mois ayant 31 jours
                J = rand()%30+1;
            }
            else { J = rand()%29+1; };  //Pour les mois ayant 30 jours
}
//on procede maintenant à corriger les erreurs s'il en a bien sur
AN=AN+24;//la date de naissance minimale pour le recrutement
if(AR<AN){ //si l'enseignant a moins que 24ans il faut corriger la date de recrutement
    AR=AN;
}
    strcpy(d_r,"");
    itoa(J,str,10);//convertion du jour en un entier en décimal
    strcat(d_r,str);
    strcat(d_r,"/");
    itoa(M,str,10);//convertion du mois en un entier en décimal
    strcat(d_r,str);
    strcat(d_r,"/");
    itoa(AR,str,10);//convertion de l'année en un entier en décimal
    strcat(d_r,str);
};

//module qui génère aléatoirement la wilaya de naissance de l'enseignant
void Generation_Wilaya(char wilaya[30]){//cette procédure génère une wilaya aléatoirement
    FILE *fichier=NULL;//pointeur sur fichier text "wilayas"
     char chaine[30] = ""; // Chaîne vide
int i,cpt=0;
//srand(time(NULL));//activer le mode de génération aléatoire pour changer la valeur à chaque fois
i=rand()%57+1;//on génère aléatoirement le matricule de la wilaya [1..58]
fichier=fopen("wilayas.txt","r");//ouvrir le fichier des wilayas en mode lecture seule
if (fichier != NULL)//tester s'il y a eurreur lors de l'ouverture
    {
        while (fgets(chaine, 30, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            cpt++;//incrémenter le compteur
            if (i==cpt){ //quand on arrive à la ligne qui correspond au numéro de la wilaya
            strcpy(wilaya,chaine);//on copie la chaine obtenue dans le paramètre de la procédure
        }}

        fclose(fichier);//fermer le fichier
    }
else printf("fichier wilayas inexistant");//cas ou le fichier n'existe pas dans le répertoire du programme
}

//module qui génère aléatoirement l'établissement de l'enseignant
void Generation_Etablissement_Reg(char x[],char y[]){//cette proc dure g n re un  tablissement al atoirement
FILE *fichier=NULL;//pointeur sur fichier text " tablissements"
bool exit = false;
char chaine[Max_Etab] = ""; // Cha ne vide
int i,cpt=0;
//srand(time(NULL));//activer le mode de g n ration al atoire pour changer la valeur   chaque fois
i=rand()%110+1;//on g n re al atoirement le matricule des  tablissements [1..111]
fichier=fopen("Etablissement.txt","r");//ouvrir le fichier des  Etablissements en mode lecture seule
if (fichier != NULL)//tester s'il y a eurreur lors de l'ouverture
    {
       while (fgets(chaine, Max_Etab, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            cpt++;//incrémenter le compteur
            if (i==cpt){ //quand on arrive à la ligne qui correspond au numéro de la wilaya
            strcpy(x,chaine);
             }
        }

        fclose(fichier);//fermer le fichier
    }
else printf("fichier Etablissement inexistant");//cas ou le fichier n'existe pas dans le r pertoire du programme
   if (i<32){  strcpy(y,"Est"); }
   if ((i>=32) && (i<82)) { strcpy(y,"Centre"); }
   if (i>=82){ strcpy(y,"Ouest"); }
return (0);
}

/*********************************************** DEBUT DE CHARGEMENT INITIAL *************************************************/

 void charg_init(LO_F *f,int n)
{
   int id=0,b=1,nb;
   int w;
   int mtr;
    char x[Max_Nom] , y[Max_Nom] ,d[Max_S] , m[Max_GS] , Dr[DMax] , Dn[DMax] ,S[Max_Specialite],G[Max_Grade],DD[Max_Dernier_Diplome],wly[Max_Wilaya] ;
    char t[50];
   Tbloc buf,buf1;

    for(int i=0 ; i<n; i++)
{
     if(id==MAX)//si on depasse le nombre maximum d'enregistrement dans un bloc
     {
              buf.suiv=b+1;//chainage de buf avec le buffer precedant
              buf.NB=MAX;
          EcrirDir(f,b,&buf);//enregistrement de buffer precedant
          ecrdir++;
           b++;
           id=0;
           buf.suiv=-1;//son suivant sera Null
          buf.NB=0 ;//on sauvgarde le nombre danregistrement dans le bloc

} //it generate the nb of enreg but it is supposed to be modified later
    mtr=GenAleaMat(f,b,id);
      //nb=nombre /100000;

      Insert_ind(mtr,b,id);//on insert la valeur dans la table d'index
      cpt++;
      buf.Tab[id].matricule=mtr;
    Generation_Nom(x);
    Generation_Prenom(y);
    Generation_Dates(Dn,Dr);
    Generation_Wilaya(wly);
    Generation_Sexe(d);
    Generation_Groupe_sanguin(m);
    Generation_Grade(G);
    Generation_Specialite(S);
    Generation_Dernier_Diplome(DD);
    strcpy(buf.Tab[id].Nom,x);//Génération aléatoire du nom et du prénom de l'enseignant
    strcpy(buf.Tab[id].Prenom,y);//Génération aléatoire de la wilaya de naissance de l'enseignant à partir du fichier texte wilayas.txt
    strcpy(buf.Tab[id].Sexe,d);//Génération aléatoire du sexe de l'enseignant
    strcpy(buf.Tab[id].Groupe_Sanguin,m);//Génération aléatoire du groupe sanguin de l'enseignant
    strcpy(buf.Tab[id].Date_Naissance,Dn);//Génération aléatoire de la date de naissance de l'enseignant
    strcpy(buf.Tab[id].Wilaya_Naissance,wly);//Génération aléatoire de la wilaya de naissance de l'enseignant
    strcpy(buf.Tab[id].Date_Recrutement,Dr);//Génération aléatoire de la date de recrutement de l'enseignant
    strcpy(buf.Tab[id].Grade,G);//Génération aléatoire du grade de l'enseignant
    strcpy(buf.Tab[id].Specialite,S);//Génération aléatoire de la spécialité de l'enseignant
    strcpy(buf.Tab[id].Dernier_Diplome,DD);//Génération aléatoire du dernier diplome de l'enseignant
    Generation_Etablissement_Reg(buf.Tab[id].Etablissement.eta,buf.Tab[id].Etablissement.reg);



 id++;

}
if(id>0)//sauvgarde de dernier  bloc qui n'as pas atteint le maximum des enregistrement
{
//      if(b==1)//si on est dans l'entete
  //      {
            buf.suiv=-1;//son suivant sera Null
            buf.NB= id;//on sauvgarde le nombre danregistrement dans le bloc
           EcrirDir(f,b,&buf) ;//sauvgarde de bloc numero b
           ecrdir++;


}

//l'affectation dans l'entete
Aff_entete(f,1,b);
Aff_entete(f,3,n);
Aff_entete(f,2,1);
}
          /************************************* FIN DE CHARGEMENT INITIAL *************************************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
          /**************************** DEBUT DE INSERTION D'ENREGISTREMENT *************************************/
void Inser_enr(LO_F *f)
{   Tbloc buf;
    int Mat , i,j,nb,eff,k,p,choix=0;
    LO_F *fichier;
     char ins[100];
     bool repeat,trouv;
     i = Entete(f,1);
     LirDir(f,i,&buf);
     lirdir++;
     j = buf.NB;       //     j=buf.NB;

     if(j==MAX) {//si le bloc est plein
            buf.suiv=i+1;//on increment le nombre du bloc
            EcrirDir(f,i,&buf);//on ecrit le bloc precedant
            ecrdir++;
            j=0;
     }

    printf("veuillez inserer les informations relies a cette personne ");
    printf("Le matricule (compris entre 111111 et 999999:  \n");
    scanf("%d",&Mat);
    cpt++;
   recherche_ind(Mat,&i,&j,&trouv,&k,&eff,cpt);
//on test l'existance de ce matricule

while(((trouv) && (eff==0)) || ((Mat<111110)||(Mat>1000000)))
{      printf("Veuillez reessayer -- Matricule existant deja ou erronne --\n");
       scanf("%d",&Mat);
       recherche_ind(Mat,&i,&j,&trouv,&p,&eff,cpt);
       }
  buf.Tab[j].matricule =Mat;
  Insert_ind(Mat,i,j);
  //les affectations
    printf("le Nom : \n");
    scanf("%s",ins);
    while((strlen(ins))<4 || (strlen(ins)>30))
{      printf("Veuillez reessayer -- le nobmre de caracteres du nom doit etre compris entre 4 et 30 caracteres --\n");
       scanf("%s",&ins);
       }
    strcpy(buf.Tab[j].Nom,ins);
     printf("le prenom : \n");
    scanf("%s",ins);
    while((strlen(ins))<4 || (strlen(ins)>30))
{      printf("Veuillez reessayer -- le nobmre de caracteres du prenom doit etre compris entre 4 et 30 caracteres --\n");
       scanf("%s",&ins);
       }
    strcpy(buf.Tab[j].Prenom,ins);
     printf("la date de naissance :  \n");
     printf("Veuillez selectionner un jour (entre 1 et 31)  \n");
     int date=0;
     char str[10];//variable trasitoire pour permettre la creation de la chaine

     scanf("%d",&date);
     while((date<1) || (date>31))
{      printf("Veuillez reessayer -- le jour doit etre compris entre 1 et 31 --\n");
       scanf("%d",&date);
       }
    strcpy(ins,"");
    itoa(date,str,10);//convertion du jour en une chaine de caracteres
    strcat(ins,str);
    strcat(ins,"/");
    printf("Veuillez selectionner un mois (entre 1 et 12)  \n");
    printf("\n1-Janvier\n2-Fevrier\n3-Mars\n4-Avril\n5-Mai\n6-Juin\n7-Juillet\n8-Aout\n9-Septembre\n10-Octobre\n11-Novembre\n12-Decembre");
    printf("\n\nVeuillez entrer le numero du mois correspondant ");
    scanf("%d",&date);
    while((date<1) || (date>12))
{      printf("Veuillez reessayer -- le mois doit etre compris entre 1 et 12 --\n");
       scanf("%d",&date);
       }
    itoa(date,str,10);//convertion du mois en une chaine de caracteres
    strcat(ins,str);
    strcat(ins,"/");

    printf("\nVeuillez selectionner une annee (entre 1953 et 1998):  ");
scanf("%d",&date);
    while((date<1953) || (date>1998))
{      printf("Veuillez reessayer -- l'annee doit etre comprise entre 1953 et 1998 --\n");
       scanf("%d",&date);
       }
       itoa(date,str,10);//convertion de l'annee en une chaine de caracteres
       strcat(ins,str);
    strcpy(buf.Tab[j].Date_Naissance,ins);
    printf("La wilaya de naissance : \n");
    FILE *fich=NULL;//pointeur sur fichier text "wilayas"
    char chaine[Max_Etab] = ""; // Chaîne vide
    int cpt=0;
    fich=fopen("wilayas.txt","r");//ouvrir le fichier des wilayas en mode lecture seule
if (fich != NULL)//tester s'il y a eurreur lors de l'ouverture
    {
        while (fgets(chaine, 30, fich) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            cpt++;//incrémenter le compteur
            printf("%d %s %s\n",cpt,"-",chaine);
        }

        fclose(fich);//fermer le fichier
    }
else printf("fichier wilayas inexistant");//cas ou le fichier n'existe pas dans le répertoire du programme
cpt=0;
int matr=0;
printf("\nSelectionnez le matricule de la wilaya: \n");
    scanf("%d",&matr);
     while((matr<1) || (matr>58))
{      printf("Veuillez reessayer -- le matricule doit etre compris entre 1 et 58 --\n");
       scanf("%d",&matr);
       }
    fich=fopen("wilayas.txt","r");//ouvrir le fichier des wilayas en mode lecture seule
if (fich != NULL)//tester s'il y a eurreur lors de l'ouverture
    {
        while (fgets(chaine, 30, fich) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            cpt++;//incrémenter le compteur
            if (cpt==matr){ //quand on arrive à la ligne qui correspond au numéro de la wilaya
            strcpy(buf.Tab[j].Wilaya_Naissance,chaine);
        }}

        fclose(fich);//fermer le fichier
    }

      printf("Le sexe : \n");

    printf("1-Femme\n2-Homme");
    printf("\n\nVeuillez choisir le numero correspondant: ");
    scanf("%d",&choix);
    while((choix<1) || (choix>2))
{      printf("Veuillez reessayer -- le choix doit etre soit 1 ou 2 --\n");
       scanf("%d",&choix);
       }
       switch (choix) {
          case 1:
             {
                strcpy(ins,"Feminin");
              }
          break;
          case 2:
             {
                strcpy(ins,"Masculin");
              }}
    strcpy(buf.Tab[j].Sexe,ins);
       printf("Le groupe sanguin  : \n");
       printf("Veuillez choisir un groupage parmi ces choix");
       printf("\n1-O+\n2-A+\n3-B+\n4-O-\n5-A-\n6-AB+\n7-B-\n8-AB-");
       printf("\nVeuillez entrer votre choix: ");
       scanf("%d",&choix);
       while((choix<1) || (choix>8))
{      printf("Veuillez reessayer -- le choix doit etre compris entre 1 et 8 --\n");
       scanf("%d",&choix);
       strcpy(ins,"");
       }
       switch (choix) {
          case 1://le groupage de l'enseignat est: O+
             {
                strcpy(ins,"O+");
              }
          break;
          case 2://le groupage de l'enseignat est: A+
             {
                strcpy(ins,"A+");
              }
          break;
          case 3://le groupage de l'enseignat est: B+
             {
                strcpy(ins,"B+");
              }
          break;
          case 4://le groupage de l'enseignat est:O-
             {
                strcpy(ins,"O-");
              }
          break;
          case 5://le groupage de l'enseignat est: A-
             {
                strcpy(ins,"A-");
              }
          break;
          case 6://le groupage de l'enseignat est: AB+
             {
                strcpy(ins,"AB+");
              }
          break;
          case 7://le groupage de l'enseignat est: B-
             {
                strcpy(ins,"B-");
              }
          break;
          case 8://le groupage de l'enseignat est: AB-
             {
                strcpy(ins,"AB-");
              }
          break;
   }


    strcpy(buf.Tab[j].Groupe_Sanguin,ins);


       printf("La date de recrutement  : \n");
       printf("Veuillez selectionner un jour (entre 1 et 31)  \n");
     strcpy(str,"");//vider la chaine pour l'utisliser de nouveau
     scanf("%d",&date);
     while((date<1) || (date>31))
{      printf("Veuillez reessayer -- le jour doit etre compris entre 1 et 31 --\n");
       scanf("%d",&date);
       }
    strcpy(ins,"");
    itoa(date,str,10);//convertion du jour en une chaine de caracteres
    strcat(ins,str);
    strcat(ins,"/");
    printf("Veuillez selectionner un mois (entre 1 et 12)  \n");
    printf("\n1-Janvier\n2-Fevrier\n3-Mars\n4-Avril\n5-Mai\n6-Juin\n7-Juillet\n8-Aout\n9-Septembre\n10-Octobre\n11-Novembre\n12-Decembre");
    printf("\n\nVeuillez entrer le numero du mois correspondant ");
    scanf("%d",&date);
    while((date<1) || (date>12))
{      printf("Veuillez reessayer -- le mois doit etre compris entre 1 et 12 --\n");
       scanf("%d",&date);
       }
    itoa(date,str,10);//convertion du mois en une chaine de caracteres
    strcat(ins,str);
    strcat(ins,"/");

    printf("\nVeuillez selectionner  l'annee de recrutement (entre 1985 et 2022):  ");
    scanf("%d",&date);
    while((date<1985) || (date>2022))
{      printf("Veuillez reessayer -- l'annee doit etre comprise entre 1985 et 2022 --\n");
       scanf("%d",&date);
       }
       itoa(date,str,10);//convertion de l'annee en une chaine de caracteres
       strcat(ins,str);
      strcpy(buf.Tab[j].Date_Recrutement,ins);


     printf("Le grade : \nveuillez choisir l'un des suivants\n\n");
     printf("\n 1- Professeur(e)\n 2- Maitre de conférences Rang A\n 3- Maitre de conférences Rang B\n 4- Maitre assistant(e) Rang A\n 5- Maitre assistant(e) Rang B\n 6- Assistant(e)\n\n");
     printf("\nVeuillez entrer votre choix: ");
   scanf("%d",&choix);
    while((choix<1) || (choix>6))
{      printf("Veuillez reessayer -- le choix doit etre compris entre 1 et 6 --\n");
       scanf("%d",&choix);
       }

   switch (choix) {
          case 1://Professeur(e)
             {
                strcpy(ins,"");//initialiser la chaine à vide
                strcpy(ins,"Professeur");
              }
          break;
          case 2://Le grade de l'enseignant est: Maître de conférences Rang A
             {
                strcpy(ins,"");//initialiser la chaine à vide
                strcat(ins,"Maitre");
                strcat(ins," ");
                strcat(ins,"De");
                strcat(ins," ");
                strcat(ins,"Conferences");
                strcat(ins," ");
                strcat(ins,"Rang");
                strcat(ins," ");
                strcat(ins,"A");
              }
          break;
          case 3://Le grade de l'enseignant est: Maître de conférences Rang B
             {

                strcpy(ins,"");//initialiser la chaine à vide
                strcat(ins,"Maitre");
                strcat(ins," ");
                strcat(ins,"De");
                strcat(ins," ");
                strcat(ins,"Conferences");
                strcat(ins," ");
                strcat(ins,"Rang");
                strcat(ins," ");
                strcat(ins,"B");
              }
          break;
          case 4://Le grade de l'enseignant est: Maître assistant(e) Rang A
             {

                strcpy(ins,"");//initialiser la chaine à vide
                strcat(ins,"Maitre");
                strcat(ins," ");
                strcat(ins,"Assistant");
                strcat(ins," ");
                strcat(ins,"Rang");
                strcat(ins," ");
                strcat(ins,"A");
              }
          break;
          case 5://Le grade de l'enseignant est: Maître assistant(e) Rang B
             {
                strcpy(ins,"");//initialiser la chaine à vide
                strcat(ins,"Maitre");
                strcat(ins," ");
                strcat(ins,"Assistant");
                strcat(ins," ");
                strcat(ins,"Rang");
                strcat(ins," ");
                strcat(ins,"B");
              }
          break;
          case 6://Le grade de l'enseignant est: Assistant
             {
                strcpy(ins,"");//initialiser la chaine à vide
                strcpy(ins,"Assistant");
              }
          break;

   }
  // printf("%s",ins);
    strcpy(buf.Tab[j].Grade,ins);//copier le grade dans le champ grade du buffer
     printf("La Specialite : \n");
     printf("\n1-Informatique\n2-Architecture\n3-Medecine\n4-Agronomie\n5-Psychologie\n6-Journalisme\n7-Ingenierie\n8-Pharmacie\n9-Commerce\n10-Mathematiques");
     printf("\n\nVeuillez selectionnez le numero correspondant a la specialite: ");
     scanf("%d",&choix);
     strcpy(ins,"");
     while((choix<1) || (choix>10))
{      printf("Veuillez reessayer -- le choix doit etre compris entre 1 et 10 --\n");
       scanf("%d",&choix);
       }
       switch (choix) {
          case 1://La spécialité de l'enseignant est: Informatique
             {
                strcpy(ins,"Informatique");
              }
          break;
          case 2://La spécialité de l'enseignant est: Architecture
             {
                strcpy(ins,"Architecture");
              }
          break;
          case 3://La spécialité de l'enseignant est: Medecine
             {
                strcpy(ins,"Medecine");
              }
          break;
          case 4://La spécialité de l'enseignant est: Agronomie
             {
                strcpy(ins,"Agronomie");
              }
          break;
          case 5://La spécialité de l'enseignant est: Psychologie
             {
                strcpy(ins,"Psychologie");
              }
          break;
          case 6://La spécialité de l'enseignant est: Journalisme
             {
                strcpy(ins,"Journalisme");
              }
          break;
          case 7://La spécialité de l'enseignant est: Ingenierie
             {
                strcpy(ins,"Ingenierie");
              }
          break;
          case 8://La spécialité de l'enseignant est: Pharmacie
             {
                strcpy(ins,"Pharmacie");
              }
          break;
         case 9://La spécialité de l'enseignant est: Commerce
             {
                strcpy(ins,"Commerce");
              }
          break;

         case 10://La spécialité de l'enseignant est: Mathematiques
             {
                strcpy(ins,"Mathematiques");
              }
          break;
   }

    strcpy(buf.Tab[j].Specialite,ins);
       printf("Le dernier diplome : \nveuillez choisir l'un des suivants\n\n");
      printf("\n 1- Doctorat d'Etat \n 2- Doctorat en sciences \n 3- Doctorat D-LMD\n 4- Phd\n 5- Habilitation Universitaire\n 6- Magistere \n");
      strcpy(ins,"");
      printf("\nentrez votre choix: ");
    scanf("%d",&choix);
while((choix<1) || (choix>6))
{      printf("Veuillez reessayer -- le choix doit etre compris entre 1 et 6 --\n");
       scanf("%d",&choix);
       }
       switch (choix) {
          case 1://Le dernier diplome de l'enseignant est: Doctorat d’Etat
             {
                strcpy(ins,"");
                strcat(ins,"Doctorat");
                strcat(ins," ");
                strcat(ins,"D'Etat");
              }
          break;
          case 2://Le dernier diplome de l'enseignant est: Doctorat en sciences
             {
                strcpy(ins,"");
                strcat(ins,"Doctorat");
                strcat(ins," ");
                strcat(ins,"En");
                strcat(ins," ");
                strcat(ins,"Sciences");
              }
          break;
          case 3://Le dernier diplome de l'enseignant est: Doctorat D-LMD
             {

                strcpy(ins,"");
                strcat(ins,"Doctorat");
                strcat(ins," ");
                strcat(ins,"D-LMD");
              }
          break;
          case 4://Le dernier diplome de l'enseignant est: PhD
             {

                strcpy(ins,"PHD");
              }
          break;
          case 5://Le dernier diplome de l'enseignant est: Habilitation Universitaire
             {
                strcpy(ins,"");
                strcat(ins,"Habiliation");
                strcat(ins," ");
                strcat(ins,"Universitaire");
              }
          break;
          case 6://Le dernier diplome de l'enseignant est: Magistere
             {
                strcpy(ins,"Magistere");
              }
          break;

   }
    strcpy(buf.Tab[j].Dernier_Diplome,ins);
       printf("\nL'etablissement  : \n");
    //afficher le fichier des etablissements
    FILE *Fich=NULL;//pointeur sur fichier text "etablissements"
    char ch[Max_Etab] = ""; // Chaîne vide
    cpt=0;
    Fich=fopen("eta.txt","r");//ouvrir le fichier des établissements en mode lecture seule
if (Fich != NULL)//tester s'il y a erreur lors de l'ouverture
    {
        while (fgets(chaine, Max_Etab, Fich) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            cpt++;//incrémenter le compteur
            printf("%d %s %s\n",cpt,"-",chaine);
        }

        fclose(Fich);//fermer le fichier
    }
else printf("fichier etablissements inexistant");//cas ou le fichier n'existe pas dans le répertoire du programme
cpt=0;//remettre le compteur a 0
int num_etab=0;
printf("\nSelectionnez le numero de l'etablissement: \n");
    scanf("%d",&num_etab);
    Fich=fopen("eta.txt","r");//ouvrir le fichier des etablissements en mode lecture seule
if (Fich != NULL)//tester s'il y a eurreur lors de l'ouverture
    {
        while (fgets(chaine, Max_Etab, Fich) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            cpt++;//incrémenter le compteur
            if (cpt==num_etab){ //quand on arrive à la ligne qui correspond au numéro de l'etablissement
            strcpy(buf.Tab[j].Etablissement.eta,chaine);} //copier le nom de l'etablissement dans le buffer

            }
            if (num_etab<32){
                strcpy(buf.Tab[j].Etablissement.reg,"Est");
                }
            if ((num_etab>31)&&(num_etab<82)){
               strcpy(buf.Tab[j].Etablissement.reg,"Centre");
                }
            if (num_etab>81){
                strcpy(buf.Tab[j].Etablissement.reg,"Ouest");
                }
        }

    else{printf("\nErreur, le fichier eta.txt n'existe pas dans votre repertoire");}
 fclose(Fich);//fermer le fichier
    if(j==0)//si  on est dans un nouveau bloc
    {   buf.suiv= -1;//sont suivant est nil
        buf.NB=1;
        EcrirDir(f,i+1,&buf);
        Aff_entete(f,1,i+1);//incrementation du nombre des blocs


    }
    else{   buf.NB=buf.NB+1;//sinon on  inser dans le bloc courant
            EcrirDir(f,i,&buf);
    }
k = Entete(f,3);
        k++;
        Aff_entete(f,3,k);//incrementation du nombre d'enregistrements

}

            /**************************** FIN DE INSERTION D'ENREGISTREMENT *************************************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
            /********************* DEBUT DE SUPPRESION D'ENREGISTREMENT par matricule ***************************/
void Supp_Matr(LO_F *f,int mat)
{   int i, j ,N,nb,nch,k,i2,j2,ch,eff;
    bool trouv;
    Tbloc buf1,buf;
   recherche_ind(mat,&i,&j,&trouv,&nb,&eff,cpt);//on cherche si cet enreg exist
   if((trouv)&&(!eff))
   {
   Index[nb].eff=1;

    N = Entete(f,1);//sauvgarde de dernier enregistrement

 if (i != (Entete(f,1))) //si l'enregistrement ne se trouve pas dans le dernier enregistrement
     {  LirDir(f,i,&buf);//on lit le bloc qui contient l'enregistrement a supprimer
     lirdir++;
        LirDir(f,N,&buf1);//on lit le dernier bloc
        lirdir++;
         buf.Tab[j] = buf1.Tab[buf1.NB-1];//affectation du dernier enregistrement à l'enregistrement courant

         buf1.NB = buf1.NB-1;//on decrement leurs nombre d'enregistrement

         EcrirDir(f,i,&buf);//sauvgarde de ce bloc
         nch=buf.Tab[j].matricule;//on sauvgarde la valeur du matricule
         if (buf1.NB > 0)//si le bloc n'st pas vide encore
         {

             buf1.suiv=-1;//son suivant sura null
           EcrirDir(f,N,&buf1);//on l'ecrit
           ecrdir++;
         }
         else {//si le bloc est vide

              LirDir(f,N-1,&buf1);//on lit son precedant
              lirdir++;
              buf1.suiv=-1;//son suivant est null
            Aff_entete(f,1,(N-1));//on decrement le nombre des blocs

         }
     }
     else//si l'enregistrement dans le dernier bloc
     { LirDir(f,i,&buf);
lirdir++;
     buf.Tab[j] = buf.Tab[buf.NB-1];
     nch = buf.Tab[j].matricule;
     buf.NB = buf.NB -1 ;

      if(buf.NB > 0)
       {

            buf.suiv=-1;

           EcrirDir(f,i,&buf);
           ecrdir++;
         }
         else
         {

         if(buf.NB==0)
            {
                N=N-1;
         LirDir(f,(N),&buf1);
         lirdir++;
         buf1.suiv= -1;
         buf1.NB=buf1.NB;

         EcrirDir(f,(N),&buf1);
      ecrdir++;
          Aff_entete(f,1,N);

         }
         }
      }

  ch=nb;
 recherche_ind(nch,&i2,&j2,&trouv,&k,&eff,cpt);//recherche d'emplacement k de dernier matricule

 Index[k].nblc = i;//mise a jour du numero de bloc de dernier enregistrement dans l'index
  Index[k].nenreg = j; //mise a jour du numero d'enregistrement de dernier enregistrement  dans l'index

  int en = Entete(f,3)-1;

 Aff_entete(f,3,en);
 }else{printf("ce matricule n'existe pas\n");}

}
             /********************* FIN DE SUPPRESION D'ENREGISTREMENT par matricule ***************************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
             /**************************** DEBUT DE SUPPRESION D'UNE SPECIALITE ********************************/
void Supp_SPE(LO_F* f,char Spe[30])//ON UTILISE LA FUNC PRECEDANT APRES QU4ON RECUPERE LES MATRICULES DE CES REGIONS
{
int i,j,k,mat;

i=Entete(f,2);
//printf ("i= %d \n",i);
Tbloc buf;
while(i != -1)//TQ on est pas dansla fin de fichier
{
    LirDir(f,i,&buf);//on lit le bloc
    lirdir++;
for(int j =0;j<buf.NB;j++)//on parcours le bloc
{   k=strcmp(strupr(buf.Tab[j].Specialite),strupr(Spe));

    if(k==0)  //(strcmp(buf.Tab[j].Force_Armee,FA))==0
{
    Supp_Matr(f,buf.Tab[j].matricule);
}
}
i=buf.suiv;
}

}
               /**************************** FIN DE SUPPRESION D'UNE SPECIALITE **********************************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
/************************** Affichage des enregistrements selon ETABLISSEMENT + requete à intervalle (2 années différentes) ************************************/
void Affich_Etab_A(LO_F* f , char Etabl[Max_Etab],int ANmin,int ANmax)
{
//FUNCT REQUET A INTERVALLE
   char str[DMax] ;
   const char s[2] = "/";
   char *token;
   Tbloc buf;
   int n=0,annee,i,a=0;

   Ouvrir(f,"ENSEIGNANT-MESRS.bin",'a'); //ouvrir le fichier en mode ancien
   i=1; //recuperer le num du 1er bloc
    printf("\n\n|=======******************************************************************************************=======|\n");
	printf("|                                                L'Affichage                                              \n");

	printf("|+----------************************************************************************************----------+|\n");
  while(i!= -1) //parcours entre les blocs
{
    LirDir(f,i,&buf);  //charger le bloc dans le buffer
for(int j =0;j<buf.NB;j++) // parcours dans le bloc
{
    strcpy(str,buf.Tab[j].Date_Naissance); //copier la date de naissance en variable str pour l'utiliser

   token = strtok(str, s); //pour avoir le 1er mot avant 's'



   while( n < 2 ) { // traverser la chaine jusqu'a l'obtention de la date

      token = strtok(NULL, s);
      n++;
   } // Fin while (n<2)
    a++;
    n=0; //rendre n à 0 pour recuperer à chaque fois
    annee=atoi(token);   //convertir char en int
if((strcmp(buf.Tab[j].Etablissement.eta,Etabl)==0) && (annee<=ANmax) && (annee>=ANmin)) //si(RM Donnee = celle du soldat ) et l'annee est
                                                           // compris entre annee max et annee min on consulte l'enregistrement
{
   printf("  M = %d\n  Nom = %s\n  Prenom = %s\n  Date de naissance = %s\n  Wilaya de naissance = %s  Sexe = %s\n  Groupe sanguin = %s\n  Date de rectrutement = %s \n  Grade = %s \n  Specialite = %s \n  Dernier diplome = %s\n  Etablissement = %s",buf.Tab[j].matricule,buf.Tab[j].Nom
                            ,buf.Tab[j].Prenom,buf.Tab[j].Date_Naissance,buf.Tab[j].Wilaya_Naissance,buf.Tab[j].Sexe,buf.Tab[j].Groupe_Sanguin,buf.Tab[j].Date_Recrutement
                            ,buf.Tab[j].Grade,buf.Tab[j].Specialite,buf.Tab[j].Dernier_Diplome,buf.Tab[j].Etablissement.eta);

          printf("\n            ****************************************\n");

} // fin if

} //FIN for (j=0,j<buf.NB)
i=buf.suiv; //recuperer le num du prochain bloc
} //FIN WHILE(i != -1)


Fermer(f); //Fermeture du fichier
}
            /************************** FIN Affichage de la requete à intervalle *****************************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
                  /**************************** DEBUT AFFICH_REGION *************************************/
void Affich_REG(LO_F *f)
{

int i=1,j,result;
Tbloc buf;
char rg[Max_reg];
Ouvrir(f,"ENSEIGNANT-MESRS.bin",'A');
printf("\n  -> Entrez la region : \n        o Est        o Centre        o Ouest \n      ->");
scanf("%s",rg);
    printf("\n\n|=======******************************************************************************************=======|\n");
	printf("|                                                L'Affichage                                              \n");

	printf("|+----------************************************************************************************----------+|\n");
       while( i != -1) //PARCOURS ENTRE BLOCS
        { j=0;
          LirDir(f,i,&buf); //CHARGER LE BLOC DANS BUFFER
           while(j < buf.NB) //pARCOURS DANS LE BLOC
            {
             if (strcmp(strupr(buf.Tab[j].Etablissement.reg),strupr(rg))==0)
           {
            printf(" M=%d\n Nom=%s\n Prenom=%s\n DN=%s\n WN=%s\n Sexe=%s\n GS=%s\n DR=%s \n GD=%s \n Spe=%s \n DDpl=%s\n eat=%s",buf.Tab[j].matricule,buf.Tab[j].Nom
                            ,buf.Tab[j].Prenom,buf.Tab[j].Date_Naissance,buf.Tab[j].Wilaya_Naissance,buf.Tab[j].Sexe,buf.Tab[j].Groupe_Sanguin,buf.Tab[j].Date_Recrutement
                            ,buf.Tab[j].Grade,buf.Tab[j].Specialite,buf.Tab[j].Dernier_Diplome,buf.Tab[j].Etablissement.eta);

             printf ("*********************************************************************************************************\n");
           }

           j++;} //FIN WHILE ( j < buf.NB)
           i=buf.suiv;
        } // FIN WHILE ( i!= -1)
Fermer(f);
}
                       /**************************** FIN Affich_REGION ******************************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
                       /******************* Modification_etablissement ******************************/
void Mod_Eta(LO_F *f,int mat)
{
int i, j ,k,eff;
char Etabl[Max_Etab];
Tbloc buf;
bool trouv,tend;
recherche_ind(mat,&i,&j,&trouv,&k,&eff,cpt);
if((trouv)&&(!eff))
   {
LirDir(f,i,&buf);
lirdir++;
  // printf(" \n\n m=%d n=%s p=%s d=%s w=%s r=%s \n",buf.Tab[k1].Matricule,buf.Tab[k2].Nom,buf.Tab[k2].Prenom,buf.Tab[k2].Date_Naissance,buf.Tab[k2].Wilaya_Naissance,buf.Tab[k2].Region_Militaire);
                printf("\t|+----------+----------+\n\n ");
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
            printf("%d - %s\n",cpt,ch);
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
            strcpy(buf.Tab[j].Etablissement.eta,ch);} //copier le nom de l'etablissement dans le buffer

            }
            if (num_etab<32){
                strcpy(buf.Tab[j].Etablissement.reg,"Est");
                }
            if ((num_etab>31)&&(num_etab<82)){
               strcpy(buf.Tab[j].Etablissement.reg,"Centre");
                }
            if (num_etab>81){
                strcpy(buf.Tab[j].Etablissement.reg,"Ouest");
                }
        }
  EcrirDir(f,i,&buf);
  ecrdir++;
}else{printf("ce matricule n'existe pas\n");}


}
                         /**************************FIN  Mod_Eta *******************************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
                        /*********************** AFFICHAGE DU FICHIER **************************/
void affichage (LO_F *f,char nom_fich[40])
{int i,j,n,a;
Tbloc buf;
    a=0;
    Ouvrir(f,nom_fich,'A');//ouvrir le fichier en mode ancien
    if(f->fichier !=NULL)//si le fichier existe
    {i=Entete(f,2);//recuperer le numero du premier bloc
     n=Entete(f,3);//recuperer le nombre d'enregistrements
    //i=1;
    if (n!=0)//si le fichier n'est pas vide
    {printf("\n\n|=======******************************************************************************************=======|\n");
	printf("|                                                L'Affichage                                              \n");

	printf("|+----------************************************************************************************----------+|\n");

        while(i != -1)//tant qu'on est pas arrive à la fin de fichier
    {
        LirDir(f,i,&buf);//lire le buf i
            for (j=0;j<buf.NB;j++)//parcourir tout le tableau
            {
                      printf(" enregistrement Num%d\n",a);//affichage de numero d'enregistrement
                     printf("  M = %d\n  Nom = %s\n  Prenom = %s\n  Date de naissance = %s\n  Wilaya de naissance = %s  Sexe = %s\n  Groupe sanguin = %s\n  Date de rectrutement = %s \n  Grade = %s \n  Specialite = %s \n  Dernier diplome = %s\n  Etablissement = %s",buf.Tab[j].matricule,buf.Tab[j].Nom
                            ,buf.Tab[j].Prenom,buf.Tab[j].Date_Naissance,buf.Tab[j].Wilaya_Naissance,buf.Tab[j].Sexe,buf.Tab[j].Groupe_Sanguin,buf.Tab[j].Date_Recrutement
                            ,buf.Tab[j].Grade,buf.Tab[j].Specialite,buf.Tab[j].Dernier_Diplome,buf.Tab[j].Etablissement.eta);
                printf("\n|______________________________________________________________________________________________________________________\n\n ");
                a++;
            }

     //printf("\t|+----------+----------+ les suiv i = %d\n",buf.suiv);
        i=buf.suiv;//aller au prochain bloc
    }
    }
    }
    else {printf("\n**Le fichier est vide**");}
    Fermer(f);
    return(0);
}
                            /*********************** FIN affichage **************************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
                            /************* AFFICHAGE DU FICHIER CODE/DECODE ***************/
void affichage_Code (LO_F *f,char nom_fich[40])
{int i,j,n,a;
Tbloc2 buf;
    a=0;
    Ouvrir(f,nom_fich,'A');//ouvrir le fichier en mode ancien
    if(f->fichier !=NULL)//si le fichier existe
    {i=Entete(f,2);//recuperer le numero du premier bloc
     n=Entete(f,3);//recuperer le nombre d'enregistrements
    //i=1;
    if (n!=0)//si le fichier n'est pas vide
    {printf("\n\n|=======******************************************************************************************=======|\n");
	printf("|                                                L'Affichage                                              \n");

	printf("|+----------************************************************************************************----------+|\n");

        while(i != -1)//tant qu'on est pas arrive à la fin de fichier
    {
        LirDir(f,i,&buf);//lire le buf i
            for (j=0;j<buf.NB;j++)//parcourir tout le tableau
            {
                      printf(" enregistrement Num%d\n",a);//affichage de numero d'enregistrement
                     printf(" M=%s\n Nom=%s\n Prenom=%s\n DN=%s\n WN=%s\n Sexe=%s\n GS=%s\n DR=%s \n GD=%s \n Spe=%s \n DDpl=%s\n eta=%s \n ",buf.Tab[j].matricule,
                            buf.Tab[j].Nom,buf.Tab[j].Prenom,buf.Tab[j].Date_Naissance,buf.Tab[j].Wilaya_Naissance,buf.Tab[j].Sexe,buf.Tab[j].Groupe_Sanguin,buf.Tab[j].Date_Recrutement,buf.Tab[j].Grade,buf.Tab[j].Specialite,buf.Tab[j].Dernier_Diplome,buf.Tab[j].Etablissement.eta);
                printf("\n|______________________________________________________________________________________________________________________\n\n ");
                a++;
            }

     //printf("\t|+----------+----------+ les suiv i = %d\n",buf.suiv);
        i=buf.suiv;//aller au prochain bloc
    }
    }
    }
    else {printf("\n**Le fichier est vide**");}
    Fermer(f);
    return(0);
}
                                      /************* FIN affichage_Code ***************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
                                /***********Codage du fichier ENSEIGNANT-MESRS.bin**********/
 void codage( unsigned char ligne2[], unsigned char mot[],unsigned char ligne[])
 {
 // signed char -128 -> +127
 // unsigned char 0 -> +255
 int i = 0, j = 0;
 strcpy(ligne,ligne2);
 printf("---------\n %s \n--------\n",ligne);
 while ( ligne[i] != '\0' ) {//Tant que ce n'est pas la fin de la chaine de caractères
 if ((ligne[i] >= 32) && (ligne[i] < 127)) {
 ligne[i] = ligne[i] + mot[j];
 while ( ligne[i] > 126 )
 ligne[i] = ligne[i] - 127 + 32;
 // pour que le code obtenu reste un caractere affichable
 // les caract affichables ont un code ascii entre 32 et 126
 i++;
 j++;
 if (mot[j] == '\0') j = 0; // si c'est la fin de la chaine de caractère du mot ou de la clé
 }
 else
 i++;
 }
 }
 /* cryptage d'une ligne par un mot-cle */

void codage_fichier (char nom_fich[20])
{int i,j,j2=0,n,b=1,nb;
char mtr[DMax],mtr2[DMax];
Tbloc buf;
Tbloc2 buf2;
    LO_F *f, *f2;
    char nomf2[200];
    char mot[20];
    f = malloc(sizeof(LO_F));  // INITIALISER LES 6 FICHIERS AVEC MALLOC
    f2 =malloc(sizeof(LO_F));
    printf("Nom du fichier texte en sortie : ");
    scanf(" %s", nomf2);
    printf("Le mot cle (<20 car) : ");
    scanf(" %s", mot);
    Ouvrir(f,nom_fich,'A');//ouvrir le fichier en mode ancien
    Ouvrir(f2,nomf2,'N');
    if(f->fichier !=NULL)//si le fichier existe
    {
     i=Entete(f,2);//recuperer le numero du premier bloc
     n=Entete(f,3);//recuperer le nombre d'enregistrements
    //i=1;
    if (n!=0)//si le fichier n'est pas vide
    {

        while(i != -1)//tant qu'on est pas arrive à la fin de fichier
    {
        LirDir(f,i,&buf);//lire le buf i

            for (j=0;j<buf.NB;j++)//parcourir tout le tableau
            {
                     itoa(buf.Tab[j].matricule,mtr,10);
                     codage(mtr,mot,buf2.Tab[j2].matricule);
                     codage(buf.Tab[j].Nom,mot,buf2.Tab[j2].Nom);
                     codage(buf.Tab[j].Prenom,mot,buf2.Tab[j2].Prenom);
                     codage(buf.Tab[j].Date_Naissance,mot,buf2.Tab[j2].Date_Naissance);
                     codage(buf.Tab[j].Wilaya_Naissance,mot,buf2.Tab[j2].Wilaya_Naissance);
                     codage(buf.Tab[j].Sexe,mot,buf2.Tab[j2].Sexe);
                     codage(buf.Tab[j].Groupe_Sanguin,mot,buf2.Tab[j2].Groupe_Sanguin);
                     codage(buf.Tab[j].Date_Recrutement,mot,buf2.Tab[j2].Date_Recrutement);
                     codage(buf.Tab[j].Grade,mot,buf2.Tab[j2].Grade);
                     codage(buf.Tab[j].Specialite,mot,buf2.Tab[j2].Specialite);
                     codage(buf.Tab[j].Dernier_Diplome,mot,buf2.Tab[j2].Dernier_Diplome);
                     codage(buf.Tab[j].Etablissement.eta,mot,buf2.Tab[j2].Etablissement.eta);
                     codage(buf.Tab[j].Etablissement.reg,mot,buf2.Tab[j2].Etablissement.reg);
                     j2++;
            }

     //printf("\t|+----------+----------+ les suiv i = %d\n",buf.suiv);
        if(j2==MAX)//si on depasse le nombre maximum d'enregistrement dans un bloc
        {
              buf2.suiv=b+1;//chainage de buf avec le buffer precedant
              buf2.NB=MAX;
              EcrirDir(f2,b,&buf2);//enregistrement de buffer precedant
              ecrdir++;
              b++;
              j2=0;
              buf2.suiv=-1;//son suivant sera Null
              buf2.NB=0 ;//on sauvgarde le nombre danregistrement dans le bloc
        }
              i=buf.suiv;//aller au prochain bloc
        }
    }
    if(j2>0)//sauvgarde de dernier  bloc qui n'as pas atteint le maximum des enregistrement
    {
       //      if(b==1)//si on est dans l'entete
            buf2.suiv=-1;//son suivant sera Null
            buf2.NB= j2;//on sauvgarde le nombre danregistrement dans le bloc
           EcrirDir(f2,b,&buf2) ;//sauvgarde de bloc numero b
           ecrdir++;
     }
     //l'affectation dans l'entete
     Aff_entete(f2,1,b);
     Aff_entete(f2,3,n);
     Aff_entete(f2,2,1);
     }
    else {printf("\n**Le fichier est vide**");}
    Fermer(f);
    Fermer(f2);
    return(0);
}



                                   /***********FIN codage_fichier************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
                            /***********Decodage du fichier ENSEIGNANT-MESRS.bin**********/
 void decodage( signed char ligne2[], signed char mot[],signed char ligne[])
 {
 int i = 0, j = 0;
 strcpy(ligne,ligne2);
 while ( ligne[i] != '\0' )
 if ( ligne[i] >= 32 && ligne[i] < 127 ) {
 ligne[i] = ligne[i] - mot[j];
 while ( ligne[i] < 32 )
 ligne[i] = 127 - 32 + ligne[i];
 // pour que le code obtenu reste un caractere affichable
 // les caract affichables ont un code asci entre 32 et 126
 i++;
 j++;
 if (mot[j] == '\0') j = 0;
 }
 else
 i++;
 }
 /* decryptage d'une ligne par un mot-cle */
void decodage_fichier (char nom_fich[])
{
    int i,j;
    int j2=0;
    int n,nb;
    int b=1;
char mtr[DMax],mtr2[DMax];
Tbloc buf;
Tbloc2 buf2;
    LO_F *f, *f2;
    char nomf2[200];
    char mot[20];
    f = malloc(sizeof(LO_F));  // INITIALISER LES 6 FICHIERS AVEC MALLOC
    f2 =malloc(sizeof(LO_F));
    printf("Nom du fichier texte en sortie : ");
    scanf(" %s", nomf2);
    printf("Le mot cle (<20 car) : ");
    scanf(" %s", mot);
    Ouvrir(f,nom_fich,'A');//ouvrir le fichier en mode ancien
    Ouvrir(f2,nomf2,'N');
    if(f->fichier !=NULL)//si le fichier existe
    {
     i=Entete(f,2);//recuperer le numero du premier bloc
     n=Entete(f,3);//recuperer le nombre d'enregistrements
    //i=1;
    if (n!=0)//si le fichier n'est pas vide
    {

        while(i != -1)//tant qu'on est pas arrive à la fin de fichier
    {
        LirDir(f,i,&buf);//lire le buf i

            for (j=0;j<buf.NB;j++)//parcourir tout le tableau
            {
                     itoa(buf.Tab[j].matricule,mtr,10);
                     decodage(mtr,mot,buf2.Tab[j].matricule);
                     decodage(buf.Tab[j].Nom,mot,buf2.Tab[j2].Nom);
                     decodage(buf.Tab[j].Prenom,mot,buf2.Tab[j2].Prenom);
                     decodage(buf.Tab[j].Date_Naissance,mot,buf2.Tab[j2].Date_Naissance);
                     decodage(buf.Tab[j].Wilaya_Naissance,mot,buf2.Tab[j2].Wilaya_Naissance);
                     decodage(buf.Tab[j].Sexe,mot,buf2.Tab[j2].Sexe);
                     decodage(buf.Tab[j].Groupe_Sanguin,mot,buf2.Tab[j2].Groupe_Sanguin);
                     decodage(buf.Tab[j].Date_Recrutement,mot,buf2.Tab[j2].Date_Recrutement);
                     decodage(buf.Tab[j].Grade,mot,buf2.Tab[j2].Grade);
                     decodage(buf.Tab[j].Specialite,mot,buf2.Tab[j2].Specialite);
                     decodage(buf.Tab[j].Dernier_Diplome,mot,buf2.Tab[j2].Dernier_Diplome);
                     decodage(buf.Tab[j].Etablissement.eta,mot,buf2.Tab[j2].Etablissement.eta);
                     decodage(buf.Tab[j].Etablissement.reg,mot,buf2.Tab[j2].Etablissement.reg);
                     j2++;
            }

     //printf("\t|+----------+----------+ les suiv i = %d\n",buf.suiv);
        if(j2==MAX)//si on depasse le nombre maximum d'enregistrement dans un bloc
        {
              buf2.suiv=b+1;//chainage de buf avec le buffer precedant
              buf2.NB=MAX;
              EcrirDir(f2,b,&buf2);//enregistrement de buffer precedant
              ecrdir++;
              b++;
              j2=0;
              buf2.suiv=-1;//son suivant sera Null
              buf2.NB=0 ;//on sauvgarde le nombre danregistrement dans le bloc
        }
              i=buf.suiv;//aller au prochain bloc
        }
    }
    if(j2>0)//sauvgarde de dernier  bloc qui n'as pas atteint le maximum des enregistrement
    {
       //      if(b==1)//si on est dans l'entete
            buf2.suiv=-1;//son suivant sera Null
            buf2.NB= j2;//on sauvgarde le nombre danregistrement dans le bloc
           EcrirDir(f2,b,&buf2) ;//sauvgarde de bloc numero b
           ecrdir++;
     }
     //l'affectation dans l'entete
     Aff_entete(f2,1,b);
     Aff_entete(f2,3,n);
     Aff_entete(f2,2,1);
     }
    else {printf("\n**Le fichier est vide**");}
    Fermer(f);
    Fermer(f2);
    return(0);
}


                                   /***********FIN decodage_fichier************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
                       /********************** AFFICHAGE DES 3 BLOCS ***************************/
void affichage3bloc(LO_F *f,char nom_fich[40])
{int i,j,n;
Tbloc buf;
char cadre1[]={201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187,'\0'};
    char  cadre2[]={200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188,'\0'};

    Ouvrir(f,nom_fich,'A');//ouvrir le fichier en mode ancien
    if(f->fichier !=NULL)//si le fichier existe
    {//i=Entete(f,2);//recuperer le numero du premier bloc
     n=Entete(f,3);//recuperer le nombre d'enregistrements
    i=1;
    if (n!=0)//si le fichier n'est pas vide
    {printf("\n\n|=======******************************************************************************************=======|\n");
	printf("|                                                L'Affichage                                              \n");

	printf("|+----------************************************************************************************----------+|\n");

        while((i!= -1) &&(i <4))//tant qu'on est pas arrive � la fin de fichier
    {
        LirDir(f,i,&buf);//lire le buf i

         printf("\t\t\t\t") ;
    printf("%s\n",cadre1);
        printf("\n %c|__________________________________________BLOC NUM  %d_____________________________________________________________\n\n ",186,i);
            for (j=0;j<buf.NB;j++)//parcourir tout le tableau
            {   printf("%c enregistrement Num%d\n",186,j);//affichage de numero d'enregistrement
                    printf("  M = %d\n  Nom = %s\n  Prenom = %s\n  Date de naissance = %s\n  Wilaya de naissance = %s  Sexe = %s\n  Groupe sanguin = %s\n  Date de rectrutement = %s \n  Grade = %s \n  Specialite = %s \n  Dernier diplome = %s\n  Etablissement = %s",buf.Tab[j].matricule,buf.Tab[j].Nom
                            ,buf.Tab[j].Prenom,buf.Tab[j].Date_Naissance,buf.Tab[j].Wilaya_Naissance,buf.Tab[j].Sexe,buf.Tab[j].Groupe_Sanguin,buf.Tab[j].Date_Recrutement
                            ,buf.Tab[j].Grade,buf.Tab[j].Specialite,buf.Tab[j].Dernier_Diplome,buf.Tab[j].Etablissement.eta);
            }

     //printf("\t|+----------+----------+ les suiv i = %d\n",buf.suiv);
        i=buf.suiv;//aller au prochain bloc
    }
    }
    }
    else {printf("\n**Le fichier est vide**");}
    Fermer(f);
}

                                /****************FIN affichage3bloc****************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/
                            /******************* AFFICHAGE D'ENTETE *********************/
void Affichage_entete(LO_F *f,char NF[35])
{
    Ouvrir(f,NF,'a');
    if(f->fichier)
   {
        printf("\n\nNombre de dernier bloc = %d \n",f->entete->nb_der);
         printf("Nombre d'enregistrements dans le fichier = %d \n",f->entete->nb_enr);
          printf("Nombre de premier bloc = %d \n",f->entete->nb_tete);
   }
    Fermer(f);
}

                              /****************FIN Affichage_entete****************/
/*----------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------*/

