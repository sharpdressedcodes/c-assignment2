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

    bool result = false;
    char catName[MAX_NAME_LEN + EXTRA_SPACE] = {0};
    char catDesc[MAX_DESC_LEN + EXTRA_SPACE] = {0};
    char catType[EXTRA_SPACES] = {0};
    const char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    char message[MAX_STRING_LARGE] = {0};
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

    sprintf(message, INPUT_CATEGORY_NAME, MIN_NAME_LEN, MAX_NAME_LEN);
    printf("%s\n%s%s\n", title, INPUT_NEW_CATEGORY_ID, tokens[eCategoryId]);
    freeString(&title);

    while (!result){
        memset(catName, 0, sizeof(char) * (MAX_NAME_LEN + EXTRA_SPACE));
        result = getStringFromStdIn(catName, MAX_NAME_LEN, message, MIN_NAME_LEN, true, true);
    }

    if (strlen(catName)){

        tokens[eCategoryName] = copyString(catName);
        result = false;

        while (!result){

            catType[0] = 0;
            result = getStringFromStdIn(catType, DRINK_LEN, INPUT_CATEGORY_TYPE, DRINK_LEN, true, true);

            if (strlen(catType)){

                freeString(&tokens[eCategoryType]);
                tokens[eCategoryType] = copyString(catType);
                result = validateCategoryToken(tokens, eCategoryType, true);

            }

        }

        if (strlen(catType)){

            memset(message, 0, sizeof(char) * MAX_STRING_LARGE);
            sprintf(message, INPUT_DESCRIPTION, MIN_DESC_LEN, MAX_DESC_LEN);
            result = false;

            while (!result){
                memset(catDesc, 0, sizeof(char) * (MAX_DESC_LEN + EXTRA_SPACE));
                result = getStringFromStdIn(catDesc, MAX_DESC_LEN, message, MIN_DESC_LEN, true, true);
            }

            if (strlen(catDesc)){

                tokens[eCategoryDescription] = copyString(catDesc);

                line = implode(delim, tokens, eCategoryMax);

                if (line){
                    populateMenu(menu, line, false, DEFAULT_SORT_ORDER);
                    freeString(&line);
                }

            }

        }

    }

    freeDynamicStringArray(&tokens, eCategoryMax);

}

