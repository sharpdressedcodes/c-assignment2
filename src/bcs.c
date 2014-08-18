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
    char menuString[MAX_STRING_LARGE] = {0};
    bool abort = false;
    int option = 0;
    int result = EXIT_FAILURE;
    char *menuFileName = null;
    char *subMenuFileName = null;
    menuoption_t *ptr = null;
    menuoption_t *options = getMenuOptions();

    fixConsole(stdout);
    fixConsole(stderr);

    systemInit(&menu);

    if (argc != MIN_ARGS){
       fprintf(stderr, MESSAGE_ERROR_INVALID_ARGS);

    } else {

        menuFileName = argv[EXPECTED_CATEGORY_ARG_INDEX];
        subMenuFileName = argv[EXPECTED_ITEM_ARG_INDEX];

        if (!fileExists(menuFileName)){
           fprintf(stderr, MESSAGE_ERROR_FILE_NOT_EXIST, menuFileName);

        } else if (!fileExists(subMenuFileName)){
           fprintf(stderr, MESSAGE_ERROR_FILE_NOT_EXIST, subMenuFileName);

        } else if (!checkArgumentOrder(argv)){
            /* do nothing, the error messages are taken care of. */

        } else if (!loadData(&menu, menuFileName, subMenuFileName)){
            fprintf(stderr, MESSAGE_ERROR_LOAD_DATA_FAIL, menuFileName, subMenuFileName);

        } else {

            /*************************************/
            /* uncomment below to test memory deallocation */
            /*systemFree(&menu);
            result = EXIT_SUCCESS;
            return result;*/
            /*************************************/

            /* Append title. */
            strcpy(menuString, "\nMain Menu:\n");

            /* Iterate through menu option structures and append
             * index and title to menu string. */
            for (ptr = options; ptr->index != MAX_MENU_OPTION + 1; ++ptr){

                /* Create a temp variable. This will be formatted
                 * and passed to the menu. */
                char s[MAX_STRING_MEDIUM] = {0};

                /* Format the string. */
                sprintf(s, "(%d) %s\n", ptr->index, ptr->str);

                /* Now append the formatted string to the menu. */
                strcat(menuString, s);
            }

            /* Append the request. */
            strcat(menuString, "\nSelect your option: ");

            /* Main menu loop. Abort will be modified when user selects "Exit". */
            while (!abort) {

                /* Get the menu option from the user.
                 * NUM_OPTION_STATS + 1 to count the exit option. */
                if (getIntegerFromStdIn(&option, MIN_STRING, menuString,
                        MIN_MENU_OPTION, MAX_MENU_OPTION, true, false)) {

                    switch (option){
                        case eMethodDisplayHot:
                            displaySummary(&menu, eDrinkHot);
                            break;
                        case eMethodDisplayCold:
                            displaySummary(&menu, eDrinkCold);
                            break;
                        case eMethodReport:
                            categoryReport(&menu);
                            break;
                        case eMethodAddCategory:
                            addCategory(&menu);
                            break;
                        case eMethodDeleteCategory:
                            deleteCategory(&menu);
                            break;
                        case eMethodAddItem:
                            addItem(&menu);
                            break;
                        case eMethodDeleteItem:
                            deleteItem(&menu);
                            break;
                        case eMethodSaveData:
                            saveData(&menu, menuFileName, subMenuFileName);
                            abort = true;
                            break;
                        case eMethodExitApp:
                            abort = true;
                            break;
                    }

                }

            }

            systemFree(&menu);

            result = EXIT_SUCCESS;

        }


    }

    return result;

}
