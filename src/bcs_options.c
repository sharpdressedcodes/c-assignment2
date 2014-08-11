/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period  2  2014 Assignment #2 - Brazilian  Coffee Shop system
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by the CTEACH team
****************************************************************************/

#include "bcs.h"
#include "bcs_options.h"
#include "bcs_utility.h"

/****************************************************************************
* Menu option #1: Display Summary
* Allows the user to display a summary of all hot or cold drink categories
* and items.
****************************************************************************/
void displaySummary(BCSType* menu, char drinkType)
{

    CategoryTypePtr cp = menu->headCategory;
    ItemTypePtr ip = null;
    char title[MAX_STRING_MEDIUM] = {0};
    char *titleDashes = null;
    char *subtitleDashes = null;

    sprintf(title, FORMAT_DASHED_HEADER_TITLE, drinkType == eDrinkCold ? TITLE_COLD : TITLE_HOT);
    titleDashes = createDashesFromString(title);

    if (!titleDashes)
        return;

    printf("%s\n", titleDashes);
    freeString(&titleDashes);

    while (cp){

        if (cp->drinkType == drinkType){

            subtitleDashes = createDashedHeader(cp);

            if (subtitleDashes){

                printf("%s\n", subtitleDashes);
                freeString(&subtitleDashes);

                ip = cp->headItem;

                while (ip){

                    int i = 0;
                    char item[MAX_STRING_MEDIUM] = {0};

                    sprintf(item, FORMAT_ITEM, ip->itemID, ip->itemName);

                    for (i = 0; i < NUM_PRICES; i++){
                        char price[MAX_STRING_SMALL] = {0};
                        sprintf(price, FORMAT_PRICE, ip->prices[i].dollars, ip->prices[i].cents);
                        strcat(item, price);
                    }

                    printf("%s\n", item);

                    ip = ip->nextItem;

                }

                printf("\n");

            }
        }

        cp = cp->nextCategory;

    }

}


/****************************************************************************
* Menu option #2: Category Report
* Allows the user to make a new report file for a chosen category.
****************************************************************************/
void categoryReport(BCSType* menu)
{
}


/****************************************************************************
* Menu option #3: Add Category
* Allows the user to add a new category record to the linked list.
****************************************************************************/
void addCategory(BCSType* menu)
{
}

/****************************************************************************
* Menu option #4: Delete Category
* Deletes a category and all corresponding items.
****************************************************************************/
void deleteCategory(BCSType* menu)
{

    char *title = createDashesFromString(MENU_TITLE_DELETE_CATEGORY);
    char catId[ID_LEN + EXTRA_SPACES] = {0};
    bool result = false;
    CategoryTypePtr cp = null;

    printf("%s\n%s", title, MESSAGE_DELETE_CATEGORY);

    while (!result){

        memset(catId, 0, sizeof(char) * ID_LEN + EXTRA_SPACES);
        result = getStringFromStdIn(catId, ID_LEN, INPUT_CATEGORY_ID, MIN_STRING_NONE, true);

        if (strlen(catId) == 0)
            break;

        cp = getCategoryFromId(menu, catId);

        if (!cp){

            fprintf(stderr, MESSAGE_ERROR_CATEGORY_NOT_EXIST, catId);
            result = false;

        } else {

            CategoryTypePtr lastCategory = menu->headCategory;

            if (strcmp(lastCategory->categoryID, cp->categoryID) == 0){

                menu->headCategory = lastCategory->nextCategory;
                freeCategory(lastCategory);

            } else {

                CategoryTypePtr currentCategory = lastCategory->nextCategory;

                while (currentCategory){

                    if (strcmp(currentCategory->categoryID, cp->categoryID) == 0){
                        lastCategory->nextCategory = currentCategory->nextCategory;
                        freeCategory(currentCategory);
                        break;
                    }

                    lastCategory = currentCategory;
                    currentCategory = currentCategory->nextCategory;

                }

            }

            menu->numCategories--;

        }


    }

    freeString(&title);

}


/****************************************************************************
* Menu option #5: Add Item
* Allows the user to add a new item to an existing category. An error 
* message is given if the category doesn't exist.
****************************************************************************/
void addItem(BCSType* menu)
{
}


/****************************************************************************
* Menu option #6: Delete Item
* Deletes a single item from a particular category.
****************************************************************************/
void deleteItem(BCSType* menu)
{
}


/****************************************************************************
* Menu option #7: Save and Exit
* Saves all system data back to the original files. This function does not
* terminate the program - this is left to the main() function instead.
****************************************************************************/
void saveData(BCSType* menu, char* menuFile, char* submenuFile)
{
}
