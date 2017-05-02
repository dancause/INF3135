/******************************************

nom: Janin Dancause
code: danj17087507
email: janin2000@gmail.com
cours INF3135

*******************************************/
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifndef DNBMAXTRAVAUX
	#define DNBMAXTRAVAUX CINQ
#endif
#define CINQ 5
#if	DNBMAXTRAVAUX==CINQ
	#define DNBMAXTRAVAUX CINQ
#endif

void reset();
int getNote(char *argv[]);
void imprimerHistogramme();
void lireFichier(char *argv[]);
int calculerEtoiles(int nbNote);
void traiterEntete(char *argv[]);
void imprimerEtoile(int nbEtoile);
void validerSeuil(int argc,char *argv[]);
void traiterNote(char temp[],char *argv[]);
void triNoteLitteral(float moyenne,char *argv[]);
void validerCode(char code_etudiant [],char *argv[]);

const int MAXABC=4;
const int MAXNUM=8;
const float ZERO=0.0;
const float MINNOTE=1.00;
const int MAXETUDIANT=50;
const int Longueur_code=12;
const float MAXNOTE=100.00;

int c;
int nbNote;	/*nombre de note a traité par étudiant*/
char tempo[10];
int noteMax[10];
int nb_etudiant=0;
char temp_note[40];//tableau contient les informations brute des notes avant traitement
int ponderation[10];
char msgErreur[100];
int noteLitteral[12];
char code_etudiant[12];

int main (int argc,char *argv[])
{

		if(argc > 12){		/* premier traitement valider le nombre d'argument*/
		fprintf(stderr,"%s --- nombre d'argument est inférieur \n", argv[0]); 
		exit(1);
		}else if(argc < 12){ 
		fprintf(stderr,"%s --- nombre d'argument insuffisant est inférieur \n", argv[0]); 
		exit(1);
		}
		else{	
				validerSeuil(argc,argv); /* valide que les arguments sont dans l'ordre et contient des notes */
				traiterEntete(argv);/* va lire les configs du début du fichier */
				lireFichier(argv); /* va lire le fichier envoyé dans l'entrée standard */
				imprimerHistogramme();
			}
}

void lireFichier(char *argv[]){
	int detect_code_etudiant=0;
	while ( ( c = getchar() )!= EOF ){
	
		if(detect_code_etudiant == 0){ /* s'assure que chaque caractère pour le code
										est soit une lettre ou un nombre */
						if( (tolower(c) >='a' && tolower(c) <= 'z')||(c >='0' && c <='9') )	{	
								code_etudiant[(int)strlen(code_etudiant)]=c;
							if((int)strlen(code_etudiant)==Longueur_code){
								validerCode(code_etudiant,argv);	
								detect_code_etudiant=1;
								nb_etudiant++;
								}
						}								
		}else {
					if( tolower(c) >='a' && tolower(c) <= 'z' ){ 	
						traiterNote(temp_note,argv);
						reset(); 
						detect_code_etudiant=0;
						} 				
					else{
						temp_note[strlen(temp_note)]=c;	
						}
				}		
		}
	traiterNote(temp_note,argv);
	detect_code_etudiant=0;
	reset();

}

void traiterNote(char temp[],char *argv[]){/* traite les notes d'un étudiant à la fois pour obtenir sa moyenne*/
	char *token;
	float moyenne=0;
	int count_note=0; //compte le nombre de note de chacun des étudiant
		token = strtok (temp," ,\n\r\t"); 
		
  			while (token != NULL){
  				float tempo=strtof(token, NULL);
  					if(tempo >= ZERO && tempo <= MAXNOTE){
  						tempo=(tempo/noteMax[count_note])*ponderation[count_note];
  						moyenne+=tempo;
    					token = strtok (NULL, " ,\n\r\t");
   						count_note++; 	
   						}else{
   						fprintf(stderr,"%s ----- Une des notes est en erreur\n", argv[0]);
						exit(1);
   						}
  				}			
  				if(count_note==nbNote){
						triNoteLitteral((moyenne),argv);
				}else{	
						fprintf(stderr,"%s ----- Le nombre de note est erroné pour le traitement\n", argv[0]);
						exit(1);
				}
}

