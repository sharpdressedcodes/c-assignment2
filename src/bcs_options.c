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
/*
 * valgrind -v --leak-check=full ./assignment2 ../menu.dat ../submenu.dat
 * */

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

    char *title = createDashesFromString(MENU_TITLE_REPORT);
    char *catId = null;
    char fileName[MAX_STRING_SMALL] = {0};

    printf("%s\n", title);
    freeString(&title);

    catId = getCategoryIdFromStdIn(menu);

    if (strlen(catId)){

        sprintf(fileName, FORMAT_REPORT_NAME, catId);

        if (createAndSaveReport(getCategoryFromId(menu, catId), fileName))
            printf(MESSAGE_CREATED_REPORT, catId);

    }

    freeString(&catId);

}

/****************************************************************************
* Menu option #3: Add Category
* Allows the user to add a new category record to the linked list.
****************************************************************************/
void addCategory(BCSType* menu)
{

    char *catName = null;
    char *catType = null;
    char *catDesc = null;
    const char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    char *line = null;
    char *title = createDashesFromString(MENU_TITLE_ADD_CATEGORY);
    char **tokens = calloc(eCategoryMax, sizeof(char*));
    int i = 0;

    if (!tokens){
        fprintf(stderr, MESSAGE_ERROR_NO_MEMORY);
        freeString(&title);
        return;
    }

    for (i = 0; i < eCategoryMax; i++)
        tokens[i] = null;

    tokens[eCategoryId] = generateCategoryId(menu);

    if (!tokens[eCategoryId]){
        fprintf(stderr, MESSAGE_ERROR_NO_MEMORY);
        freeString(&title);
        return;
    }

    printf("%s\n%s%s\n", title, INPUT_NEW_CATEGORY_ID, tokens[eCategoryId]);
    freeString(&title);

    catName = getCategoryNameFromStdIn(menu);

    if (strlen(catName)){

        catType = getCategoryTypeFromStdIn(menu);

        if (strlen(catType)){

            catDesc = getCategoryDescFromStdIn(menu);

            if (strlen(catDesc)){

                tokens[eCategoryName] = copyString(catName);
                tokens[eCategoryType] = copyString(catType);
                tokens[eCategoryDescription] = copyString(catDesc);

                line = implode(delim, tokens, eCategoryMax);

                if (line){
                    populateMenu(menu, line, false, DEFAULT_SORT_ORDER);
                    freeString(&line);
                }

            }

        }

    }

    freeStrings(3, &catName, &catType, &catDesc);
    freeDynamicStringArray(&tokens, eCategoryMax);

}

/****************************************************************************
* Menu option #4: Delete Category
* Deletes a category and all corresponding items.
****************************************************************************/
void deleteCategory(BCSType* menu)
{

    char *title = createDashesFromString(MENU_TITLE_DELETE_CATEGORY);
    char *catId = null;

    printf("%s\n%s", title, MESSAGE_DELETE_CATEGORY);
    freeString(&title);

    catId = getCategoryIdFromStdIn(menu);

    if (strlen(catId)){

        CategoryTypePtr lastCategory = menu->headCategory;

        if (strcmp(lastCategory->categoryID, catId) == 0){

            menu->headCategory = lastCategory->nextCategory;
            printf(MESSAGE_DELETED_CATEGORY, lastCategory->categoryID, lastCategory->categoryName);
            freeCategory(lastCategory);

        } else {

            CategoryTypePtr currentCategory = lastCategory->nextCategory;

            while (currentCategory){

                if (strcmp(currentCategory->categoryID, catId) == 0){
                    lastCategory->nextCategory = currentCategory->nextCategory;
                    printf(MESSAGE_DELETED_CATEGORY, currentCategory->categoryID, currentCategory->categoryName);
                    freeCategory(currentCategory);
                    break;
                }

                lastCategory = currentCategory;
                currentCategory = currentCategory->nextCategory;

            }

        }

        menu->numCategories--;

    }

    freeString(&catId);

}

