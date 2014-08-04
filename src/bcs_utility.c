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

    return 0; /*gk*/
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

/* This function is used to underline a string in the console. */
char *createDashes(const char *str){

    const int len = strlen(str);
    const int max = (len << 1) + EXTRA_SPACES_DASH; /* including 2 \n's and \0*/
    char *dashes = null;

    /* Did memory allocation succeed? */
    if (allocateString(&dashes, max)){

        /* Append the string. */
        sprintf(dashes, "%s\n", str);

        /* Append the dashes. */
        memset(dashes + (sizeof(char) * strlen(dashes)), DASH_CHAR, len);
        strcat(dashes, "\n");

    }

    return dashes;

}

/* This function will get an integer value from the user.
 * Depending on the parameters set, it can also show an error message,
 * or totally ignore errors.
 *
 * This function is based on:
 * Source: Steven Burrows
 * URL: https://www.dlsweb.rmit.edu.au/set/Courses/Content/CSIT/oua/cpt220/c-function-examples/InputValidation/getInteger-advanced.c
 * */
bool getIntegerFromStdIn(int *result, const int length, const char *message,
        const int min, const int max, bool showError, bool allowEmpty){

    int i = 0;
    char errorMessage[MAX_STRING_MEDIUM] = {0};
    char *s = null;
    char *endPtr = null;
    bool passed = false;

    /* Try to allocate memory, exit if it fails. */
    if (!allocateString(&s, length + EXTRA_SPACES))
        return false;

    sprintf(errorMessage, "%s %d %s %d. %s",
        "You must enter a number between",
        min,
        "and",
        max,
        "Try again.\n"
    );

    /* Keep looping until the user enters the correct integer.
     * If allowEmpty is enabled, the user is allowed to break
     * the loop by entering nothing. */
    while (!passed) {

        /* Ask the user. */
        fputs(message, stdout);

        /* Grab the input. */
        fgets(s, length + EXTRA_SPACES, stdin);

        if (strlen(s) == 1 && s[0] == '\n' && allowEmpty){
            /* User entered nothing, in this case, set the result
             * to one below the minimum to signal this. (along with
             * the function returning true.) */
            *result = min - 1;

            /* Cleanup our mess. */
            freeString(&s);
            break;
        }

        /* The user entered something that is out of range.
         * Inform the user, and consume the rest of the string. */
        if (s[strlen(s) - 1] != '\n') {

            if (showError)
                fputs(errorMessage, stderr);

            readRestOfLine();

        } else {

            /* Terminate the string. */
            s[strlen(s) - 1] = '\0';

            /* Convert the string to a decimal based long. */
            i = (int) strtol(s, &endPtr, BASE10);

            /* Validate the number (if it is indeed a number). */
            if (strcmp(endPtr, "") != 0 || i < min || i > max) {

                /* Only inform the user if we are told to. */
                if (showError){

                    fputs(errorMessage, stderr);

                /* Fail silently. Signal the failure by returning false. */
                } else {

                    /* Set the result to one below the minimum. */
                    *result = min - 1;

                    /* Cleanup before returning the failure flag. */
                    freeString(&s);
                    return false;

                }

            /* The user entered a value that is within range. */
            } else {

                /* Set the result. */
                *result = i;

                /* Set the success flag. */
                passed = true;

                /* Cleanup. */
                freeString(&s);

            }

        }

    }

    /* Success flag. */
    return true;

}

/* This function will get a character array from the user.
 * Depending on the parameters set, it can also show an error message,
 * or totally ignore errors.
 *
 * This function is based on:
 * Source: Steven Burrows
 * URL: https://www.dlsweb.rmit.edu.au/set/Courses/Content/CSIT/oua/cpt220/c-function-examples/InputValidation/getString-advanced.c
 * */
