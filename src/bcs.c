/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period  2 2014 Assignment #2 - Brazilian  Coffee Shop  system
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by the CTEACH team
****************************************************************************/

#include "bcs.h"
#include "bcs_options.h"
#include "bcs_utility.h"

int main(int argc, char* argv[]){

    BCSType menu;
    int result = EXIT_FAILURE;
    char menuFileName[MAX_STRING_MEDIUM] = {0};
    char subMenuFileName[MAX_STRING_MEDIUM] = {0};

    /* Stupid Eclipse won't show the console until after it has stopped.
    * See http://stackoverflow.com/questions/13035075/printf-not-printing-on-console */
    setvbuf (stdout, NULL, _IONBF, 0);

    if (argc != MIN_ARGS){
       fprintf(stderr, MESSAGE_ERROR_INVALID_ARGS);

    } else {

        strcpy(menuFileName, *argv[1]);
        strcpy(subMenuFileName, *argv[2]);

        if (!fileExists(menuFileName)){
           fprintf(stderr, MESSAGE_ERROR_FILE_NOT_EXIST, menuFileName);

        } else if (!fileExists(subMenuFileName)){
           fprintf(stderr, MESSAGE_ERROR_FILE_NOT_EXIST, subMenuFileName);

        } else {


            result = EXIT_SUCCESS;

        }

    }

    return result;

}