void triNoteLitteral(float Moyenne,char *argv[]){ /*classe chaque moyenne d'étudiant en l'associant
													 à une note littéral*/
int i;
int trouver=0;
for(i=1;i<12;i++){
		if(Moyenne > strtof(argv[i],NULL)){
			if(trouver!=1){
				noteLitteral[i-1]++;
				trouver=1;
			}
		}
}
if(trouver!=1){ /*si une note n'a été classer dans la première boucle elle est ajouter à la plus basse note*/
	noteLitteral[11]++;
	}
}

void reset(){
		memset(temp_note, 0, sizeof temp_note);
		memset(code_etudiant, 0, sizeof code_etudiant);
		code_etudiant[0]=c;	
}

void validerCode(char code_etudiant [],char *argv[]){
	int ABC=0;
	int NUM=0;
	int i;
	for(i=0;i<(int)strlen(code_etudiant);i++){
		if( tolower(code_etudiant[i]) >='a' &&  tolower(code_etudiant[i]) <= 'z'){
			if( code_etudiant[i] >='A' &&  code_etudiant[i] <= 'Z'){
			ABC++;
			}
		}
		if(tolower(code_etudiant[i]) >='0' &&  tolower(code_etudiant[i]) <= '9'){
			NUM++;
		}
	}
	if(ABC != MAXABC && NUM != MAXNUM){
		fprintf(stderr,"%s ----- Un des codes étudiants est erroné\n", argv[0]);
		exit(1);
	}
}

void validerSeuil(int argc,char *argv[]){
	int i;
	for(i=1;i< argc;i++){	
			if(strtof(argv[i],NULL) >= MAXNOTE || strtof(argv[i],NULL) <= MINNOTE){
			printf("seuil %s \n",argv[i]);
				fprintf(stderr,"%s ----- Erreur dans le montant d'une des notes de seuils\n", argv[0]);
				exit(1);
			}
		}
	for(i=1;i< argc-1;i++){		
			if( strtof(argv[i],NULL) <= strtof(argv[i+1] ,NULL )){
				fprintf(stderr,"%s ----- Erreur dans l'ordre des seuils de note \n", argv[0]);
				exit(1);
			}
		}
}

void traiterEntete( char *argv[]){
int temp_ponderation=0;
int i=0;
		fscanf(stdin,"%d",&nbNote);
	if(nbNote <= ZERO || nbNote > DNBMAXTRAVAUX){
		fprintf(stderr,"%s ----- Erreur avec le nombre de travaux \n", argv[0]);
		exit(1);
		}
	
	for(i=0;i < nbNote;i++){
		fscanf(stdin,"%d", &ponderation[i]);
		temp_ponderation=temp_ponderation+ponderation[i];
			if(ponderation[i] < (int)MINNOTE || ponderation[i] > (int)MAXNOTE){
				fprintf(stderr,"%s ----- Erreur dans les notes de pondération \n", argv[0]);
				exit(1);
			}
		}
		if(temp_ponderation != (int)MAXNOTE){
			fprintf(stderr,"%s ----- Erreur dans le total des notes de pondération \n", argv[0]);
			exit(1);
		}
	
	for(i=0;i < nbNote;i++){
		fscanf(stdin,"%d", &noteMax[i]);
			if(noteMax[i] < (int)MINNOTE || noteMax[i] > (int)MAXNOTE){
			fprintf(stderr,"%s ----- Erreur avec les notes maximalles potentielles \n", argv[0]);
			exit(1);
			}
		}
}

void imprimerHistogramme(){
char note[]={"+A  A -A +B  B -B +C  C -C +D  D  E "};
		int i;
		int j=11;
		for(i=strlen(note)-1;i>0;i=i-3){
		fprintf(stdout," %c%c%c ",note[i],note[i-1],note[i-2]);
		imprimerEtoile(calculerEtoiles(noteLitteral[j]));
		putchar('\n');
		j--;
		}
}

int calculerEtoiles(int nbNote){ 
		if(nb_etudiant>MAXETUDIANT && nbNote > 0){
			float tempo=ceil((float)nb_etudiant/(float)MAXETUDIANT);
			nbNote=ceil((float)nbNote/tempo);	
			}
return nbNote;		
}

void imprimerEtoile(int nbEtoile){
int i;
	for(i=0;i<nbEtoile;i++){
		fprintf(stdout,"X");
	}
}