bool getStringFromStdIn(char *result, int length, const char *message,
        int min, bool showError){

    char * s = null;
    char errorMessage[MAX_STRING_MEDIUM] = {0};
    bool passed = false;

    /* Try to allocate memory, exit if it fails. */
    if (!allocateString(&s, length + EXTRA_SPACES))
        return false;

    sprintf(errorMessage, "Invalid entry! Try again.\n");

    /* Keep looping until the user enters a string that is within specified
     * parameters. */
    while (!passed) {

        size_t len;

        /* Ask the user. */
        fputs(message, stdout);

        /* Grab the input. */
        fgets(s, length + EXTRA_SPACES, stdin);

        len = strlen(s);

        /* If the user entered a string that is too long,
         * just consume the rest of the string. */
        if (s[len - 1] != '\n')
            readRestOfLine();

        /* Did the user enter anything? Or did they enter a long string? */
        if (len < EXTRA_SPACES || s[len - 1] != '\n') {

            /* Are we allowed to not enter anything? Abort if so. */
            if (len < EXTRA_SPACES && min == MIN_STRING_NONE)
                passed = true;

            /* Inform the user that they screwed up. */
            else if (showError)
                fputs(errorMessage, stderr);

        /* The user entered a valid string. */
        } else {

            /* Terminate the string. */
            s[len - 1] = '\0';

            /* Copy the string to the result. */
            strcpy(result, s);

            /* Break the loop, and set the success flag. */
            passed = true;

        }

    }

    /* Cleanup. */
    freeString(&s);

    return passed;

}

/* This function is used for dynamic string allocation.
 * It will allocate the required memory, then set allocated bytes to null. */
bool allocateString(char **str, const int size){

    bool result = false;
    /* The required size. */
    const size_t newSize = sizeof(char) * size;
    /* The original size (if any). */
    const size_t oldSize = *str == null ? 0 : sizeof(char) * strlen(*str);

    /* Don't bother allocating 0 memory. */
    if (newSize > 0){

        /* Reallocate memory for the string. */
        *str = realloc(*str, newSize);

        /* Did we succeed? Inform the user if we failed. */
        if (*str == null){

            fputs(MESSAGE_ERROR_NO_MEMORY, stderr);

        /* Success. Set all new bytes to null and set the success flag. */
        } else {

            memset(*str + oldSize, 0, newSize - oldSize);
            result = true;

        }

    }

    return result;

}

/* This function is used to delete dynamic strings. */
void freeString(char **str){

    /* Test that we have a valid pointer. */
    if (*str != null){

        /* Free the memory, and set the pointer to null to be safe. */
        free(*str);
        *str = null;

    }

}

/* This function is used to delete an array of dynamic strings. */
void freeStringArray(char **arr, const int length){

    int i = 0;

    /* Loop until the end of the array has been reached. */
    while (i < length)
        /* Call the freeString() method which takes care of cleaning up.
         * Increment the index as well. */
        freeString(&arr[i++]);

}

/* This function is used as a helper function to delete an indefinite
 * number of dynamic strings. */
void freeStrings(const int length, ...){

    int i = 0;
    va_list ap;

    /* Initialise the argument list. */
    va_start(ap, length);

    /* Iterate through the arguments. */
    for (i = 0; i < length; i++)
        /* Call the freeString() method which takes care of cleaning up. */
        freeString(va_arg(ap, char**));

    /* Cleanup the argument list. */
    va_end(ap);

}

/* This function is used to lookup a menu option by it's index. */
menuoption_t *getMenuOptionByIndex(const int index){

    menuoption_t *ptr = getMenuOptions();

    /* Iterate through the menu structure array and look for the index. */
    for (; ptr->index != MAX_MENU_OPTION; ++ptr)
        if (ptr->index == index)
            break;

    /* Return the address of the structure. */
    return &(*ptr);

}

/* This function is used to lookup a menu option by it's title. */
menuoption_t *getMenuOptionByTitle(const char *title){

    menuoption_t *ptr = getMenuOptions();

    /* Iterate through the menu structure array and look for the title. */
    for (; ptr->index != MAX_MENU_OPTION; ++ptr)
        /* Perform case sensitive comparison. */
        if (strcmp(ptr->str, title) == 0)
            break;

    /* Return the address of the structure. */
    return &(*ptr);

}
