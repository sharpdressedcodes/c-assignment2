/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period  2 2014 Assignment #2 - Brazilian Coffee Shop system
* Full Name        : Greg Kappatos
* Student Number   : s3460969
* Start up code provided by the CTEACH team
****************************************************************************/

#ifndef BCS_UTILITY_H
#define BCS_UTILITY_H

/* Function prototypes. */
void readRestOfLine();
void systemInit(BCSType* menu);
int loadData(BCSType* menu, char* menuFile, char* submenuFile);
void systemFree(BCSType* menu);

/* BCSType functions. */

char *generateCategoryId(BCSType *menu);
char *generateItemId(BCSType *menu);
void freeCategories(BCSType* menu);
void addCategoryToMenu(BCSType *menu, CategoryTypePtr category,
        SortOrder order);
void addItemToMenu(BCSType *menu, CategoryTypePtr category,
        ItemTypePtr item, SortOrder order);
CategoryTypePtr getCategoryFromId(BCSType *menu, const char *id);
ItemTypePtr getItemFromId(BCSType *menu, const char *id);
CategoryTypePtr menuCategoryFromString(BCSType *menu, const char *str);
ItemTypePtr menuItemFromString(BCSType *menu, const char *str,
        CategoryTypePtr *category);
bool populateMenu(BCSType *menu, const char *line, bool isSubMenu,
        SortOrder order);
bool loadDataFromFile(BCSType* menu, const char* fileName, bool isSubMenu);

#ifdef BONUS_2
void freeCategoryNode(ListNodeTypePtr node);
ListNodeTypePtr createNode(void *data, ListNodeTypePtr next);
ListNodeTypePtr findCategoryNode(BCSType *menu, CategoryTypePtr category);
ListNodeTypePtr findItemNode(BCSType *menu, CategoryTypePtr category,
        ItemTypePtr item);
#endif

bool validateItemPrice(const char* price, const char *prevPrice,
        bool showError);
bool validateCategoryTokens(char **tokens, bool showError);
bool validateMenuTokens(char **tokens, bool showError);
bool validateCategoryType(const char *type, bool showError);
bool validateCategoryToken(char **tokens, const int token, bool showError);
bool validateMenuToken(char **tokens, const int token, bool showError);

char *categoryToString(CategoryTypePtr category);
char *itemToString(ItemTypePtr item, CategoryTypePtr parent);
void freeCategory(CategoryTypePtr category);
char *createDashedHeader(CategoryTypePtr category);
char *createReport(CategoryTypePtr category);
bool createAndSaveReport(CategoryTypePtr category, const char *fileName);
void eachItem(CategoryTypePtr category, void (*fp)(ItemTypePtr item));
void displayItem(ItemTypePtr ip);

char *getCategoryIdFromStdIn(BCSType* menu);
char *getCategoryNameFromStdIn(BCSType* menu);
char *getCategoryTypeFromStdIn(BCSType* menu);
char *getCategoryDescFromStdIn(BCSType* menu);
char *getItemIdFromStdIn(BCSType *menu);
char *getItemNameFromStdIn(BCSType *menu);
char *getItemPriceFromStdIn(BCSType *menu, const int priceIndex,
        const char *prevPrice);
char *getItemDescFromStdIn(BCSType *menu);


/* stdin functions. */
bool getIntegerFromStdIn(int *result, const int length, const char *message,
        const int min, const int max, bool showError, bool allowEmpty);
bool getStringFromStdIn(char *result, const int length, const char *message,
        const int min, bool showError, bool allowEmpty);
int getLineFromStream(char **result, FILE *stream, bool stripNewLine);
int readLineFromStream(char **result, FILE *fp);
int getFirstLineFromFile(char **result, const char *fileName);


/* Dynamic memory functions. */
bool allocateString(char **str, const int size);
void freeString(char **str);
void freeStringArray(char **arr, const int length);
void freeDynamicStringArray(char ***arr, const int length);
void freeStrings(const int length, ...);

/* String functions. */
char *copyString(const char *str);
bool isNumeric(const char *str);
bool stringToInteger(const char *str, int *result);
int explode(const char *delimeter, const char *str, char ***array);
char *implode(const char *delimeter, char **array, const int length);
int generateRandomNumber(const int min, const int max);
char *wordWrap(const char *str, const int limit);

/* FILE functions. */
bool fileExists(const char *fileName);
bool checkArgumentOrder(char* argv[]);
void fixConsole(FILE *stream);

/* General helper functions. */
char *createDashes(const int length);
char *createDashesFromString(const char *str);
menuoption_t *getMenuOptionByIndex(const int index);
menuoption_t *getMenuOptionByTitle(const char *title);
menuoption_t *getMenuOptions();
#endif
