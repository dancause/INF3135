
/*  Il reste la fonction  "commonBorders" qui est déjà déclarée et les doublons
	quand on entre la même commande plusieurs fois, Bonne Chance Paule! ;) */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <jansson.h>
#include "country.h"

#define SAVED_FILE "./data/countries.json"

#define COM_COUNTRY "--country"
#define COM_LANGUAGES  "--show-languages"	
#define COM_CAPITAL "--show-capital"
#define COM_BORDERS "--show-borders"
#define COM_REGION "--region"
#define COM_SAME_BORDERS "--same-borders"
#define COM_SAME_LANGUAGE "--same-language"

json_t * openFile();
void verifyCommands(int argc, char ** argv);

json_t * comCountry(char **argv, int i);
void printCountry(json_t * objCca3,json_t * objName);
void comLanguages(json_t * objPays);
void comCapital(json_t * objPays);
void comBorders(json_t * objPays);
void comRegion(int agrc, char **argv, int i);
void printRegion(int argc,char ** argv, json_t * objPays);

int commonLanguages(int argc,char ** argv,int i);
int commonBorders(int argc,char ** argv,int i);

char * verifyCca3(char ** argv, int i);
json_t * cca3ToPointer(char * firstAbbCountry);
void validateRegion(char* region);
void verifyDuplicate (char** argv, int argc);
void verifyArguments(char** argv, int argc);
void abortMission(char *s); 

json_t * openFile(){

	FILE* file = fopen (SAVED_FILE, "r");
	if(file == NULL){
		abortMission("Pointer called file is NULL\n");
	}//Verifies if the FILE* file pointing to "countries.json" is NULL

	json_error_t error;
	json_t * buffer;
	buffer = json_loadf(file, 0, &error);
	if(buffer == NULL){
		abortMission("Pointer called buffer is NULL\n");
	}//Verifies if the json_t * buffer pointing to "countries.json" is NULL
	
	if (json_is_array(buffer) == 0){
		abortMission("The first object is not an array\n");
	}
	return buffer;
}

void verifyCommands(int argc, char **argv){
	
	verifyArguments(argv,argc);
	verifyDuplicate(argv, argc);
	
	json_t * objPays;
	int i;
	for (i = 1; i != argc; i++){
		if (strcmp(argv[i] , COM_COUNTRY) == 0) {
			objPays = comCountry(argv, i);  
			++i; // To skip de accronyme (cca3) command

		}else if (strcmp(argv[i] , COM_LANGUAGES) == 0){
			comLanguages(objPays);   

		}else if (strcmp(argv[i] , COM_CAPITAL) == 0){
			comCapital(objPays);  
		
		}else if (strcmp(argv[i] , COM_BORDERS) == 0){
			comBorders(objPays);  
		
		}else if (strcmp(argv[i] , COM_REGION) == 0){
			comRegion(argc, argv, i);   
			i = argc -1; // comRegion is already handleling fails

		}else if (strcmp(argv[i] , COM_SAME_LANGUAGE) == 0){
			 i = commonLanguages(argc, argv, i); 

		}else if (strcmp(argv[i] , COM_SAME_BORDERS) == 0){
			 i = commonBorders(argc, argv, i);	 	
		
		}else {
			printf("%d",i);
			abortMission("One of the command in Argv[] is not valid");
		}
	}
	return;
}	

json_t * comCountry(char **argv, int i){
	
	if (i != 1){ 
		abortMission("Command --country has not been typed as the first command in command line");
	}

	char * abbCountry = argv[++i];
	abbCountry = verifyCca3(argv, i);
	
	json_t * buffer = openFile (); // ** CALL **
	json_t * objRightCountry;
	size_t size = json_array_size(buffer); 
	size_t index;
	for (index = 0; index < size; index++){	  
		//Getting the countries[index] and "cca3" value in a String
		json_t * objCountry = json_array_get(buffer, index);
		json_t * objCca3 = json_object_get(objCountry, "cca3");
		const char * strCca3 = json_string_value(objCca3);

		if (strcmp(strCca3 ,abbCountry) == 0){
			objRightCountry = objCountry;			
			json_t * objName = json_object_get(objCountry, "name");
			json_t * objNameCommon = json_object_get(objName, "common");
			printCountry(objCca3,objNameCommon ); // ** CALL **  
		}	
	}
	return objRightCountry; // return the "Big" Object of the proper country
}

