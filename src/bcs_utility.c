/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period  2  2014 Assignment #2 - Brazilian Coffee Shop system
* Full Name        : Greg Kappatos
* Student Number   : s3460969
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

    menu->headCategory = null;
    menu->numCategories = 0;

    srand(time(null));

}

/****************************************************************************
* Loads all data into the system.
****************************************************************************/
int loadData(BCSType* menu, char* menuFile, char* submenuFile)
{

    int result = 0;

    result = (int)loadDataFromFile(menu, menuFile, false);

    if (result)
        result = (int)loadDataFromFile(menu, submenuFile, true);

    return result;

}

/****************************************************************************
* Deallocates memory used in the program.
****************************************************************************/
void systemFree(BCSType* menu)
{

    freeCategories(menu);
    systemInit(menu);

}


/****************************************************************************
 Custom Methods
****************************************************************************/

/* Copy all category information (excluding items) into a
 * delimited string.
 * */
char *categoryToString(CategoryTypePtr category){

    int len = 0;
    char *result = null;
    const char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    char drink[DRINK_LEN + EXTRA_SPACE] = {0};
    size_t delimSize = strlen(delim);

    drink[0] = category->drinkType;

    /* Calculate correct length. */
    len += strlen(category->categoryID) + delimSize;
    len += DRINK_LEN + delimSize;
    len += strlen(category->categoryName) + delimSize;
    len += strlen(category->categoryDescription) + EXTRA_SPACE;

    if (allocateString(&result, len)){
        strcpy(result, category->categoryID);
        strcat(result, delim);
        strcat(result, drink);
        strcat(result, delim);
        strcat(result, category->categoryName);
        strcat(result, delim);
        strcat(result, category->categoryDescription);
    }

    return result;

}

/* Copy all item information into a delimited string.
 * */
char *itemToString(ItemTypePtr item, CategoryTypePtr parent){

    int i = 0;
    int len = 0;
    char *result = null;
    const char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    size_t delimSize = strlen(delim);

    /* Calculate correct length. */
    len += strlen(item->itemID) + delimSize;
    len += strlen(parent->categoryID) + delimSize;
    len += strlen(item->itemName) + delimSize;
    len += (PRICE_LEN + delimSize) * NUM_PRICES;
    len += strlen(item->itemDescription) + EXTRA_SPACE;

    if (allocateString(&result, len)){

        strcpy(result, item->itemID);
        strcat(result, delim);
        strcat(result, parent->categoryID);
        strcat(result, delim);
        strcat(result, item->itemName);
        strcat(result, delim);

        /* Get all prices. */
        for (i = 0; i < NUM_PRICES; i++){

            char price[PRICE_LEN + EXTRA_SPACE] = {0};

            sprintf(
                price,
                "%d%c%02d",
                item->prices[i].dollars,
                PRICE_SEPARATOR_CHAR,
                item->prices[i].cents
            );
            strcat(result, price);
            strcat(result, delim);

        }

        strcat(result, item->itemDescription);

    }

    return result;

}

/* Generates a new random category id.
 * */
char *generateCategoryId(BCSType *menu){

    char *result = null;
    int random = 0;
    ItemTypePtr item = null;

    if (allocateString(&result, ID_LEN + EXTRA_SPACE)){

        do {

            /* Make sure this id is unique. */
            random = generateRandomNumber(RANDOM_ID_MIN, RANDOM_ID_MAX);
            memset(result, 0, sizeof(char) * (ID_LEN + EXTRA_SPACE));
            sprintf(result, "%c%04d", CATEGORY_PREFIX_CHAR, random);

            item = getItemFromId(menu, result);

        } while (item);

    }

    return result;

}

/* Generates a new random item id.
 * */
char *generateItemId(BCSType *menu){

    char *result = null;
    int random = 0;
    ItemTypePtr item = null;

    if (allocateString(&result, ID_LEN + EXTRA_SPACE)){

        do {

            /* Make sure this id is unique. */
            random = generateRandomNumber(RANDOM_ID_MIN, RANDOM_ID_MAX);
            memset(result, 0, sizeof(char) * (ID_LEN + EXTRA_SPACE));
            sprintf(result, "%c%04d", ITEM_PREFIX_CHAR, random);

            item = getItemFromId(menu, result);

        } while (item);

    }

    return result;

}

void freeCategories(BCSType* menu){

    CategoryTypePtr current = menu->headCategory;

    while (current){

        CategoryTypePtr prev = current;

        current = current->nextCategory;
        freeCategory(prev);

    }

}

/* Iterates through all categories, and free's associated memory.
 * */
void freeCategory(CategoryTypePtr category){

    ItemTypePtr current = category->headItem;

    while (current){

        /* Store the item in prev, so we can access it to free it. */
        ItemTypePtr prev = current;

        current = current->nextItem;
        free(prev);

    }

    free(category);

}

/* Creates a dashed header. Used for individual category headers.
 * */
