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

   /* Stupid Eclipse won't show the console until after it has stopped.
    * See http://stackoverflow.com/questions/13035075/printf-not-printing-on-console */
   setvbuf (stdout, NULL, _IONBF, 0);

   if (!fileExists(FILE_MENU)){
       fprintf(stderr, MESSAGE_ERROR_FILE_NOT_EXIST, FILE_MENU);

   } else if (!fileExists(FILE_SUBMENU)){
       fprintf(stderr, MESSAGE_ERROR_FILE_NOT_EXIST, FILE_SUBMENU);

   } else if (argc != MIN_ARGS){
       fprintf(stderr, MESSAGE_ERROR_INVALID_ARGS);

   } else {


       result = EXIT_SUCCESS;
   }



   return result;

}