void printCountry(json_t * objCca3,json_t * objNameCommon){

	printf("Name:  %s \n", json_string_value (objNameCommon) );
	printf("Code:  %s \n", json_string_value(objCca3) );
	return;
}

void comLanguages(json_t * objPays){

	json_t * objLanguages = json_object_get(objPays, "languages");

	const char *key; json_t *value;

	printf("Languages: ");
	json_object_foreach(objLanguages, key, value) {
    	printf("%s ",json_string_value(value) );
	}	
	printf("\n");
	return;
}

void comCapital(json_t * objPays){

	printf("Capital: ");
    printf("%s \n",json_string_value (json_object_get (objPays,"capital") ) );
	return;
}

void comBorders(json_t * objPays){

	json_t * objBorders = json_object_get(objPays, "borders");
	size_t index;
	json_t *value;

	printf("Borders: ");
	json_array_foreach(objBorders, index, value) {
		if (index != 0){
			printf(", ");
		}
    	printf("%s",json_string_value(value) );
	}	
	printf("\n");
	return;
}

void comRegion(int argc, char **argv, int i){

	// Changing the first letter to an uppercase
	char * region = argv[++i];
	region[0] = toupper(argv[i][0]);
	validateRegion(region);

	json_t * buffer = openFile (); // ** CALL ** 

	size_t size = json_array_size(buffer); 
	size_t index;
	for (index = 0; index < size; index++){	// PASS all countries in main array
		//Getting the countries[index] and "region" value in a String
		json_t * objPays = json_array_get(buffer, index);
		json_t *  objRegion = json_object_get(objPays, "region");
		const char * strRegion = json_string_value(objRegion);

		if (strcmp(strRegion ,region) == 0){
			//Getting the "common name" and "cca3" values 
			json_t * objName = json_object_get(objPays, "name");
			json_t * objNameCommon = json_object_get(objName, "common");
			json_t *  objCca3 = json_object_get(objPays, "cca3");
		 	printCountry(objCca3,objNameCommon);

		 	printRegion(argc, argv, objPays);
		}
	}
	return;
}

void printRegion(int argc,char ** argv, json_t * objPays){

	int j;
	for (j = 3; j != argc; j++){
		 		// Finding out which command has been tipped	 	
		 		if (strcmp(argv[j] , COM_LANGUAGES) == 0){
					comLanguages(objPays); // ** CALL **  

				}else if (strcmp(argv[j] , COM_CAPITAL) == 0){
					comCapital(objPays); // ** CALL **  
		
				}else if (strcmp(argv[j] , COM_BORDERS) == 0){
					comBorders(objPays);// ** CALL ** 
				}else{
					abortMission("One of the command in Argv[] is not valid"); //Error cases
				}   
			}
			printf("\n");
	return;
}