/****************************************************************************
* Menu option #5: Add Item
* Allows the user to add a new item to an existing category. An error 
* message is given if the category doesn't exist.
****************************************************************************/
void addItem(BCSType* menu)
{

    int i = 0;
    bool priceResult = false;
    const char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    char **tokens = calloc(eMenuMax, sizeof(char*));
    char *line = null;
    char *title = null;
    char *catId = null;
    char *itemName = null;
    char *itemDesc = null;
    char *itemPrices[NUM_PRICES] = {null};

    if (!tokens){
        fprintf(stderr, MESSAGE_ERROR_NO_MEMORY);
        return;
    }

    for (i = 0; i < eMenuMax; i++)
        tokens[i] = null;

    tokens[eMenuId] = generateItemId(menu);

    if (!tokens[eMenuId]){
        fprintf(stderr, MESSAGE_ERROR_NO_MEMORY);
        return;
    }

    title = createDashesFromString(MENU_TITLE_ADD_ITEM);
    printf("%s\n", title);
    freeString(&title);

    catId = getCategoryIdFromStdIn(menu);

    if (strlen(catId)){

        tokens[eMenuCategoryId] = copyString(catId);
        printf("%s%s\n", INPUT_NEW_ITEM_ID, tokens[eMenuId]);

        itemName = getItemNameFromStdIn(menu);

        if (strlen(itemName)){

            tokens[eMenuType] = copyString(itemName);

            for (i = 0; i < NUM_PRICES; i++){
                itemPrices[i] = getItemPriceFromStdIn(menu, i);

                if (strlen(itemPrices[i]) == 0){
                    priceResult = false;
                    break;
                }

                tokens[eMenuPrice1 + i] = copyString(itemPrices[i]);
                priceResult = true;
            }

            if (priceResult){

                itemDesc = getItemDescFromStdIn(menu);

                if (strlen(itemDesc)){

                    tokens[eMenuDescription] = copyString(itemDesc);

                    line = implode(delim, tokens, eMenuMax);

                    if (line){
                        populateMenu(menu, line, true, DEFAULT_SORT_ORDER);
                        freeString(&line);
                    }

                }

            }

        }

    }

    freeStrings(3, &catId, &itemName, &itemDesc);
    freeStringArray(itemPrices, NUM_PRICES);
    freeDynamicStringArray(&tokens, eMenuMax);

}

/****************************************************************************
* Menu option #6: Delete Item
* Deletes a single item from a particular category.
****************************************************************************/
void deleteItem(BCSType* menu)
{

    char *title = createDashesFromString(MENU_TITLE_DELETE_ITEM);
    char *catId = null;
    char *itemId = null;
    CategoryTypePtr category = null;
    ItemTypePtr item = null;

    printf("%s\n", title);
    freeString(&title);

    catId = getCategoryIdFromStdIn(menu);

    if (strlen(catId)){

        itemId = getItemIdFromStdIn(menu);

        if (strlen(itemId)){

            category = getCategoryFromId(menu, catId);
            item = getItemFromId(menu, itemId);

            if (strcmp(category->headItem->itemID, itemId) == 0){

                category->headItem = item->nextItem;

            } else {

                ItemTypePtr prev = category->headItem;
                ItemTypePtr current = prev->nextItem;

                while (current){

                    if (strcmp(current->itemID, itemId) == 0){
                        prev->nextItem = item->nextItem;
                        break;
                    }

                    prev = current;
                    current = current->nextItem;
                }

            }

            printf(MESSAGE_DELETED_ITEM, item->itemID, item->itemName);
            category->numItems--;
            free(item);

        }

    }

    freeStrings(2, &catId, &itemId);

}

/****************************************************************************
* Menu option #7: Save and Exit
* Saves all system data back to the original files. This function does not
* terminate the program - this is left to the main() function instead.
****************************************************************************/
void saveData(BCSType* menu, char* menuFile, char* submenuFile)
{

    FILE *fpMenu = fopen(menuFile, "w");
    FILE *fpSubMenu = fopen(submenuFile, "w");
    CategoryTypePtr category = menu->headCategory;
    ItemTypePtr item = null;

    while (category){

        char *categoryString = categoryToString(category);
        fprintf(fpMenu, "%s\n", categoryString);
        freeString(&categoryString);

        item = category->headItem;

        while (item){

            char *itemString = itemToString(item, category);
            fprintf(fpSubMenu, "%s\n", itemString);
            freeString(&itemString);

            item = item->nextItem;
        }
        category = category->nextCategory;
    }

    fclose(fpMenu);
    fclose(fpSubMenu);

}
