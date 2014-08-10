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

    menu->headCategory = null;
    menu->numCategories = 0;

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

    CategoryTypePtr cp = menu->headCategory;

    while (cp){

        CategoryTypePtr cp2 = &(*cp);
        ItemTypePtr ip = cp->headItem;

        while (ip){

            ItemTypePtr ip2 = &(*ip);

            ip = ip->nextItem;
            free(ip2);

        }

        cp = cp->nextCategory;
        free(cp2);

    }

    systemInit(menu);

}



void addCategoryToMenu(BCSType *menu, CategoryTypePtr category, SortOrder order){

    static CategoryTypePtr lastCategory = null;
    CategoryTypePtr currentCategory = null;

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
                if (strcmp(currentCategory->categoryName, category->categoryName) > 0){

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

                        else if (strcmp(currentCategory->categoryName, category->categoryName) > 0){
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
                if (strcmp(currentCategory->categoryName, category->categoryName) < 0){

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

                        else if (strcmp(currentCategory->categoryName, category->categoryName) < 0){
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

void addItemToMenu(BCSType *menu, CategoryTypePtr category, ItemTypePtr item, SortOrder order){

    ItemTypePtr currentItem = null;
    ItemTypePtr lastItem = null;

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
                if (strcmp(currentItem->itemName, item->itemName) > 0){

                    item->nextItem = currentItem;
                    category->headItem = item;

                } else {

                    /* leave first item as is, search for item that is higher,
                     *  and insert in the chain at that point*/

                    lastItem = currentItem;
                    currentItem = currentItem->nextItem;

                    do {

                        if (currentItem == null){
                            lastItem->nextItem = item;
                            break;
                        }

                        else if (strcmp(currentItem->itemName, item->itemName) > 0){
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
                if (strcmp(currentItem->itemName, item->itemName) < 0){

                    item->nextItem = currentItem;
                    category->headItem = item;

                } else {

                    /* leave first item as is, search for item that is lower,
                     *  and insert in the chain at that point*/

                    lastItem = currentItem;
                    currentItem = currentItem->nextItem;

                    do {

                        if (currentItem == null){
                            lastItem->nextItem = item;
                            break;
                        }

                        else if (strcmp(currentItem->itemName, item->itemName) < 0){
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

bool validateItemPrice(const char* price){

    bool result = false;
    const char delim[] = {PRICE_SEPARATOR_CHAR, 0};
    char **tokens = null;
    const int count = explode(delim, price, &tokens);
    int i = 0;

    if (count == PRICE_TOKEN_COUNT){

        for (i = 0, result = true; i < count && result; i++)
            if (!isNumeric(tokens[i]))
                result = false;

    }

    freeDynamicStringArray(&tokens, count);

    return result;

}

bool validateCategoryTokens(char **tokens, bool showError){

    bool result = true;
    int i = 0;

    for (i = 0; i < eCategoryMax && result; i++)
        result &= validateCategoryToken(tokens, i, showError);

    return result;

}

bool validateMenuTokens(char **tokens, bool showError){

    bool result = true;
    int i = 0;

    for (i = 0; i < eMenuMax && result; i++)
        result &= validateMenuToken(tokens, i, showError);

    return result;

}

bool validateCategoryToken(char **tokens, const int token, bool showError){

    bool result = false;
    const char *s = tokens[token];
    const size_t len = strlen(s);

    switch (token){
        case eCategoryId:

            result = (len == ID_LEN);
            break;

        case eCategoryType:

            result = (len == DRINK_LEN && (toupper(s[0]) == eDrinkHot || toupper(s[0]) == eDrinkCold));
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

            result = validateItemPrice(s);
            break;

        case eMenuPrice2:

            result = validateItemPrice(s);
            break;

        case eMenuPrice3:

            result = validateItemPrice(s);
            break;

        case eMenuDescription:

            result = (len > MIN_DESC_LEN - 1 && len < MAX_DESC_LEN + 1);
            break;
    }

    return result;

}

bool populateMenu(BCSType *menu, const char *line, bool isSubMenu, SortOrder order){

    bool result = false;
    ItemTypePtr newItem = null;
    CategoryTypePtr newCategory = null;
    CategoryTypePtr currentCategory = null;

    if (isSubMenu){

        newItem = menuItemFromString(menu, line, &currentCategory);

        if (newItem){
            addItemToMenu(menu, currentCategory, newItem, eSortOrderAscending);
            result = true;
        }

    } else {

        newCategory = menuCategoryFromString(menu, line);

        if (newCategory){
            addCategoryToMenu(menu, newCategory, eSortOrderAscending);
            result = true;
        }

    }

    return result;

}

bool loadDataFromFile(BCSType* menu, const char* fileName, bool isSubMenu){

    FILE *fp = null;
    bool result = false;
    bool moreChunks = false;
    char *chunk = null;
    char *line = null;
    int power = 0;
    int len = 0;
    const int chunkSize = MAX_STRING_SMALL;

    fp = fopen(fileName, "r");

    if (fp){

        do {

            power = 0;

            do {

                const int lineSize = chunkSize * ++power;

                if (!allocateString(&chunk, chunkSize) || !allocateString(&line, lineSize)){
                    freeStrings(2, &chunk, &line);
                    return result;
                }

                fgets(chunk, chunkSize, fp);
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

                int len2 = strlen(line) - 1;

                if (line[len2] == '\n')
                    line[len2] = 0;

                if (!populateMenu(menu, line, isSubMenu, eSortOrderAscending)){
                    freeStrings(2, &chunk, &line);
                    return result;
                }

            }

            freeString(&line);

        } while (len > 0);

        result = true;
        fclose(fp);

    }

    return result;

}

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

ItemTypePtr getItemFromId(BCSType *menu, const char *id){

    ItemTypePtr ptr = null;
    ItemTypePtr head = null;
    CategoryTypePtr chead = null;

    for (chead = menu->headCategory; chead != null && ptr == null; chead = chead->nextCategory){
        for (head = chead->headItem; head != null; head = head->nextItem){
            if (strcmp(head->itemID, id) == 0){
                ptr = head;
                break;
            }
        }
    }

    return ptr;

}

CategoryTypePtr menuCategoryFromString(BCSType *menu, const char *str){

    const char delim[] = {INPUT_SEPARATOR_CHAR, 0};
    char **tokens = null;
    int count = 0;
    CategoryTypePtr ptr = null;
    CategoryTypePtr cp = null;

    count = explode(delim, str, &tokens);

    if (count == eCategoryMax){

        if (!validateCategoryTokens(tokens, true)){
            freeDynamicStringArray(&tokens, count);
            return ptr;
        }

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

ItemTypePtr menuItemFromString(BCSType *menu, const char *str, CategoryTypePtr *category){

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

    if (count == eMenuMax){

        if (!validateMenuTokens(tokens, true)){
            freeDynamicStringArray(&tokens, count);
            return ptr;
        }

        *category = getCategoryFromId(menu, tokens[eMenuCategoryId]);

        if (*category == null){
            fprintf(stderr, MESSAGE_ERROR_CATEGORY_NOT_EXIST, tokens[eMenuCategoryId]);
            freeDynamicStringArray(&tokens, count);
            return ptr;
        }

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

                priceCount = explode(priceDelim, tokens[eMenuPrice1 + i], &prices);

                stringToInteger(prices[ePriceDollars], (int*)&ptr->prices[i].dollars);
                stringToInteger(prices[ePriceCents], (int*)&ptr->prices[i].cents);

                freeDynamicStringArray(&prices, priceCount);

            }

        }

    } else {

        fprintf(stderr, MESSAGE_ERROR_INVALID_TOKEN_ARGS, count, eMenuMax);

    }

    freeDynamicStringArray(&tokens, count);

    return ptr;

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



char *copyString(const char *str){

    int i = 0;
    size_t len = strlen(str);
    char *s = malloc(sizeof(char) * (len + 1));

    if (!s){
        fputs(MESSAGE_ERROR_NO_MEMORY, stderr);
        return null;
    }

    for (; i < len; i++)
        s[i] = str[i];

    s[len] = 0;

    return s;

}

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