int commonLanguages(int argc,char ** argv,int i){
	
	if((argc > 5) || (argc < 4)) {
		abortMission("The number of arguments is incorrect for the command --same-language");
	}

	int same_language = 0;
	const char * language;
	int indexFirst = 2;
	int indexSecond = 3;
	int indexThird = 4;
	i = indexSecond;
	int firstPassage =0;

	char * firstAbbCountry = verifyCca3(argv, indexFirst); // ** CALL ** 
	json_t * firstObjPays = cca3ToPointer(firstAbbCountry); // ** CALL ** 
	json_t * firstObjLanguages = json_object_get(firstObjPays, "languages"); //GET first country languages

    char * secondAbbCountry = verifyCca3(argv, indexSecond); // ** CALL ** 
    json_t * secondObjPays = cca3ToPointer(secondAbbCountry); // ** CALL ** 
    json_t * secondObjLanguages = json_object_get(secondObjPays, "languages"); //GET second country languages

    json_t * thirdObjLanguages;
    if (argc > indexThird){
    	i = indexThird;
    	char * thirdAbbCountry = verifyCca3(argv, indexThird); // ** CALL ** 
    	json_t * thirdObjPays = cca3ToPointer(thirdAbbCountry); // ** CALL ** 
    	thirdObjLanguages = json_object_get(thirdObjPays, "languages"); //GET third country languages
    }

    const char * key1; json_t * value1;
    const char * key2; json_t * value2;
    const char * key3; json_t * value3;

    json_object_foreach(firstObjLanguages,  key1,  value1) { // PASS all first country languages
		json_object_foreach(secondObjLanguages, key2, value2) { // PASS all second country languages
    		if ( strcmp (json_string_value (value1) , json_string_value(value2) ) == 0 ){
    			if(argc == indexThird){
					same_language = 1;
					language = json_string_value (value1);
					
					if(firstPassage == 0){
						printf("yes ");
						++firstPassage;
					}
					
					printf("%s ", language);
					
				}else if (argc > indexThird){

    				json_object_foreach(thirdObjLanguages, key3, value3) { // PASS all third country languages
    					
						if ( strcmp (json_string_value (value2) , json_string_value(value3) ) == 0 ){
    						same_language =1;
							language = json_string_value (value2);
							
							if(firstPassage == 0){
								printf("yes ");
								++firstPassage;
							}
							printf("%s ",language);
						}
					}
				}
			}
		}
	}
	if(same_language == 1) {
		printf("\n");
	}else {
		printf("no\n");
	}
	
	return i;
}

int commonBorders(int argc,char ** argv,int i){
	
	if((argc > 5) || (argc < 4)) {
		abortMission("The number of arguments is incorrect for the command --same-borders");
	}

	int same_borders = 0;
	int indexFirst = 2;
	int indexSecond = 3;
	int indexThird = 4;
	
	if (argc == indexThird) {
		i = indexSecond;
	}else {
		i = indexThird;
	}
	
	char* firstAbbCountry = verifyCca3(argv, indexFirst);// ** CALL ** 
	json_t* firstObjPays = cca3ToPointer(firstAbbCountry);// ** CALL ** 
	json_t* firstObjBorders = json_object_get(firstObjPays, "borders");//GET first country borders
	
	int j;
	json_t* firstBorder;
	size_t firstSize = json_array_size(firstObjBorders);
	for ( j = 0; j < (int)firstSize; j++) {
		firstBorder = json_array_get(firstObjBorders, j);
		if (strcmp(json_string_value(firstBorder), verifyCca3(argv,indexSecond)) == 0) {
			++same_borders;
		}
	}	
	
	if ((same_borders == 1) && (argc == indexThird)) {
		printf("yes\n");
	}else if (argc == indexThird) {
		printf("no\n");
	} 
	
	if ((argc > indexThird) && (same_borders == 1)) {
		char* secondAbbCountry = verifyCca3(argv, indexSecond);// ** CALL ** 
		json_t* secondObjPays = cca3ToPointer(secondAbbCountry);// ** CALL ** 
		json_t* secondObjBorders = json_object_get(secondObjPays, "borders");//GET second country borders
		
		char* thirdAbbCountry = verifyCca3(argv, indexThird);
		json_t* thirdObjPays = cca3ToPointer(thirdAbbCountry);
		json_t* thirdObjBorders = json_object_get(thirdObjPays, "borders");//GET third country borders
		
		json_t* secondBorder;
		size_t secondSize = json_array_size(secondObjBorders);
		for (j = 0; j < (int)secondSize; j++) {
			secondBorder = json_array_get(secondObjBorders, j);
			if(strcmp(json_string_value(secondBorder), thirdAbbCountry) == 0) {
				++same_borders;
			}
		}
		
		json_t* thirdBorder;
		size_t thirdSize = json_array_size(thirdObjBorders);
		for (j = 0; j < (int)thirdSize; j++) {
			thirdBorder = json_array_get(thirdObjBorders, j);
			if(strcmp(json_string_value(thirdBorder), firstAbbCountry) == 0) {
				++same_borders;
			}
		}
	}	
	
	if((same_borders == 3) && (argc > indexThird)){
		printf("yes\n");
	}else if (argc > indexThird) {
		printf("no\n");
	}
		
	return i;
}