char *createDashedHeader(CategoryTypePtr category){

    char bottom[MAX_STRING_LARGE] = {0};
    char top[MAX_STRING_LARGE] = {0};
    char top2[MAX_STRING_LARGE] = {0};
    char *top3 = null;
    char *result = null;
    int i = 0;
    int count = category->numItems;

    sprintf(top,
        FORMAT_DASHED_HEADER_TOP1,
        category->categoryID,
        category->categoryName,
        count
    );
    sprintf(top2, FORMAT_DASHED_HEADER_TOP2, top);
    top3 = createDashesFromString(top2);

    if (count){

        sprintf(bottom,
            FORMAT_DASHED_HEADER_BOTTOM,
            HEADER_TITLE_ID,
            HEADER_TITLE_NAME,
            HEADER_TITLE_SMALL,
            HEADER_TITLE_MEDIUM,
            HEADER_TITLE_LARGE
        );

        memset(bottom + strlen(bottom), DASH_CHAR, sizeof(char) * ID_LEN);
        bottom[strlen(bottom)] = SPACE_CHAR;

        memset(bottom + strlen(bottom), DASH_CHAR, sizeof(char) * MAX_NAME_LEN);
        bottom[strlen(bottom)] = SPACE_CHAR;

        for (i = 0; i < NUM_PRICES; i++){
            memset(bottom + strlen(bottom), DASH_CHAR, sizeof(char) * ID_LEN);
            bottom[strlen(bottom)] = SPACE_CHAR;
        }

    }

    if (allocateString(&result, strlen(top3) + strlen(bottom) + EXTRA_SPACE))
        sprintf(result, "%s%s", top3, bottom);

    freeString(&top3);

    return result;

}




/* Add a category to the main data structure, in the correct sorted order.
 * */
void addCategoryToMenu(BCSType *menu, CategoryTypePtr category,
        SortOrder order){

    CategoryTypePtr currentCategory = null;
    static CategoryTypePtr lastCategory = null;

    if (menu->headCategory == null){

        menu->headCategory = category;
        lastCategory = menu->headCategory;

    } else {

        switch (order){
            case eSortOrderAsIs:

                lastCategory->nextCategory = category;
                lastCategory = lastCategory->nextCategory;

                break;

            case eSortOrderAscending:

                currentCategory = menu->headCategory;

                /* string2 is less than string1 */
                if (strcasecmp(currentCategory->categoryName,
                        category->categoryName) > 0){

                    category->nextCategory = currentCategory;
                    menu->headCategory = category;

                } else {

                    /* leave first item as is, search for item that is higher,
                     *  and insert in the chain at that point*/

                    lastCategory = currentCategory;
                    currentCategory = currentCategory->nextCategory;

                    do {

                        if (currentCategory == null){
                            lastCategory->nextCategory = category;
                            currentCategory = category;
                            break;
                        }

                        else if (strcasecmp(currentCategory->categoryName,
                                category->categoryName) > 0){
                            category->nextCategory = currentCategory;
                            lastCategory->nextCategory = category;
                            break;
                        }

                        lastCategory = currentCategory;
                        currentCategory = currentCategory->nextCategory;

                    } while (currentCategory != null);

                    if (currentCategory == null)
                        lastCategory->nextCategory = category;

                }

                break;

            case eSortOrderDescending:

                currentCategory = menu->headCategory;

                /* string1 is less than string2 */
                if (strcasecmp(currentCategory->categoryName,
                        category->categoryName) < 0){

                    category->nextCategory = currentCategory;
                    menu->headCategory = category;

                } else {

                    /* leave first item as is, search for item that is lower,
                     *  and insert in the chain at that point*/

                    lastCategory = currentCategory;
                    currentCategory = currentCategory->nextCategory;

                    do {

                        if (currentCategory == null){
                            lastCategory->nextCategory = category;
                            currentCategory = category;
                            break;
                        }

                        else if (strcasecmp(currentCategory->categoryName,
                                category->categoryName) < 0){
                            category->nextCategory = currentCategory;
                            lastCategory->nextCategory = category;
                            break;
                        }

                        lastCategory = currentCategory;
                        currentCategory = currentCategory->nextCategory;

                    } while (currentCategory != null);

                    if (currentCategory == null)
                        lastCategory->nextCategory = category;

                }

                break;
        }

    }

    menu->numCategories++;

}

/* Add an item to the main data structure, in the correct sorted order.
 * */
