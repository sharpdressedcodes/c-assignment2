/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period  2  2014 Assignment #2 - Brazilian Coffee Shop system
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by the CTEACH team
****************************************************************************/

#include "bcs.h"
#include "bcs_options.h"
#include "bcs_utility.h"

/****************************************************************************
* Function readRestOfLine() is used for buffer clearing. Source: 
* https://inside.cs.rmit.edu.au/~sdb/teaching/C-Prog/CourseDocuments/
* FrequentlyAskedQuestions/
****************************************************************************/
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}


/****************************************************************************
* Initialises the system to a safe empty state.
****************************************************************************/
void systemInit(BCSType* menu)
{
}


/****************************************************************************
* Loads all data into the system.
****************************************************************************/
int loadData(BCSType* menu, char* menuFile, char* submenuFile)
{
}


/****************************************************************************
* Deallocates memory used in the program.
****************************************************************************/
void systemFree(BCSType* menu)
{
}

/****************************************************************************
* Test for file existence.
****************************************************************************/
bool fileExists(const char *fileName){

    bool result = false;
    FILE *fp = null;

    fp = fopen(fileName, "r");

    if (fp){
        fclose(fp);
        result = true;
    }

    return result;

}
