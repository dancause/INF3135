
/* Open the countries.json file and link it with a buffer that will be used for the entire process of the program.*/
json_t * openFile();

/* The main function that verifies every arguments in the commmand line then redirects the program to the proper function.*/
void verifyCommands(int argc, char ** argv);

/* Called with the command --country, verifies all the datas then prints them. It also returns a * on the proper country object.*/
json_t * comCountry(char **argv, int i);

/* Print the country in the "cca3" object.*/
void printCountry(json_t * objCca3,json_t * objNameCommon);

/* Gets and prints the proper languages.*/
void comLanguages(json_t * objPays);

/* Gets and prints the proper capital.*/
void comCapital(json_t * objPays);

/* Gets and prints the proper borders.*/
void comBorders(json_t * objPays);

/* Prints all the infos on all crountries in a region depending on witch of them has been tipped in the command line */
void comRegion(int argc, char **argv, int i);

/* Filters all the commands tipped by the user for "--region" and prints the proper infos on every country */
void printRegion(int argc,char ** argv, json_t * objPays);

/* Finds out if 2 or 3 countries have a common language and if they do, prints the languages */
int commonLanguages(int argc,char ** argv,int i);

/*Finds out if 2 or 3 countries have common borders, prints yes or no */
int commonBorders(int argc,char ** argv,int i);



/* Validates the country accronym "cca3" to make sure it contains 3 letters and that it exists, then 
	transforms the 3 letters in Caps */
char * verifyCca3(char ** argv, int i);

/* Returns a * of the proper country object based on its accronym "cca3" */
json_t * cca3ToPointer(char * AbbCountry);

/*Validates the region name to make sure it's supported */
void validateRegion(char* region);

/*Verifies if a command has been entered more than one time */
void verifyDuplicate (char** argv, int argc);

/*Verifies that the first argument is either --country, --region, --same-borders or --same-language and that the arguments are entered correctly*/
void verifyArguments(char** argv, int argc);

/* Used for all the insight test fails, prints the proper message on sterr*/
void abortMission(char *s);