void addItemToMenu(BCSType *menu, CategoryTypePtr category, ItemTypePtr item,
        SortOrder order){

    ItemTypePtr currentItem = null;

    if (category->headItem == null){

        category->headItem = item;

    } else {

        switch (order){
            case eSortOrderAsIs:

                currentItem = category->headItem;

                do {

                    if (currentItem->nextItem == null){
                        currentItem->nextItem = item;
                        break;
                    }

                    currentItem = currentItem->nextItem;

                } while (currentItem != null);

                break;

            case eSortOrderAscending:

                currentItem = category->headItem;

                /* string2 is less than string1 */
                if (strcasecmp(currentItem->itemName, item->itemName) > 0){

                    item->nextItem = currentItem;
                    category->headItem = item;

                } else {

                    /* leave first item as is, search for item that is higher,
                     *  and insert in the chain at that point*/

                    ItemTypePtr lastItem = currentItem;
                    currentItem = currentItem->nextItem;

                    do {

                        if (currentItem == null){
                            lastItem->nextItem = item;
                            break;
                        }

                        else if (strcasecmp(currentItem->itemName,
                                item->itemName) > 0){
                            item->nextItem = currentItem;
                            lastItem->nextItem = item;
                            break;
                        }

                        lastItem = currentItem;
                        currentItem = currentItem->nextItem;

                    } while (currentItem != null);

                    if (currentItem == null)
                        lastItem->nextItem = item;

                }

                break;

            case eSortOrderDescending:

                currentItem = category->headItem;

                /* string1 is less than string2 */
                if (strcasecmp(currentItem->itemName, item->itemName) < 0){

                    item->nextItem = currentItem;
                    category->headItem = item;

                } else {

                    /* leave first item as is, search for item that is lower,
                     *  and insert in the chain at that point*/

                    ItemTypePtr lastItem = currentItem;
                    currentItem = currentItem->nextItem;

                    do {

                        if (currentItem == null){
                            lastItem->nextItem = item;
                            break;
                        }

                        else if (strcasecmp(currentItem->itemName,
                                item->itemName) < 0){
                            item->nextItem = currentItem;
                            lastItem->nextItem = item;
                            break;
                        }

                        lastItem = currentItem;
                        currentItem = currentItem->nextItem;

                    } while (currentItem != null);

                    if (currentItem == null)
                        lastItem->nextItem = item;

                }

                break;
        }

    }

    category->numItems++;

}

/* Validates individual item prices. This also ensures the current price is
 * not lower than previous price, if any.
 * */

bool validateItemPrice(const char* price, const char *prevPrice,
        bool showError){

    bool result = false;
    const char delim[] = {PRICE_SEPARATOR_CHAR, 0};
    char **tokens = null;
    const int count = explode(delim, price, &tokens);
    int i = 0;
    int len = 0;

    /* Only continue with validation, if correct token count. */
    if (count == PRICE_TOKEN_COUNT){

        for (i = 0, result = true; i < count && result; i++){
            switch (i){
                case ePriceDollars:
                    len = DOLLARS_LEN;
                    break;
                case ePriceCents:
                    len = CENTS_LEN;
                    break;
            }
            if (strlen(tokens[i]) != len || !isNumeric(tokens[i]))
                result = false;
        }

        /* Ensure current price is not lower than previous price. */
        if (result && prevPrice && strcmp(price, prevPrice) < 0)
            result = false;

    }

    if (!result && showError)
        fprintf(stderr, MESSAGE_ERROR_INVALID_PRICE);

    freeDynamicStringArray(&tokens, count);

    return result;

}

/* Validates all category tokens.
 * */
bool validateCategoryTokens(char **tokens, bool showError){

    bool result = true;
    int i = 0;

    for (i = 0; i < eCategoryMax && result; i++)
        result &= validateCategoryToken(tokens, i, showError);

    return result;

}

/* Validates all menu tokens.
 * */
bool validateMenuTokens(char **tokens, bool showError){

    bool result = true;
    int i = 0;

    for (i = 0; i < eMenuMax && result; i++)
        result &= validateMenuToken(tokens, i, showError);

    return result;

}

/* Validate the drink type.
 * */
bool validateCategoryType(const char *type, bool showError){

    const size_t len = strlen(type);
    const char c = toupper(type[0]);
    const bool result =
            (len == DRINK_LEN && (c == eDrinkHot || c == eDrinkCold));

    if (!result && showError)
        fputs(MESSAGE_ERROR_INVALID_CATEGORY_TYPE, stderr);

    return result;

}

/* Validate a category token, according to it's index.
 * */
bool validateCategoryToken(char **tokens, const int token, bool showError){

    bool result = false;
    const char *s = tokens[token];
    const size_t len = strlen(s);

    switch (token){
        case eCategoryId:

            result = (len == ID_LEN);
            break;

        case eCategoryType:

            result = validateCategoryType(s, false);
            break;

        case eCategoryName:

            result = (len > MIN_NAME_LEN - 1 && len < MAX_NAME_LEN + 1);
            break;

        case eCategoryDescription:

            result = (len > MIN_DESC_LEN - 1 && len < MAX_DESC_LEN + 1);
            break;
    }

    if (!result && showError)
        fprintf(stderr, MESSAGE_ERROR_INVALID_TOKEN, "Category", s, token);

    return result;

}

/* Validate a menu token, according to it's index.
 * */
bool validateMenuToken(char **tokens, const int token, bool showError){

    bool result = false;
    const char *s = tokens[token];
    const size_t len = strlen(s);

    switch (token){
        case eMenuId:

            result = (len == ID_LEN);
            break;

        case eMenuCategoryId:

            result = (len == ID_LEN);
            break;

        case eMenuType:

            result = (len > MIN_NAME_LEN - 1 && len < MAX_NAME_LEN + 1);
            break;

        case eMenuPrice1:

            result = validateItemPrice(s, null, false);
            break;

        case eMenuPrice2:

            result = validateItemPrice(s, tokens[token - 1], false);
            break;

        case eMenuPrice3:

            result = validateItemPrice(s, tokens[token - 1], false);
            break;

        case eMenuDescription:

            result = (len > MIN_DESC_LEN - 1 && len < MAX_DESC_LEN + 1);
            break;
    }

    if (!result && showError)
        fprintf(stderr, MESSAGE_ERROR_INVALID_TOKEN, "Item", s, token);

    return result;

}