char * verifyCca3(char ** argv, int i){

// Changing all letters of "AbbCountry" in upper cases & Verify that the country abbriviation has 3 letters
	char * AbbCountry = argv[i];
	int j=0;
	while (AbbCountry[j] != '\0') { 
			AbbCountry[j] = toupper(argv[i][j]);
			j++;
	}
	if (j!=3){
		abortMission("The country name abriviation is not composed of 3 letters");
	}

	cca3ToPointer(AbbCountry); // Call for the validity of the accronyme


	return AbbCountry;
}

json_t * cca3ToPointer(char * AbbCountry){

	json_t * buffer = openFile (); // - CALL -
	json_t * objRightCountry = NULL;
	json_t * objCca3;

	size_t size = json_array_size(buffer); 
	size_t index;
	for (index = 0; index < size; index++){	//Getting the countries[index] "cca3" value in a String
	    json_t * objCountry = json_array_get(buffer, index);
		objCca3 = json_object_get(objCountry, "cca3");
		const char * strCca3 = json_string_value(objCca3);
		
		if (strcmp(AbbCountry , strCca3) == 0){ // Catch * on the rigth countries index []
			objRightCountry = json_array_get(buffer, index);
		}
	}
	
	if (objRightCountry == NULL){
		abortMission("An accronym (cca3) doesn't exist"); //Invalid accronym (cca3)
	}
	return objRightCountry; // return the "Big" Object of the proper country
}

void validateRegion(char* region){
	char *africa = "Africa", *americas = "Americas", *asia = "Asia", *europe = "Europe", *oceania = "Oceania";
	
	if ((strcmp(region, africa) != 0) && (strcmp(region, americas) != 0) && (strcmp(region, asia) != 0) &&
		(strcmp(region, europe) != 0) && (strcmp(region, oceania) != 0)) {
			abortMission("The region name is not valid");//Region name not valid
	}
	return;
}

void verifyArguments(char** argv, int argc) {
	if(argc < 3) {
		abortMission("The number of arguments is incorrect");
	}
	
	if ((strcmp(argv[1],COM_COUNTRY) != 0) && (strcmp(argv[1],COM_REGION) != 0) &&
		(strcmp(argv[1],COM_SAME_BORDERS) != 0) && (strcmp(argv[1],COM_SAME_LANGUAGE) != 0)) {
			printf("diablo");
			abortMission("The first command must be --country, --region, --same-language or --same-borders");
	}
	
	int i;
	for(i = 1; i < argc; i ++) {
		if (strcmp(argv[i], COM_COUNTRY) == 0) {
			i++;		
		}else if (strcmp(argv[i], COM_LANGUAGES) == 0) {
		}else if (strcmp(argv[i], COM_CAPITAL) == 0) {
		}else if (strcmp(argv[i],COM_BORDERS) == 0) {
		}else if (strcmp(argv[i],COM_REGION) == 0) {
			i++;
		}else if (strcmp(argv[i],COM_SAME_BORDERS) == 0) {
			i = argc;
		}else if (strcmp(argv[i],COM_SAME_LANGUAGE) == 0) {
			i = argc;
		}else {
			abortMission("The arguments entered are not valid");
		}
	}
	return;
}

void verifyDuplicate (char** argv, int argc) {
	int i, j;
	for (i = 0; i < argc; i++) {
		for (j = i+1; j < argc; j++) {
			if (strcmp(argv[i], argv[j]) == 0) {
				abortMission("An argument has been entered more than one time");//Avoid command duplicate
			}
		}
	}
	return;
}
	
void abortMission(char *s) {
	fprintf(stderr, "Erreur dans l'executable : %s\n",  s);
	exit(1); 	
}	


