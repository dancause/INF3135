/*

*/

#include <stdio.h>
#include <string.h>
#include <jansson.h>
#include "country.h"
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;


/* The suite initialization function.
* Opens the temporary file used by the tests.
* Returns zero on success, non-zero otherwise.
*/
int init_suite1(void)
{
	if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
		return -1;
	}
	else {
		return 0;
	}
}

/* The suite cleanup function.
* Closes the temporary file used by the tests.
* Returns zero on success, non-zero otherwise.
*/
int clean_suite1(void)
{
	if (0 != fclose(temp_file)) {
		return -1;
	}
	else {
		temp_file = NULL;
		return 0;
	}
}


void testopenFile(void){
CU_ASSERT_PTR_NOT_NULL(openFile);
}

void testcommonLanguages(void){


char *tabTestA[10];
tabTestA[0] = (char *) malloc(sizeof("../bin/Programme"));
strcpy(tabTestA[0], "../bin/Programme");
tabTestA[1] = (char *) malloc(sizeof("--SAME-LANGUAGE"));
strcpy(tabTestA[1], "--SAME-LANGUAGE");
tabTestA[2] = (char *) malloc(sizeof("can"));
strcpy(tabTestA[2], "can");
tabTestA[3] = (char *) malloc(sizeof("usa"));
strcpy(tabTestA[3], "usa");
tabTestA[4] = (char *) malloc(sizeof("fra"));
strcpy(tabTestA[4], "fra");

char *tabTestB[10];
tabTestB[0] = (char *) malloc(sizeof("../bin/Programme"));
strcpy(tabTestB[0], "../bin/Programme");
tabTestB[1] = (char *) malloc(sizeof("--SAME-LANGUAGE"));
strcpy(tabTestB[1], "--SAME-LANGUAGE");
tabTestB[2] = (char *) malloc(sizeof("can"));
strcpy(tabTestB[2], "can");
tabTestB[3] = (char *) malloc(sizeof("usa"));
strcpy(tabTestB[3], "usa");
tabTestB[4] = (char *) malloc(sizeof("rus"));
strcpy(tabTestB[4], "rus");


CU_ASSERT(commonLanguages(5,tabTestA,1));
CU_ASSERT(commonLanguages(4,tabTestB,1));

}

void testverifyCca3(void){
char *tabTestB[10];
tabTestB[0] = (char *) malloc(sizeof("../bin/Programme"));
strcpy(tabTestB[0], "../bin/Programme");
tabTestB[1] = (char *) malloc(sizeof("--SAME-LANGUAGE"));
strcpy(tabTestB[1], "--SAME-LANGUAGE");
tabTestB[2] = (char *) malloc(sizeof("can"));
strcpy(tabTestB[2], "can");
tabTestB[3] = (char *) malloc(sizeof("usa"));
strcpy(tabTestB[3], "usa");
tabTestB[4] = (char *) malloc(sizeof("rus"));
strcpy(tabTestB[4], "rus");

CU_ASSERT(verifyCca3(tabTestB,2));
CU_ASSERT(verifyCca3(tabTestB,3));
CU_ASSERT(verifyCca3(tabTestB,4));
}

void testcommonBorders(void){
char *tabTestB[10];
tabTestB[0] = (char *) malloc(sizeof("../bin/Programme"));
strcpy(tabTestB[0], "../bin/Programme");
tabTestB[1] = (char *) malloc(sizeof("--SAME-LANGUAGE"));
strcpy(tabTestB[1], "--SAME-LANGUAGE");
tabTestB[2] = (char *) malloc(sizeof("can"));
strcpy(tabTestB[2], "can");
tabTestB[3] = (char *) malloc(sizeof("usa"));
strcpy(tabTestB[3], "mex");
tabTestB[4] = (char *) malloc(sizeof("rus"));
strcpy(tabTestB[4], "usa");

char *tabTestA[10];
tabTestA[0] = (char *) malloc(sizeof("../bin/Programme"));
strcpy(tabTestA[0], "../bin/Programme");
tabTestA[1] = (char *) malloc(sizeof("--SAME-LANGUAGE"));
strcpy(tabTestA[1], "--SAME-LANGUAGE");
tabTestA[2] = (char *) malloc(sizeof("can"));
strcpy(tabTestA[2], "can");
tabTestA[3] = (char *) malloc(sizeof("usa"));
strcpy(tabTestA[3], "usa");
tabTestA[4] = (char *) malloc(sizeof("fra"));
strcpy(tabTestA[4], "fra");

printf("test");
CU_ASSERT(commonBorders(5,tabTestB,0));
printf("test");
CU_ASSERT(commonBorders(4,tabTestA,0));
printf("test");
}

void testcca3ToPointer(void){
CU_ASSERT_PTR_NOT_NULL(cca3ToPointer("CAN"));
CU_ASSERT_PTR_NOT_NULL(cca3ToPointer("USA"));
}


/* The main() function for setting up and running the tests.
* Returns a CUE_SUCCESS on successful running, another
* CUnit error code on failure.
*/
int main()
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	/* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
	if (
		
		(NULL == CU_add_test(pSuite,"test ouverture fichier()",testopenFile))|	
		(NULL == CU_add_test(pSuite,"test commonLanguages()",testcommonLanguages))||
		(NULL == CU_add_test(pSuite,"test commonBorders()",testcommonBorders))||	
		(NULL == CU_add_test(pSuite,"test cca3ToPointer()",testcca3ToPointer))||	
		(NULL == CU_add_test(pSuite,"test tverifyCca3()",testverifyCca3))

		)

		
	{
	

		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