/* Converts the string into either a category or an item, then
 * creates either a category or an item from that string.
 * */
bool populateMenu(BCSType *menu, const char *line, bool isSubMenu,
        SortOrder order){

    bool result = false;
    ItemTypePtr item = null;
    CategoryTypePtr category = null;

    if (isSubMenu){

        item = menuItemFromString(menu, line, &category);

        if (item){
            addItemToMenu(menu, category, item, order);
            result = true;
        }

    } else {

        category = menuCategoryFromString(menu, line);

        if (category){
            addCategoryToMenu(menu, category, order);
            result = true;
        }

    }

    return result;

}

/* Load data from a file, into either categories or items.
 * */
bool loadDataFromFile(BCSType* menu, const char* fileName, bool isSubMenu){

    FILE *fp = null;
    bool result = false;
    char *line = null;
    int len = 0;

    fp = fopen(fileName, "r");

    if (fp){

        do {

            result = false;
            freeString(&line);

            /* Keep reading lines (skipping blanks) until EOF. */
            len = readLineFromStream(&line, fp);

            if (len > 0 &&
                    !populateMenu(menu, line, isSubMenu, DEFAULT_SORT_ORDER)){
                freeString(&line);
                fclose(fp);
                return result;
            }

            freeString(&line);

        } while (len > 0);

        result = true;
        fclose(fp);

    }

    return result;

}

/* Lookup and return an existing category by it's id.
 * */
CategoryTypePtr getCategoryFromId(BCSType *menu, const char *id){

    CategoryTypePtr ptr = null;
    CategoryTypePtr head = null;

    for (head = menu->headCategory; head != null; head = head->nextCategory){
        if (strcmp(head->categoryID, id) == 0){
            ptr = head;
            break;
        }
    }

    return ptr;

}

/* Lookup and return an existing item by it's id.
 * */
ItemTypePtr getItemFromId(BCSType *menu, const char *id){

    ItemTypePtr ptr = null;
    ItemTypePtr head = null;
    CategoryTypePtr chead = null;

    for (chead = menu->headCategory;
            chead != null && ptr == null;
            chead = chead->nextCategory){
        for (head = chead->headItem; head != null; head = head->nextItem){
            if (strcmp(head->itemID, id) == 0){
                ptr = head;
                break;
            }
        }
    }

    return ptr;

}

/* Convert a delimited string into a category. This will fail if the input
 * string is not in correct format.
 * */
CategoryTypePtr menuCategoryFromString(BCSType *menu, const char *str){

    const char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    char **tokens = null;
    int count = 0;
    CategoryTypePtr ptr = null;
    CategoryTypePtr cp = null;

    count = explode(delim, str, &tokens);

    /* Only continue if token count is valid. */
    if (count == eCategoryMax){

        if (!validateCategoryTokens(tokens, true)){
            freeDynamicStringArray(&tokens, count);
            return ptr;
        }

        /* Does this category already exist? */
        cp = getCategoryFromId(menu, tokens[eCategoryId]);

        if (cp != null){
            fprintf(stderr, MESSAGE_ERROR_CATEGORY_EXIST, tokens[eCategoryId]);
            freeDynamicStringArray(&tokens, count);
            return ptr;
        }

        ptr = calloc(1, sizeof(CategoryType));

        if (!ptr){

            fputs(MESSAGE_ERROR_NO_MEMORY, stderr);

        } else {

            ptr->numItems = 0;
            ptr->headItem = null;
            ptr->nextCategory = null;
            ptr->drinkType = toupper(tokens[eCategoryType][0]);

            strcpy(ptr->categoryID, tokens[eCategoryId]);
            strcpy(ptr->categoryName, tokens[eCategoryName]);
            strcpy(ptr->categoryDescription, tokens[eCategoryDescription]);

        }

    } else {

        fprintf(stderr, MESSAGE_ERROR_INVALID_TOKEN_ARGS, count, eCategoryMax);

    }

    freeDynamicStringArray(&tokens, count);

    return ptr;

}

/* Convert a delimited string into an item. This will fail if the input
 * string is not in correct format.
 * */