/****************************************************************************
* Menu option #4: Delete Category
* Deletes a category and all corresponding items.
****************************************************************************/
void deleteCategory(BCSType* menu)
{

    char *title = createDashesFromString(MENU_TITLE_DELETE_CATEGORY);
    char catId[ID_LEN + EXTRA_SPACES] = {0};
    char message[MAX_STRING_SMALL] = {0};
    bool result = false;
    CategoryTypePtr cp = null;

    printf("%s\n%s", title, MESSAGE_DELETE_CATEGORY);
    freeString(&title);

    sprintf(message, INPUT_CATEGORY_ID, ID_LEN);

    while (!result){

        memset(catId, 0, sizeof(char) * ID_LEN + EXTRA_SPACES);
        result = getStringFromStdIn(catId, ID_LEN, message, ID_LEN, true, true);

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
                printf(MESSAGE_DELETED_CATEGORY, lastCategory->categoryID, lastCategory->categoryName);
                freeCategory(lastCategory);

            } else {

                CategoryTypePtr currentCategory = lastCategory->nextCategory;

                while (currentCategory){

                    if (strcmp(currentCategory->categoryID, cp->categoryID) == 0){
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

    }

}

/****************************************************************************
* Menu option #5: Add Item
* Allows the user to add a new item to an existing category. An error 
* message is given if the category doesn't exist.
****************************************************************************/
void addItem(BCSType* menu)
{

    bool result = false;
    bool priceResult = false;
    char catId[ID_LEN + EXTRA_SPACE] = {0};
    char itemName[MAX_NAME_LEN + EXTRA_SPACE] = {0};
    char itemDesc[MAX_DESC_LEN + EXTRA_SPACE] = {0};
    char itemPrices[NUM_PRICES][PRICE_LEN + EXTRA_SPACE] = {{0}};
    const char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    char message[MAX_STRING_LARGE] = {0};
    char *line = null;
    char *title = null;
    char **tokens = calloc(eMenuMax, sizeof(char*));
    int i = 0;

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

    sprintf(message, INPUT_CATEGORY_ID, ID_LEN);

    title = createDashesFromString(MENU_TITLE_ADD_ITEM);
    printf("%s\n", title);
    freeString(&title);

    do {

        memset(catId, 0, sizeof(char) * (ID_LEN + EXTRA_SPACE));
        result = getStringFromStdIn(catId, ID_LEN, message, ID_LEN, true, true);

        if (strlen(catId) && !getCategoryFromId(menu, catId)){
            fprintf(stderr, MESSAGE_ERROR_CATEGORY_NOT_EXIST, catId);
            result = false;
        }

    } while (!result);

    if (strlen(catId)){

        tokens[eMenuCategoryId] = copyString(catId);
        memset(message, 0, sizeof(char) * MAX_STRING_LARGE);
        sprintf(message, INPUT_ITEM_NAME, MIN_NAME_LEN, MAX_NAME_LEN);

        printf("%s%s\n", INPUT_NEW_ITEM_ID, tokens[eMenuId]);

        do {
            memset(itemName, 0, sizeof(char) * (MAX_NAME_LEN + EXTRA_SPACE));
            result = getStringFromStdIn(itemName, MAX_NAME_LEN, message, MIN_NAME_LEN, true, true);
        } while (!result);

        if (strlen(itemName)){

            tokens[eMenuType] = copyString(itemName);

            for (i = 0; i < NUM_PRICES; i++){

                char temp[MAX_STRING_MEDIUM] = {0};
                memset(message, 0, sizeof(char) * MAX_STRING_LARGE);

                switch (eMenuPrice1 + i){
                    case eMenuPrice1:
                        strcpy(temp, INPUT_ITEM_PRICE_SMALL);
                        break;
                    case eMenuPrice2:
                        strcpy(temp, INPUT_ITEM_PRICE_MEDIUM);
                        break;
                    case eMenuPrice3:
                        strcpy(temp, INPUT_ITEM_PRICE_LARGE);
                        break;
                }

                sprintf(message, temp, CURRENCY_CHAR, MIN_ITEM_PRICE, CURRENCY_CHAR, MAX_ITEM_PRICE);

                do {

                    memset(itemPrices[i], 0, sizeof(char) * (PRICE_LEN + EXTRA_SPACE));
                    result = getStringFromStdIn(itemPrices[i], PRICE_LEN, message, PRICE_LEN, true, true);

                    if (strlen(itemPrices[i]) && !validateItemPrice(itemPrices[i], true))
                        result = false;

                } while (!result);

                if (strlen(itemPrices[i]) == 0){
                    priceResult = false;
                    break;
                }

                tokens[eMenuPrice1 + i] = copyString(itemPrices[i]);
                priceResult = true;

            }

            if (priceResult){

                memset(message, 0, sizeof(char) * MAX_STRING_LARGE);
                sprintf(message, INPUT_DESCRIPTION, MIN_DESC_LEN, MAX_DESC_LEN);

                do {
                    memset(itemDesc, 0, sizeof(char) * (MAX_DESC_LEN + EXTRA_SPACE));
                    result = getStringFromStdIn(itemDesc, MAX_DESC_LEN, message, MIN_DESC_LEN, true, true);
                } while (!result);

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

    freeDynamicStringArray(&tokens, eMenuMax);

}

/****************************************************************************
* Menu option #6: Delete Item
* Deletes a single item from a particular category.
****************************************************************************/
void deleteItem(BCSType* menu)
{

    char *title = createDashesFromString(MENU_TITLE_DELETE_ITEM);
    char catId[ID_LEN + EXTRA_SPACES] = {0};
    char itemId[ID_LEN + EXTRA_SPACES] = {0};
    char message[MAX_STRING_SMALL] = {0};
    bool result = false;
    CategoryTypePtr category = null;
    ItemTypePtr item = null;

    printf("%s\n", title);
    freeString(&title);

    sprintf(message, INPUT_CATEGORY_ID, ID_LEN);

    while (!result){

        memset(catId, 0, sizeof(char) * ID_LEN + EXTRA_SPACES);
        result = getStringFromStdIn(catId, ID_LEN, message, MIN_STRING_NONE, true, true);

        if (strlen(catId) == 0)
            break;

        category = getCategoryFromId(menu, catId);

        if (!category){

            fprintf(stderr, MESSAGE_ERROR_CATEGORY_NOT_EXIST, catId);
            result = false;

        }

    }

    if (category){

        memset(message, 0, sizeof(char) * MAX_STRING_SMALL);
        sprintf(message, INPUT_ITEM_ID, ID_LEN);
        result = false;

        while (!result){

            memset(itemId, 0, sizeof(char) * ID_LEN + EXTRA_SPACES);
            result = getStringFromStdIn(itemId, ID_LEN, message, MIN_STRING_NONE, true, true);

            if (strlen(itemId) == 0)
                break;

            item = getItemFromId(menu, itemId);

            if (!item){
                fprintf(stderr, MESSAGE_ERROR_MENU_NOT_EXIST, itemId);
                result = false;
            }

        }

        if (item){

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
