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
    /*int i = 0;*/
    char menuString[MAX_STRING_LARGE] = {0};
    bool abort = false;
    int option = 0;
    int result = EXIT_FAILURE;
    char *menuFileName = null;
    char *subMenuFileName = null;
    menuoption_t *ptr = null;
    menuoption_t *options = getMenuOptions();

    /* Stupid Eclipse won't show the console until after it has stopped.
    * See http://stackoverflow.com/questions/13035075/printf-not-printing-on-console */
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    systemInit(&menu);

    if (argc != MIN_ARGS){
       fprintf(stderr, MESSAGE_ERROR_INVALID_ARGS);

    } else {

        menuFileName = argv[1];
        subMenuFileName = argv[2];

        if (!fileExists(menuFileName)){
           fprintf(stderr, MESSAGE_ERROR_FILE_NOT_EXIST, menuFileName);

        } else if (!fileExists(subMenuFileName)){
           fprintf(stderr, MESSAGE_ERROR_FILE_NOT_EXIST, subMenuFileName);

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

                    /* Lookup the option by it's index */
                    ptr = getMenuOptionByIndex(option);

                    switch (option){
                    case 0:
                        ptr->method(&menu, HOT);
                        break;
                    case 1:
                        ptr->method(&menu, COLD);
                        break;
                    case MAX_MENU_OPTION - 1:
                        ptr->method(&menu, menuFileName, subMenuFileName);
                        abort = true;
                        break;
                    case MAX_MENU_OPTION:
                        abort = true;
                        break;
                    default:
                        ptr->method(&menu);
                        break;

                    }

                    /* Call the function pointer. */
                    /*ptr->method(strcmp(ptr->str, MENU_TITLE_EXIT) == 0 ? (int*)&abort : optionStats);

                    switch (option){

                    case 0:
                        ptr->method(menu, HOT);
                    break;
                    case 1:
                        ptr->method(menu, COLD);
                        break;
                    case MAX_MENU_OPTION - 1:
                        ptr->method(menu, menuFileName, subMenuFileName);
                        abort = true;
                        break;
                    case MAX_MENU_OPTION:
                        abort = true;
                        break;
                    default:
                        ptr->method(menu);

                    }

                    displaySummary(BCSType* menu, char drinkType)
void categoryReport(BCSType* menu);
void addCategory(BCSType* menu);
void deleteCategory(BCSType* menu);
void addItem(BCSType* menu);
void deleteItem(BCSType* menu);
void saveData(BCSType* menu, char* menuFile, char* submenuFile);

                    */

                }

            }

            systemFree(&menu);

            result = EXIT_SUCCESS;

        }


    }

    return result;

}

/* This function is used to break the main menu option loop by modifying
 * the abort parameter.
 *
 * Requirement  8 - Exit
 * */
void exitApplication(int *abort){

    /* Set the abort flag to true. This in turn will break the main menu loop. */
    *abort = true;

}

/* This function creates the menu statically, and keeps returning same menu */
menuoption_t *getMenuOptions(){

    /*#define MENU_TITLE_SUMMARY_HOT "Hot Drinks Summary"
#define MENU_TITLE_SUMMARY_COLD "Cold Drinks Summary"
#define MENU_TITLE_REPORT "Details Menu Report"
#define MENU_TITLE_ADD_CATEGORY "Add Menu Category"
#define MENU_TITLE_DELETE_CATEGORY "Delete Menu Category"
#define MENU_TITLE_ADD_ITEM "Add Menu Item"
#define MENU_TITLE_DELETE_ITEM "Delete Menu Item"
#define MENU_TITLE_EXIT "Save & Exit"
#define MENU_TITLE_ABORT "Abort"

displaySummary(BCSType* menu, char drinkType)
void categoryReport(BCSType* menu);
void addCategory(BCSType* menu);
void deleteCategory(BCSType* menu);
void addItem(BCSType* menu);
void deleteItem(BCSType* menu);
void saveData(BCSType* menu, char* menuFile, char* submenuFile);

*/

    static menuoption_t options[] = {
        {
            MIN_MENU_OPTION,
            MENU_TITLE_SUMMARY_HOT,
            &displaySummary
        },
        {
            MIN_MENU_OPTION + 1,
            MENU_TITLE_SUMMARY_COLD,
            &displaySummary
        },
        {
            MIN_MENU_OPTION + 2,
            MENU_TITLE_REPORT,
            &categoryReport
        },
        {
            MIN_MENU_OPTION + 3,
            MENU_TITLE_ADD_CATEGORY,
            &addCategory
        },
        {
            MIN_MENU_OPTION + 4,
            MENU_TITLE_DELETE_CATEGORY,
            &deleteCategory
        },
        {
            MIN_MENU_OPTION + 5,
            MENU_TITLE_ADD_ITEM,
            &addItem
        },
        {
            MIN_MENU_OPTION + 6,
            MENU_TITLE_DELETE_ITEM,
            &deleteItem
        },
        {
            MIN_MENU_OPTION + 7,
            MENU_TITLE_EXIT,
            &saveData
        },
        {
            MIN_MENU_OPTION + 8,
            MENU_TITLE_ABORT,
            &exitApplication
        },
        {MAX_MENU_OPTION + 1, null, null}
    };


    return options;

}