ItemTypePtr menuItemFromString(BCSType *menu, const char *str,
        CategoryTypePtr *category){

    const char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    char **tokens = null;
    int count = 0;
    ItemTypePtr ptr = null;
    ItemTypePtr ip = null;
    char **prices = null;
    int priceCount = 0;
    char priceDelim[] = {PRICE_SEPARATOR_CHAR, 0};
    int i = 0;

    count = explode(delim, str, &tokens);

    /* Only continue if token count is valid. */
    if (count == eMenuMax){

        if (!validateMenuTokens(tokens, true)){
            freeDynamicStringArray(&tokens, count);
            return ptr;
        }

        /* Does this category exist? */
        *category = getCategoryFromId(menu, tokens[eMenuCategoryId]);

        if (*category == null){
            fprintf(
                stderr,
                MESSAGE_ERROR_CATEGORY_NOT_EXIST,
                tokens[eMenuCategoryId]
            );
            freeDynamicStringArray(&tokens, count);
            return ptr;
        }

        /* Does this item already exist? */
        ip = getItemFromId(menu, tokens[eMenuId]);

        if (ip != null){
            fprintf(stderr, MESSAGE_ERROR_MENU_EXIST, tokens[eMenuId]);
            freeDynamicStringArray(&tokens, count);
            return ptr;
        }

        ptr = calloc(1, sizeof(ItemType));

        if (!ptr){

            fputs(MESSAGE_ERROR_NO_MEMORY, stderr);

        } else {

            ptr->nextItem = null;

            strcpy(ptr->itemID, tokens[eMenuId]);
            strcpy(ptr->itemName, tokens[eMenuType]);
            strcpy(ptr->itemDescription, tokens[eMenuDescription]);

            for (i = 0; i < NUM_PRICES; i++){

                priceCount =
                        explode(priceDelim, tokens[eMenuPrice1 + i], &prices);

                stringToInteger(prices[ePriceDollars],
                        (int*)&ptr->prices[i].dollars);

                stringToInteger(prices[ePriceCents],
                        (int*)&ptr->prices[i].cents);

                freeDynamicStringArray(&prices, priceCount);

            }

        }

    } else {

        fprintf(stderr, MESSAGE_ERROR_INVALID_TOKEN_ARGS, count, eMenuMax);

    }

    freeDynamicStringArray(&tokens, count);

    return ptr;

}

/* Converts category information to a report style string.
 * */
char *createReport(CategoryTypePtr category){

    int i = 0;
    int len = 0;
    char *result = null;
    char *title = null;
    char s1[MAX_STRING_MEDIUM] = {0};
    char s2[MAX_STRING_MEDIUM] = {0};
    ItemTypePtr item = category->headItem;

    sprintf(
        s1,
        FORMAT_DASHED_HEADER_REPORT,
        category->categoryID,
        category->categoryName
    );
    sprintf(s2, "%-61s", s1);
    title = createDashesFromString(s2);

    if (!allocateString(&result, strlen(title) + EXTRA_SPACE)){
        freeString(&title);
        return null;
    }

    strcpy(result, title);
    freeString(&title);
    len = strlen(result);

    while (item){

        i = 0;

        /* Iterate through all item tokens. */
        while (i < eMenuMax){

            char temp[MAX_STRING_LARGE] = {0};
            char *description = null;
            int j = 0;

            switch (i){
                case eMenuId:

                    sprintf(temp, "\n%-12s: %s\n",
                            TITLE_REPORT_ITEM_ID, item->itemID);
                    i++; /* bypass cat id*/
                    break;

                case eMenuType:

                    sprintf(temp, "%-12s: %s\n",
                            TITLE_REPORT_ITEM_NAME, item->itemName);
                    break;

                case eMenuPrice1:

                    sprintf(temp, "%-12s:",
                            TITLE_REPORT_ITEM_PRICES);

                    while (j < NUM_PRICES){

                        char temp2[MAX_STRING_SMALL] = {0};

                        sprintf(temp2, " %c%d.%02d",
                                CURRENCY_CHAR, item->prices[j].dollars,
                                item->prices[j].cents);
                        strcat(temp, temp2);

                        j++;

                    }

                    strcat(temp, "\n");
                    i += NUM_PRICES - 1; /* bypass rest of prices */

                    break;

                case eMenuDescription:

                    description = wordWrap(
                        item->itemDescription,
                        WORD_WRAP_LIMIT
                    );
                    sprintf(temp, "%-12s:\n%s\n",
                            TITLE_REPORT_ITEM_DESCRIPTION, description);
                    freeString(&description);

                    break;
            }


            if (!allocateString(&result, len + strlen(temp) + EXTRA_SPACE))
                return null;

            strcat(result, temp);
            len = strlen(result);
            i++;

        }

        item = item->nextItem;

    }

    return result;

}

/* Creates a report from category information, then saves the report
 * to file.
 * */
bool createAndSaveReport(CategoryTypePtr category, const char *fileName){

    bool result = false;
    char *report = createReport(category);
    FILE *fp = fopen(fileName, "w");

    if (fp){
        fputs(report, fp);
        fclose(fp);
        result = true;
    }

    freeString(&report);

    return result;

}

/* Iterate through each item in a category, using a function
 * pointer as a call back.
 * */
void eachItem(CategoryTypePtr category, itemIteratorCallback itemCallback){

    ItemTypePtr ptr = category->headItem;

    while (ptr){
        itemCallback(ptr);
        ptr = ptr->nextItem;
    }

}

/* Output item information to stdout.
 * */
void displayItem(ItemTypePtr ip){

    int i = 0;
    char item[MAX_STRING_MEDIUM] = {0};

    sprintf(item, FORMAT_ITEM, ip->itemID, ip->itemName);

    for (i = 0; i < NUM_PRICES; i++){
        char price[MAX_STRING_SMALL] = {0};
        sprintf(price, FORMAT_PRICE, ip->prices[i].dollars,
                ip->prices[i].cents);
        strcat(item, price);
    }

    printf("%s\n", item);

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
        int min, bool showError, bool allowEmpty){

    char *s = null;
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
        if (len < min + EXTRA_SPACE || s[len - 1] != '\n') {

            /* Are we allowed to not enter anything? Abort if so. */
            if (len < EXTRA_SPACES && allowEmpty)
                passed = true;

            /* Inform the user that they screwed up. */
            else if (showError)
                fputs(errorMessage, stderr);

            memset(result, 0, sizeof(char) * 1);

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

/* Reads the next available line from a stream.
 * This reads the string as chunks and appends those chunks
 * to a buffer. The final buffer is returned.
 * */
int getLineFromStream(char **result, FILE *stream, bool stripNewLine){

    bool moreChunks = false;
    char *chunk = null;
    char *line = null;
    int power = 0;
    int len = 0;
    const int chunkSize = MAX_STRING_SMALL;

    if (stream){

        power = 0;

        do {

            const int lineSize = chunkSize * ++power;

            if (!allocateString(&chunk, chunkSize) ||
                    !allocateString(&line, lineSize)){
                freeStrings(2, &chunk, &line);
                return len;
            }

            fgets(chunk, chunkSize, stream);
            len = strlen(chunk);
            moreChunks = len > 0 && chunk[len - 1] != '\n';

            if (len > 0){
                if (power > 1)
                    strncat(line, chunk, len);
                else
                    strncpy(line, chunk, len);
            }

            freeString(&chunk);

        } while (moreChunks);


        if (len > 0){

            if (stripNewLine && line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = 0;

            *result = copyString(strlen(line) ? line : "");
            /* Reset the length, since we have now modified the string. */
            len = strlen(*result);

        }

        freeString(&line);

    }

    return len;

}

/* Reads the next readable line from a stream - skipping new lines.
 * */
int readLineFromStream(char **result, FILE *fp){

    int len = 0;

    if (fp){

        while (!len && !feof(fp)){
            len = getLineFromStream(result, fp, true);
            if (!len)
                freeString(result);
        }

    }

    return len;

}

/* Reads the first readable line from a file - skipping empty lines.
 * */
int getFirstLineFromFile(char **result, const char *fileName){

    int len = 0;
    FILE *fp = fopen(fileName, "r");

    if (fp){
        len = readLineFromStream(result, fp);
        fclose(fp);
    }

    return len;

}

/* Helper method to get category id from user.
 * */
char *getCategoryIdFromStdIn(BCSType* menu){

    char catId[ID_LEN + EXTRA_SPACES] = {0};
    char message[MAX_STRING_SMALL] = {0};
    bool result = false;

    sprintf(message, INPUT_CATEGORY_ID, ID_LEN);

    while (!result){

        memset(catId, 0, sizeof(char) * ID_LEN + EXTRA_SPACES);
        result = getStringFromStdIn(catId, ID_LEN, message, ID_LEN, true,
                true);

        if (strlen(catId) && !getCategoryFromId(menu, catId)){

            fprintf(stderr, MESSAGE_ERROR_CATEGORY_NOT_EXIST, catId);
            result = false;

        }

    }

    return copyString(catId);

}

/* Helper method to get category name from user when
 * adding a new category.
 * */
char *getCategoryNameFromStdIn(BCSType* menu){

    bool result = false;
    char catName[MAX_NAME_LEN + EXTRA_SPACE] = {0};
    char message[MAX_STRING_LARGE] = {0};

    sprintf(message, INPUT_CATEGORY_NAME, MIN_NAME_LEN, MAX_NAME_LEN);

    while (!result){
        memset(catName, 0, sizeof(char) * (MAX_NAME_LEN + EXTRA_SPACE));
        result = getStringFromStdIn(catName, MAX_NAME_LEN, message,
                MIN_NAME_LEN, true, true);
    }

    return copyString(catName);

}

/* Helper method to get category type from user when
 * adding a new category.
 * */
char *getCategoryTypeFromStdIn(BCSType* menu){

    bool result = false;
    char catType[EXTRA_SPACES] = {0};

    while (!result){

        catType[0] = 0;
        result = getStringFromStdIn(catType, DRINK_LEN,
                INPUT_CATEGORY_TYPE, DRINK_LEN, true, true);

        if (strlen(catType))
            result = validateCategoryType(catType, true);

    }

    return copyString(catType);

}

/* Helper method to get category description from user when
 * adding a new category.
 * */
char *getCategoryDescFromStdIn(BCSType* menu){

    bool result = false;
    char catDesc[MAX_DESC_LEN + EXTRA_SPACE] = {0};
    char message[MAX_STRING_LARGE] = {0};

    sprintf(message, INPUT_DESCRIPTION, MIN_DESC_LEN, MAX_DESC_LEN);

    while (!result){
        memset(catDesc, 0, sizeof(char) * (MAX_DESC_LEN + EXTRA_SPACE));
        result = getStringFromStdIn(catDesc, MAX_DESC_LEN, message,
                MIN_DESC_LEN, true, true);
    }

    return copyString(catDesc);

}

/* Helper method to get item id from user when deleting an item.
 * */
char *getItemIdFromStdIn(BCSType *menu){

    char itemId[ID_LEN + EXTRA_SPACES] = {0};
    char message[MAX_STRING_SMALL] = {0};
    bool result = false;

    sprintf(message, INPUT_ITEM_ID, ID_LEN);

    while (!result){

        memset(itemId, 0, sizeof(char) * ID_LEN + EXTRA_SPACES);
        result = getStringFromStdIn(itemId, ID_LEN, message,
                MIN_STRING_NONE, true, true);

        if (strlen(itemId) && !getItemFromId(menu, itemId)){
            fprintf(stderr, MESSAGE_ERROR_MENU_NOT_EXIST, itemId);
            result = false;
        }

    }

    return copyString(itemId);

}

/* Helper method to get item name from user when adding a new item.
 * */
char *getItemNameFromStdIn(BCSType *menu){

    bool result = false;
    char itemName[MAX_NAME_LEN + EXTRA_SPACE] = {0};
    char message[MAX_STRING_LARGE] = {0};

    sprintf(message, INPUT_ITEM_NAME, MIN_NAME_LEN, MAX_NAME_LEN);

    do {

        memset(itemName, 0, sizeof(char) * (MAX_NAME_LEN + EXTRA_SPACE));
        result = getStringFromStdIn(itemName, MAX_NAME_LEN, message,
                MIN_NAME_LEN, true, true);

    } while (!result);

    return copyString(itemName);

}

/* Helper method to get item prices from user when adding a new item.
 * This will also validate the price against previous prices and
 * ensure it is not lower.
 * */
char *getItemPriceFromStdIn(BCSType *menu, const int priceIndex,
        const char *prevPrice){

    bool result = false;
    char price[PRICE_LEN + EXTRA_SPACE] = {0};
    char message[MAX_STRING_LARGE] = {0};
    char temp[MAX_STRING_MEDIUM] = {0};

    switch (eMenuPrice1 + priceIndex){
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

    sprintf(message, temp,
            CURRENCY_CHAR, MIN_ITEM_PRICE, CURRENCY_CHAR, MAX_ITEM_PRICE);

    do {

        memset(price, 0, sizeof(char) * (PRICE_LEN + EXTRA_SPACE));
        result = getStringFromStdIn(price, PRICE_LEN, message,
                PRICE_LEN, true, true);

        if (strlen(price) && !validateItemPrice(price, prevPrice, true))
            result = false;

    } while (!result);

    return copyString(price);

}

/* Helper method to get item description from user when adding a new item.
 * */
char *getItemDescFromStdIn(BCSType *menu){

    bool result = false;
    char itemDesc[MAX_DESC_LEN + EXTRA_SPACE] = {0};
    char message[MAX_STRING_LARGE] = {0};

    sprintf(message, INPUT_DESCRIPTION, MIN_DESC_LEN, MAX_DESC_LEN);

    do {

        memset(itemDesc, 0, sizeof(char) * (MAX_DESC_LEN + EXTRA_SPACE));
        result = getStringFromStdIn(itemDesc, MAX_DESC_LEN, message,
                MIN_DESC_LEN, true, true);

    } while (!result);

    return copyString(itemDesc);

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

/* Used to free a string array that has been created with the explode() method.
 * */
void freeDynamicStringArray(char ***arr, const int length){

    int i = 0;
    char **a = *arr;

    for (; i < length; i++)
        free(a[i]);

    free(a);

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


/* Allocate memory and then copy supplied string to new buffer.
 * */
char *copyString(const char *str){

    int i = 0;
    size_t len = str ? strlen(str) : 0;
    char *s = malloc(sizeof(char) * (len + EXTRA_SPACE));

    if (!s){
        fputs(MESSAGE_ERROR_NO_MEMORY, stderr);
        return null;
    }

    for (; i < len; i++)
        s[i] = str[i];

    s[len] = 0;

    return s;

}

/* Split a delimited string into a string array.
 * */
int explode(const char *delimeter, const char *str, char ***array){

    int count = 0;
    char **arr = null;
    char *s = copyString(str);
    char *token = strtok(s, delimeter);

    while (token){

        arr = realloc(arr, sizeof(char*) * ++count);

        if (arr == null){
            fputs(MESSAGE_ERROR_NO_MEMORY, stderr);
            free(arr);
            free(s);
            return 0;
        }

        arr[count - 1] = copyString(token);

        /* Continue the loop (if possible). */
        token = strtok(null, delimeter);
    }

    *array = arr;
    free(s);

    return count;

}

/* Convert an array of strings to a delimited string.
 * */
char *implode(const char *delimeter, char **array, const int length){

    int len = 0;
    int i = 0;
    char *result = null;

    for (i = 0; i < length; i++)
        len += strlen(array[i]) + (i < length - 1 ? strlen(delimeter) : 0);

    len += EXTRA_SPACE;

    if (allocateString(&result, len)){

        for (i = 0; i < length; i++){

            if (!i)
                strcpy(result, array[i]);
            else
                strcat(result, array[i]);

            if (i < length - 1)
                strcat(result, delimeter);

        }

    }

    return result;

}

/* Converts a numeric string to an int.
 * */
bool stringToInteger(const char *str, int *result){

    bool succeeded = false;
    char *endPtr = null;
    int i = 0;

    i = (int)strtol(str, &endPtr, BASE10);

    succeeded = (strcmp(endPtr, "") == 0);

    if (succeeded)
        *result = i;

    return succeeded;

}

/* Tests if a string is numeric.
 * */
bool isNumeric(const char *str){

    bool result = false;
    char *ptr = copyString(str);

    if (ptr){

        result = true;

        while (*ptr != 0){
            if (!isdigit(*(ptr++))){
                result = false;
                break;
            }
        }

        /* rewind pointer back to the beginning of string,
         * otherwise free() will fail */
        ptr -= strlen(str);
        free(ptr);

    }

    return result;

}

/* Generates a random number. Used for category and item id generation.
 * */
int generateRandomNumber(const int min, const int max){

    return min + (rand() % max);

}

/* This will replace spaces with a new line character by looking
 * for the last word that will fit inside the length (max).
 * */
char *wordWrap(const char *str, const int limit){

    char *result = null;
    char *s = copyString(str);
    char **arr = null;
    int count = 0;
    int len = 0;
    int i = 0;
    const char delim[] = {SPACE_CHAR, 0};

    if (!s)
        return null;

    if (strlen(s) <= limit - 1)
        return s;

    count = explode(delim, s, &arr);
    freeString(&s);

    if (!arr)
        return null;

    if (!allocateString(&result, strlen(str) + EXTRA_SPACE)){
        freeDynamicStringArray(&arr, count);
        return null;
    }

    for (i = 0; i < count; i++){

        int potentialLength = strlen(arr[i]) + (i == count - 1 ? 0 : 1);

        if (len + potentialLength >= limit){
            strcat(result, "\n");
            len = 0;
        } else if (i > 0) {
            strcat(result, delim);
        }

        len += potentialLength;
        if (i == 0)
            strcpy(result, arr[i]);
        else
            strcat(result, arr[i]);

    }

    freeDynamicStringArray(&arr, count);

    return result;

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

/* This method ensures that the category file
 * comes before the items file. It does this by checking
 * the number of tokens after the first readable line
 * has been split.
 * */
bool checkArgumentOrder(char* argv[]){

    char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    char *line = null;
    char **arr = null;
    int len = 0;

    len = getFirstLineFromFile(&line, argv[EXPECTED_CATEGORY_ARG_INDEX]);

    if (!len){
        freeString(&line);
        fprintf(stderr, MESSAGE_ERROR_FILE_EMPTY,
                argv[EXPECTED_CATEGORY_ARG_INDEX]);
        return false;
    }

    len = explode(delim, line, &arr);
    freeString(&line);
    freeDynamicStringArray(&arr, len);

    if (len != eCategoryMax){
        fprintf(stderr, MESSAGE_ERROR_ARG_CATEGORY_ORDER,
                EXPECTED_CATEGORY_ARG_INDEX);
        return false;
    }

    len = getFirstLineFromFile(&line, argv[EXPECTED_ITEM_ARG_INDEX]);

    if (!len){
        freeString(&line);
    } else {

        len = explode(delim, line, &arr);
        freeString(&line);
        freeDynamicStringArray(&arr, len);

        if (len != eMenuMax){
            fprintf(stderr, MESSAGE_ERROR_ARG_ITEM_ORDER,
                    EXPECTED_ITEM_ARG_INDEX);
            return false;
        }

    }

    return true;

}

/* This makes the console usable in Eclipse for debugging.
 * */
void fixConsole(FILE *stream){

    /* Stupid Eclipse won't show the console until after it has stopped.
    * See http://stackoverflow.com/questions/13035075/printf-not-printing-on-console */
    setvbuf(stream, NULL, _IONBF, 0);

}


/* Helper method to create a dashed string.
 * */
char *createDashes(const int length){

    char *dashes = null;

    if (allocateString(&dashes, length + EXTRA_SPACE))
        memset(dashes, DASH_CHAR, length);

    return dashes;

}

/* This function is used to underline a string in the console. */
char *createDashesFromString(const char *str){

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

/* This function creates the menu statically, and keeps returning same menu */
menuoption_t *getMenuOptions(){

    static menuoption_t options[] = {
        {
            eMethodDisplayHot,
            MENU_TITLE_SUMMARY_HOT
        },
        {
            eMethodDisplayCold,
            MENU_TITLE_SUMMARY_COLD
        },
        {
            eMethodReport,
            MENU_TITLE_REPORT
        },
        {
            eMethodAddCategory,
            MENU_TITLE_ADD_CATEGORY
        },
        {
            eMethodDeleteCategory,
            MENU_TITLE_DELETE_CATEGORY
        },
        {
            eMethodAddItem,
            MENU_TITLE_ADD_ITEM
        },
        {
            eMethodDeleteItem,
            MENU_TITLE_DELETE_ITEM
        },
        {
            eMethodSaveData,
            MENU_TITLE_EXIT
        },
        {
            eMethodExitApp,
            MENU_TITLE_ABORT
        },
        {MAX_MENU_OPTION + 1, null}
    };


    return options;

}
